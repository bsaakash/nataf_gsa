//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_gevinv.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_gevinv.h"
#include "ntf_ERADist.h"
#include "ntf_expm1.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<double, 1U> *p
//                double k
//                coder::array<double, 1U> *x
// Return Type  : void
//
void ntf_gevinv(const coder::array<double, 1U> &p, double k, coder::array<double,
                1U> &x)
{
  int i;
  double d;
  x.set_size(p.size(0));
  i = p.size(0);
  for (int j = 0; j < i; j++) {
    if ((0.0 <= p[j]) && (p[j] <= 1.0)) {
      if (p[j] == 0.0) {
        if (k <= 0.0) {
          x[j] = rtMinusInf;
        } else {
          x[j] = 0.0 - 1.0 / k;
        }
      } else if (p[j] == 1.0) {
        if (k < 0.0) {
          x[j] = 0.0 - 1.0 / k;
        } else {
          x[j] = rtInf;
        }
      } else if (std::abs(k) < 2.2204460492503131E-16) {
        x[j] = -std::log(-std::log(p[j]));
      } else {
        d = -k * std::log(-std::log(p[j]));
        ntf_expm1(&d);
        x[j] = d / k;
      }
    } else {
      x[j] = rtNaN;
    }
  }
}

//
// File trailer for ntf_gevinv.cpp
//
// [EOF]
//
