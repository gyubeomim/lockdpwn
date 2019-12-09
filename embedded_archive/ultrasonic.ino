/*
 	arduino ==> 초음파센서로 거리를 읽어서 각도,거리. 값을 pc로 보내는 예제코드
				프로세싱과 같이 사용한다
 */
#include "Servo.h"

const int trigPin = 7;
const int echoPin = 6;

long duration;
int distance;

Servo myServo;

void setup()
{
	pinMode(trigPin,OUTPUT);
	pinMode(echoPin,INPUT);
	Serial.begin(9600);
	myServo.attach(2);
}

void loop()
{
	for(int i=5 ; i<=175 ; i++)
	{
		myServo.write(i);
		delay(2);
	
		distance = calculateDistance();

		Serial.print(i);
		Serial.print(",");
		Serial.print(distance);
		Serial.print(".");
	}
	
	for(int i=175 ; i>5 ; i--)
	{
		myServo.write(i);
		delay(2);
	
		distance = calculateDistance();

		Serial.print(i);
		Serial.print(",");
		Serial.print(distance);
		Serial.print(".");
	}
}

int calculateDistance(){
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);

	digitalWrite(trigPin,HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin,LOW);

	duration = pulseIn(echoPin,HIGH);
	distance = duration * 0.034/2;

	return distance;
}











