//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_gevstat.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_gevstat.h"
#include "ntf_expm1.h"
#include "ntf_gammaln.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double k
//                double sigma
//                double mu
//                double *m
//                double *v
// Return Type  : void
//
void ntf_gevstat(double k, double sigma, double mu, double *m, double *v)
{
  double abskj;
  double d;
  if ((sigma > 0.0) && (!rtIsNaN(mu)) && (!rtIsNaN(k))) {
    abskj = std::abs(k);
    if (abskj < 1.0E-8) {
      *m = mu + 0.57721566490153231 * sigma;
      *v = 1.6449340668482264 * (sigma * sigma);
    } else if (abskj < 5.0E-6) {
      d = 1.0 - k;
      ntf_gammaln(&d);
      ntf_expm1(&d);
      *m = mu + sigma * (d / k);
      *v = 1.6449340668482264 * (sigma * sigma);
    } else if (k < 0.5) {
      abskj = 1.0 - k;
      ntf_gammaln(&abskj);
      d = abskj;
      ntf_expm1(&d);
      *m = mu + sigma * (d / k);
      d = 1.0 - 2.0 * k;
      ntf_gammaln(&d);
      ntf_expm1(&d);
      abskj *= 2.0;
      ntf_expm1(&abskj);
      *v = (d - abskj) / (k * k) * (sigma * sigma);
    } else if (k < 1.0) {
      d = 1.0 - k;
      ntf_gammaln(&d);
      ntf_expm1(&d);
      *m = mu + sigma * (d / k);
      *v = rtInf;
    } else {
      *m = rtInf;
      *v = rtInf;
    }
  } else {
    *m = rtNaN;
    *v = rtNaN;
  }
}

//
// File trailer for ntf_gevstat.cpp
//
// [EOF]
//
