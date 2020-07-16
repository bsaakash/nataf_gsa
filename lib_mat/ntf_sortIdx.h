//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_sortIdx.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//
#ifndef NTF_SORTIDX_H
#define NTF_SORTIDX_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "ntf_inataf_types.h"

// Function Declarations
extern void ntf_b_sortIdx(const double x[4], int idx[4]);
extern void ntf_c_sortIdx(coder::array<double, 1U> &x, coder::array<int, 1U>
  &idx);
extern void ntf_sortIdx(const double x[3], int idx[3]);

#endif

//
// File trailer for ntf_sortIdx.h
//
// [EOF]
//
