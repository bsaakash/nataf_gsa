//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_mod.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//

// Include Files
#include "ntf_mod.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<double, 1U> *x
//                coder::array<double, 1U> *r
// Return Type  : void
//
void ntf_b_mod(const coder::array<double, 1U> &x, coder::array<double, 1U> &r)
{
  int nx;
  r.set_size(x.size(0));
  nx = x.size(0);
  for (int k = 0; k < nx; k++) {
    double b_r;
    if (rtIsNaN(x[k]) || rtIsInf(x[k])) {
      b_r = rtNaN;
    } else if (x[k] == 0.0) {
      b_r = 0.0;
    } else {
      b_r = std::fmod(x[k], 1.0);
      if (b_r == 0.0) {
        b_r = 0.0;
      } else {
        if (x[k] < 0.0) {
          b_r++;
        }
      }
    }

    r[k] = b_r;
  }
}

//
// File trailer for ntf_mod.cpp
//
// [EOF]
//
