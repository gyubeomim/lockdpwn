/*
   arduino ==> 셀프밸런싱로봇을 만들어 실험해본 코드
 */
//------------------------------------------------------------
// PID 제어, 모터 제어, MPU6050센서 값을 받기 위한 선언문
#include <PID_v1.h>
#include <LMotorController.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
	#include "Wire.h"
#endif


//------------------------------------------------------------
#define OUTPUT_TEAPOT 1					// Processing을 통해 MPU6050 센서를 Visualize 하고 싶은 경우 1, 아니면 0으로 선언합니다
#define MIN_ABS_SPEED 30  				// 모터의 최저속도를 설정합니다
#define OUTPUT_READABLE_YAWPITCHROLL    // Yaw, Pitch, Roll 값을 얻기 위해 선언합니다
#define INTERRUPT_PIN 2  				// MPU6050 센서의 INT 핀이 꽂혀있는 번호를 설정합니다. 보통 2번
#define LED_PIN 13 						// Arudino Uno의 13번핀 LED를 동작 중에 반짝거리게 하려고 선언합니다 



//------------------------------------------------------------
//MPU 객체를 선언합니다
MPU6050 mpu;
// MPU control/status vars
bool blinkState = false;	// LED를 반짝거리게 하기 위한 변수
bool dmpReady = false;		// set true if DMP init was successful
uint8_t mpuIntStatus;		// holds actual interrupt status byte from MPU
uint8_t devStatus;			// return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;		// expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;			// count of all bytes currently in FIFO
uint8_t fifoBuffer[64];		// FIFO storage buffer


//------------------------------------------------------------
// MPU6050 센서를 통해 쿼터니언과 오일러각, Yaw, Pitch, Roll 값을 얻기 위해 선언합니다
// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector


//------------------------------------------------------------
// Processing으로 MPU6050 센서를 Visualize 하기 위한 변수
// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };


//------------------------------------------------------------
// PID 제어용 변수 선언
double kp , ki, kd;

kp = 60;
ki = 200;
kd = 1.5;

// 기울일 각도 선택 // 내가 만든 밸런싱로봇에는 184.0도가 가장 최적의 평형각도였습니다
double originalSetpoint = 184.0;
double setpoint = originalSetpoint;
double movingAngleOffset = 0.3;

// PID 제어용 input, output 변수를 선언합니다
double input, output;

// PID값을 설정해준다
PID pid(&input, &output, &setpoint, kp, ki, kd, DIRECT);


// 모터 제어용 변수 선언
// EnA, EnB는 속도제어용(pwm), IN1,2,3,4는 방향제어용 핀입니다
int ENA = 10;
int IN1 = 12;
int IN2 = 6;
int IN3 = 9;
int IN4 = 8;
int ENB = 11;

// motorController 객체 생성, 맨 끝 파라미터 1,1은 각각 좌측, 우측모터의 최대속도(%) 입니다.
LMotorController motorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);



// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high

void dmpDataReady() {
	mpuInterrupt = true;
}

