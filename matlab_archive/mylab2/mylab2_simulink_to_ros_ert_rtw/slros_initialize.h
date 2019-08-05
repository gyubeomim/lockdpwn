#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block mylab2_simulink_to_ros/Subscribe1
extern SimulinkSubscriber<arduino_sub_pub::msgs_type, SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type> Sub_mylab2_simulink_to_ros_13;

// For Block mylab2_simulink_to_ros/Publish
extern SimulinkPublisher<std_msgs::Float32, SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32> Pub_mylab2_simulink_to_ros_1;

// For Block mylab2_simulink_to_ros/Publish1
extern SimulinkPublisher<std_msgs::Float32, SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32> Pub_mylab2_simulink_to_ros_12;

// For Block mylab2_simulink_to_ros/Publish2
extern SimulinkPublisher<arduino_sub_pub::msgs_type, SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type> Pub_mylab2_simulink_to_ros_24;

// For Block mylab2_simulink_to_ros/cmd
extern SimulinkParameterGetter<int32_T, int> ParamGet_mylab2_simulink_to_ros_27;

void slros_node_init(int argc, char** argv);

#endif
