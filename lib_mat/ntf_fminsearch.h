//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_fminsearch.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//
#ifndef NTF_FMINSEARCH_H
#define NTF_FMINSEARCH_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "ntf_inataf_types.h"

// Function Declarations
extern void ntf_b_fminsearch(const ntf_b_coder_internal_anonymous_ *funfcn,
  double x[2]);
extern void ntf_c_fminsearch(double x[2]);
extern void ntf_d_fminsearch(const ntf_b_coder_internal_anonymous_ *funfcn,
  double x[3]);
extern double ntf_fminsearch(const ntf_coder_internal_anonymous_fu *funfcn);

#endif

//
// File trailer for ntf_fminsearch.h
//
// [EOF]
//
