//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_binodeviance.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_binodeviance.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>

// Function Definitions

//
// Arguments    : double x
//                double np
// Return Type  : double
//
double ntf_binodeviance(double x, double np)
{
  double bd0;
  double v;
  double r;
  double e;
  double j;
  int exponent;
  v = x - np;
  r = x + np;
  if (std::abs(v) < 0.1 * r) {
    double vv;
    bd0 = v * v / r;
    v /= r;
    e = 2.0 * x * v;
    j = 1.0;
    vv = v * v;
    double d;
    do {
      e *= vv;
      j += 2.0;
      d = e / j;
      bd0 += d;
      v = std::abs(bd0);
      if ((!rtIsInf(v)) && (!rtIsNaN(v))) {
        if (v <= 2.2250738585072014E-308) {
          r = 4.94065645841247E-324;
        } else {
          frexp(v, &exponent);
          r = std::ldexp(1.0, exponent - 53);
        }
      } else {
        r = rtNaN;
      }
    } while (!(std::abs(d) <= r));
  } else {
    bd0 = (x * std::log(x / np) + np) - x;
  }

  return bd0;
}

//
// File trailer for ntf_binodeviance.cpp
//
// [EOF]
//
