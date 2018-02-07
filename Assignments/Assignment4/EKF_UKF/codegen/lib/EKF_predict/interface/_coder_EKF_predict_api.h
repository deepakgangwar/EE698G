/*
 * File: _coder_EKF_predict_api.h
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 02-Apr-2017 18:48:16
 */

#ifndef ___CODER_EKF_PREDICT_API_H__
#define ___CODER_EKF_PREDICT_API_H__

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_EKF_predict_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void EKF_predict(real_T x[3], real_T P[9], real_T v, real_T g, real_T Q[4],
  real_T dt);
extern void EKF_predict_api(const mxArray *prhs[6], const mxArray *plhs[2]);
extern void EKF_predict_atexit(void);
extern void EKF_predict_initialize(void);
extern void EKF_predict_terminate(void);
extern void EKF_predict_xil_terminate(void);
extern void EKF_update(real_T x[3], real_T P[9], real_T z_data[], int32_T
  z_size[2], real_T R[4], real_T idf_data[], int32_T idf_size[2], real_T lm[40]);
extern void EKF_update_api(const mxArray *prhs[6], const mxArray *plhs[2]);

#endif

/*
 * File trailer for _coder_EKF_predict_api.h
 *
 * [EOF]
 */
