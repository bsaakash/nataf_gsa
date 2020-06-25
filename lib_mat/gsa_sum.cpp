//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_sum.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:12:52
//

// Include Files
#include "gsa_sum.h"
#include "gsa_combineVectorElements.h"
#include "gsa_runGSA.h"
#include "gsa_vvarstd.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const coder::array<double, 2U> *x
//                coder::array<double, 1U> *y
// Return Type  : void
//
void gsa_sum(const coder::array<double, 2U> &x, coder::array<double, 1U> &y)
{
  int vlen;
  vlen = x.size(1);
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    unsigned int sz_idx_0;
    sz_idx_0 = static_cast<unsigned int>(x.size(0));
    y.set_size((static_cast<int>(sz_idx_0)));
    vlen = static_cast<int>(sz_idx_0);
    for (int vstride = 0; vstride < vlen; vstride++) {
      y[vstride] = 0.0;
    }
  } else {
    int vstride;
    int j;
    vstride = x.size(0);
    y.set_size(x.size(0));
    for (j = 0; j < vstride; j++) {
      y[j] = x[j];
    }

    for (int k = 2; k <= vlen; k++) {
      int xoffset;
      xoffset = (k - 1) * vstride;
      for (j = 0; j < vstride; j++) {
        y[j] = y[j] + x[xoffset + j];
      }
    }
  }
}

//
// File trailer for gsa_sum.cpp
//
// [EOF]
//
