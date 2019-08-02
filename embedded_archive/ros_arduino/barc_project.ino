/*
	arduino ==> ROS, barc-project에서 가져온 traction control 관련 코드
					 Encoder, Ultrasound 값을          아두이노 --> 오드로이드    Publish 한 다음
					 Motor speed와 Servo 모터 값을     아두이노 <-- 오드로이드    Subscribe 하는 코드
*/
#include <ros.h>
#include <barc/Ultrasound.h>
#include <barc/Encoder.h>
#include <barc/MOT.h>
#include <barc/SERV.h>
#include <Servo.h>
#include ”Maxbotix.h”

//Number of encoder counts on tires
//count tick on {FL,FR,BL,BR}
//F=front,B=back,L=left,R=right
volatile int FL_count = 0;
volatile int FR_count = 0;

//encoder pins: pins 2, 3 are hardware interrupts
const int encPinA = 2;
const int encPinB = 3;

//Actuator pins: interrupts 5, 6
//<Servo> data type performs PWM
//Declare variables to hold actuator commands
Servo motor;
Servo steering;

const int motorPin = 10;
const int servoPin = 11;

int motorCMD;
int servoCMD;

const int noAction = 0;

//Actuator constraints(servo)
//Not sure if constraints should be active on motor as well
int d_theta_max = 50;
int theta_center = 90;
int motor_neutral = 90;
int theta_max = theta_center + d_theta_max;
int theta_min = theta_center - d_theta_max;
int motor_max = 180;
int motor_min = 0;

//variable for time
volatile unsigned long dt;
volatile unsigned long t0;

ros::NodeHandle nh;

//define global message variables
//Encoder, Electronic Control Unit,Ultrasound
barc::Ultrasound ultrasound;
barc::MOT mot;
barc::SERV serv;
barc::Encoder encoder;

ros::Publisher pub_encoder("encoder", &encoder);
ros::Publisher pub_ultrasound("ultrasound", &ultrasound);

//--------------------------------------------------------------------------
// MOT COMMAND CALLBACK
//--------------------------------------------------------------------------
void messageCbMOT(const barc::MOT &mot){
  //deconstruct message
  motorCMD = saturateMotor(int(mot.motor_pwm));

  //apply commands to motor and servo
  motor.write(motorCMD);
}

//ECU := Engine Control Unit
ros::Subscriber<barc::MOT> s("mot", messageCbMOT);


//--------------------------------------------------------------------------
// SERV COMMAND CALLBACK
//--------------------------------------------------------------------------
void messageCbSERV(const barc::SERV &serv){
  //deconstruct message
  servoCMD = saturateServo(int(serv.servo_pwm));

  //apply commands to motor and servo
  steering.write(servoCMD);
}

//ECU := Engine Control Unit
ros::Subscriber<barc::SERV> t("serv", messageCbSERV);

//Setup ultrasound sensors
/*
	usfr(14,Maxbotix::PW,Maxbotix::LV);Maxbotixusbk(15,Maxbotix::PW,Maxbotix::LV);//back
	Maxbotixusrt(16,Maxbotix::PW,Maxbotix::LV);//right
	Maxbotixuslt(17,Maxbotix::PW,Maxbotix::LV);//
	Maxbotix
	//front
	left
*/


//--------------------------------------------------------------------------
// ARDUINO INITIALIZATION
//--------------------------------------------------------------------------
void setup() {
  //Setup encoder sensors
  pinMode(encPinA, INPUT_PULLUP);
  pinMode(encPinB, INPUT_PULLUP);

  attachInterrupt(0, FL_inc, CHANGE);// args=(digital Pin to Interrupt, ISR, mode), mode set={LOW, CHANGE, RISING}
  attachInterrupt(1, FR_inc, CHANGE);// pin1=INT1, which is pinD3

  //Setup actuators
  motor.attach(motorPin);
  steering.attach(servoPin);

  //Start ROS node
  nh.initNode();

  //Publish/Subscribe to topics
  nh.advertise(pub_ultrasound);
  nh.advertise(pub_encoder);
  nh.subscribe(s);
  nh.subscribe(t);

  // ArmingESC, 1 sec delay for arming and ROS
  motor.write(theta_center);
  steering.write(theta_center);
  delay(1000);
  t0 = millis();
}


//--------------------------------------------------------------------------
// ARDUINO MAIN lOOP
//--------------------------------------------------------------------------
void loop(){
  //compute time elapsed (in ms)
  dt = millis() - t0;

  //publish measurements
  if (dt >= 50){
    //publish encodeer measurement
    encoder.FL = FL_count;
    encoder.FR = FR_count;
    encoder.BL = 0;
    encoder.BR = 0;
    pub_encoder.publish(&encoder);

    //publish ultra-sound measurement
    /*
      ultrasound.front=usfr.getRange();
      ultrasound.back=usbk.getRange();
      ultrasound.right=usrt.getRange();
      ultrasound.left=uslt.getRange();
    */

    pub_ultrasound.publish(&ultrasound);
    t0 = millis();
  }
  nh.spinOnce();
}

//--------------------------------------------------------------------------
// ENCODER COUNTERS
//--------------------------------------------------------------------------
//increment the counters
void FL_inc() { FL_count++; }
void FR_inc() { FR_count++; }



//--------------------------------------------------------------------------
// SATURATE MOTOR AND SERVO COMMANDS
//--------------------------------------------------------------------------
int saturateMotor(int x){
  if(x == noAction)    return motor_neutral;
  if(x > motor_max)    x = motor_max;
  else if(x < motor_min)   x = motor_min;

  return x;
}

int saturateServo(int x){
  if(x == noAction)    return theta_center;
  if(x > theta_max)    x = theta_max;
  else if(x < theta_min)   x = theta_min;

  return x;
}
