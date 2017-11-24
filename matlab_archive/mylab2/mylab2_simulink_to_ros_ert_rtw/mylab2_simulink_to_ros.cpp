//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: mylab2_simulink_to_ros.cpp
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
#include "mylab2_simulink_to_ros.h"
#include "mylab2_simulink_to_ros_private.h"
#define mylab2_simulink_MessageQueueLen (1)

// Block states (auto storage)
DW_mylab2_simulink_to_ros_T mylab2_simulink_to_ros_DW;

// Real-time model
RT_MODEL_mylab2_simulink_to_r_T mylab2_simulink_to_ros_M_;
RT_MODEL_mylab2_simulink_to_r_T *const mylab2_simulink_to_ros_M =
  &mylab2_simulink_to_ros_M_;

// Model step function
void mylab2_simulink_to_ros_step(void)
{
  SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32 rtb_servo;
  SL_Bus_mylab2_simulink_to_ros_std_msgs_Float32 rtb_motor;

  // BusAssignment: '<Root>/motor' incorporates:
  //   Constant: '<Root>/Constant2'

  rtb_motor.Data = mylab2_simulink_to_ros_P.Constant2_Value;

  // Outputs for Atomic SubSystem: '<Root>/Publish'
  // Start for MATLABSystem: '<S3>/SinkBlock' incorporates:
  //   MATLABSystem: '<S3>/SinkBlock'

  Pub_mylab2_simulink_to_ros_1.publish(&rtb_motor);

  // End of Outputs for SubSystem: '<Root>/Publish'

  // BusAssignment: '<Root>/servo' incorporates:
  //   Constant: '<Root>/Constant1'

  rtb_servo.Data = mylab2_simulink_to_ros_P.Constant1_Value;

  // Outputs for Atomic SubSystem: '<Root>/Publish1'
  // Start for MATLABSystem: '<S4>/SinkBlock' incorporates:
  //   MATLABSystem: '<S4>/SinkBlock'

  Pub_mylab2_simulink_to_ros_12.publish(&rtb_servo);

  // End of Outputs for SubSystem: '<Root>/Publish1'
}

// Model initialize function
void mylab2_simulink_to_ros_initialize(void)
{
  // Registration code

  // initialize error status
  rtmSetErrorStatus(mylab2_simulink_to_ros_M, (NULL));

  // states (dwork)
  (void) memset((void *)&mylab2_simulink_to_ros_DW, 0,
                sizeof(DW_mylab2_simulink_to_ros_T));

  {
    static const char_T tmp[10] = { '/', 's', 'e', 'r', 'v', 'o', '_', 'p', 'w',
      'm' };

    static const char_T tmp_0[10] = { '/', 'm', 'o', 't', 'o', 'r', '_', 'p',
      'w', 'm' };

    char_T tmp_1[11];
    int32_T i;

    // Start for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S3>/SinkBlock'
    mylab2_simulink_to_ros_DW.obj_e.isInitialized = 0;
    mylab2_simulink_to_ros_DW.obj_e.isInitialized = 1;
    for (i = 0; i < 10; i++) {
      tmp_1[i] = tmp_0[i];
    }

    tmp_1[10] = '\x00';
    Pub_mylab2_simulink_to_ros_1.createPublisher(tmp_1,
      mylab2_simulink_MessageQueueLen);

    // End of Start for MATLABSystem: '<S3>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish'

    // Start for Atomic SubSystem: '<Root>/Publish1'
    // Start for MATLABSystem: '<S4>/SinkBlock'
    mylab2_simulink_to_ros_DW.obj.isInitialized = 0;
    mylab2_simulink_to_ros_DW.obj.isInitialized = 1;
    for (i = 0; i < 10; i++) {
      tmp_1[i] = tmp[i];
    }

    tmp_1[10] = '\x00';
    Pub_mylab2_simulink_to_ros_12.createPublisher(tmp_1,
      mylab2_simulink_MessageQueueLen);

    // End of Start for MATLABSystem: '<S4>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish1'
  }
}

// Model terminate function
void mylab2_simulink_to_ros_terminate(void)
{
  // Terminate for Atomic SubSystem: '<Root>/Publish'
  // Start for MATLABSystem: '<S3>/SinkBlock' incorporates:
  //   Terminate for MATLABSystem: '<S3>/SinkBlock'

  if (mylab2_simulink_to_ros_DW.obj_e.isInitialized == 1) {
    mylab2_simulink_to_ros_DW.obj_e.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S3>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish'

  // Terminate for Atomic SubSystem: '<Root>/Publish1'
  // Start for MATLABSystem: '<S4>/SinkBlock' incorporates:
  //   Terminate for MATLABSystem: '<S4>/SinkBlock'

  if (mylab2_simulink_to_ros_DW.obj.isInitialized == 1) {
    mylab2_simulink_to_ros_DW.obj.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S4>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish1'
}

//
// File trailer for generated code.
//
// [EOF]
//
