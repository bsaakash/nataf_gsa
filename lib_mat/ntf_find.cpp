//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_find.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_find.h"
#include "ntf_inataf.h"
#include "ntf_sort.h"
#include "ntf_sortIdx.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const coder::array<boolean_T, 1U> *x
//                coder::array<int, 1U> *i
// Return Type  : void
//
void ntf_eml_find(const coder::array<boolean_T, 1U> &x, coder::array<int, 1U> &i)
{
  int nx;
  int idx;
  int ii;
  boolean_T exitg1;
  nx = x.size(0);
  idx = 0;
  i.set_size(x.size(0));
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= nx - 1)) {
    if (x[ii]) {
      idx++;
      i[idx - 1] = ii + 1;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }

  if (x.size(0) == 1) {
    if (idx == 0) {
      i.set_size(0);
    }
  } else {
    if (1 > idx) {
      idx = 0;
    }

    i.set_size(idx);
  }
}

//
// File trailer for ntf_find.cpp
//
// [EOF]
//
