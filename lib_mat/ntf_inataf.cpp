//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_inataf.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
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
//                const coder::array<ntf_cell_wrap_1, 2U> *addition
//                coder::array<double, 2U> *x
//                coder::array<double, 1U> *px
// Return Type  : void
//
void inataf(const coder::array<double, 2U> &u, const coder::array<
            ntf_cell_wrap_0, 2U> &distnames, const coder::array<ntf_cell_wrap_0,
            2U> &opts, const coder::array<ntf_cell_wrap_1, 2U> &vals, const
            coder::array<double, 2U> &corrs, const coder::array<ntf_cell_wrap_1,
            2U> &addition, coder::array<double, 2U> &x, coder::array<double, 1U>
            &px)
{
  int i;
  coder::array<ntf_ERADist, 1U> M;
  int b_i;
  coder::array<double, 2U> b_vals;
  int loop_ub;
  int i1;
  ntf_ERANataf Distobj;
  coder::array<double, 2U> r;

  // == Marginal PDFs
  i = u.size(1);
  M.set_size(u.size(1));
  for (b_i = 0; b_i < i; b_i++) {
    b_vals.set_size(1, vals[vals.size(0) * b_i].f1.size(1));
    loop_ub = vals[b_i].f1.size(0) * vals[b_i].f1.size(1) - 1;
    for (i1 = 0; i1 <= loop_ub; i1++) {
      b_vals[i1] = vals[b_i].f1[i1];
    }

    M[b_i].ntf_init(distnames[b_i].f1, opts[b_i].f1, b_vals, addition[b_i].f1);
  }

  //      valB=[M{1}.mean, M{1}.std M{1}.Par'];
  //      disp(num2str(valB));
  //      valB=[M{2}.mean, M{2}.std M{2}.Par'];
  //      disp(num2str(valB));
  // == Change into Physical domain
  Distobj.ntf_init(M, corrs);
  b_vals.set_size(u.size(1), u.size(0));
  loop_ub = u.size(0);
  for (i = 0; i < loop_ub; i++) {
    b_i = u.size(1);
    for (i1 = 0; i1 < b_i; i1++) {
      b_vals[i1 + b_vals.size(0) * i] = u[i + u.size(0) * i1];
    }
  }

  Distobj.ntf_U2X(b_vals, r);
  x.set_size(r.size(1), r.size(0));
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    b_i = r.size(1);
    for (i1 = 0; i1 < b_i; i1++) {
      x[i1 + x.size(0) * i] = r[i + r.size(0) * i1];
    }
  }

  Distobj.ntf_fb_pdf(x, px);
}

//
// File trailer for ntf_inataf.cpp
//
// [EOF]
//
