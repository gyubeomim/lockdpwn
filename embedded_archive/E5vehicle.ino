/*
	arduino ==> E5 자동차 모듈용 코드
				Follow me 로봇. 거리에 따라서 차량이 따라간다
 */
#include "Servo.h"
#define EA 3
#define EB 11
#define M_IN1 4
#define M_IN2 5
#define M_IN3 13
#define M_IN4 12
#define echo 6
#define trig 7
#define servo_mortor 2

int motorA_vector = 1;
int motorB_vector = 1;
int motor_speed = 100;
Servo LKservo;

void setup() 
{
  // put your setup code here, to run once
	Serial.begin(9600);
	pinMode(EA,OUTPUT);
	pinMode(EB,OUTPUT);
	pinMode(M_IN1,OUTPUT);
	pinMode(M_IN2,OUTPUT);
	pinMode(M_IN3,OUTPUT);
	pinMode(M_IN4,OUTPUT);
	pinMode(trig,OUTPUT);
	pinMode(echo,INPUT);
	LKservo.attach(servo_mortor);
	LKservo.write(90);  // 서보모터의 각도를 90도로 설정한다
	delay(2000);
}

void loop() 
{
	if(read_ultrasonic() < 12)
	{
		motor_con(-motor_speed,-motor_speed);  // 후진 
		delay(100);
	}
	else if(read_ultrasonic() > 18)
	{
		motor_con(motor_speed,motor_speed);   // 직진
		delay(100);
	}
	else
	{
		motor_con(0,0);  // 정지
	}
}

// 초음파센서 거리 읽는 코드
int read_ultrasonic()
{
	float return_time, howlong;

	digitalWrite(trig,HIGH);
	delay(5);
	digitalWrite(trig,LOW);
	return_time = pulseIn(echo,HIGH);
	howlong = ((float)(340*return_time)/10000)/2;
	
	// pc에 연결되지 않았을 때는 해당 구문을 주석처리해야한다
	//Serial.println(howlong);
	
	return howlong;
}

// 모터바퀴 제어하는 함수
void motor_con(int M1, int M2)
{
	if(M1>0)
	{
		digitalWrite(M_IN1,motorA_vector);
		digitalWrite(M_IN2,!motorA_vector);
	}
	else if(M1<0)
	{
		digitalWrite(M_IN1,!motorA_vector);
		digitalWrite(M_IN2,motorA_vector);
	}
	else
	{
		digitalWrite(M_IN1,LOW);
		digitalWrite(M_IN2,LOW);
	}

	if(M2>0)
	{
		digitalWrite(M_IN3,!motorB_vector);
		digitalWrite(M_IN4,motorB_vector);
	}
	else if(M2<0)
	{
		digitalWrite(M_IN3,motorB_vector);
		digitalWrite(M_IN4,!motorB_vector);
	}
	else
	{
		digitalWrite(M_IN3,LOW);
		digitalWrite(M_IN4,LOW);
	}

	analogWrite(EA,abs(M1));
	analogWrite(EB,abs(M2));
}
