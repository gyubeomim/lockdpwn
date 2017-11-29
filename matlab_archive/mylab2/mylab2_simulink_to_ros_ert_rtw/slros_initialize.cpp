#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "mylab2_simulink_to_ros";

// For Block mylab2_simulink_to_ros/Subscribe1
SimulinkSubscriber<arduino_sub_pub::msgs_type, SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type> Sub_mylab2_simulink_to_ros_13;

// For Block mylab2_simulink_to_ros/Publish
SimulinkPublisher<std_msgs::Float32, SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32> Pub_mylab2_simulink_to_ros_1;

// For Block mylab2_simulink_to_ros/Publish1
SimulinkPublisher<std_msgs::Float32, SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32> Pub_mylab2_simulink_to_ros_12;

// For Block mylab2_simulink_to_ros/Publish2
SimulinkPublisher<arduino_sub_pub::msgs_type, SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type> Pub_mylab2_simulink_to_ros_24;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

