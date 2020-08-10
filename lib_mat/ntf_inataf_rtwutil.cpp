//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_inataf_rtwutil.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_inataf_rtwutil.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
double ntf_rt_powd_snf(double u0, double u1)
{
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    double d;
    double d1;
    d = std::abs(u0);
    d1 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

//
// File trailer for ntf_inataf_rtwutil.cpp
//
// [EOF]
//
