/*
	 arduino ==> 디지털제어, 텀프로젝트용 PID 제어 코드
*/
#include <PID_v1.h>
#include <TimerOne.h>

#define encPinA  2     // EncorderA
#define encPinB  12    // EncorerB

const int motor1a =9;
const int motor1b = 10;

const int interval = 100;
unsigned int long pre_millis=0;
unsigned int long curr_millis=0;
int cnt=0;

unsigned enBState = 0;  
volatile long rev = 0;

float angVel=0;

int motorSpeed;
int inputVel;

void encoder()
{ 
  enBState = digitalRead(encPinB);
  
  if (enBState ==HIGH) 
  {
	  rev++;     
  }
  else
  {
	  rev--;               
  }
}

void setup()
{
	Serial.begin(9600);

	pinMode(encPinA,INPUT_PULLUP);  // encoder input
	pinMode(encPinB,INPUT_PULLUP);  // encder input
	attachInterrupt(0, encoder, RISING);

	pinMode(motor1a,OUTPUT);
	pinMode(motor1b,OUTPUT);
	Serial.println("Start");
}

void loop()
{
  curr_millis = millis();
  
   //Serial.println(rev);
   //delay(100);
 /*  
  inputVel = Serial.parseInt();
  if(inputVel >=0 && inputVel <= 255)
  {
    analogWrite(motor1a,inputVel);   
    digitalWrite(motor1b,0);
  
  }
 */
   analogWrite(motor1a,255);   
   digitalWrite(motor1b,0);
  

   if(curr_millis - pre_millis == interval)
   {
    cnt++;
    angVel = (float)(rev*2*PI*10)/(3*60);
    Serial.println(angVel);
    //Serial.println(rev);
    
    //Serial.print(angVel); 
    //Serial.println(" [rad/s]");
    //delay(100);
    
    rev = 0;
    pre_millis = curr_millis;
   }
}

