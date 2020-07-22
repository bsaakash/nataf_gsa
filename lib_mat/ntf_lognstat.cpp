//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_lognstat.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_lognstat.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double mu
//                double sigma
//                double *m
//                double *v
// Return Type  : void
//
void ntf_lognstat(double mu, double sigma, double *m, double *v)
{
  if ((sigma > 0.0) && (!rtIsNaN(mu))) {
    double s2;
    s2 = sigma * sigma;
    *m = std::exp(mu + 0.5 * s2);
    *v = std::exp(2.0 * mu + s2) * (std::exp(s2) - 1.0);
  } else {
    *m = rtNaN;
    *v = rtNaN;
  }
}

//
// File trailer for ntf_lognstat.cpp
//
// [EOF]
//
