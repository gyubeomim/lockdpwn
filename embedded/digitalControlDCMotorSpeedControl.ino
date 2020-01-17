#include <PID_v1.h>             //sketch > include libraries > manage libraries > download "PID" library 
#include <TimerOne.h>           //sketch > include libraries > manage libraries > download "TIMERONE" library

//----------------------------default settings---------------------------//
#define encPinA  2              // Pin number of EncorderA on arduino board
#define encPinB  12             // Encorer B  // this pinB doesn't matter if you put it to different pin #

float Kp = 1.5;              
float Ki = 20;              
float Kd = 5;              

double Setpoint, Input, Output, motorOutput;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);   

const int motor1a = 9;
const int motor1b = 10; // Motor A,B pin don't matter if you put it to different pin #

const int interval = 100;  		 // Sampling Time : 100ms (0.1s)

unsigned int long pre_millis=0;  
unsigned int long curr_millis=0;  // Those two lines are to calculate Sampling Time

unsigned enBState = 0;  // Encoder B status
volatile long rev = 0;  // revolution

float angVel=0;		// Angular Velocity 

int motorSpeed;
int inputVel;

//---------------------------encoder function--------------------------//
void encoder()
{ 
	enBState = digitalRead(encPinB);
	if (enBState == HIGH) 
		rev++;     
	else 
		rev--;               
}

void setup()
{
	Serial.begin(9600);

	pinMode(encPinA,INPUT_PULLUP);  // sets encPinA pin as input pin
	pinMode(encPinB,INPUT_PULLUP);  // sets encPinB pin as input pin
	attachInterrupt(0, encoder, RISING); // executes function "encoder" whenever value of encPinB rises

	pinMode(motor1a,OUTPUT);        // sets motor1a pin as output pin
	pinMode(motor1b,OUTPUT);        // sets motor1b pin as output pin

	Input = angVel;
	myPID.SetMode(AUTOMATIC);             
	myPID.SetOutputLimits(-140,75);  // 이코드도 중요한 코드인듯 그런데 최적값의 기준이 없다..
	myPID.SetSampleTime(interval);   // 추가 코드 : 샘플링시간 수정
	Serial.println("Start");
}


void loop()
{
	curr_millis = millis();

	if(curr_millis - pre_millis == interval)
	{
		Setpoint = 14;              // setting steady state value
		cnt++;
		angVel = (float)((rev*2*PI*(1000/interval))/(180)); // 코드 수정 : 1000/interval, 180펄스당 1바퀴이므로 180으로 나눠준다
		RPS = angVel/2/PI;

		Serial.print("[");
		Serial.print(Setpoint);
		Serial.print("]");
		Serial.print(", ");
		Serial.print(angVel);
		Serial.print(" [rad/s], "); // 코드 추가
		Serial.print(RPS);
		Serial.print(" [RPS], ");

		Input = angVel;
		myPID.Compute();              

		Serial.print("Output : ");
		Serial.print(Output);
		Serial.print(", ");

		motorOutput = 180 + Output;    // 최종적으로 모터에 analog 값으로 0 ~255값이 들어가는 코드. 이 코드는 최적값의 기준이 뭘까?

		Serial.print("MotorOutput : ");
		Serial.print(motorOutput);
		Serial.println(" ");
		
		if(motorOutput > 255)
		{
			motorOutput = 255;
		}

		if(motorOutput <= 255 && motorOutput >= 0)
		{
			analogWrite(motor1a,motorOutput);   //export motorOutput value to motor1a pin
			analogWrite(motor1b,0);             //export 0 to motor1b pin
		}
		rev = 0;
		pre_millis = curr_millis;
	}  
}
