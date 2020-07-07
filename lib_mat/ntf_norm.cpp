//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_norm.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 06-Jul-2020 21:30:41
//

// Include Files
#include "ntf_norm.h"
#include "ntf_ERANataf.h"
#include "ntf_inataf.h"
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
  double tmp_data[2];
  int tmp_size[1];
  if (x.size(1) == 0) {
    y = 0.0;
  } else if (x.size(1) == 1) {
    double absx;
    double absxk;
    double t;
    absx = 3.3121686421112381E-170;
    absxk = std::abs(x[0]);
    if (absxk > 3.3121686421112381E-170) {
      y = 1.0;
      absx = absxk;
    } else {
      t = absxk / 3.3121686421112381E-170;
      y = t * t;
    }

    absxk = std::abs(x[1]);
    if (absxk > absx) {
      t = absx / absxk;
      y = y * t * t + 1.0;
      absx = absxk;
    } else {
      t = absxk / absx;
      y += t * t;
    }

    y = absx * std::sqrt(y);
  } else {
    int n;
    n = x.size(1);
    y = 0.0;
    for (int j = 0; j < n; j++) {
      double absx;
      absx = std::abs(x[2 * j]);
      if (rtIsNaN(absx) || (absx > y)) {
        y = absx;
      }

      absx = std::abs(x[2 * j + 1]);
      if (rtIsNaN(absx) || (absx > y)) {
        y = absx;
      }
    }

    if ((!rtIsInf(y)) && (!rtIsNaN(y))) {
      ntf_svd(x, tmp_data, tmp_size);
      y = tmp_data[0];
    }
  }

  return y;
}

//
// File trailer for ntf_norm.cpp
//
// [EOF]
//
