/* Include files */

#include <stddef.h>
#include "blas.h"
#include "vehicle_longitudinal_model_sfun.h"
#include "c2_vehicle_longitudinal_model.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "vehicle_longitudinal_model_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c2_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c2_IN_Decrease_Brake_Torque    ((uint8_T)1U)
#define c2_IN_Increase_Brake_Torque    ((uint8_T)2U)

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void initialize_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance);
static void initialize_params_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance);
static void enable_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance);
static void disable_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance);
static void set_sim_state_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance, const mxArray
   *c2_st);
static void c2_set_sim_state_side_effects_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance);
static void finalize_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance);
static void sf_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance);
static void initSimStructsc2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static int32_T c2_emlrt_marshallIn(SFc2_vehicle_longitudinal_modelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_b_emlrt_marshallIn
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance, const mxArray
   *c2_b_tp_Decrease_Brake_Torque, const char_T *c2_identifier);
static uint8_T c2_c_emlrt_marshallIn
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance, const mxArray
   *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_d_emlrt_marshallIn
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance, const mxArray
   *c2_b_setSimStateSideEffectsInfo, const char_T *c2_identifier);
static const mxArray *c2_e_emlrt_marshallIn
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance, const mxArray
   *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_vehicle_longitudinal_modelInstanceStruct *
  chartInstance);

/* Function Definitions */
static void initialize_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_doSetSimStateSideEffects = 0U;
  chartInstance->c2_setSimStateSideEffectsInfo = NULL;
  chartInstance->c2_tp_Decrease_Brake_Torque = 0U;
  chartInstance->c2_tp_Increase_Brake_Torque = 0U;
  chartInstance->c2_is_active_c2_vehicle_longitudinal_model = 0U;
  chartInstance->c2_is_c2_vehicle_longitudinal_model = c2_IN_NO_ACTIVE_CHILD;
}

static void initialize_params_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance)
{
}

static void enable_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  sf_call_output_fcn_enable(chartInstance->S, 0, "Decrease_Brake_Torque", 0);
  sf_call_output_fcn_enable(chartInstance->S, 1, "Increase_Brake_Torque", 0);
}

static void disable_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  sf_call_output_fcn_disable(chartInstance->S, 0, "Decrease_Brake_Torque", 0);
  sf_call_output_fcn_disable(chartInstance->S, 1, "Increase_Brake_Torque", 0);
}

static void c2_update_debugger_state_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance)
{
  uint32_T c2_prevAniVal;
  c2_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c2_is_active_c2_vehicle_longitudinal_model == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_c2_vehicle_longitudinal_model ==
      c2_IN_Decrease_Brake_Torque) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_c2_vehicle_longitudinal_model ==
      c2_IN_Increase_Brake_Torque) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
  }

  _SFD_SET_ANIMATION(c2_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_u;
  const mxArray *c2_b_y = NULL;
  uint8_T c2_b_hoistedGlobal;
  uint8_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(2), FALSE);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_vehicle_longitudinal_model;
  c2_u = c2_hoistedGlobal;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_hoistedGlobal = chartInstance->c2_is_c2_vehicle_longitudinal_model;
  c2_b_u = c2_b_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance, const mxArray
   *c2_st)
{
  const mxArray *c2_u;
  c2_u = sf_mex_dup(c2_st);
  chartInstance->c2_is_active_c2_vehicle_longitudinal_model =
    c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
    "is_active_c2_vehicle_longitudinal_model");
  chartInstance->c2_is_c2_vehicle_longitudinal_model = c2_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)),
     "is_c2_vehicle_longitudinal_model");
  sf_mex_assign(&chartInstance->c2_setSimStateSideEffectsInfo,
                c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 2)), "setSimStateSideEffectsInfo"), TRUE);
  sf_mex_destroy(&c2_u);
  chartInstance->c2_doSetSimStateSideEffects = 1U;
  c2_update_debugger_state_c2_vehicle_longitudinal_model(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void c2_set_sim_state_side_effects_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance)
{
  if (chartInstance->c2_doSetSimStateSideEffects != 0) {
    if (chartInstance->c2_is_c2_vehicle_longitudinal_model ==
        c2_IN_Decrease_Brake_Torque) {
      chartInstance->c2_tp_Decrease_Brake_Torque = 1U;
    } else {
      chartInstance->c2_tp_Decrease_Brake_Torque = 0U;
    }

    if (chartInstance->c2_is_c2_vehicle_longitudinal_model ==
        c2_IN_Increase_Brake_Torque) {
      chartInstance->c2_tp_Increase_Brake_Torque = 1U;
    } else {
      chartInstance->c2_tp_Increase_Brake_Torque = 0U;
    }

    chartInstance->c2_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c2_setSimStateSideEffectsInfo);
}

