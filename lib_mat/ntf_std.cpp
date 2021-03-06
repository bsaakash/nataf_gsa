//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_std.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_std.h"
#include "ntf_ERADist.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<double, 1U> *x
// Return Type  : double
//
double ntf_std(const coder::array<double, 1U> &x)
{
  double y;
  int kend;
  double xbar;
  coder::array<double, 1U> absdiff;
  kend = x.size(0);
  if (x.size(0) == 0) {
    y = rtNaN;
  } else if (x.size(0) == 1) {
    if ((!rtIsInf(x[0])) && (!rtIsNaN(x[0]))) {
      y = 0.0;
    } else {
      y = rtNaN;
    }
  } else {
    int k;
    xbar = x[0];
    for (k = 2; k <= kend; k++) {
      xbar += x[k - 1];
    }

    xbar /= static_cast<double>(x.size(0));
    absdiff.set_size(x.size(0));
    for (k = 0; k < kend; k++) {
      absdiff[k] = std::abs(x[k] - xbar);
    }

    y = 0.0;
    xbar = 3.3121686421112381E-170;
    kend = x.size(0);
    for (k = 0; k < kend; k++) {
      if (absdiff[k] > xbar) {
        double t;
        t = xbar / absdiff[k];
        y = y * t * t + 1.0;
        xbar = absdiff[k];
      } else {
        double t;
        t = absdiff[k] / xbar;
        y += t * t;
      }
    }

    y = xbar * std::sqrt(y);
    y /= std::sqrt(static_cast<double>(x.size(0)) - 1.0);
  }

  return y;
}

//
// File trailer for ntf_std.cpp
//
// [EOF]
//
