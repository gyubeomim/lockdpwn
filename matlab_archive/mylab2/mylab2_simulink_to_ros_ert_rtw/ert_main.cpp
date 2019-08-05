//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ert_main.cpp
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
#include <stdio.h>
#include <stdlib.h>
#include "mylab2_simulink_to_ros.h"
#include "mylab2_simulink_to_ros_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "linuxinitialize.h"
#define UNUSED(x)                      x = x

// Function prototype declaration
void exitFcn(int sig);
void *terminateTask(void *arg);
void *baseRateTask(void *arg);
void *subrateTask(void *arg);
volatile boolean_T runModel = true;
sem_t stopSem;
sem_t baserateTaskSem;
pthread_t schedulerThread;
pthread_t baseRateThread;
unsigned long threadJoinStatus[8];
int terminatingmodel = 0;
void *baseRateTask(void *arg)
{
  runModel = (rtmGetErrorStatus(mylab2_simulink_to_ros_M) == (NULL));
  while (runModel) {
    sem_wait(&baserateTaskSem);
    mylab2_simulink_to_ros_step();

    // Get model outputs here
    runModel = (rtmGetErrorStatus(mylab2_simulink_to_ros_M) == (NULL));
  }

  runModel = 0;
  terminateTask(arg);
  pthread_exit((void *)0);
  return NULL;
}

void exitFcn(int sig)
{
  UNUSED(sig);
  rtmSetErrorStatus(mylab2_simulink_to_ros_M, "stopping the model");
}

void *terminateTask(void *arg)
{
  UNUSED(arg);
  terminatingmodel = 1;

  {
    runModel = 0;
  }

  // Disable rt_OneStep() here

  // Terminate model
  mylab2_simulink_to_ros_terminate();
  sem_post(&stopSem);
  return NULL;
}

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);
  void slros_node_init(int argc, char** argv);
  slros_node_init(argc, argv);
  rtmSetErrorStatus(mylab2_simulink_to_ros_M, 0);

  // Initialize model
  mylab2_simulink_to_ros_initialize();

  // Call RTOS Initialization function
  myRTOSInit(0.1, 0);

  // Wait for stop semaphore
  sem_wait(&stopSem);
  return 0;
}

//
// File trailer for generated code.
//
// [EOF]
//
