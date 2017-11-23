#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "ros_test";

// For Block ros_test/Publish
SimulinkPublisher<std_msgs::Float64, SL_Bus_ros_test_std_msgs_Float64> Pub_ros_test_4;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

