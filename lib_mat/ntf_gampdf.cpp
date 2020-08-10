//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_gampdf.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_gampdf.h"
#include "ntf_ERADist.h"
#include "ntf_binodeviance.h"
#include "ntf_gammaln.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "ntf_stirlerr.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<double, 1U> *x
//                double a
//                double b
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_gampdf(const coder::array<double, 1U> &x, double a, double b, coder::
                array<double, 1U> &y)
{
  int i;
  double b_y;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int k = 0; k < i; k++) {
    if ((a >= 0.0) && (b > 0.0) && (!rtIsNaN(x[k]))) {
      double zk;
      zk = x[k] / b;
      if (zk == 0.0) {
        if (a < 1.0) {
          y[k] = rtInf;
        } else if (a > 1.0) {
          y[k] = 0.0;
        } else {
          y[k] = 1.0 / b;
        }
      } else if ((zk < 0.0) || rtIsInf(zk) || rtIsInf(a)) {
        y[k] = 0.0;
      } else if (a < 1.0) {
        if (a <= 2.2250738585072014E-308 * zk) {
          b_y = std::exp(-zk);
        } else if (zk < 2.2250738585072014E-308 * a) {
          b_y = a + 1.0;
          ntf_gammaln(&b_y);
          b_y = std::exp((a * std::log(zk) - zk) - b_y);
        } else {
          b_y = ((-0.91893853320467267 - 0.5 * std::log(a)) - ntf_stirlerr(a)) -
            ntf_binodeviance(a, zk);
          b_y = std::exp(b_y);
        }

        y[k] = b_y * std::exp(std::log(a) - std::log(zk)) / b;
      } else {
        if (a - 1.0 <= 2.2250738585072014E-308 * zk) {
          b_y = std::exp(-zk);
        } else if (zk < 2.2250738585072014E-308 * (a - 1.0)) {
          b_y = (a - 1.0) + 1.0;
          ntf_gammaln(&b_y);
          b_y = std::exp(((a - 1.0) * std::log(zk) - zk) - b_y);
        } else {
          b_y = ((-0.91893853320467267 - 0.5 * std::log(a - 1.0)) - ntf_stirlerr
                 (a - 1.0)) - ntf_binodeviance(a - 1.0, zk);
          b_y = std::exp(b_y);
        }

        y[k] = b_y / b;
      }
    } else {
      y[k] = rtNaN;
    }
  }
}

//
// File trailer for ntf_gampdf.cpp
//
// [EOF]
//
