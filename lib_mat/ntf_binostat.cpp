//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_binostat.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_binostat.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double n
//                double p
//                double *m
//                double *v
// Return Type  : void
//
void ntf_binostat(double n, double p, double *m, double *v)
{
  if ((p >= 0.0) && (p <= 1.0) && (n >= 0.0) && (std::floor(n) == n)) {
    *m = n * p;
    *v = *m * (1.0 - p);
  } else {
    *m = rtNaN;
    *v = rtNaN;
  }
}

//
// File trailer for ntf_binostat.cpp
//
// [EOF]
//
