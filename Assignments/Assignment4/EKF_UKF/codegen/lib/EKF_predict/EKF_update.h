//
// File: EKF_update.h
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 02-Apr-2017 18:48:16
//
#ifndef __EKF_UPDATE_H__
#define __EKF_UPDATE_H__

// Include Files
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "EKF_predict_types.h"

// Function Declarations
extern void EKF_update(double x[3], double P[9], double z_data[], int z_size[2],
  const double R[4], const double idf_data[], const int idf_size[2], const
  double lm[40]);

#endif

//
// File trailer for EKF_update.h
//
// [EOF]
//
