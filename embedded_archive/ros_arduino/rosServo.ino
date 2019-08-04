/*
 *  arduino ==> ROS 토픽으로 데이터를 전송해서 Servo 모터의 각도를 조절하는 코드 
 				rosrun rosserial_python serial_node.py 
				rostopic pub -1 /angle_msg std_msgs/Int32 "179"
 */
#include <ros.h>
#include <std_msgs/Int32.h>  // 거리값을 전송하기 위한 헤더 선언
#include "Servo.h"

Servo myservo;

ros::NodeHandle  nh;
std_msgs::Int32 int_msg;
ros::Publisher dist("dist", &int_msg);

// rostopic pub -1 /angle_msg std_msgs/Int32 "110"
// 위와 같은 명령어로 서보모터의 각도를 조절하는 함수
void messageCb(const std_msgs::Int32& angle_msg){
	myservo.write(angle_msg.data);
}
ros::Subscriber<std_msgs::Int32> sub("angle_msg", messageCb );

void setup(){
  myservo.attach(9);

  // 노드를 초기화하고 dist 노드와 sub을 선언한다
  nh.initNode();
  nh.subscribe(sub);
}

void loop(){
	nh.spinOnce();
}



