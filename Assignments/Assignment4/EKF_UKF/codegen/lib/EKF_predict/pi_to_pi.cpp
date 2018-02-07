//
// File: pi_to_pi.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 02-Apr-2017 18:48:16
//

// Include Files
#include "rt_nonfinite.h"
#include "EKF_predict.h"
#include "EKF_update.h"
#include "pi_to_pi.h"

// Function Declarations
static double rt_roundd_snf(double u);

// Function Definitions

//
// Arguments    : double u
// Return Type  : double
//
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

//
// Input: array of angles.
// Arguments    : double *angle
// Return Type  : void
//
void pi_to_pi(double *angle)
{
  int ii_size_idx_0;
  int ii_size_idx_1;
  signed char ii_data[1];
  int loop_ub;
  int i3;
  signed char i_data[1];
  double dv2[1];
  double dv3[1];
  *angle /= 6.2831853071795862;
  if (fabs(*angle - rt_roundd_snf(*angle)) <= 2.2204460492503131E-16 * fabs
      (*angle)) {
    *angle = 0.0;
  } else {
    *angle = (*angle - floor(*angle)) * 6.2831853071795862;
  }

  if (*angle > 3.1415926535897931) {
    ii_size_idx_0 = 1;
    ii_size_idx_1 = 1;
    ii_data[0] = 1;
  } else {
    ii_size_idx_0 = 0;
    ii_size_idx_1 = 0;
  }

  loop_ub = ii_size_idx_0 * ii_size_idx_1;
  i3 = 0;
  while (i3 <= loop_ub - 1) {
    i_data[0] = 1;
    i3 = 1;
  }

  loop_ub = ii_size_idx_0 * ii_size_idx_1;
  i3 = 0;
  while (i3 <= loop_ub - 1) {
    ii_data[0] = 0;
    i3 = 1;
  }

  dv2[0] = *angle;
  loop_ub = ii_size_idx_0 * ii_size_idx_1;
  i3 = 0;
  while (i3 <= loop_ub - 1) {
    dv2[0] = *angle - 6.2831853071795862;
    i3 = 1;
  }

  if (dv2[0] < -3.1415926535897931) {
    ii_size_idx_0 = 1;
    ii_size_idx_1 = 1;
    ii_data[0] = 1;
  } else {
    ii_size_idx_0 = 0;
    ii_size_idx_1 = 0;
  }

  loop_ub = ii_size_idx_0 * ii_size_idx_1;
  i3 = 0;
  while (i3 <= loop_ub - 1) {
    i_data[0] = ii_data[0];
    i3 = 1;
  }

  dv3[0] = dv2[0];
  loop_ub = ii_size_idx_0 * ii_size_idx_1;
  i3 = 0;
  while (i3 <= loop_ub - 1) {
    dv3[i_data[0] - 1] = dv2[0] + 6.2831853071795862;
    i3 = 1;
  }

  *angle = dv3[0];
}

//
// File trailer for pi_to_pi.cpp
//
// [EOF]
//
