/*
 	arduino ==> 디지털제어 텀프로젝트
				TimerOne.h 라이브러리 대신 MsTimer2를 사용한 코드
				TimerOne.h를 삭제해도 아무런 에러가 나지 않는다
 */
#include <PID_v1.h>             //sketch > include libraries > manage libraries > download "PID" library 
#include <MsTimer2.h>

//----------------------------default settings---------------------------//
#define encPinA  2              // Pin number of EncorderA on arduino board
#define encPinB  3             // Pin number of EncorderB on arduino board

float Kp = 1.5;              
float Ki = 20;              
float Kd = 5;              

double Setpoint, Input, Output, motorOutput;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);   

const int motor1a = 9;   // Pin number of motor1a on arduino board
const int motor1b = 10;  // Pin number of motor1b on arduino board 

const int interval = 100;   
unsigned int long pre_millis=0;
unsigned int long curr_millis=0;
int cnt=0;

unsigned enBState = 0;  
volatile long rev = 0;

float angVel=0;
float RPS = 0;
float voltage = 0;

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

	MsTimer2::set(interval,PIDControl);
	MsTimer2::start();

	Input = angVel;
	myPID.SetMode(AUTOMATIC);             
	myPID.SetOutputLimits(-140,75);  // 이코드도 중요한 코드인듯 그런데 최적값의 기준이 없다..
	myPID.SetSampleTime(interval);   // 추가 코드 : 샘플링시간 수정
}


void loop()
{
	noInterrupts();
	delayMicroseconds(5);
	interrupts();
}

void PIDControl()
{
	Setpoint = 3*PI;              // setting steady state value
	cnt++;
	angVel = (float)((rev*2*PI*(1000/interval))/(180)); // 코드 수정 : 1000/interval, 180펄스당 1바퀴이므로 180으로 나눠준다
	RPS = angVel/2/PI;

	Serial.println(angVel);

	Input = angVel;
	myPID.Compute();              


	motorOutput = 180 + Output;    // 최종적으로 모터에 analog 값으로 0 ~255값이 들어가는 코드. 이 코드는 최적값의 기준이 뭘까?

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
}
