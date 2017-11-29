//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: mylab2_simulink_to_ros.cpp
//
// Code generated for Simulink model 'mylab2_simulink_to_ros'.
//
// Model version                  : 1.21
// Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
// C/C++ source code generated on : Tue Nov 28 03:48:40 2017
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "mylab2_simulink_to_ros.h"
#include "mylab2_simulink_to_ros_private.h"
#define mylab2_simulink_MessageQueueLen (1)

// Block signals (auto storage)
B_mylab2_simulink_to_ros_T mylab2_simulink_to_ros_B;

// Block states (auto storage)
DW_mylab2_simulink_to_ros_T mylab2_simulink_to_ros_DW;

// Real-time model
RT_MODEL_mylab2_simulink_to_r_T mylab2_simulink_to_ros_M_;
RT_MODEL_mylab2_simulink_to_r_T *const mylab2_simulink_to_ros_M =
  &mylab2_simulink_to_ros_M_;

// Model step function
void mylab2_simulink_to_ros_step(void)
{
  SL_Bus_mylab2_simulink_to_ros_arduino_sub_pub_msgs_type varargout_2;
  boolean_T varargout_1;
  SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32 rtb_servo;
  SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32 rtb_motor;

  // Switch: '<Root>/Switch' incorporates:
  //   Clock: '<Root>/Clock'

  if (mylab2_simulink_to_ros_M->Timing.t[0] >
      mylab2_simulink_to_ros_P.Switch_Threshold) {
    // BusAssignment: '<Root>/motor' incorporates:
    //   Constant: '<Root>/Constant2'

    rtb_motor.Data = mylab2_simulink_to_ros_P.Constant2_Value;
  } else {
    // BusAssignment: '<Root>/motor' incorporates:
    //   Constant: '<Root>/Constant3'

    rtb_motor.Data = mylab2_simulink_to_ros_P.Constant3_Value;
  }

  // End of Switch: '<Root>/Switch'

  // Outputs for Atomic SubSystem: '<Root>/Publish'
  // Start for MATLABSystem: '<S4>/SinkBlock' incorporates:
  //   MATLABSystem: '<S4>/SinkBlock'

  Pub_mylab2_simulink_to_ros_1.publish(&rtb_motor);

  // End of Outputs for SubSystem: '<Root>/Publish'

  // BusAssignment: '<Root>/servo' incorporates:
  //   Constant: '<Root>/Constant1'

  rtb_servo.Data = mylab2_simulink_to_ros_P.Constant1_Value;

  // Outputs for Atomic SubSystem: '<Root>/Publish1'
  // Start for MATLABSystem: '<S5>/SinkBlock' incorporates:
  //   MATLABSystem: '<S5>/SinkBlock'

  Pub_mylab2_simulink_to_ros_12.publish(&rtb_servo);

  // End of Outputs for SubSystem: '<Root>/Publish1'

  // Outputs for Atomic SubSystem: '<Root>/Subscribe1'
  // Start for MATLABSystem: '<S8>/SourceBlock' incorporates:
  //   Inport: '<S10>/In1'
  //   MATLABSystem: '<S8>/SourceBlock'

  varargout_1 = Sub_mylab2_simulink_to_ros_13.getLatestMessage(&varargout_2);

  // Outputs for Enabled SubSystem: '<S8>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S10>/Enable'

  if (varargout_1) {
    mylab2_simulink_to_ros_B.In1 = varargout_2;
  }

  // End of Start for MATLABSystem: '<S8>/SourceBlock'
  // End of Outputs for SubSystem: '<S8>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe1'

  // Outputs for Atomic SubSystem: '<Root>/Publish2'
  // Start for MATLABSystem: '<S6>/SinkBlock' incorporates:
  //   BusAssignment: '<Root>/servo1'
  //   MATLABSystem: '<S6>/SinkBlock'

  Pub_mylab2_simulink_to_ros_24.publish(&mylab2_simulink_to_ros_B.In1);

  // End of Outputs for SubSystem: '<Root>/Publish2'

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  mylab2_simulink_to_ros_M->Timing.t[0] =
    (++mylab2_simulink_to_ros_M->Timing.clockTick0) *
    mylab2_simulink_to_ros_M->Timing.stepSize0;

  {
    // Update absolute timer for sample time: [0.1s, 0.0s]
    // The "clockTick1" counts the number of times the code of this task has
    //  been executed. The resolution of this integer timer is 0.1, which is the step size
    //  of the task. Size of "clockTick1" ensures timer will not overflow during the
    //  application lifespan selected.

    mylab2_simulink_to_ros_M->Timing.clockTick1++;
  }
}

