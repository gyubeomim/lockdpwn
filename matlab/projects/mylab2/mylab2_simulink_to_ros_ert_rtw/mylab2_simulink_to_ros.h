//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: mylab2_simulink_to_ros.h
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
#ifndef RTW_HEADER_mylab2_simulink_to_ros_h_
#define RTW_HEADER_mylab2_simulink_to_ros_h_
#include <string.h>
#include <stddef.h>
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

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

// Block signals (auto storage)
typedef struct {
  SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type In1;// '<S12>/In1'
  real32_T Switch;                     // '<S5>/Switch'
  real32_T OutportBufferForStop;       // '<S4>/Constant'
} B_mylab2_simulink_to_ros_T;

// Block states (auto storage) for system '<Root>'
typedef struct {
  robotics_slros_internal_block_T obj; // '<Root>/cmd'
  void *SourceBlock_PWORK;             // '<S10>/SourceBlock'
  void *SinkBlock_PWORK;               // '<S8>/SinkBlock'
  void *SinkBlock_PWORK_i;             // '<S7>/SinkBlock'
  void *SinkBlock_PWORK_g;             // '<S6>/SinkBlock'
  void *cmd_PWORK;                     // '<Root>/cmd'
  robotics_slros_internal_blo_b_T obj_m;// '<S8>/SinkBlock'
  robotics_slros_internal_blo_b_T obj_j;// '<S7>/SinkBlock'
  robotics_slros_internal_blo_b_T obj_e;// '<S6>/SinkBlock'
  robotics_slros_internal_bl_bx_T obj_l;// '<S10>/SourceBlock'
} DW_mylab2_simulink_to_ros_T;

// Parameters (auto storage)
struct P_mylab2_simulink_to_ros_T_ {
  SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type Out1_Y0;// Computed Parameter: Out1_Y0
                                                                  //  Referenced by: '<S12>/Out1'

  SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type Constant_Value;// Computed Parameter: Constant_Value
                                                                      //  Referenced by: '<S10>/Constant'

  SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type Constant_Value_o;// Computed Parameter: Constant_Value_o
                                                                      //  Referenced by: '<S3>/Constant'

  real_T cmd_SampleTime;               // Expression: SampleTime
                                       //  Referenced by: '<Root>/cmd'

  real_T Switch_Threshold;             // Expression: 5
                                       //  Referenced by: '<S5>/Switch'

  SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32 Constant_Value_l;// Computed Parameter: Constant_Value_l
                                                                  //  Referenced by: '<S1>/Constant'

  SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32 Constant_Value_ln;// Computed Parameter: Constant_Value_ln
                                                                   //  Referenced by: '<S2>/Constant'

  real32_T Constant_Value_op;          // Computed Parameter: Constant_Value_op
                                       //  Referenced by: '<S4>/Constant'

  real32_T Normal_Y0;                  // Computed Parameter: Normal_Y0
                                       //  Referenced by: '<S5>/Normal'

  real32_T Constant2_Value;            // Computed Parameter: Constant2_Value
                                       //  Referenced by: '<S5>/Constant2'

  real32_T Constant3_Value;            // Computed Parameter: Constant3_Value
                                       //  Referenced by: '<S5>/Constant3'

  real32_T Switch_Threshold_c;         // Computed Parameter: Switch_Threshold_c
                                       //  Referenced by: '<Root>/Switch'

  real32_T Constant1_Value;            // Computed Parameter: Constant1_Value
                                       //  Referenced by: '<Root>/Constant1'

};

// Real-time Model Data Structure
struct tag_RTM_mylab2_simulink_to_ro_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

// Block parameters (auto storage)
#ifdef __cplusplus

extern "C" {

#endif

  extern P_mylab2_simulink_to_ros_T mylab2_simulink_to_ros_P;

#ifdef __cplusplus

}
#endif

// Block signals (auto storage)
extern B_mylab2_simulink_to_ros_T mylab2_simulink_to_ros_B;

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
//  '<S3>'   : 'mylab2_simulink_to_ros/Blank Message2'
//  '<S4>'   : 'mylab2_simulink_to_ros/If Action Subsystem'
//  '<S5>'   : 'mylab2_simulink_to_ros/If Action Subsystem1'
//  '<S6>'   : 'mylab2_simulink_to_ros/Publish'
//  '<S7>'   : 'mylab2_simulink_to_ros/Publish1'
//  '<S8>'   : 'mylab2_simulink_to_ros/Publish2'
//  '<S9>'   : 'mylab2_simulink_to_ros/Subscribe'
//  '<S10>'  : 'mylab2_simulink_to_ros/Subscribe1'
//  '<S11>'  : 'mylab2_simulink_to_ros/Subscribe/Enabled Subsystem'
//  '<S12>'  : 'mylab2_simulink_to_ros/Subscribe1/Enabled Subsystem'

#endif                                 // RTW_HEADER_mylab2_simulink_to_ros_h_

//
// File trailer for generated code.
//
// [EOF]
//