static void sf_c2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance)
{
  boolean_T c2_out;
  boolean_T c2_b_out;
  real_T *c2_Slip_Ratio;
  c2_Slip_Ratio = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c2_set_sim_state_side_effects_c2_vehicle_longitudinal_model(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  chartInstance->c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  if (chartInstance->c2_is_active_c2_vehicle_longitudinal_model == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
    chartInstance->c2_is_active_c2_vehicle_longitudinal_model = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c2_sfEvent);
    chartInstance->c2_is_c2_vehicle_longitudinal_model =
      c2_IN_Decrease_Brake_Torque;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
    chartInstance->c2_tp_Decrease_Brake_Torque = 1U;
  } else {
    switch (chartInstance->c2_is_c2_vehicle_longitudinal_model) {
     case c2_IN_Decrease_Brake_Torque:
      CV_CHART_EVAL(1, 0, 1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 0U,
                   chartInstance->c2_sfEvent);
      c2_out = (CV_TRANSITION_EVAL(0U, (int32_T)_SFD_CCP_CALL(0U, 0,
                  *c2_Slip_Ratio >= -0.1 != 0U, chartInstance->c2_sfEvent)) != 0);
      if (c2_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
        chartInstance->c2_tp_Decrease_Brake_Torque = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
        chartInstance->c2_is_c2_vehicle_longitudinal_model =
          c2_IN_Increase_Brake_Torque;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
        chartInstance->c2_tp_Increase_Brake_Torque = 1U;
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                     chartInstance->c2_sfEvent);
        sf_call_output_fcn_call(chartInstance->S, 0, "Decrease_Brake_Torque", 0);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
      break;

     case c2_IN_Increase_Brake_Torque:
      CV_CHART_EVAL(1, 0, 2);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U,
                   chartInstance->c2_sfEvent);
      c2_b_out = (CV_TRANSITION_EVAL(1U, (int32_T)_SFD_CCP_CALL(1U, 0,
        *c2_Slip_Ratio <= -0.3 != 0U, chartInstance->c2_sfEvent)) != 0);
      if (c2_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
        chartInstance->c2_tp_Increase_Brake_Torque = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
        chartInstance->c2_is_c2_vehicle_longitudinal_model =
          c2_IN_Decrease_Brake_Torque;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
        chartInstance->c2_tp_Decrease_Brake_Torque = 1U;
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                     chartInstance->c2_sfEvent);
        sf_call_output_fcn_call(chartInstance->S, 1, "Increase_Brake_Torque", 0);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
      break;

     default:
      CV_CHART_EVAL(1, 0, 0);
      chartInstance->c2_is_c2_vehicle_longitudinal_model = c2_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_vehicle_longitudinal_modelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc2_vehicle_longitudinal_model
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

const mxArray *sf_c2_vehicle_longitudinal_model_get_eml_resolved_functions_info
  (void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c2_nameCaptureInfo;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance;
  chartInstance = (SFc2_vehicle_longitudinal_modelInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_emlrt_marshallIn(SFc2_vehicle_longitudinal_modelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i0, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance;
  chartInstance = (SFc2_vehicle_longitudinal_modelInstanceStruct *)
    chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent), &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance;
  chartInstance = (SFc2_vehicle_longitudinal_modelInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(uint8_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static uint8_T c2_b_emlrt_marshallIn
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance, const mxArray
   *c2_b_tp_Decrease_Brake_Torque, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_tp_Decrease_Brake_Torque), &c2_thisId);
  sf_mex_destroy(&c2_b_tp_Decrease_Brake_Torque);
  return c2_y;
}

static uint8_T c2_c_emlrt_marshallIn
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance, const mxArray
   *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_tp_Decrease_Brake_Torque;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance;
  chartInstance = (SFc2_vehicle_longitudinal_modelInstanceStruct *)
    chartInstanceVoid;
  c2_b_tp_Decrease_Brake_Torque = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_tp_Decrease_Brake_Torque), &c2_thisId);
  sf_mex_destroy(&c2_b_tp_Decrease_Brake_Torque);
  *(uint8_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance;
  chartInstance = (SFc2_vehicle_longitudinal_modelInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_d_emlrt_marshallIn
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance, const mxArray
   *c2_b_setSimStateSideEffectsInfo, const char_T *c2_identifier)
{
  const mxArray *c2_y = NULL;
  emlrtMsgIdentifier c2_thisId;
  c2_y = NULL;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  sf_mex_assign(&c2_y, c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_setSimStateSideEffectsInfo), &c2_thisId), FALSE);
  sf_mex_destroy(&c2_b_setSimStateSideEffectsInfo);
  return c2_y;
}

static const mxArray *c2_e_emlrt_marshallIn
  (SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance, const mxArray
   *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_duplicatearraysafe(&c2_u), FALSE);
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_vehicle_longitudinal_modelInstanceStruct *
  chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_vehicle_longitudinal_model_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3741799709U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4208961209U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2741334267U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(713020365U);
}

