#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block ros_test/Publish
extern SimulinkPublisher<std_msgs::Float64, SL_Bus_ros_test_std_msgs_Float64> Pub_ros_test_4;

void slros_node_init(int argc, char** argv);

#endif
