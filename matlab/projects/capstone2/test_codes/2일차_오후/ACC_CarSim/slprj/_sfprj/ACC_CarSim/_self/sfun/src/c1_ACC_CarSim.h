#ifndef __c1_ACC_CarSim_h__
#define __c1_ACC_CarSim_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_SFc1_ACC_CarSimInstanceStruct
#define typedef_SFc1_ACC_CarSimInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  uint8_T c1_tp_Cruise_Mode;
  uint8_T c1_tp_FollowUp_Mode;
  boolean_T c1_isStable;
  uint8_T c1_is_active_c1_ACC_CarSim;
  uint8_T c1_is_c1_ACC_CarSim;
  real_T c1_TVSpd;
  uint8_T c1_doSetSimStateSideEffects;
  const mxArray *c1_setSimStateSideEffectsInfo;
} SFc1_ACC_CarSimInstanceStruct;

#endif                                 /*typedef_SFc1_ACC_CarSimInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_ACC_CarSim_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_ACC_CarSim_get_check_sum(mxArray *plhs[]);
extern void c1_ACC_CarSim_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
