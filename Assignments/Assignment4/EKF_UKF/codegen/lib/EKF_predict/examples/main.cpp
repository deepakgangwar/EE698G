//
// File: main.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 02-Apr-2017 18:48:16
//

//***********************************************************************
// This automatically generated example C main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************
// Include Files
#include "rt_nonfinite.h"
#include "EKF_predict.h"
#include "EKF_update.h"
#include "main.h"
#include "EKF_predict_terminate.h"
#include "EKF_predict_initialize.h"

// Function Declarations
static void argInit_1xd2_real_T(double result_data[], int result_size[2]);
static void argInit_2x20_real_T(double result[40]);
static void argInit_2x2_real_T(double result[4]);
static void argInit_2xd2_real_T(double result_data[], int result_size[2]);
static void argInit_3x1_real_T(double result[3]);
static void argInit_3x3_real_T(double result[9]);
static double argInit_real_T();
static void main_EKF_predict();
static void main_EKF_update();

// Function Definitions

//
// Arguments    : double result_data[]
//                int result_size[2]
// Return Type  : void
//
static void argInit_1xd2_real_T(double result_data[], int result_size[2])
{
  int b_j1;

  // Set the size of the array.
  // Change this size to the value that the application requires.
  result_size[0] = 1;
  result_size[1] = 2;

  // Loop over the array to initialize each element.
  for (b_j1 = 0; b_j1 < 2; b_j1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result_data[b_j1] = argInit_real_T();
  }
}

//
// Arguments    : double result[40]
// Return Type  : void
//
static void argInit_2x20_real_T(double result[40])
{
  int b_j0;
  int b_j1;

  // Loop over the array to initialize each element.
  for (b_j0 = 0; b_j0 < 2; b_j0++) {
    for (b_j1 = 0; b_j1 < 20; b_j1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[b_j0 + (b_j1 << 1)] = argInit_real_T();
    }
  }
}

//
// Arguments    : double result[4]
// Return Type  : void
//
static void argInit_2x2_real_T(double result[4])
{
  int b_j0;
  int b_j1;

  // Loop over the array to initialize each element.
  for (b_j0 = 0; b_j0 < 2; b_j0++) {
    for (b_j1 = 0; b_j1 < 2; b_j1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[b_j0 + (b_j1 << 1)] = argInit_real_T();
    }
  }
}

//
// Arguments    : double result_data[]
//                int result_size[2]
// Return Type  : void
//
static void argInit_2xd2_real_T(double result_data[], int result_size[2])
{
  int b_j0;
  int b_j1;

  // Set the size of the array.
  // Change this size to the value that the application requires.
  result_size[0] = 2;
  result_size[1] = 2;

  // Loop over the array to initialize each element.
  for (b_j0 = 0; b_j0 < 2; b_j0++) {
    for (b_j1 = 0; b_j1 < 2; b_j1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result_data[b_j0 + 2 * b_j1] = argInit_real_T();
    }
  }
}

//
// Arguments    : double result[3]
// Return Type  : void
//
static void argInit_3x1_real_T(double result[3])
{
  int b_j0;

  // Loop over the array to initialize each element.
  for (b_j0 = 0; b_j0 < 3; b_j0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[b_j0] = argInit_real_T();
  }
}

//
// Arguments    : double result[9]
// Return Type  : void
//
static void argInit_3x3_real_T(double result[9])
{
  int b_j0;
  int b_j1;

  // Loop over the array to initialize each element.
  for (b_j0 = 0; b_j0 < 3; b_j0++) {
    for (b_j1 = 0; b_j1 < 3; b_j1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[b_j0 + 3 * b_j1] = argInit_real_T();
    }
  }
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_EKF_predict()
{
  double x[3];
  double P[9];
  double dv0[4];

  // Initialize function 'EKF_predict' input arguments.
  // Initialize function input argument 'x'.
  argInit_3x1_real_T(x);

  // Initialize function input argument 'P'.
  argInit_3x3_real_T(P);

  // Initialize function input argument 'Q'.
  // Call the entry-point 'EKF_predict'.
  argInit_2x2_real_T(dv0);
  EKF_predict(x, P, argInit_real_T(), argInit_real_T(), dv0, argInit_real_T());
}

//
// Arguments    : void
// Return Type  : void
//
static void main_EKF_update()
{
  double x[3];
  double P[9];
  int z_size[2];
  double z_data[4];
  double R[4];
  int idf_size[2];
  double idf_data[2];
  double dv1[40];

  // Initialize function 'EKF_update' input arguments.
  // Initialize function input argument 'x'.
  argInit_3x1_real_T(x);

  // Initialize function input argument 'P'.
  argInit_3x3_real_T(P);

  // Initialize function input argument 'z'.
  argInit_2xd2_real_T(z_data, z_size);

  // Initialize function input argument 'R'.
  argInit_2x2_real_T(R);

  // Initialize function input argument 'idf'.
  argInit_1xd2_real_T(idf_data, idf_size);

  // Initialize function input argument 'lm'.
  // Call the entry-point 'EKF_update'.
  argInit_2x20_real_T(dv1);
  EKF_update(x, P, z_data, z_size, R, idf_data, idf_size, dv1);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const [])
{
  // Initialize the application.
  // You do not need to do this more than one time.
  EKF_predict_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_EKF_predict();
  main_EKF_update();

  // Terminate the application.
  // You do not need to do this more than one time.
  EKF_predict_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
