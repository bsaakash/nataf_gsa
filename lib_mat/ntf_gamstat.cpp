//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_gamstat.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:09:55
//

// Include Files
#include "ntf_gamstat.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const double a[4]
//                double m[4]
//                double v[4]
// Return Type  : void
//
void ntf_gamstat(const double a[4], double m[4], double v[4])
{
  double d;
  if (a[0] > 0.0) {
    d = a[0] * 2.0;
    m[0] = d;
    v[0] = d * 2.0;
  } else {
    m[0] = rtNaN;
    v[0] = rtNaN;
  }

  if (a[1] > 0.0) {
    d = a[1] * 2.0;
    m[1] = d;
    v[1] = d * 2.0;
  } else {
    m[1] = rtNaN;
    v[1] = rtNaN;
  }

  if (a[2] > 0.0) {
    d = a[2] * 2.0;
    m[2] = d;
    v[2] = d * 2.0;
  } else {
    m[2] = rtNaN;
    v[2] = rtNaN;
  }

  if (a[3] > 0.0) {
    d = a[3] * 2.0;
    m[3] = d;
    v[3] = d * 2.0;
  } else {
    m[3] = rtNaN;
    v[3] = rtNaN;
  }
}

//
// File trailer for ntf_gamstat.cpp
//
// [EOF]
//
