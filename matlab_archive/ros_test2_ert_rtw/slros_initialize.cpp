#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "ros_test2";

// For Block ros_test2/Subscribe
SimulinkSubscriber<std_msgs::Float64, SL_Bus_ros_test2_std_msgs_Float64> Sub_ros_test2_3;

// For Block ros_test2/Publish
SimulinkPublisher<std_msgs::Float64, SL_Bus_ros_test2_std_msgs_Float64> Pub_ros_test2_7;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

