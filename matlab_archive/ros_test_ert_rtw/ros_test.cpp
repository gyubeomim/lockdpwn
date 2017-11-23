//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ros_test.cpp
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
#include "ros_test.h"
#include "ros_test_private.h"
#define ros_test_MessageQueueLen       (1)

// Block states (auto storage)
DW_ros_test_T ros_test_DW;

// Real-time model
RT_MODEL_ros_test_T ros_test_M_;
RT_MODEL_ros_test_T *const ros_test_M = &ros_test_M_;

// Model step function
void ros_test_step(void)
{
  SL_Bus_ros_test_std_msgs_Float64 rtb_BusAssignment;

  // BusAssignment: '<Root>/Bus Assignment' incorporates:
  //   Sin: '<Root>/Sine Wave'

  rtb_BusAssignment.Data = sin(ros_test_P.SineWave_Freq * ros_test_M->Timing.t[0]
    + ros_test_P.SineWave_Phase) * ros_test_P.SineWave_Amp +
    ros_test_P.SineWave_Bias;

  // Outputs for Atomic SubSystem: '<Root>/Publish'
  // Start for MATLABSystem: '<S2>/SinkBlock' incorporates:
  //   MATLABSystem: '<S2>/SinkBlock'

  Pub_ros_test_4.publish(&rtb_BusAssignment);

  // End of Outputs for SubSystem: '<Root>/Publish'

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  ros_test_M->Timing.t[0] =
    (++ros_test_M->Timing.clockTick0) * ros_test_M->Timing.stepSize0;

  {
    // Update absolute timer for sample time: [0.2s, 0.0s]
    // The "clockTick1" counts the number of times the code of this task has
    //  been executed. The resolution of this integer timer is 0.2, which is the step size
    //  of the task. Size of "clockTick1" ensures timer will not overflow during the
    //  application lifespan selected.

    ros_test_M->Timing.clockTick1++;
  }
}

// Model initialize function
void ros_test_initialize(void)
{
  // Registration code

  // initialize real-time model
  (void) memset((void *)ros_test_M, 0,
                sizeof(RT_MODEL_ros_test_T));

  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&ros_test_M->solverInfo,
                          &ros_test_M->Timing.simTimeStep);
    rtsiSetTPtr(&ros_test_M->solverInfo, &rtmGetTPtr(ros_test_M));
    rtsiSetStepSizePtr(&ros_test_M->solverInfo, &ros_test_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&ros_test_M->solverInfo, (&rtmGetErrorStatus
      (ros_test_M)));
    rtsiSetRTModelPtr(&ros_test_M->solverInfo, ros_test_M);
  }

  rtsiSetSimTimeStep(&ros_test_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&ros_test_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(ros_test_M, &ros_test_M->Timing.tArray[0]);
  ros_test_M->Timing.stepSize0 = 0.2;

  // states (dwork)
  (void) memset((void *)&ros_test_DW, 0,
                sizeof(DW_ros_test_T));

  {
    static const char_T tmp[5] = { '/', 's', 'i', 'n', 'e' };

    char_T tmp_0[6];
    int32_T i;

    // Start for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S2>/SinkBlock'
    ros_test_DW.obj.isInitialized = 0;
    ros_test_DW.obj.isInitialized = 1;
    for (i = 0; i < 5; i++) {
      tmp_0[i] = tmp[i];
    }

    tmp_0[5] = '\x00';
    Pub_ros_test_4.createPublisher(tmp_0, ros_test_MessageQueueLen);

    // End of Start for MATLABSystem: '<S2>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish'
  }
}

// Model terminate function
void ros_test_terminate(void)
{
  // Terminate for Atomic SubSystem: '<Root>/Publish'
  // Start for MATLABSystem: '<S2>/SinkBlock' incorporates:
  //   Terminate for MATLABSystem: '<S2>/SinkBlock'

  if (ros_test_DW.obj.isInitialized == 1) {
    ros_test_DW.obj.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S2>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish'
}

//
// File trailer for generated code.
//
// [EOF]
//
