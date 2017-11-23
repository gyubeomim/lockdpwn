#ifndef __c3_mode_scc2_h__
#define __c3_mode_scc2_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc3_mode_scc2InstanceStruct
#define typedef_SFc3_mode_scc2InstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c3_sfEvent;
  uint8_T c3_tp_Cruise_Mode;
  uint8_T c3_tp_FollowUp_Mode;
  boolean_T c3_isStable;
  uint8_T c3_is_active_c3_mode_scc2;
  uint8_T c3_is_c3_mode_scc2;
  real_T c3_TVSpd;
  uint8_T c3_doSetSimStateSideEffects;
  const mxArray *c3_setSimStateSideEffectsInfo;
} SFc3_mode_scc2InstanceStruct;

#endif                                 /*typedef_SFc3_mode_scc2InstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_mode_scc2_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_mode_scc2_get_check_sum(mxArray *plhs[]);
extern void c3_mode_scc2_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
