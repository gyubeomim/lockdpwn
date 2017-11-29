#include "slros_busmsg_conversion.h"


// Conversions between SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type and arduino_sub_pub::msgs_type

void convertFromBus(arduino_sub_pub::msgs_type* msgPtr, SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type const* busPtr)
{
  const std::string rosMessageType("arduino_sub_pub/msgs_type");

  msgPtr->rpm1 =  busPtr->Rpm1;
  msgPtr->rpm2 =  busPtr->Rpm2;
  msgPtr->rpm3 =  busPtr->Rpm3;
  msgPtr->rpm4 =  busPtr->Rpm4;
}

void convertToBus(SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type* busPtr, arduino_sub_pub::msgs_type const* msgPtr)
{
  const std::string rosMessageType("arduino_sub_pub/msgs_type");

  busPtr->Rpm1 =  msgPtr->rpm1;
  busPtr->Rpm2 =  msgPtr->rpm2;
  busPtr->Rpm3 =  msgPtr->rpm3;
  busPtr->Rpm4 =  msgPtr->rpm4;
}


// Conversions between SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32 and std_msgs::Float32

void convertFromBus(std_msgs::Float32* msgPtr, SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32 const* busPtr)
{
  const std::string rosMessageType("std_msgs/Float32");

  msgPtr->data =  busPtr->Data;
}

void convertToBus(SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32* busPtr, std_msgs::Float32 const* msgPtr)
{
  const std::string rosMessageType("std_msgs/Float32");

  busPtr->Data =  msgPtr->data;
}

