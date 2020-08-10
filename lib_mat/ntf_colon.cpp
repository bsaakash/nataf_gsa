//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_colon.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_colon.h"
#include "ntf_ERADist.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double b
//                coder::array<double, 2U> *y
// Return Type  : void
//
void ntf_eml_float_colon(double b, coder::array<double, 2U> &y)
{
  double ndbl;
  double apnd;
  double cdiff;
  double u1;
  int n;
  ndbl = std::floor((b - 0.5) + 0.5);
  apnd = ndbl + 0.5;
  cdiff = (ndbl + 0.5) - b;
  u1 = std::abs(b);
  if ((0.5 > u1) || rtIsNaN(u1)) {
    u1 = 0.5;
  }

  if (std::abs(cdiff) < 4.4408920985006262E-16 * u1) {
    ndbl++;
    apnd = b;
  } else if (cdiff > 0.0) {
    apnd = (ndbl - 1.0) + 0.5;
  } else {
    ndbl++;
  }

  n = static_cast<int>(ndbl);
  y.set_size(1, n);
  if (n > 0) {
    y[0] = 0.5;
    if (n > 1) {
      int nm1d2;
      y[n - 1] = apnd;
      nm1d2 = (n - 1) / 2;
      for (int k = 0; k <= nm1d2 - 2; k++) {
        int y_tmp;
        y_tmp = k + 1;
        y[k + 1] = static_cast<double>(y_tmp) + 0.5;
        y[(n - k) - 2] = apnd - static_cast<double>(y_tmp);
      }

      if (nm1d2 << 1 == n - 1) {
        y[nm1d2] = (apnd + 0.5) / 2.0;
      } else {
        y[nm1d2] = static_cast<double>(nm1d2) + 0.5;
        y[nm1d2 + 1] = apnd - static_cast<double>(nm1d2);
      }
    }
  }
}

//
// File trailer for ntf_colon.cpp
//
// [EOF]
//
