//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_fzero.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:09:55
//
#ifndef NTF_FZERO_H
#define NTF_FZERO_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "ntf_inataf_types.h"

// Function Declarations
extern void ntf_b_fzero(const ntf_coder_internal_anonymous_fu FunFcn, double *b,
  double *fval, double *exitflag);
extern void ntf_c_fzero(const ntf_coder_internal_anonymous_fu FunFcn, double x,
  double *b, double *fval, double *exitflag);
extern void ntf_d_fzero(const ntf_b_coder_internal_anonymous_ *FunFcn, double x,
  double *b, double *fval, double *exitflag);
extern void ntf_fzero(const ntf_coder_internal_anonymous_fu FunFcn, double *b,
                      double *fval, double *exitflag);

#endif

//
// File trailer for ntf_fzero.h
//
// [EOF]
//
