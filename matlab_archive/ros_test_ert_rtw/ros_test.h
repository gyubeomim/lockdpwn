//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ros_test.h
//
// Code generated for Simulink model 'ros_test'.
//
// Model version                  : 1.2
// Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
// C/C++ source code generated on : Tue Nov 14 00:36:16 2017
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_ros_test_h_
#define RTW_HEADER_ros_test_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef ros_test_COMMON_INCLUDES_
# define ros_test_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 // ros_test_COMMON_INCLUDES_

#include "ros_test_types.h"

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

// Block states (auto storage) for system '<Root>'
typedef struct {
  void *SinkBlock_PWORK;               // '<S2>/SinkBlock'
  robotics_slros_internal_block_T obj; // '<S2>/SinkBlock'
} DW_ros_test_T;

// Parameters (auto storage)
struct P_ros_test_T_ {
  real_T SineWave_Amp;                 // Expression: 5
                                       //  Referenced by: '<Root>/Sine Wave'

  real_T SineWave_Bias;                // Expression: 0
                                       //  Referenced by: '<Root>/Sine Wave'

  real_T SineWave_Freq;                // Expression: 1
                                       //  Referenced by: '<Root>/Sine Wave'

  real_T SineWave_Phase;               // Expression: 0
                                       //  Referenced by: '<Root>/Sine Wave'

  SL_Bus_ros_test_std_msgs_Float64 Constant_Value;// Computed Parameter: Constant_Value
                                                  //  Referenced by: '<S1>/Constant'

};

// Real-time Model Data Structure
struct tag_RTM_ros_test_T {
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

  extern P_ros_test_T ros_test_P;

#ifdef __cplusplus

}
#endif

// Block states (auto storage)
extern DW_ros_test_T ros_test_DW;

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
  extern void ros_test_initialize(void);
  extern void ros_test_step(void);
  extern void ros_test_terminate(void);

#ifdef __cplusplus

}
#endif

// Real-time Model object
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_ros_test_T *const ros_test_M;

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
//  '<Root>' : 'ros_test'
//  '<S1>'   : 'ros_test/Blank Message'
//  '<S2>'   : 'ros_test/Publish'

#endif                                 // RTW_HEADER_ros_test_h_

//
// File trailer for generated code.
//
// [EOF]
//
