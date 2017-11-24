#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block mylab2_simulink_to_ros/Publish
extern SimulinkPublisher<std_msgs::Float32, SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32> Pub_mylab2_simulink_to_ros_1;

// For Block mylab2_simulink_to_ros/Publish1
extern SimulinkPublisher<std_msgs::Float32, SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32> Pub_mylab2_simulink_to_ros_12;

void slros_node_init(int argc, char** argv);

#endif
