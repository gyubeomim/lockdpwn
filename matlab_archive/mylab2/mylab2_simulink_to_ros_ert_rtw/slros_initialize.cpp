#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "mylab2_simulink_to_ros";

// For Block mylab2_simulink_to_ros/Publish
SimulinkPublisher<std_msgs::Float32, SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32> Pub_mylab2_simulink_to_ros_1;

// For Block mylab2_simulink_to_ros/Publish1
SimulinkPublisher<std_msgs::Float32, SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32> Pub_mylab2_simulink_to_ros_12;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

