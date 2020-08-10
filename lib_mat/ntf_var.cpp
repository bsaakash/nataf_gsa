//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_var.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_var.h"
#include "ntf_ERADist.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const coder::array<double, 1U> *x
// Return Type  : double
//
double ntf_b_var(const coder::array<double, 1U> &x)
{
  double y;
  int n;
  double xbar;
  n = x.size(0);
  if (x.size(0) == 0) {
    y = rtNaN;
  } else if (x.size(0) == 1) {
    if ((!rtIsInf(x[0])) && (!rtIsNaN(x[0]))) {
      y = 0.0;
    } else {
      y = rtNaN;
    }
  } else {
    int k;
    xbar = x[0];
    for (k = 2; k <= n; k++) {
      xbar += x[k - 1];
    }

    xbar /= static_cast<double>(x.size(0));
    y = 0.0;
    for (k = 0; k < n; k++) {
      double t;
      t = x[k] - xbar;
      y += t * t;
    }

    y /= static_cast<double>(x.size(0)) - 1.0;
  }

  return y;
}

//
// Arguments    : const coder::array<double, 1U> *x
// Return Type  : double
//
double ntf_var(const coder::array<double, 1U> &x)
{
  double y;
  int n;
  double xbar;
  n = x.size(0);
  if (x.size(0) == 0) {
    y = rtNaN;
  } else if (x.size(0) == 1) {
    if ((!rtIsInf(x[0])) && (!rtIsNaN(x[0]))) {
      y = 0.0;
    } else {
      y = rtNaN;
    }
  } else {
    int k;
    xbar = x[0];
    for (k = 2; k <= n; k++) {
      xbar += x[k - 1];
    }

    xbar /= static_cast<double>(x.size(0));
    y = 0.0;
    for (k = 0; k < n; k++) {
      double t;
      t = x[k] - xbar;
      y += t * t;
    }

    y /= static_cast<double>(x.size(0));
  }

  return y;
}

//
// File trailer for ntf_var.cpp
//
// [EOF]
//
