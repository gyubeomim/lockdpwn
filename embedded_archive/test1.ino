#include <PID_v1.h>             //sketch > include libraries > manage libraries > download "PID" library 
#include <TimerOne.h>           //sketch > include libraries > manage libraries > download "TIMERONE" library

//----------------------------default settings---------------------------//
#define encPinA  2              // Pin number of EncorderA on arduino board
#define encPinB  12             // Pin number of EncorderB on arduino board

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

	pinMode(encPinA,INPUT_PULLUP);  // sets encPinA pin as input pin
	pinMode(encPinB,INPUT_PULLUP);  // sets encPinB pin as input pin
	attachInterrupt(0, encoder, RISING); // executes function "encoder" whenever value of encPinB rises

	pinMode(motor1a,OUTPUT);        // sets motor1a pin as output pin
	pinMode(motor1b,OUTPUT);        // sets motor1b pin as output pin
}


void loop()
{
	analogWrite(9,255);	
	analogWrite(10,0);	

	Serial.print("                                     ");
	Serial.println(rev);

	angVel = (float)((rev*2*PI*(1000/interval))/(180)); // 코드 수정 : 1000/interval, 180펄스당 1바퀴이므로 180으로 나눠준다
 
	Serial.print("                                           ");
	Serial.println(angVel);

	rev = 0 ;
}

