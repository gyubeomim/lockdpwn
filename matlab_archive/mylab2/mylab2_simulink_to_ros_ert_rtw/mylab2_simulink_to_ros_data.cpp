//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: mylab2_simulink_to_ros_data.cpp
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
#include "mylab2_simulink_to_ros.h"
#include "mylab2_simulink_to_ros_private.h"

// Block parameters (auto storage)
P_mylab2_simulink_to_ros_T mylab2_simulink_to_ros_P = {
  {
    0.0F,                              // Rpm1
    0.0F,                              // Rpm2
    0.0F,                              // Rpm3
    0.0F                               // Rpm4
  },                                   // Computed Parameter: Out1_Y0
                                       //  Referenced by: '<S12>/Out1'


  {
    0.0F,                              // Rpm1
    0.0F,                              // Rpm2
    0.0F,                              // Rpm3
    0.0F                               // Rpm4
  },                                   // Computed Parameter: Constant_Value
                                       //  Referenced by: '<S10>/Constant'


  {
    0.0F,                              // Rpm1
    0.0F,                              // Rpm2
    0.0F,                              // Rpm3
    0.0F                               // Rpm4
  },                                   // Computed Parameter: Constant_Value_o
                                       //  Referenced by: '<S3>/Constant'

  -1.0,                                // Expression: SampleTime
                                       //  Referenced by: '<Root>/cmd'

  5.0,                                 // Expression: 5
                                       //  Referenced by: '<S5>/Switch'


  {
    0.0F                               // Data
  },                                   // Computed Parameter: Constant_Value_l
                                       //  Referenced by: '<S1>/Constant'


  {
    0.0F                               // Data
  },                                   // Computed Parameter: Constant_Value_ln
                                       //  Referenced by: '<S2>/Constant'

  1500.0F,                             // Computed Parameter: Constant_Value_op
                                       //  Referenced by: '<S4>/Constant'

  0.0F,                                // Computed Parameter: Normal_Y0
                                       //  Referenced by: '<S5>/Normal'

  1510.0F,                             // Computed Parameter: Constant2_Value
                                       //  Referenced by: '<S5>/Constant2'

  1507.0F,                             // Computed Parameter: Constant3_Value
                                       //  Referenced by: '<S5>/Constant3'

  0.0F,                                // Computed Parameter: Switch_Threshold_c
                                       //  Referenced by: '<Root>/Switch'

  1200.0F                              // Computed Parameter: Constant1_Value
                                       //  Referenced by: '<Root>/Constant1'

};

//
// File trailer for generated code.
//
// [EOF]
//
