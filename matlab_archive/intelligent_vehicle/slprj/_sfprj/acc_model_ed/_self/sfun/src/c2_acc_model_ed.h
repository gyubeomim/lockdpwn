#ifndef __c2_acc_model_ed_h__
#define __c2_acc_model_ed_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_acc_model_edInstanceStruct
#define typedef_SFc2_acc_model_edInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_acc_model_ed;
  real_T c2_setSpeed;
  boolean_T c2_setSpeed_not_empty;
} SFc2_acc_model_edInstanceStruct;

#endif                                 /*typedef_SFc2_acc_model_edInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_acc_model_ed_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_acc_model_ed_get_check_sum(mxArray *plhs[]);
extern void c2_acc_model_ed_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
