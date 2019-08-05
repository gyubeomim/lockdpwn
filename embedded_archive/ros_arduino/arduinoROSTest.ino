/*
 *  arduino ==> ROS, 초음파센서의 값을 오드로이드로 퍼블리시하고 
                     서보모터값을 오드로이드로부터 서브스크라이브 하는 코드
					 
					 arduino_test 패키지와 같이 실행된다
					 
					 rosrun rosserial_python serial_node
					 rosrun arduino_test arduino_test_subscriber
 */
#include <ros.h>
#include <std_msgs/Int32.h>  // 거리값을 전송하기 위한 헤더 선언
#include "Servo.h"

// 서보모터와 핀 값들을 선언한다
Servo myservo;
const int trigPin = 7;
const int echoPin = 6;
long duration = 0;
int distance = 0;

// ROS 관련 변수들
ros::NodeHandle  nh;
std_msgs::Int32 int_msg;

// 초음파센서 값을 오드로이드로 전달하는 퍼블리셔 선언
ros::Publisher dist("getUltrasonicData", &int_msg);

// 서보모터값을 입력받는 서브스크라이버 콜백함수 선언
void messageCb(const std_msgs::Int32& angle_msg){
	myservo.write(angle_msg.data);
}

// 서보모터 값을 오드로이드로부터 전달받는 서브스크라이버 선언
ros::Subscriber<std_msgs::Int32> sub("setServoData", messageCb );

// 초음파센서의 거리를 계산해서 반환하는 함수
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

void setup(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(2);
  	
  // 노드를 초기화하고 dist 노드를 선언한다
  nh.initNode();
  nh.advertise(dist);
  nh.subscribe(sub);
}

void loop(){
	// 초음파 센서 거리를 계산해서 int_msg에 넣고 dist 노드에 publish한다
	distance = calculateDistance();
	int_msg.data = distance;
	dist.publish( &int_msg );

	nh.spinOnce();
	delay(100);  // 0.1초 간격
}


