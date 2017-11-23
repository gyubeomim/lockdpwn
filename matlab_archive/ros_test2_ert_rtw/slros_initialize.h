#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block ros_test2/Subscribe
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_ros_test2_std_msgs_Float64> Sub_ros_test2_3;

// For Block ros_test2/Publish
extern SimulinkPublisher<std_msgs::Float64, SL_Bus_ros_test2_std_msgs_Float64> Pub_ros_test2_7;

void slros_node_init(int argc, char** argv);

#endif
