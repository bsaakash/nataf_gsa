//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_sum.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 21:17:14
//

// Include Files
#include "gsa_sum.h"
#include "gsa_runGSA.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const coder::array<double, 2U> *x
//                coder::array<double, 2U> *y
// Return Type  : void
//
void gsa_sum(const coder::array<double, 2U> &x, coder::array<double, 2U> &y)
{
  int vlen;
  vlen = x.size(0);
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    unsigned int sz_idx_1;
    sz_idx_1 = static_cast<unsigned int>(x.size(1));
    y.set_size(1, (static_cast<int>(sz_idx_1)));
    vlen = static_cast<int>(sz_idx_1);
    for (int npages = 0; npages < vlen; npages++) {
      y[npages] = 0.0;
    }
  } else {
    int npages;
    npages = x.size(1);
    y.set_size(1, x.size(1));
    for (int i = 0; i < npages; i++) {
      int xpageoffset;
      xpageoffset = i * x.size(0);
      y[i] = x[xpageoffset];
      for (int k = 2; k <= vlen; k++) {
        y[i] = y[i] + x[(xpageoffset + k) - 1];
      }
    }
  }
}

//
// File trailer for gsa_sum.cpp
//
// [EOF]
//
