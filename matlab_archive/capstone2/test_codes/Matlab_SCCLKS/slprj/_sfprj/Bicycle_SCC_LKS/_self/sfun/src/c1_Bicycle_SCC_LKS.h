#ifndef __c1_Bicycle_SCC_LKS_h__
#define __c1_Bicycle_SCC_LKS_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_Bicycle_SCC_LKSInstanceStruct
#define typedef_SFc1_Bicycle_SCC_LKSInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  uint8_T c1_tp_Cruise_Mode;
  uint8_T c1_tp_FollowUp_Mode;
  boolean_T c1_isStable;
  uint8_T c1_is_active_c1_Bicycle_SCC_LKS;
  uint8_T c1_is_c1_Bicycle_SCC_LKS;
  real_T c1_TVSpd;
  uint8_T c1_doSetSimStateSideEffects;
  const mxArray *c1_setSimStateSideEffectsInfo;
} SFc1_Bicycle_SCC_LKSInstanceStruct;

#endif                                 /*typedef_SFc1_Bicycle_SCC_LKSInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_Bicycle_SCC_LKS_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_Bicycle_SCC_LKS_get_check_sum(mxArray *plhs[]);
extern void c1_Bicycle_SCC_LKS_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
