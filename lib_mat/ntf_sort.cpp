//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_sort.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//

// Include Files
#include "ntf_sort.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "ntf_sortIdx.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : coder::array<double, 1U> *x
// Return Type  : void
//
void ntf_sort(coder::array<double, 1U> &x)
{
  int dim;
  int vstride;
  int vlen;
  coder::array<double, 1U> vwork;
  int k;
  coder::array<int, 1U> b_vwork;
  dim = 0;
  if (x.size(0) != 1) {
    dim = -1;
  }

  if (dim + 2 <= 1) {
    vstride = x.size(0);
  } else {
    vstride = 1;
  }

  vlen = vstride - 1;
  vwork.set_size(vstride);
  vstride = 1;
  for (k = 0; k <= dim; k++) {
    vstride *= x.size(0);
  }

  for (dim = 0; dim < vstride; dim++) {
    for (k = 0; k <= vlen; k++) {
      vwork[k] = x[dim + k * vstride];
    }

    ntf_c_sortIdx(vwork, b_vwork);
    for (k = 0; k <= vlen; k++) {
      x[dim + k * vstride] = vwork[k];
    }
  }
}

//
// File trailer for ntf_sort.cpp
//
// [EOF]
//