// Model initialize function
void mylab2_simulink_to_ros_initialize(void)
{
  // Registration code

  // initialize real-time model
  (void) memset((void *)mylab2_simulink_to_ros_M, 0,
                sizeof(RT_MODEL_mylab2_simulink_to_r_T));

  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&mylab2_simulink_to_ros_M->solverInfo,
                          &mylab2_simulink_to_ros_M->Timing.simTimeStep);
    rtsiSetTPtr(&mylab2_simulink_to_ros_M->solverInfo, &rtmGetTPtr
                (mylab2_simulink_to_ros_M));
    rtsiSetStepSizePtr(&mylab2_simulink_to_ros_M->solverInfo,
                       &mylab2_simulink_to_ros_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&mylab2_simulink_to_ros_M->solverInfo,
                          (&rtmGetErrorStatus(mylab2_simulink_to_ros_M)));
    rtsiSetRTModelPtr(&mylab2_simulink_to_ros_M->solverInfo,
                      mylab2_simulink_to_ros_M);
  }

  rtsiSetSimTimeStep(&mylab2_simulink_to_ros_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&mylab2_simulink_to_ros_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(mylab2_simulink_to_ros_M, &mylab2_simulink_to_ros_M->Timing.tArray
             [0]);
  mylab2_simulink_to_ros_M->Timing.stepSize0 = 0.1;

  // block I/O
  (void) memset(((void *) &mylab2_simulink_to_ros_B), 0,
                sizeof(B_mylab2_simulink_to_ros_T));

  // states (dwork)
  (void) memset((void *)&mylab2_simulink_to_ros_DW, 0,
                sizeof(DW_mylab2_simulink_to_ros_T));

  {
    static const char_T tmp[18] = { '/', 'h', 'a', 'l', 'l', '_', 'p', 'u', 'b',
      'l', 'i', 's', 'h', 'e', 'r', '_', 'e', 'd' };

    static const char_T tmp_0[18] = { '/', 'h', 'a', 'l', 'l', '_', 'p', 'a',
      'r', 's', 'i', 'n', 'g', '_', 'd', 'a', 't', 'a' };

    static const char_T tmp_1[10] = { '/', 's', 'e', 'r', 'v', 'o', '_', 'p',
      'w', 'm' };

    static const char_T tmp_2[10] = { '/', 'm', 'o', 't', 'o', 'r', '_', 'p',
      'w', 'm' };

    char_T tmp_3[19];
    char_T tmp_4[11];
    int32_T i;

    // Start for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S4>/SinkBlock'
    mylab2_simulink_to_ros_DW.obj_e.isInitialized = 0;
    mylab2_simulink_to_ros_DW.obj_e.isInitialized = 1;
    for (i = 0; i < 10; i++) {
      tmp_4[i] = tmp_2[i];
    }

    tmp_4[10] = '\x00';
    Pub_mylab2_simulink_to_ros_1.createPublisher(tmp_4,
      mylab2_simulink_MessageQueueLen);

    // End of Start for MATLABSystem: '<S4>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish'

    // Start for Atomic SubSystem: '<Root>/Publish1'
    // Start for MATLABSystem: '<S5>/SinkBlock'
    mylab2_simulink_to_ros_DW.obj_j.isInitialized = 0;
    mylab2_simulink_to_ros_DW.obj_j.isInitialized = 1;
    for (i = 0; i < 10; i++) {
      tmp_4[i] = tmp_1[i];
    }

    tmp_4[10] = '\x00';
    Pub_mylab2_simulink_to_ros_12.createPublisher(tmp_4,
      mylab2_simulink_MessageQueueLen);

    // End of Start for MATLABSystem: '<S5>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish1'

    // Start for Atomic SubSystem: '<Root>/Subscribe1'
    // Start for MATLABSystem: '<S8>/SourceBlock'
    mylab2_simulink_to_ros_DW.obj_l.isInitialized = 0;
    mylab2_simulink_to_ros_DW.obj_l.isInitialized = 1;
    for (i = 0; i < 18; i++) {
      tmp_3[i] = tmp_0[i];
    }

    tmp_3[18] = '\x00';
    Sub_mylab2_simulink_to_ros_13.createSubscriber(tmp_3,
      mylab2_simulink_MessageQueueLen);

    // End of Start for MATLABSystem: '<S8>/SourceBlock'
    // End of Start for SubSystem: '<Root>/Subscribe1'

    // Start for Atomic SubSystem: '<Root>/Publish2'
    // Start for MATLABSystem: '<S6>/SinkBlock'
    mylab2_simulink_to_ros_DW.obj.isInitialized = 0;
    mylab2_simulink_to_ros_DW.obj.isInitialized = 1;
    for (i = 0; i < 18; i++) {
      tmp_3[i] = tmp[i];
    }

    tmp_3[18] = '\x00';
    Pub_mylab2_simulink_to_ros_24.createPublisher(tmp_3,
      mylab2_simulink_MessageQueueLen);

    // End of Start for MATLABSystem: '<S6>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish2'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1'
    // SystemInitialize for Enabled SubSystem: '<S8>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S10>/Out1'
    mylab2_simulink_to_ros_B.In1 = mylab2_simulink_to_ros_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S8>/Enabled Subsystem'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe1'
  }
}

