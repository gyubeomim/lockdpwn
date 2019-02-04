/*
 	arduino ==> 초음파센서로 거리읽는 코드2 
 */
#include <Servo.h>
#define TRIG 7
#define ECHO 6

Servo servo;
int servoDirection = 1,  rad = 0;

void setup()
{
	Serial.begin(9600);
	pinMode(TRIG,OUTPUT);
	pinMode(ECHO,INPUT);
	servo.attach(2);
}

void loop()
{
	digitalWrite(TRIG,LOW);
	delayMicroseconds(2);
	digitalWrite(TRIG,HIGH);
	delayMicroseconds(5);
	digitalWrite(TRIG,LOW);

	long distance = pulseIn(ECHO,HIGH,5800)/58;

	Serial.print("r");
	Serial.print(rad);
	Serial.print("d");
	Serial.println(distance);

	rad += servoDirection;

	if(rad > 180)
	{
		rad = 179;
		servoDirection = -1;
	}
	else if(rad < 0)
	{
		rad = 1;
		servoDirection = 1;
	}
	servo.write(rad);
	delay(15);
}
