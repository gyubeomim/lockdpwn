/*
 *  arduino ==> ROS의 예제인 pubsub을 구현해본 코드
 				rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0 
				rostopic pub -1 /toggle_led std_msgs/Empty "{}" 로 LED를 껏다 켰다 하고
				rostopic echo /chatter 로 hello edward를 0.5초마다 출력한다
 */
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;

void messageCb( const std_msgs::Empty& toggle_msg){
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}

ros::Subscriber<std_msgs::Empty> sub("toggle_led", messageCb );

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello edward!";

void setup(){
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
}

void loop(){
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(1500);
}




















