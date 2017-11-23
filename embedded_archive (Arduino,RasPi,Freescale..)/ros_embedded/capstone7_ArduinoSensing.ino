/*
 * arudino ==> 캡스톤, 아두이노로부터 RC카 센서를 받아오는 코드

				1,2 pub 홀센서 : FR, RR의 홀센서 값
				3 pub 초음파 : maxSonar 초음파센서 값 
				4 sub DC 모터 : 모터의 속도
				5 sub Servo 모터 : 서보모터 각도

 */
#include <ros.h>
#include <std_msgs/Int32.h>  
#include <std_msgs/Float32.h>
#include <MsTimer2.h>
#include "Servo.h"

Servo myservo;
Servo esc;

const int pwPin = 7;
float duration = 0;

int n=0; 
int m=0;
int dt=100;
int rps_front;
int rps_rear;

int arraysize = 9;
int rangevalue[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
long pulse;
int modE;

ros::NodeHandle  nh;
std_msgs::Int32 int_msg;
std_msgs::Float32 float_msg;
std_msgs::Float32 float_hallfront_msg;
std_msgs::Float32 float_hallrear_msg;
ros::Publisher dist("dist", &float_msg);
ros::Publisher Rps_front("Rps_front", &float_hallfront_msg);
ros::Publisher Rps_rear("Rps_rear", &float_hallrear_msg);

//Sorting function
// sort function (Author: Bill Gentles, Nov. 12, 2010)
void isort(int *a, int n) {
	//  *a is an array pointer function
	for (int i = 1; i < n; ++i){
		int j = a[i];
		int k;
		for (k = i - 1; (k >= 0) && (j < a[k]); k--){
			a[k + 1] = a[k];
		}
		a[k + 1] = j;
	}
}

//Mode function, returning the mode or median.
int mode(int *x, int n) {
	int i = 0;
	int count = 0;
	int maxCount = 0;
	int mode = 0;
	int bimodal;
	int prevCount = 0;

	while (i < (n - 1)) {
		prevCount = count;
		count = 0;
		while (x[i] == x[i + 1]) {
			count++;
			i++;
		}

		if (count > prevCount & count > maxCount) {
			mode = x[i];
			maxCount = count;
			bimodal = 0;
		}

		if (count == 0)
			i++;

		if (count == maxCount) //If the dataset has 2 or more modes.
			bimodal = 1;

		if (mode == 0 || bimodal == 1) //Return the median if there is no mode.
			mode = x[(n / 2)];
		return mode;
	}
}


// servo_motor steering
void servo_control(const std_msgs::Int32& angle_msg){
	myservo.write(angle_msg.data);
}

// DC_motor duty
void motor_duty(const std_msgs::Int32& motor_speed){
	esc.writeMicroseconds(motor_speed.data);
}

ros::Subscriber<std_msgs::Int32> servo_steer("angle_msg", servo_control );
ros::Subscriber<std_msgs::Int32> DC_duty("motor_speed", motor_duty );

void calculateDistance(){
	for (int i = 0; i < arraysize; i++){
		pulse = pulseIn(pwPin, HIGH);
		rangevalue[i] = pulse / 58;
		delay(10);
	}

	isort(rangevalue, arraysize);
	modE = mode(rangevalue, arraysize);
	delay(100);


	float_msg.data=modE;
	dist.publish( &float_msg);
	delay(10);      
}

void getRps(){
	rps_front = m/(4*dt*0.001);
	rps_rear = n/(4*dt*0.001);

	float_hallfront_msg.data=rps_front;
	float_hallrear_msg.data=rps_rear;

	Rps_front.publish( &float_hallfront_msg);
	Rps_rear.publish( &float_hallrear_msg);

	m=0;
	n=0;
}

void Encoder_front(){
	m = m+1;
}

void Encoder_rear(){
	n = n+1;
}

void setup() {
//	Serial.begin(9600);

	attachInterrupt(1, Encoder_front, CHANGE);    
	attachInterrupt(0, Encoder_rear, CHANGE);   

	pinMode(pwPin, INPUT);

	myservo.attach(11);
	esc.attach(5);    
	esc.writeMicroseconds(1000);

	MsTimer2::set(dt, getRps);	// 0.1초에 한 번씩 getRpm() 함수를 실행하는 타이머를 설정합니다
	MsTimer2::start();			// 타이머를 실행합니다

	nh.initNode();
	nh.getHardware()->setBaud(57600);
	nh.advertise(dist);  
	nh.advertise(Rps_front);
	nh.advertise(Rps_rear);
	nh.subscribe(servo_steer);
	nh.subscribe(DC_duty);
}

void loop() {
	calculateDistance(); 
	nh.spinOnce();
	
	delay(50);
}

