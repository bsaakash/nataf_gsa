//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_cospiAndSinpi.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:09:55
//

// Include Files
#include "ntf_cospiAndSinpi.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double x
//                double *c
//                double *s
// Return Type  : void
//
void ntf_cospiAndSinpi(double x, double *c, double *s)
{
  boolean_T negateSinpi;
  double r;
  if (x < 0.0) {
    x = -x;
    negateSinpi = true;
  } else {
    negateSinpi = false;
  }

  if (x < 0.25) {
    *c = std::cos(x * 3.1415926535897931);
    *s = std::sin(x * 3.1415926535897931);
  } else {
    r = x - 2.0 * std::floor(x / 2.0);
    if (r < 0.25) {
      r *= 3.1415926535897931;
      *c = std::cos(r);
      *s = std::sin(r);
    } else if (r < 0.75) {
      r = 0.5 - r;
      r *= 3.1415926535897931;
      *c = std::sin(r);
      *s = std::cos(r);
    } else if (r < 1.25) {
      r = 1.0 - r;
      r *= 3.1415926535897931;
      *c = -std::cos(r);
      *s = std::sin(r);
    } else if (r < 1.75) {
      r -= 1.5;
      r *= 3.1415926535897931;
      *c = std::sin(r);
      *s = -std::cos(r);
    } else {
      r -= 2.0;
      r *= 3.1415926535897931;
      *c = std::cos(r);
      *s = std::sin(r);
    }
  }

  if (negateSinpi) {
    *s = -*s;
  }
}

//
// File trailer for ntf_cospiAndSinpi.cpp
//
// [EOF]
//