// Model terminate function
void mylab2_simulink_to_ros_terminate(void)
{
  // Terminate for Atomic SubSystem: '<Root>/Publish'
  // Start for MATLABSystem: '<S4>/SinkBlock' incorporates:
  //   Terminate for MATLABSystem: '<S4>/SinkBlock'

  if (mylab2_simulink_to_ros_DW.obj_e.isInitialized == 1) {
    mylab2_simulink_to_ros_DW.obj_e.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S4>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish'

  // Terminate for Atomic SubSystem: '<Root>/Publish1'
  // Start for MATLABSystem: '<S5>/SinkBlock' incorporates:
  //   Terminate for MATLABSystem: '<S5>/SinkBlock'

  if (mylab2_simulink_to_ros_DW.obj_j.isInitialized == 1) {
    mylab2_simulink_to_ros_DW.obj_j.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S5>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish1'

  // Terminate for Atomic SubSystem: '<Root>/Subscribe1'
  // Start for MATLABSystem: '<S8>/SourceBlock' incorporates:
  //   Terminate for MATLABSystem: '<S8>/SourceBlock'

  if (mylab2_simulink_to_ros_DW.obj_l.isInitialized == 1) {
    mylab2_simulink_to_ros_DW.obj_l.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S8>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe1'

  // Terminate for Atomic SubSystem: '<Root>/Publish2'
  // Start for MATLABSystem: '<S6>/SinkBlock' incorporates:
  //   Terminate for MATLABSystem: '<S6>/SinkBlock'

  if (mylab2_simulink_to_ros_DW.obj.isInitialized == 1) {
    mylab2_simulink_to_ros_DW.obj.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S6>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish2'
}

//
// File trailer for generated code.
//
// [EOF]
//
