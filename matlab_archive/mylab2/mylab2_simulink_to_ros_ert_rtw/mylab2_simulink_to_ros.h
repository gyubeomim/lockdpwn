//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: mylab2_simulink_to_ros.h
//
// Code generated for Simulink model 'mylab2_simulink_to_ros'.
//
// Model version                  : 1.14
// Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
// C/C++ source code generated on : Fri Nov 24 19:52:38 2017
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_mylab2_simulink_to_ros_h_
#define RTW_HEADER_mylab2_simulink_to_ros_h_
#include <stddef.h>
#include <string.h>
#ifndef mylab2_simulink_to_ros_COMMON_INCLUDES_
# define mylab2_simulink_to_ros_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 // mylab2_simulink_to_ros_COMMON_INCLUDES_ 

#include "mylab2_simulink_to_ros_types.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

// Block states (auto storage) for system '<Root>'
typedef struct {
  void *SinkBlock_PWORK;               // '<S4>/SinkBlock'
  void *SinkBlock_PWORK_g;             // '<S3>/SinkBlock'
  robotics_slros_internal_block_T obj; // '<S4>/SinkBlock'
  robotics_slros_internal_block_T obj_e;// '<S3>/SinkBlock'
} DW_mylab2_simulink_to_ros_T;

// Parameters (auto storage)
struct P_mylab2_simulink_to_ros_T_ {
  SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32 Constant_Value;// Computed Parameter: Constant_Value
                                                                //  Referenced by: '<S1>/Constant'

  SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32 Constant_Value_l;// Computed Parameter: Constant_Value_l
                                                                  //  Referenced by: '<S2>/Constant'

  real32_T Constant2_Value;            // Computed Parameter: Constant2_Value
                                       //  Referenced by: '<Root>/Constant2'

  real32_T Constant1_Value;            // Computed Parameter: Constant1_Value
                                       //  Referenced by: '<Root>/Constant1'

};

// Real-time Model Data Structure
struct tag_RTM_mylab2_simulink_to_ro_T {
  const char_T *errorStatus;
};

// Block parameters (auto storage)
#ifdef __cplusplus

extern "C" {

#endif

  extern P_mylab2_simulink_to_ros_T mylab2_simulink_to_ros_P;

#ifdef __cplusplus

}
#endif

// Block states (auto storage)
extern DW_mylab2_simulink_to_ros_T mylab2_simulink_to_ros_DW;

#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void mylab2_simulink_to_ros_initialize(void);
  extern void mylab2_simulink_to_ros_step(void);
  extern void mylab2_simulink_to_ros_terminate(void);

#ifdef __cplusplus

}
#endif

// Real-time Model object
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_mylab2_simulink_to_r_T *const mylab2_simulink_to_ros_M;

#ifdef __cplusplus

}
#endif

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'mylab2_simulink_to_ros'
//  '<S1>'   : 'mylab2_simulink_to_ros/Blank Message'
//  '<S2>'   : 'mylab2_simulink_to_ros/Blank Message1'
//  '<S3>'   : 'mylab2_simulink_to_ros/Publish'
//  '<S4>'   : 'mylab2_simulink_to_ros/Publish1'
//  '<S5>'   : 'mylab2_simulink_to_ros/Subscribe'
//  '<S6>'   : 'mylab2_simulink_to_ros/Subscribe1'
//  '<S7>'   : 'mylab2_simulink_to_ros/Subscribe/Enabled Subsystem'
//  '<S8>'   : 'mylab2_simulink_to_ros/Subscribe1/Enabled Subsystem'

#endif                                 // RTW_HEADER_mylab2_simulink_to_ros_h_

//
// File trailer for generated code.
//
// [EOF]
//
