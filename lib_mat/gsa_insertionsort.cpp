//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_insertionsort.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 21:17:14
//

// Include Files
#include "gsa_insertionsort.h"
#include "gsa_runGSA.h"
#include "gsa_unique.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : coder::array<int, 1U> *x
//                int xstart
//                int xend
//                const gsa_coder_internal_anonymous_fu *cmp
// Return Type  : void
//
void gsa_insertionsort(coder::array<int, 1U> &x, int xstart, int xend, const
  gsa_coder_internal_anonymous_fu *cmp)
{
  int i;
  i = xstart + 1;
  for (int k = i; k <= xend; k++) {
    int xc;
    int idx;
    boolean_T exitg1;
    xc = x[k - 1] - 1;
    idx = k - 2;
    exitg1 = false;
    while ((!exitg1) && (idx + 1 >= xstart)) {
      boolean_T varargout_1;
      varargout_1 = ((cmp->tunableEnvironment[0].f1[xc] <
                      cmp->tunableEnvironment[0].f1[x[idx] - 1]) ||
                     ((cmp->tunableEnvironment[0].f1[xc] ==
                       cmp->tunableEnvironment[0].f1[x[idx] - 1]) &&
                      (cmp->tunableEnvironment[1].f1[xc] <
                       cmp->tunableEnvironment[1].f1[x[idx] - 1])));
      if (varargout_1) {
        x[idx + 1] = x[idx];
        idx--;
      } else {
        exitg1 = true;
      }
    }

    x[idx + 1] = xc + 1;
  }
}

//
// File trailer for gsa_insertionsort.cpp
//
// [EOF]
//
