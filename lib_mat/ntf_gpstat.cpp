//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_gpstat.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:09:55
//

// Include Files
#include "ntf_gpstat.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double k
//                double sigma
//                double theta
//                double *m
//                double *v
// Return Type  : void
//
void ntf_gpstat(double k, double sigma, double theta, double *m, double *v)
{
  if ((sigma > 0.0) && (!rtIsNaN(k))) {
    if (std::abs(k) < 2.2204460492503131E-16) {
      *m = sigma;
      *v = sigma * sigma;
    } else if (k >= 0.5) {
      if (k >= 1.0) {
        *m = rtInf;
      } else {
        *m = sigma / (1.0 - k);
      }

      *v = rtInf;
    } else {
      *m = sigma / (1.0 - k);
      *v = *m * *m / (1.0 - 2.0 * k);
    }

    *m += theta;
  } else {
    *m = rtNaN;
    *v = rtNaN;
  }
}

//
// File trailer for ntf_gpstat.cpp
//
// [EOF]
//
