/*
	 arduino ==> 디지털제어, 텀프로젝트용 PID제어 코드
 */
#include <PID_v1.h>
#include <TimerOne.h>

#define encPinA  2   // EncorderA
#define encPinB  12    // EncorerB

float Kp = 0.5;                
float Ki = 22;                   
float Kd = 0;    
              
double Setpoint, Input, Output, motorOutput;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);   

const int motor1a =9;
const int motor1b = 10;
const int motor2a = 5;
const int motor2b = 6;

const int interval = 100;
unsigned int long pre_millis=0;
unsigned int long curr_millis=0;
int cnt=0;

unsigned enBState = 0;  
volatile long rev = 0;

 float angVel=0;

int motorSpeed;
int inputVel;

void setup()
{
Serial.begin(9600);

pinMode(encPinA,INPUT_PULLUP);  // encoder input
pinMode(encPinB,INPUT_PULLUP);  // encder input
attachInterrupt(0, encoder, RISING);

pinMode(motor1a,OUTPUT);
pinMode(motor1b,OUTPUT);
pinMode(motor2a,OUTPUT);
pinMode(motor2b,OUTPUT);

Input = angVel;

  myPID.SetMode(AUTOMATIC);             
  myPID.SetOutputLimits(-98,157);

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

   if(curr_millis - pre_millis == interval)
   {
    Setpoint = 5.93;
    cnt++;
    angVel = (float)((rev*2*PI*10)/(3*60));
    Serial.println(angVel);
    
Input = angVel;
 myPID.Compute();                       //PID계산 

 motorOutput=180+Output;
 if(motorOutput<=255&&motorOutput>=0)
 {//Serial.print("::");
 //Serial.println(Output);
 
   analogWrite(motor1a,motorOutput);   
   digitalWrite(motor1b,0);
 }

    //Serial.println(rev);
    
    //Serial.print(angVel); 
    //Serial.println(" [rad/s]");
    //delay(100);
    
    rev = 0;
    pre_millis = curr_millis;
   
   }  
}

void encoder()
{ 
  enBState = digitalRead(encPinB);
 if (enBState ==HIGH) rev++;     
  else rev--;               

}