void setup(){
	// join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
	Wire.begin();
	Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
	Fastwire::setup(400, true);
#endif

	Serial.begin(115200);
	while (!Serial); // wait for Leonardo enumeration, others continue immediately

	// initialize device
	Serial.println(F("Initializing I2C devices..."));
	mpu.initialize();
	pinMode(INTERRUPT_PIN, INPUT);
	// verify connection
	Serial.println(F("Testing device connections..."));
	Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

	// 키입력을 기다리는 코드. 주석처리했습니다
	// wait for ready
	//Serial.println(F("\nSend any character to begin DMP programming and demo: "));
	//while (Serial.available() && Serial.read()); // empty buffer
	//while (!Serial.available());                 // wait for data
	//while (Serial.available() && Serial.read()); // empty buffer again


	// load and configure the DMP
	Serial.println(F("Initializing DMP..."));
	devStatus = mpu.dmpInitialize();

	// supply your own gyro offsets here, scaled for min sensitivity
	mpu.setXGyroOffset(220);
	mpu.setYGyroOffset(76);
	mpu.setZGyroOffset(-85);
	mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

	// devStatus 값이 0 이면 정상작동, 0이 아니면 오작동입니다
	// make sure it worked (returns 0 if so)
	if (devStatus == 0){
		// turn on the DMP, now that it's ready
		Serial.println(F("Enabling DMP..."));
		mpu.setDMPEnabled(true);

		// enable Arduino interrupt detection
		Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
		attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
		mpuIntStatus = mpu.getIntStatus();

		// set our DMP Ready flag so the main loop() function knows it's okay to use it
		Serial.println(F("DMP ready! Waiting for first interrupt..."));
		dmpReady = true;

		// get expected DMP packet size for later comparison
		packetSize = mpu.dmpGetFIFOPacketSize();


		// MPU6050 센서가 정삭작동하면 PID 제어용 코드를 초기화합니다
		pid.SetMode(AUTOMATIC);
		pid.SetSampleTime(10);
		pid.SetOutputLimits(-255, 255);  
	}
	else{   // MPU6050 센서가 오작동한 경우
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		Serial.print(F("DMP Initialization failed (code "));
		Serial.print(devStatus);
		Serial.println(F(")"));
	}

	// 로봇이 작동 중 13번 LED를 깜빡거리기 위해 OUTPUT으로 초기화합니다
	pinMode(LED_PIN, OUTPUT);
}


void loop(){
	// if programming failed, don't try to do anything
	if (!dmpReady) return;

	// wait for MPU interrupt or extra packet(s) available
	while (!mpuInterrupt && fifoCount < packetSize){
		//no mpu data - performing PID calculations and output to motors

		pid.Compute(); // 루프를 돌면서 pid 값을 업데이트합니다
		motorController.move(output, MIN_ABS_SPEED); // pid 연산으로 나온 output 값을 motorController로 전송합니다. (모터제어)
	}

	// reset interrupt flag and get INT_STATUS byte
	mpuInterrupt = false;
	mpuIntStatus = mpu.getIntStatus();

	// get current FIFO count
	fifoCount = mpu.getFIFOCount();

	// MPU6050 센서가 정상작동하는 경우에만 PID제어를 해야하므로 아래와 같이 if-else문을 작성합니다
	// check for overflow (this should never happen unless our code is too inefficient)
	if ((mpuIntStatus & 0x10) || fifoCount == 1024){
		// reset so we can continue cleanly
		mpu.resetFIFO();
		Serial.println(F("FIFO overflow!"));
	}
	// MPU6050 센서가 정상작동하는 경우
	else if (mpuIntStatus & 0x02){
		// wait for correct available data length, should be a VERY short wait
		while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

		// read a packet from FIFO
		mpu.getFIFOBytes(fifoBuffer, packetSize);

		// track FIFO count here in case there is > 1 packet available
		// (this lets us immediately read more without waiting for an interrupt)
		fifoCount -= packetSize;

		// display Euler angles in degrees
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

#ifdef OUTPUT_READABLE_YAWPITCHROLL  // 센서를 통해 구한 Yaw, Pitch, Roll 값을 Serial Monitor에 표시합니다
		Serial.print("ypr\t");
		Serial.print(ypr[0] * 180/M_PI);
		Serial.print("\t");
		Serial.print(ypr[1] * 180/M_PI);
		Serial.print("\t");
		Serial.println(ypr[2] * 180/M_PI);
#endif
		// PID 제어를 하기 위해 input 변수에 Pitch 값을 넣습니다
		input = ypr[1] * 180/M_PI + 180;


#ifdef OUTPUT_TEAPOT  // Processing으로 MPU6050센서의 움직임을 Visualize 하기 위한 코드
		// display quaternion values in InvenSense Teapot demo format:
		teapotPacket[2] = fifoBuffer[0];
		teapotPacket[3] = fifoBuffer[1];
		teapotPacket[4] = fifoBuffer[4];
		teapotPacket[5] = fifoBuffer[5];
		teapotPacket[6] = fifoBuffer[8];
		teapotPacket[7] = fifoBuffer[9];
		teapotPacket[8] = fifoBuffer[12];
		teapotPacket[9] = fifoBuffer[13];
		Serial.write(teapotPacket, 14);
		teapotPacket[11]++; // packetCount, loops at 0xFF on purpose
#endif
	}
}

