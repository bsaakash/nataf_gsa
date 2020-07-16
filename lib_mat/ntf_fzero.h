//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_fzero.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
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
extern void ntf_d_fzero(const ntf_coder_internal_anonymous_fu FunFcn, double x,
  double *b, double *fval, double *exitflag);
extern void ntf_e_fzero(const double x[2], const coder::array<double, 1U>
  &varargin_1, double varargin_3, double *b, double *fval, double *exitflag);
extern void ntf_f_fzero(const ntf_d_coder_internal_anonymous_ *FunFcn, double x,
  double *b, double *fval, double *exitflag);
extern void ntf_fzero(const ntf_coder_internal_anonymous_fu FunFcn, double *b,
                      double *fval, double *exitflag);

#endif

//
// File trailer for ntf_fzero.h
//
// [EOF]
//
