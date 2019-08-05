#ifndef _SLROS_BUSMSG_CONVERSION_H_
#define _SLROS_BUSMSG_CONVERSION_H_

#include <ros/ros.h>
#include <arduino_sub_pub/msgs_type.h>
#include <std_msgs/Float32.h>
#include "mylab2_simulink_to_ros_types.h"
#include "slros_msgconvert_utils.h"


void convertFromBus(arduino_sub_pub::msgs_type* msgPtr, SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type const* busPtr);
void convertToBus(SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type* busPtr, arduino_sub_pub::msgs_type const* msgPtr);

void convertFromBus(std_msgs::Float32* msgPtr, SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32 const* busPtr);
void convertToBus(SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32* busPtr, std_msgs::Float32 const* msgPtr);


#endif
