#ifndef __c1_test_ed_cs_h__
#define __c1_test_ed_cs_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_test_ed_csInstanceStruct
#define typedef_SFc1_test_ed_csInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  uint8_T c1_tp_Cruise_Mode;
  uint8_T c1_tp_Follow_Mode;
  uint8_T c1_tp_Vt_mode;
  uint8_T c1_tp_V_mode;
  uint8_T c1_tp_Observe_Mode;
  boolean_T c1_isStable;
  uint8_T c1_is_active_c1_test_ed_cs;
  uint8_T c1_is_c1_test_ed_cs;
  uint8_T c1_is_Follow_Mode;
  uint8_T c1_doSetSimStateSideEffects;
  const mxArray *c1_setSimStateSideEffectsInfo;
} SFc1_test_ed_csInstanceStruct;

#endif                                 /*typedef_SFc1_test_ed_csInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_test_ed_cs_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_test_ed_cs_get_check_sum(mxArray *plhs[]);
extern void c1_test_ed_cs_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
