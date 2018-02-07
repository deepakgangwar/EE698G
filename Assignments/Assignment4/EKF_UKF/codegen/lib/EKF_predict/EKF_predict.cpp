//
// File: EKF_predict.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 02-Apr-2017 18:48:16
//

// Include Files
#include "rt_nonfinite.h"
#include "EKF_predict.h"
#include "EKF_update.h"
#include "pi_to_pi.h"

// Function Definitions

//
// function [xn,Pn]= predict (x,P,v,g,Q,WB,dt)
//
//  Inputs:
//    x, P - state and covariance
//    v, g - control inputs: velocity and gamma (steer angle)
//    Q - covariance matrix for velocity and gamma
//    dt - timestep
//
//  Outputs:
//    x, P - predicted state and covariance
// Arguments    : double x[3]
//                double P[9]
//                double v
//                double g
//                const double Q[4]
//                double dt
// Return Type  : void
//
void EKF_predict(double x[3], double P[9], double v, double g, const double Q[4],
                 double dt)
{
  double J[9];
  int i0;
  static const signed char iv0[3] = { 0, 0, 1 };

  double M[6];
  double b_J[9];
  double b_M[6];
  double c_J[9];
  double c_M[9];
  int i1;
  int i2;

  //  <------------------------- TO DO -------------------------->
  J[0] = 1.0;
  J[3] = 0.0;
  J[6] = -v * dt * sin(g + x[2]);
  J[1] = 0.0;
  J[4] = 1.0;
  J[7] = v * dt * cos(g + x[2]);
  for (i0 = 0; i0 < 3; i0++) {
    J[2 + 3 * i0] = iv0[i0];
  }

  M[0] = dt * cos(g + x[2]);
  M[3] = -v * dt * sin(g + x[2]);
  M[1] = dt * sin(g + x[2]);
  M[4] = v * dt * cos(g + x[2]);
  for (i0 = 0; i0 < 2; i0++) {
    M[2 + 3 * i0] = i0;
  }

  for (i0 = 0; i0 < 3; i0++) {
    for (i1 = 0; i1 < 3; i1++) {
      b_J[i0 + 3 * i1] = 0.0;
      for (i2 = 0; i2 < 3; i2++) {
        b_J[i0 + 3 * i1] += J[i0 + 3 * i2] * P[i2 + 3 * i1];
      }
    }

    for (i1 = 0; i1 < 2; i1++) {
      b_M[i0 + 3 * i1] = 0.0;
      for (i2 = 0; i2 < 2; i2++) {
        b_M[i0 + 3 * i1] += M[i0 + 3 * i2] * Q[i2 + (i1 << 1)];
      }
    }

    for (i1 = 0; i1 < 3; i1++) {
      c_J[i0 + 3 * i1] = 0.0;
      for (i2 = 0; i2 < 3; i2++) {
        c_J[i0 + 3 * i1] += b_J[i0 + 3 * i2] * J[i1 + 3 * i2];
      }

      c_M[i0 + 3 * i1] = 0.0;
      for (i2 = 0; i2 < 2; i2++) {
        c_M[i0 + 3 * i1] += b_M[i0 + 3 * i2] * M[i1 + 3 * i2];
      }
    }
  }

  for (i0 = 0; i0 < 3; i0++) {
    for (i1 = 0; i1 < 3; i1++) {
      P[i1 + 3 * i0] = c_J[i1 + 3 * i0] + c_M[i1 + 3 * i0];
    }
  }

  x[0] += v * dt * cos(g + x[2]);
  x[1] += v * dt * sin(g + x[2]);
  x[2] += g;
  pi_to_pi(&x[2]);
}

//
// File trailer for EKF_predict.cpp
//
// [EOF]
//
