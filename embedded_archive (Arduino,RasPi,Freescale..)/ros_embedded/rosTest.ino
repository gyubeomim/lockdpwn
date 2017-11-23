/*
 *  arduino ==> ROS
 */
#include <ros.h>
#include <std_msgs/Int32.h>  // 거리값을 전송하기 위한 헤더 선언
#include <std_msgs/Empty.h>

const int trigPin = 7;
const int echoPin = 6;
long duration = 0;
int distance = 0;

ros::NodeHandle  nh;
std_msgs::Int32 int_msg;
ros::Publisher dist("getUltrasonicData", &int_msg);

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
  	
  // 노드를 초기화하고 dist 노드를 선언한다
  nh.initNode();
  nh.advertise(dist);
}

void loop(){
	// 초음파 센서 거리를 계산해서 int_msg에 넣고 dist 노드에 publish한다
	distance = calculateDistance();
	int_msg.data = distance;
	dist.publish( &int_msg );

	nh.spinOnce();
	delay(100);  // 0.1초 간격
}


