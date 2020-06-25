//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_bsxfun.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:12:52
//

// Include Files
#include "gsa_bsxfun.h"
#include "gsa_combineVectorElements.h"
#include "gsa_runGSA.h"
#include "gsa_vvarstd.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const coder::array<double, 2U> *a
//                const coder::array<double, 1U> *b
//                coder::array<double, 2U> *c
// Return Type  : void
//
void gsa_b_bsxfun(const coder::array<double, 2U> &a, const coder::array<double,
                  1U> &b, coder::array<double, 2U> &c)
{
  int acoef;
  int u1;
  acoef = b.size(0);
  u1 = a.size(0);
  if (acoef < u1) {
    u1 = acoef;
  }

  if (b.size(0) == 1) {
    u1 = a.size(0);
  } else if (a.size(0) == 1) {
    u1 = b.size(0);
  } else {
    if (a.size(0) == b.size(0)) {
      u1 = a.size(0);
    }
  }

  c.set_size(u1, a.size(1));
  acoef = b.size(0);
  u1 = a.size(0);
  if (acoef < u1) {
    u1 = acoef;
  }

  if (b.size(0) == 1) {
    u1 = a.size(0);
  } else if (a.size(0) == 1) {
    u1 = b.size(0);
  } else {
    if (a.size(0) == b.size(0)) {
      u1 = a.size(0);
    }
  }

  if ((u1 != 0) && (a.size(1) != 0)) {
    acoef = (a.size(1) != 1);
    u1 = a.size(1) - 1;
    for (int k = 0; k <= u1; k++) {
      int varargin_2;
      int b_acoef;
      int bcoef;
      int i;
      varargin_2 = acoef * k;
      b_acoef = (a.size(0) != 1);
      bcoef = (b.size(0) != 1);
      i = c.size(0) - 1;
      for (int b_k = 0; b_k <= i; b_k++) {
        c[b_k + c.size(0) * k] = a[b_acoef * b_k + a.size(0) * varargin_2] -
          b[bcoef * b_k];
      }
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *a
//                const coder::array<double, 2U> *b
//                coder::array<double, 2U> *c
// Return Type  : void
//
void gsa_bsxfun(const coder::array<double, 2U> &a, const coder::array<double, 2U>
                &b, coder::array<double, 2U> &c)
{
  int u0;
  int u1;
  int csz_idx_1;
  u0 = b.size(1);
  u1 = a.size(1);
  if (u0 < u1) {
    u1 = u0;
  }

  if (b.size(1) == 1) {
    csz_idx_1 = a.size(1);
  } else if (a.size(1) == 1) {
    csz_idx_1 = b.size(1);
  } else if (a.size(1) == b.size(1)) {
    csz_idx_1 = a.size(1);
  } else {
    csz_idx_1 = u1;
  }

  u0 = b.size(1);
  u1 = a.size(1);
  if (u0 < u1) {
    u1 = u0;
  }

  if (b.size(1) == 1) {
    u1 = a.size(1);
  } else if (a.size(1) == 1) {
    u1 = b.size(1);
  } else {
    if (a.size(1) == b.size(1)) {
      u1 = a.size(1);
    }
  }

  c.set_size(a.size(0), u1);
  if ((a.size(0) != 0) && (csz_idx_1 != 0)) {
    int acoef;
    int bcoef;
    acoef = (a.size(1) != 1);
    bcoef = (b.size(1) != 1);
    u0 = csz_idx_1 - 1;
    for (int k = 0; k <= u0; k++) {
      int b_acoef;
      int i;
      u1 = acoef * k;
      csz_idx_1 = bcoef * k;
      b_acoef = (a.size(0) != 1);
      i = c.size(0) - 1;
      for (int b_k = 0; b_k <= i; b_k++) {
        c[b_k + c.size(0) * k] = a[b_acoef * b_k + a.size(0) * u1] * b[csz_idx_1];
      }
    }
  }
}

//
// File trailer for gsa_bsxfun.cpp
//
// [EOF]
//
