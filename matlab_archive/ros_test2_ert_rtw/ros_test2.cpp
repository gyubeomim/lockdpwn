//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ros_test2.cpp
//
// Code generated for Simulink model 'ros_test2'.
//
// Model version                  : 1.3
// Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
// C/C++ source code generated on : Tue Nov 14 00:37:06 2017
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "ros_test2.h"
#include "ros_test2_private.h"
#define ros_test2_MessageQueueLen      (1)

// Block signals (auto storage)
B_ros_test2_T ros_test2_B;

// Block states (auto storage)
DW_ros_test2_T ros_test2_DW;

// Real-time model
RT_MODEL_ros_test2_T ros_test2_M_;
RT_MODEL_ros_test2_T *const ros_test2_M = &ros_test2_M_;

// Model step function
void ros_test2_step(void)
{
  {
    real_T *lastU;
    SL_Bus_ros_test2_std_msgs_Float64 varargout_2;
    boolean_T varargout_1;
    SL_Bus_ros_test2_std_msgs_Float64 rtb_BusAssignment;
    real_T rtb_Derivative;

    // Outputs for Atomic SubSystem: '<Root>/Subscribe'
    // Start for MATLABSystem: '<S3>/SourceBlock' incorporates:
    //   Inport: '<S4>/In1'
    //   MATLABSystem: '<S3>/SourceBlock'

    varargout_1 = Sub_ros_test2_3.getLatestMessage(&varargout_2);

    // Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S4>/Enable'

    if (varargout_1) {
      ros_test2_B.In1 = varargout_2;
    }

    // End of Start for MATLABSystem: '<S3>/SourceBlock'
    // End of Outputs for SubSystem: '<S3>/Enabled Subsystem'
    // End of Outputs for SubSystem: '<Root>/Subscribe'

    // Derivative: '<Root>/Derivative'
    if ((ros_test2_DW.TimeStampA >= ros_test2_M->Timing.t[0]) &&
        (ros_test2_DW.TimeStampB >= ros_test2_M->Timing.t[0])) {
      rtb_Derivative = 0.0;
    } else {
      rtb_Derivative = ros_test2_DW.TimeStampA;
      lastU = &ros_test2_DW.LastUAtTimeA;
      if (ros_test2_DW.TimeStampA < ros_test2_DW.TimeStampB) {
        if (ros_test2_DW.TimeStampB < ros_test2_M->Timing.t[0]) {
          rtb_Derivative = ros_test2_DW.TimeStampB;
          lastU = &ros_test2_DW.LastUAtTimeB;
        }
      } else {
        if (ros_test2_DW.TimeStampA >= ros_test2_M->Timing.t[0]) {
          rtb_Derivative = ros_test2_DW.TimeStampB;
          lastU = &ros_test2_DW.LastUAtTimeB;
        }
      }

      rtb_Derivative = (ros_test2_B.In1.Data - *lastU) / (ros_test2_M->Timing.t
        [0] - rtb_Derivative);
    }

    // End of Derivative: '<Root>/Derivative'

    // BusAssignment: '<Root>/Bus Assignment'
    rtb_BusAssignment.Data = rtb_Derivative;

    // Outputs for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S2>/SinkBlock' incorporates:
    //   MATLABSystem: '<S2>/SinkBlock'

    Pub_ros_test2_7.publish(&rtb_BusAssignment);

    // End of Outputs for SubSystem: '<Root>/Publish'
  }

  {
    real_T *lastU;

    // Update for Derivative: '<Root>/Derivative'
    if (ros_test2_DW.TimeStampA == (rtInf)) {
      ros_test2_DW.TimeStampA = ros_test2_M->Timing.t[0];
      lastU = &ros_test2_DW.LastUAtTimeA;
    } else if (ros_test2_DW.TimeStampB == (rtInf)) {
      ros_test2_DW.TimeStampB = ros_test2_M->Timing.t[0];
      lastU = &ros_test2_DW.LastUAtTimeB;
    } else if (ros_test2_DW.TimeStampA < ros_test2_DW.TimeStampB) {
      ros_test2_DW.TimeStampA = ros_test2_M->Timing.t[0];
      lastU = &ros_test2_DW.LastUAtTimeA;
    } else {
      ros_test2_DW.TimeStampB = ros_test2_M->Timing.t[0];
      lastU = &ros_test2_DW.LastUAtTimeB;
    }

    *lastU = ros_test2_B.In1.Data;

    // End of Update for Derivative: '<Root>/Derivative'
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  ros_test2_M->Timing.t[0] =
    (++ros_test2_M->Timing.clockTick0) * ros_test2_M->Timing.stepSize0;

  {
    // Update absolute timer for sample time: [0.2s, 0.0s]
    // The "clockTick1" counts the number of times the code of this task has
    //  been executed. The resolution of this integer timer is 0.2, which is the step size
    //  of the task. Size of "clockTick1" ensures timer will not overflow during the
    //  application lifespan selected.

    ros_test2_M->Timing.clockTick1++;
  }
}

// Model initialize function
void ros_test2_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // initialize real-time model
  (void) memset((void *)ros_test2_M, 0,
                sizeof(RT_MODEL_ros_test2_T));

  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&ros_test2_M->solverInfo,
                          &ros_test2_M->Timing.simTimeStep);
    rtsiSetTPtr(&ros_test2_M->solverInfo, &rtmGetTPtr(ros_test2_M));
    rtsiSetStepSizePtr(&ros_test2_M->solverInfo, &ros_test2_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&ros_test2_M->solverInfo, (&rtmGetErrorStatus
      (ros_test2_M)));
    rtsiSetRTModelPtr(&ros_test2_M->solverInfo, ros_test2_M);
  }

  rtsiSetSimTimeStep(&ros_test2_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&ros_test2_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(ros_test2_M, &ros_test2_M->Timing.tArray[0]);
  ros_test2_M->Timing.stepSize0 = 0.2;

  // block I/O
  (void) memset(((void *) &ros_test2_B), 0,
                sizeof(B_ros_test2_T));

  // states (dwork)
  (void) memset((void *)&ros_test2_DW, 0,
                sizeof(DW_ros_test2_T));

  {
    static const char_T tmp[7] = { '/', 'c', 'o', 's', 'i', 'n', 'e' };

    static const char_T tmp_0[5] = { '/', 's', 'i', 'n', 'e' };

    char_T tmp_1[8];
    char_T tmp_2[6];
    int32_T i;

    // Start for Atomic SubSystem: '<Root>/Subscribe'
    // Start for MATLABSystem: '<S3>/SourceBlock'
    ros_test2_DW.obj_d.isInitialized = 0;
    ros_test2_DW.obj_d.isInitialized = 1;
    for (i = 0; i < 5; i++) {
      tmp_2[i] = tmp_0[i];
    }

    tmp_2[5] = '\x00';
    Sub_ros_test2_3.createSubscriber(tmp_2, ros_test2_MessageQueueLen);

    // End of Start for MATLABSystem: '<S3>/SourceBlock'
    // End of Start for SubSystem: '<Root>/Subscribe'

    // Start for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S2>/SinkBlock'
    ros_test2_DW.obj.isInitialized = 0;
    ros_test2_DW.obj.isInitialized = 1;
    for (i = 0; i < 7; i++) {
      tmp_1[i] = tmp[i];
    }

    tmp_1[7] = '\x00';
    Pub_ros_test2_7.createPublisher(tmp_1, ros_test2_MessageQueueLen);

    // End of Start for MATLABSystem: '<S2>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish'

    // InitializeConditions for Derivative: '<Root>/Derivative'
    ros_test2_DW.TimeStampA = (rtInf);
    ros_test2_DW.TimeStampB = (rtInf);

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S4>/Out1'
    ros_test2_B.In1 = ros_test2_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe'
  }
}

// Model terminate function
void ros_test2_terminate(void)
{
  // Terminate for Atomic SubSystem: '<Root>/Subscribe'
  // Start for MATLABSystem: '<S3>/SourceBlock' incorporates:
  //   Terminate for MATLABSystem: '<S3>/SourceBlock'

  if (ros_test2_DW.obj_d.isInitialized == 1) {
    ros_test2_DW.obj_d.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S3>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe'

  // Terminate for Atomic SubSystem: '<Root>/Publish'
  // Start for MATLABSystem: '<S2>/SinkBlock' incorporates:
  //   Terminate for MATLABSystem: '<S2>/SinkBlock'

  if (ros_test2_DW.obj.isInitialized == 1) {
    ros_test2_DW.obj.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S2>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish'
}

//
// File trailer for generated code.
//
// [EOF]
//
