//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_inataf.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:09:55
//

// Include Files
#include "ntf_inataf.h"
#include "ntf_ERADist.h"
#include "ntf_ERANataf.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const coder::array<double, 2U> *u
//                const coder::array<ntf_cell_wrap_0, 2U> *distnames
//                const coder::array<ntf_cell_wrap_0, 2U> *opts
//                const coder::array<ntf_cell_wrap_1, 2U> *vals
//                const coder::array<double, 2U> *corrs
//                coder::array<double, 2U> *x
//                coder::array<double, 1U> *px
// Return Type  : void
//
void inataf(const coder::array<double, 2U> &u, const coder::array<
            ntf_cell_wrap_0, 2U> &distnames, const coder::array<ntf_cell_wrap_0,
            2U> &opts, const coder::array<ntf_cell_wrap_1, 2U> &vals, const
            coder::array<double, 2U> &corrs, coder::array<double, 2U> &x, coder::
            array<double, 1U> &px)
{
  int i;
  coder::array<ntf_ERADist, 1U> M;
  int b_i;
  ntf_ERANataf Distobj;
  coder::array<double, 2U> b_u;
  coder::array<double, 2U> r;
  int loop_ub;
  int i1;

  // == Marginal PDFs
  i = u.size(1);
  M.set_size(u.size(1));
  for (b_i = 0; b_i < i; b_i++) {
    M[b_i].ntf_init(distnames[b_i].f1, opts[b_i].f1, vals[b_i].f1);
  }

  // == Change into Physical domain
  Distobj.ntf_init(M, corrs);
  b_u.set_size(u.size(1), u.size(0));
  b_i = u.size(0);
  for (i = 0; i < b_i; i++) {
    loop_ub = u.size(1);
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_u[i1 + b_u.size(0) * i] = u[i + u.size(0) * i1];
    }
  }

  Distobj.ntf_U2X(b_u, r);
  x.set_size(r.size(1), r.size(0));
  b_i = r.size(0);
  for (i = 0; i < b_i; i++) {
    loop_ub = r.size(1);
    for (i1 = 0; i1 < loop_ub; i1++) {
      x[i1 + x.size(0) * i] = r[i + r.size(0) * i1];
    }
  }

  Distobj.ntf_q_pdf(x, px);

  //      %== Evaluation of g
  //      g_val=zeros(size(u,1),1);
  //      coder.extrinsic('model_func');
  //      for i=1:nmc
  //          g_val(i)=model_func(x(i,:));
  //          % FEM simulation
  //      end
}

//
// File trailer for ntf_inataf.cpp
//
// [EOF]
//
