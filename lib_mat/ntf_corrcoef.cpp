//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_corrcoef.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_corrcoef.h"
#include "ntf_ERADist.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<double, 1U> *x
//                const coder::array<double, 1U> *varargin_1
//                double r[4]
// Return Type  : void
//
void ntf_corrcoef(const coder::array<double, 1U> &x, const coder::array<double,
                  1U> &varargin_1, double r[4])
{
  coder::array<double, 2U> result;
  int fm;
  int n;
  double s;
  int i;
  double d_idx_1;
  double d;
  double d1;
  result.set_size(x.size(0), 2);
  fm = x.size(0);
  for (n = 0; n < fm; n++) {
    result[n] = x[n];
  }

  fm = varargin_1.size(0);
  for (n = 0; n < fm; n++) {
    result[n + result.size(0)] = varargin_1[n];
  }

  fm = result.size(0);
  n = result.size(0) - 1;
  r[1] = 0.0;
  if (result.size(0) < 2) {
    r[0] = rtNaN;
    r[1] = rtNaN;
    r[3] = rtNaN;
  } else {
    int k;
    s = 0.0;
    for (i = 0; i <= n; i++) {
      s += result[i];
    }

    s /= static_cast<double>(result.size(0));
    for (i = 0; i <= n; i++) {
      result[i] = result[i] - s;
    }

    s = 0.0;
    for (i = 0; i <= n; i++) {
      s += result[i + result.size(0)];
    }

    s /= static_cast<double>(fm);
    for (i = 0; i <= n; i++) {
      result[i + result.size(0)] = result[i + result.size(0)] - s;
    }

    fm--;
    s = 0.0;
    for (k = 0; k <= n; k++) {
      d = result[k];
      s += d * d;
    }

    r[0] = s / static_cast<double>(fm);
    for (i = 2; i < 3; i++) {
      s = 0.0;
      for (k = 0; k <= n; k++) {
        s += result[k + result.size(0)] * result[k];
      }

      r[1] = s / static_cast<double>(fm);
    }

    s = 0.0;
    for (k = 0; k <= n; k++) {
      d = result[k + result.size(0)];
      s += d * d;
    }

    r[3] = s / static_cast<double>(fm);
  }

  s = std::sqrt(r[0]);
  d_idx_1 = std::sqrt(r[3]);
  d = r[1];
  for (i = 2; i < 3; i++) {
    d = d / d_idx_1 / s;
  }

  for (i = 2; i < 3; i++) {
    s = std::abs(d);
    if (s > 1.0) {
      d /= s;
    }

    d1 = d;
  }

  r[2] = d1;
  r[1] = d;
  if (r[0] > 0.0) {
    r[0] = 1.0;
  } else {
    r[0] = rtNaN;
  }

  if (r[3] > 0.0) {
    r[3] = 1.0;
  } else {
    r[3] = rtNaN;
  }
}

//
// File trailer for ntf_corrcoef.cpp
//
// [EOF]
//
