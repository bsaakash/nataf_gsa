//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_minOrMax.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_minOrMax.h"
#include "ntf_ERADist.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const coder::array<double, 1U> *x
// Return Type  : double
//
double ntf_maximum(const coder::array<double, 1U> &x)
{
  double ex;
  int n;
  n = x.size(0);
  if (x.size(0) <= 2) {
    if (x.size(0) == 1) {
      ex = x[0];
    } else if ((x[0] < x[1]) || (rtIsNaN(x[0]) && (!rtIsNaN(x[1])))) {
      ex = x[1];
    } else {
      ex = x[0];
    }
  } else {
    int idx;
    int k;
    if (!rtIsNaN(x[0])) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= x.size(0))) {
        if (!rtIsNaN(x[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      ex = x[0];
    } else {
      ex = x[idx - 1];
      idx++;
      for (k = idx; k <= n; k++) {
        double d;
        d = x[k - 1];
        if (ex < d) {
          ex = d;
        }
      }
    }
  }

  return ex;
}

//
// Arguments    : const coder::array<double, 1U> *x
// Return Type  : double
//
double ntf_minimum(const coder::array<double, 1U> &x)
{
  double ex;
  int n;
  n = x.size(0);
  if (x.size(0) <= 2) {
    if (x.size(0) == 1) {
      ex = x[0];
    } else if ((x[0] > x[1]) || (rtIsNaN(x[0]) && (!rtIsNaN(x[1])))) {
      ex = x[1];
    } else {
      ex = x[0];
    }
  } else {
    int idx;
    int k;
    if (!rtIsNaN(x[0])) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= x.size(0))) {
        if (!rtIsNaN(x[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      ex = x[0];
    } else {
      ex = x[idx - 1];
      idx++;
      for (k = idx; k <= n; k++) {
        double d;
        d = x[k - 1];
        if (ex > d) {
          ex = d;
        }
      }
    }
  }

  return ex;
}

//
// File trailer for ntf_minOrMax.cpp
//
// [EOF]
//