mxArray *sf_c2_vehicle_longitudinal_model_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("lV8c5zbeTmErka1NWvqNBD");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_vehicle_longitudinal_model_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_vehicle_longitudinal_model_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c2_vehicle_longitudinal_model(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[8],M[0],T\"is_active_c2_vehicle_longitudinal_model\",},{M[9],M[0],T\"is_c2_vehicle_longitudinal_model\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_vehicle_longitudinal_model_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance;
    chartInstance = (SFc2_vehicle_longitudinal_modelInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _vehicle_longitudinal_modelMachineNumber_,
           2,
           2,
           3,
           1,
           2,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation
            (_vehicle_longitudinal_modelMachineNumber_,
             chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,
             _vehicle_longitudinal_modelMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _vehicle_longitudinal_modelMachineNumber_,
            chartInstance->chartNumber,
            2,
            2,
            2);
          _SFD_SET_DATA_PROPS(0,1,1,0,"Slip_Ratio");
          _SFD_EVENT_SCOPE(0,2);
          _SFD_EVENT_SCOPE(1,2);
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_CH_SUBSTATE_COUNT(2);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,1);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(1,0);
        }

        _SFD_CV_INIT_CHART(2,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(2,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 20 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(0,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 20 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(1,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c2_Slip_Ratio;
          c2_Slip_Ratio = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c2_Slip_Ratio);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _vehicle_longitudinal_modelMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "0RieOIALlbFzXW1CMxcryF";
}

static void sf_opaque_initialize_c2_vehicle_longitudinal_model(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_vehicle_longitudinal_modelInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_vehicle_longitudinal_model
    ((SFc2_vehicle_longitudinal_modelInstanceStruct*) chartInstanceVar);
  initialize_c2_vehicle_longitudinal_model
    ((SFc2_vehicle_longitudinal_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_vehicle_longitudinal_model(void
  *chartInstanceVar)
{
  enable_c2_vehicle_longitudinal_model
    ((SFc2_vehicle_longitudinal_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_vehicle_longitudinal_model(void
  *chartInstanceVar)
{
  disable_c2_vehicle_longitudinal_model
    ((SFc2_vehicle_longitudinal_modelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_vehicle_longitudinal_model(void
  *chartInstanceVar)
{
  sf_c2_vehicle_longitudinal_model
    ((SFc2_vehicle_longitudinal_modelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_vehicle_longitudinal_model
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_vehicle_longitudinal_model
    ((SFc2_vehicle_longitudinal_modelInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_vehicle_longitudinal_model();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c2_vehicle_longitudinal_model(SimStruct* S,
  const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_vehicle_longitudinal_model();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_vehicle_longitudinal_model
    ((SFc2_vehicle_longitudinal_modelInstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_vehicle_longitudinal_model
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c2_vehicle_longitudinal_model(S);
}

static void sf_opaque_set_sim_state_c2_vehicle_longitudinal_model(SimStruct* S,
  const mxArray *st)
{
  sf_internal_set_sim_state_c2_vehicle_longitudinal_model(S, st);
}

static void sf_opaque_terminate_c2_vehicle_longitudinal_model(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_vehicle_longitudinal_modelInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_vehicle_longitudinal_model_optimization_info();
    }

    finalize_c2_vehicle_longitudinal_model
      ((SFc2_vehicle_longitudinal_modelInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_vehicle_longitudinal_model
    ((SFc2_vehicle_longitudinal_modelInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_vehicle_longitudinal_model(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_vehicle_longitudinal_model
      ((SFc2_vehicle_longitudinal_modelInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_vehicle_longitudinal_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_vehicle_longitudinal_model_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,2);
    sf_mark_output_events_with_multiple_callers(S,sf_get_instance_specialization
      (),infoStruct,2,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=0; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1129312840U));
  ssSetChecksum1(S,(174447702U));
  ssSetChecksum2(S,(3118441107U));
  ssSetChecksum3(S,(3519868824U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_vehicle_longitudinal_model(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c2_vehicle_longitudinal_model(SimStruct *S)
{
  SFc2_vehicle_longitudinal_modelInstanceStruct *chartInstance;
  chartInstance = (SFc2_vehicle_longitudinal_modelInstanceStruct *)utMalloc
    (sizeof(SFc2_vehicle_longitudinal_modelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_vehicle_longitudinal_modelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_vehicle_longitudinal_model;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_vehicle_longitudinal_model;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_vehicle_longitudinal_model;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c2_vehicle_longitudinal_model;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c2_vehicle_longitudinal_model;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_vehicle_longitudinal_model;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_vehicle_longitudinal_model;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_vehicle_longitudinal_model;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_vehicle_longitudinal_model;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_vehicle_longitudinal_model;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_vehicle_longitudinal_model;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_vehicle_longitudinal_model_method_dispatcher(SimStruct *S, int_T method,
  void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_vehicle_longitudinal_model(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_vehicle_longitudinal_model(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_vehicle_longitudinal_model(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_vehicle_longitudinal_model_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
