//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_vvarstd.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 21:17:14
//

// Include Files
#include "gsa_vvarstd.h"
#include "gsa_runGSA.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const coder::array<double, 1U> *v
//                int n
// Return Type  : double
//
double gsa_vvarstd(const coder::array<double, 1U> &v, int n)
{
  double s;
  double xbar;
  if (n == 0) {
    s = rtNaN;
  } else if (n == 1) {
    if ((!rtIsInf(v[0])) && (!rtIsNaN(v[0]))) {
      s = 0.0;
    } else {
      s = rtNaN;
    }
  } else {
    int k;
    if (v.size(0) == 0) {
      xbar = 0.0;
    } else {
      xbar = v[0];
      for (k = 2; k <= n; k++) {
        xbar += v[k - 1];
      }
    }

    xbar /= static_cast<double>(n);
    s = 0.0;
    for (k = 0; k < n; k++) {
      double t;
      t = v[k] - xbar;
      s += t * t;
    }

    s /= static_cast<double>(n - 1);
  }

  return s;
}

//
// File trailer for gsa_vvarstd.cpp
//
// [EOF]
//
