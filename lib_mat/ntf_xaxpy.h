//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_xaxpy.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:09:55
//
#ifndef NTF_XAXPY_H
#define NTF_XAXPY_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "ntf_inataf_types.h"

// Function Declarations
extern void ntf_b_xaxpy(int n, double a, const coder::array<double, 2U> &x, int
  ix0, double y[2]);
extern void ntf_c_xaxpy(int n, double a, const double x[2], coder::array<double,
  2U> &y, int iy0);
extern void ntf_xaxpy(int n, double a, int ix0, coder::array<double, 2U> &y, int
                      iy0);

#endif

//
// File trailer for ntf_xaxpy.h
//
// [EOF]
//
