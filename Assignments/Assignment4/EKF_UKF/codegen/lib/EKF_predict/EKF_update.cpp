//
// File: EKF_update.cpp
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
static void eml_xaxpy(double a, double y[4]);
static double eml_xdotc(const double x[4], const double y[4]);
static void eml_xgesvd(const double A[4], double U[4], double S[2], double V[4]);
static double eml_xnrm2(const double x[4]);
static void eml_xrot(double x[4], int ix0, int iy0, double c, double s);
static void eml_xrotg(double *a, double *b, double *c, double *s);
static void eml_xscal(double a, double x[4], int ix0);
static void eml_xswap(double x[4]);
static double rt_atan2d_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double a
//                double y[4]
// Return Type  : void
//
static void eml_xaxpy(double a, double y[4])
{
  int ix;
  int iy;
  int k;
  if (a == 0.0) {
  } else {
    ix = 0;
    iy = 2;
    for (k = 0; k < 2; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

//
// Arguments    : const double x[4]
//                const double y[4]
// Return Type  : double
//
static double eml_xdotc(const double x[4], const double y[4])
{
  double d;
  int ix;
  int iy;
  int k;
  d = 0.0;
  ix = 0;
  iy = 2;
  for (k = 0; k < 2; k++) {
    d += x[ix] * y[iy];
    ix++;
    iy++;
  }

  return d;
}

//
// Arguments    : const double A[4]
//                double U[4]
//                double S[2]
//                double V[4]
// Return Type  : void
//
static void eml_xgesvd(const double A[4], double U[4], double S[2], double V[4])
{
  double b_A[4];
  double Vf[4];
  int ixstart;
  boolean_T apply_transform;
  double nrm;
  double ztest;
  int kase;
  double s[2];
  int m;
  double e[2];
  int q;
  double rt;
  int iter;
  double snorm;
  boolean_T exitg3;
  int qs;
  boolean_T exitg2;
  double f;
  double varargin_1[5];
  double mtmp;
  boolean_T exitg1;
  double sqds;
  for (ixstart = 0; ixstart < 4; ixstart++) {
    b_A[ixstart] = A[ixstart];
    Vf[ixstart] = 0.0;
  }

  apply_transform = false;
  nrm = eml_xnrm2(A);
  if (nrm > 0.0) {
    apply_transform = true;
    if (A[0] < 0.0) {
      nrm = -nrm;
    }

    if (fabs(nrm) >= 1.0020841800044864E-292) {
      ztest = 1.0 / nrm;
      for (kase = 0; kase < 2; kase++) {
        b_A[kase] *= ztest;
      }
    } else {
      for (kase = 0; kase < 2; kase++) {
        b_A[kase] /= nrm;
      }
    }

    b_A[0]++;
    s[0] = -nrm;
  } else {
    s[0] = 0.0;
  }

  if (apply_transform) {
    eml_xaxpy(-(eml_xdotc(b_A, b_A) / b_A[0]), b_A);
  }

  m = 2;
  s[1] = b_A[3];
  e[0] = b_A[2];
  e[1] = 0.0;
  for (ixstart = 0; ixstart < 2; ixstart++) {
    U[ixstart] = b_A[ixstart];
    U[2 + ixstart] = 0.0;
  }

  U[3] = 1.0;
  if (s[0] != 0.0) {
    eml_xaxpy(-(eml_xdotc(U, U) / U[0]), U);
    for (ixstart = 0; ixstart < 2; ixstart++) {
      U[ixstart] = -U[ixstart];
    }

    U[0]++;
  } else {
    for (ixstart = 0; ixstart < 2; ixstart++) {
      U[ixstart] = 0.0;
    }

    U[0] = 1.0;
  }

  for (q = 1; q > -1; q += -1) {
    for (ixstart = 0; ixstart < 2; ixstart++) {
      Vf[ixstart + (q << 1)] = 0.0;
    }

    Vf[q + (q << 1)] = 1.0;
  }

  nrm = b_A[2];
  for (q = 0; q < 2; q++) {
    if (s[q] != 0.0) {
      rt = fabs(s[q]);
      ztest = s[q] / rt;
      s[q] = rt;
      if (q + 1 < 2) {
        nrm /= ztest;
      }

      eml_xscal(ztest, U, 1 + (q << 1));
    }

    if ((q + 1 < 2) && (nrm != 0.0)) {
      rt = fabs(nrm);
      ztest = rt / nrm;
      nrm = rt;
      s[1] *= ztest;
      eml_xscal(ztest, Vf, 3);
    }

    e[0] = nrm;
  }

  iter = 0;
  snorm = 0.0;
  for (ixstart = 0; ixstart < 2; ixstart++) {
    nrm = fabs(s[ixstart]);
    ztest = fabs(e[ixstart]);
    if ((nrm >= ztest) || rtIsNaN(ztest)) {
    } else {
      nrm = ztest;
    }

    if ((snorm >= nrm) || rtIsNaN(nrm)) {
    } else {
      snorm = nrm;
    }
  }

  while ((m > 0) && (!(iter >= 75))) {
    q = m - 1;
    exitg3 = false;
    while (!(exitg3 || (q == 0))) {
      nrm = fabs(e[0]);
      if ((nrm <= 2.2204460492503131E-16 * (fabs(s[0]) + fabs(s[1]))) || (nrm <=
           1.0020841800044864E-292) || ((iter > 20) && (nrm <=
            2.2204460492503131E-16 * snorm))) {
        e[0] = 0.0;
        exitg3 = true;
      } else {
        q = 0;
      }
    }

    if (q == m - 1) {
      kase = 4;
    } else {
      qs = m;
      ixstart = m;
      exitg2 = false;
      while ((!exitg2) && (ixstart >= q)) {
        qs = ixstart;
        if (ixstart == q) {
          exitg2 = true;
        } else {
          nrm = 0.0;
          if (ixstart < m) {
            nrm = fabs(e[0]);
          }

          if (ixstart > q + 1) {
            nrm += fabs(e[0]);
          }

          ztest = fabs(s[ixstart - 1]);
          if ((ztest <= 2.2204460492503131E-16 * nrm) || (ztest <=
               1.0020841800044864E-292)) {
            s[ixstart - 1] = 0.0;
            exitg2 = true;
          } else {
            ixstart--;
          }
        }
      }

      if (qs == q) {
        kase = 3;
      } else if (qs == m) {
        kase = 1;
      } else {
        kase = 2;
        q = qs;
      }
    }

    switch (kase) {
     case 1:
      f = e[0];
      e[0] = 0.0;
      kase = m - 1;
      while (kase >= q + 1) {
        nrm = s[0];
        eml_xrotg(&nrm, &f, &ztest, &rt);
        s[0] = nrm;
        eml_xrot(Vf, 1, 1 + ((m - 1) << 1), ztest, rt);
        kase = 0;
      }
      break;

     case 2:
      f = e[q - 1];
      e[q - 1] = 0.0;
      for (kase = q; kase + 1 <= m; kase++) {
        eml_xrotg(&s[kase], &f, &ztest, &rt);
        f = -rt * e[kase];
        e[kase] *= ztest;
        eml_xrot(U, 1 + (kase << 1), 1 + ((q - 1) << 1), ztest, rt);
      }
      break;

     case 3:
      varargin_1[0] = fabs(s[m - 1]);
      varargin_1[1] = fabs(s[0]);
      varargin_1[2] = fabs(e[0]);
      varargin_1[3] = fabs(s[q]);
      varargin_1[4] = fabs(e[q]);
      ixstart = 1;
      mtmp = varargin_1[0];
      if (rtIsNaN(varargin_1[0])) {
        kase = 2;
        exitg1 = false;
        while ((!exitg1) && (kase < 6)) {
          ixstart = kase;
          if (!rtIsNaN(varargin_1[kase - 1])) {
            mtmp = varargin_1[kase - 1];
            exitg1 = true;
          } else {
            kase++;
          }
        }
      }

      if (ixstart < 5) {
        while (ixstart + 1 < 6) {
          if (varargin_1[ixstart] > mtmp) {
            mtmp = varargin_1[ixstart];
          }

          ixstart++;
        }
      }

      f = s[m - 1] / mtmp;
      nrm = s[0] / mtmp;
      ztest = e[0] / mtmp;
      sqds = s[q] / mtmp;
      rt = ((nrm + f) * (nrm - f) + ztest * ztest) / 2.0;
      nrm = f * ztest;
      nrm *= nrm;
      if ((rt != 0.0) || (nrm != 0.0)) {
        ztest = sqrt(rt * rt + nrm);
        if (rt < 0.0) {
          ztest = -ztest;
        }

        ztest = nrm / (rt + ztest);
      } else {
        ztest = 0.0;
      }

      f = (sqds + f) * (sqds - f) + ztest;
      nrm = sqds * (e[q] / mtmp);
      while (q + 1 <= 1) {
        eml_xrotg(&f, &nrm, &ztest, &rt);
        f = ztest * s[0] + rt * e[0];
        e[0] = ztest * e[0] - rt * s[0];
        nrm = rt * s[1];
        s[1] *= ztest;
        eml_xrot(Vf, 1, 3, ztest, rt);
        s[0] = f;
        eml_xrotg(&s[0], &nrm, &ztest, &rt);
        f = ztest * e[0] + rt * s[1];
        s[1] = -rt * e[0] + ztest * s[1];
        nrm = rt * e[1];
        e[1] *= ztest;
        eml_xrot(U, 1, 3, ztest, rt);
        q = 1;
      }

      e[0] = f;
      iter++;
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
        eml_xscal(-1.0, Vf, 1 + (q << 1));
      }

      while ((q + 1 < 2) && (s[0] < s[1])) {
        rt = s[0];
        s[0] = s[1];
        s[1] = rt;
        eml_xswap(Vf);
        eml_xswap(U);
        q = 1;
      }

      iter = 0;
      m--;
      break;
    }
  }

  for (kase = 0; kase < 2; kase++) {
    S[kase] = s[kase];
    for (ixstart = 0; ixstart < 2; ixstart++) {
      V[ixstart + (kase << 1)] = Vf[ixstart + (kase << 1)];
    }
  }
}

//
// Arguments    : const double x[4]
// Return Type  : double
//
static double eml_xnrm2(const double x[4])
{
  double y;
  double scale;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 2.2250738585072014E-308;
  for (k = 0; k < 2; k++) {
    absxk = fabs(x[k]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

//
// Arguments    : double x[4]
//                int ix0
//                int iy0
//                double c
//                double s
// Return Type  : void
//
static void eml_xrot(double x[4], int ix0, int iy0, double c, double s)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 2; k++) {
    temp = c * x[ix] + s * x[iy];
    x[iy] = c * x[iy] - s * x[ix];
    x[ix] = temp;
    iy++;
    ix++;
  }
}

//
// Arguments    : double *a
//                double *b
//                double *c
//                double *s
// Return Type  : void
//
static void eml_xrotg(double *a, double *b, double *c, double *s)
{
  double roe;
  double absa;
  double absb;
  double scale;
  double ads;
  double bds;
  roe = *b;
  absa = fabs(*a);
  absb = fabs(*b);
  if (absa > absb) {
    roe = *a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    scale = 0.0;
    *b = 0.0;
  } else {
    ads = absa / scale;
    bds = absb / scale;
    scale *= sqrt(ads * ads + bds * bds);
    if (roe < 0.0) {
      scale = -scale;
    }

    *c = *a / scale;
    *s = *b / scale;
    if (absa > absb) {
      *b = *s;
    } else if (*c != 0.0) {
      *b = 1.0 / *c;
    } else {
      *b = 1.0;
    }
  }

  *a = scale;
}

//
// Arguments    : double a
//                double x[4]
//                int ix0
// Return Type  : void
//
static void eml_xscal(double a, double x[4], int ix0)
{
  int k;
  for (k = ix0; k <= ix0 + 1; k++) {
    x[k - 1] *= a;
  }
}

//
// Arguments    : double x[4]
// Return Type  : void
//
static void eml_xswap(double x[4])
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = 0;
  iy = 2;
  for (k = 0; k < 2; k++) {
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2((double)b_u0, (double)b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(double)(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

//
// Inputs:
//    x, P -  state and covariance
//    z, R - range-bearing measurements and covariances
//    idf - feature index for each z
// Arguments    : double x[3]
//                double P[9]
//                double z_data[]
//                int z_size[2]
//                const double R[4]
//                const double idf_data[]
//                const int idf_size[2]
//                const double lm[40]
// Return Type  : void
//
void EKF_update(double x[3], double P[9], double z_data[], int [2], const double
                R[4], const double idf_data[], const int idf_size[2], const
                double lm[40])
{
  double tol;
  double a;
  double dist;
  double z_predicted[2];
  double H[6];
  double X[4];
  int i4;
  double b_H[6];
  int cr;
  int vcol;
  double S[4];
  double V[4];
  double s[2];
  double U[4];
  int r;
  int ar;
  int ic;
  int ib;
  int ia;
  double K[6];
  signed char I[9];
  double b_I[9];
  double c_I[9];

  //  Outputs:
  //    x, P - updated state and covariance
  //  <---------------------------- TO DO -------------------------->
  if (idf_size[1] == 0) {
  } else {
    pi_to_pi(&z_data[1]);
    tol = x[0] - lm[((int)idf_data[0] - 1) << 1];
    a = x[1] - lm[1 + (((int)idf_data[0] - 1) << 1)];
    dist = sqrt(tol * tol + a * a);
    tol = rt_atan2d_snf(lm[1 + (((int)idf_data[0] - 1) << 1)] - x[1], lm[((int)
      idf_data[0] - 1) << 1] - x[0]) - x[2];
    pi_to_pi(&tol);
    z_predicted[0] = dist;
    z_predicted[1] = tol;
    H[0] = (x[0] - lm[((int)idf_data[0] - 1) << 1]) / dist;
    H[2] = (x[1] - lm[1 + (((int)idf_data[0] - 1) << 1)]) / dist;
    H[4] = 0.0;
    H[1] = -(x[1] - lm[1 + (((int)idf_data[0] - 1) << 1)]) / (dist * dist);
    H[3] = (x[0] - lm[((int)idf_data[0] - 1) << 1]) / (dist * dist);
    H[5] = -1.0;
    for (i4 = 0; i4 < 4; i4++) {
      X[i4] = 0.0;
    }

    for (i4 = 0; i4 < 2; i4++) {
      for (cr = 0; cr < 3; cr++) {
        b_H[i4 + (cr << 1)] = 0.0;
        for (vcol = 0; vcol < 3; vcol++) {
          b_H[i4 + (cr << 1)] += H[i4 + (vcol << 1)] * P[vcol + 3 * cr];
        }
      }
    }

    for (i4 = 0; i4 < 2; i4++) {
      for (cr = 0; cr < 2; cr++) {
        tol = 0.0;
        for (vcol = 0; vcol < 3; vcol++) {
          tol += b_H[i4 + (vcol << 1)] * H[cr + (vcol << 1)];
        }

        S[i4 + (cr << 1)] = tol + R[i4 + (cr << 1)];
      }
    }

    eml_xgesvd(S, U, s, V);
    for (i4 = 0; i4 < 4; i4++) {
      S[i4] = 0.0;
    }

    for (cr = 0; cr < 2; cr++) {
      S[cr + (cr << 1)] = s[cr];
    }

    tol = 2.0 * S[0] * 2.2204460492503131E-16;
    r = 0;
    cr = 0;
    while ((cr + 1 < 3) && (S[cr + (cr << 1)] > tol)) {
      r++;
      cr++;
    }

    if (r > 0) {
      vcol = 0;
      for (ar = 0; ar + 1 <= r; ar++) {
        tol = 1.0 / S[ar + (ar << 1)];
        for (cr = vcol; cr + 1 <= vcol + 2; cr++) {
          V[cr] *= tol;
        }

        vcol += 2;
      }

      for (cr = 0; cr < 4; cr += 2) {
        for (ic = cr; ic + 1 <= cr + 2; ic++) {
          X[ic] = 0.0;
        }
      }

      vcol = -1;
      for (cr = 0; cr < 4; cr += 2) {
        ar = 0;
        vcol++;
        i4 = (vcol + ((r - 1) << 1)) + 1;
        for (ib = vcol; ib + 1 <= i4; ib += 2) {
          if (U[ib] != 0.0) {
            ia = ar;
            for (ic = cr; ic + 1 <= cr + 2; ic++) {
              ia++;
              X[ic] += U[ib] * V[ia - 1];
            }
          }

          ar += 2;
        }
      }
    }

    for (i4 = 0; i4 < 3; i4++) {
      for (cr = 0; cr < 2; cr++) {
        b_H[i4 + 3 * cr] = 0.0;
        for (vcol = 0; vcol < 3; vcol++) {
          b_H[i4 + 3 * cr] += P[i4 + 3 * vcol] * H[cr + (vcol << 1)];
        }
      }

      for (cr = 0; cr < 2; cr++) {
        K[i4 + 3 * cr] = 0.0;
        for (vcol = 0; vcol < 2; vcol++) {
          K[i4 + 3 * cr] += b_H[i4 + 3 * vcol] * X[vcol + (cr << 1)];
        }
      }
    }

    for (i4 = 0; i4 < 2; i4++) {
      z_predicted[i4] = z_data[i4] - z_predicted[i4];
    }

    pi_to_pi(&z_predicted[1]);
    for (i4 = 0; i4 < 3; i4++) {
      tol = 0.0;
      for (cr = 0; cr < 2; cr++) {
        tol += K[i4 + 3 * cr] * z_predicted[cr];
      }

      x[i4] += tol;
    }

    pi_to_pi(&x[2]);
    for (i4 = 0; i4 < 9; i4++) {
      I[i4] = 0;
    }

    for (cr = 0; cr < 3; cr++) {
      I[cr + 3 * cr] = 1;
    }

    for (i4 = 0; i4 < 3; i4++) {
      for (cr = 0; cr < 3; cr++) {
        tol = 0.0;
        for (vcol = 0; vcol < 2; vcol++) {
          tol += K[i4 + 3 * vcol] * H[vcol + (cr << 1)];
        }

        b_I[i4 + 3 * cr] = (double)I[i4 + 3 * cr] - tol;
      }
    }

    for (i4 = 0; i4 < 3; i4++) {
      for (cr = 0; cr < 3; cr++) {
        c_I[i4 + 3 * cr] = 0.0;
        for (vcol = 0; vcol < 3; vcol++) {
          c_I[i4 + 3 * cr] += b_I[i4 + 3 * vcol] * P[vcol + 3 * cr];
        }
      }
    }

    for (i4 = 0; i4 < 3; i4++) {
      for (cr = 0; cr < 3; cr++) {
        P[cr + 3 * i4] = c_I[cr + 3 * i4];
      }
    }
  }
}

//
// File trailer for EKF_update.cpp
//
// [EOF]
//
