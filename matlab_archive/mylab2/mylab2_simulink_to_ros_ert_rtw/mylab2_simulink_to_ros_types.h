//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: mylab2_simulink_to_ros_types.h
//
// Code generated for Simulink model 'mylab2_simulink_to_ros'.
//
// Model version                  : 1.51
// Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
// C/C++ source code generated on : Fri Dec  1 19:54:22 2017
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_mylab2_simulink_to_ros_types_h_
#define RTW_HEADER_mylab2_simulink_to_ros_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32_
#define DEFINED_TYPEDEF_FOR_SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32_

// MsgType=std_msgs/Float32
typedef struct {
  real32_T Data;
} SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type_
#define DEFINED_TYPEDEF_FOR_SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type_

// MsgType=arduino_sub_pub/msgs_type
typedef struct {
  real32_T Rpm1;
  real32_T Rpm2;
  real32_T Rpm3;
  real32_T Rpm4;
} SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type;

#endif

#ifndef typedef_robotics_slros_internal_block_T
#define typedef_robotics_slros_internal_block_T

typedef struct {
  int32_T isInitialized;
  real_T SampleTime;
} robotics_slros_internal_block_T;

#endif                                 //typedef_robotics_slros_internal_block_T

#ifndef typedef_robotics_slros_internal_blo_b_T
#define typedef_robotics_slros_internal_blo_b_T

typedef struct {
  int32_T isInitialized;
} robotics_slros_internal_blo_b_T;

#endif                                 //typedef_robotics_slros_internal_blo_b_T

#ifndef typedef_robotics_slros_internal_bl_bx_T
#define typedef_robotics_slros_internal_bl_bx_T

typedef struct {
  int32_T isInitialized;
} robotics_slros_internal_bl_bx_T;

#endif                                 //typedef_robotics_slros_internal_bl_bx_T

#ifndef typedef_struct_T_mylab2_simulink_to_r_T
#define typedef_struct_T_mylab2_simulink_to_r_T

typedef struct {
  char_T f1[4];
} struct_T_mylab2_simulink_to_r_T;

#endif                                 //typedef_struct_T_mylab2_simulink_to_r_T

#ifndef typedef_struct_T_mylab2_simulink_to_b_T
#define typedef_struct_T_mylab2_simulink_to_b_T

typedef struct {
  char_T f1[8];
} struct_T_mylab2_simulink_to_b_T;

#endif                                 //typedef_struct_T_mylab2_simulink_to_b_T

#ifndef typedef_struct_T_mylab2_simulink_t_bx_T
#define typedef_struct_T_mylab2_simulink_t_bx_T

typedef struct {
  char_T f1[7];
} struct_T_mylab2_simulink_t_bx_T;

#endif                                 //typedef_struct_T_mylab2_simulink_t_bx_T

#ifndef typedef_struct_T_mylab2_simulink__bxc_T
#define typedef_struct_T_mylab2_simulink__bxc_T

typedef struct {
  char_T f1[8];
  char_T f2[4];
  char_T f3[6];
} struct_T_mylab2_simulink__bxc_T;

#endif                                 //typedef_struct_T_mylab2_simulink__bxc_T

#ifndef typedef_struct_T_mylab2_simulink_bxcj_T
#define typedef_struct_T_mylab2_simulink_bxcj_T

typedef struct {
  real_T f1[2];
} struct_T_mylab2_simulink_bxcj_T;

#endif                                 //typedef_struct_T_mylab2_simulink_bxcj_T

#ifndef typedef_struct_T_mylab2_simulin_bxcjb_T
#define typedef_struct_T_mylab2_simulin_bxcjb_T

typedef struct {
  char_T f1[8];
  char_T f2[7];
  char_T f3[6];
} struct_T_mylab2_simulin_bxcjb_T;

#endif                                 //typedef_struct_T_mylab2_simulin_bxcjb_T

// Parameters (auto storage)
typedef struct P_mylab2_simulink_to_ros_T_ P_mylab2_simulink_to_ros_T;

// Forward declaration for rtModel
typedef struct tag_RTM_mylab2_simulink_to_ro_T RT_MODEL_mylab2_simulink_to_r_T;

#endif                                 // RTW_HEADER_mylab2_simulink_to_ros_types_h_ 

//
// File trailer for generated code.
//
// [EOF]
//
