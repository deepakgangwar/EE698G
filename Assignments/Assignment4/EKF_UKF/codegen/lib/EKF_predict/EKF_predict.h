//
// File: EKF_predict.h
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 02-Apr-2017 18:48:16
//
#ifndef __EKF_PREDICT_H__
#define __EKF_PREDICT_H__

// Include Files
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "EKF_predict_types.h"

// Function Declarations
extern void EKF_predict(double x[3], double P[9], double v, double g, const
  double Q[4], double dt);

#endif

//
// File trailer for EKF_predict.h
//
// [EOF]
//
