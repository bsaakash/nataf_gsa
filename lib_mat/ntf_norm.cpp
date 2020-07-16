//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_norm.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//

// Include Files
#include "ntf_norm.h"
#include "ntf_ERANataf.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "ntf_svd.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<double, 2U> *x
// Return Type  : double
//
double ntf_norm(const coder::array<double, 2U> &x)
{
  double y;
  coder::array<double, 1U> r;
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    y = 0.0;
  } else if ((x.size(0) == 1) || (x.size(1) == 1)) {
    int n;
    n = x.size(0) * x.size(1);
    y = 0.0;
    if (n >= 1) {
      if (n == 1) {
        y = std::abs(x[0]);
      } else {
        double absx;
        absx = 3.3121686421112381E-170;
        for (int m = 0; m < n; m++) {
          double absxk;
          absxk = std::abs(x[m]);
          if (absxk > absx) {
            double t;
            t = absx / absxk;
            y = y * t * t + 1.0;
            absx = absxk;
          } else {
            double t;
            t = absxk / absx;
            y += t * t;
          }
        }

        y = absx * std::sqrt(y);
      }
    }
  } else {
    int m;
    int n;
    m = x.size(0);
    n = x.size(1);
    y = 0.0;
    for (int j = 0; j < n; j++) {
      for (int i = 0; i < m; i++) {
        double absx;
        absx = std::abs(x[i + x.size(0) * j]);
        if (rtIsNaN(absx) || (absx > y)) {
          y = absx;
        }
      }
    }

    if ((!rtIsInf(y)) && (!rtIsNaN(y))) {
      ntf_svd(x, r);
      y = r[0];
    }
  }

  return y;
}

//
// File trailer for ntf_norm.cpp
//
// [EOF]
//
