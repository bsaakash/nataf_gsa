//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_sparse.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 01:50:34
//

// Include Files
#include "gsa_sparse.h"
#include "gsa_introsort.h"
#include "gsa_mixGaussEm.h"
#include "gsa_mymvnpdf.h"
#include "gsa_runGSA.h"
#include "gsa_sum.h"
#include "gsa_unique.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : coder::array<double, 2U> &y
// Return Type  : void
//
void gsa_coder_internal_sparse::gsa_full(coder::array<double, 2U> &y) const
{
  int cend;
  int i;
  y.set_size(this->m, this->n);
  cend = this->m * this->n;
  for (i = 0; i < cend; i++) {
    y[i] = 0.0;
  }

  i = this->n;
  for (int c = 0; c < i; c++) {
    int i1;
    cend = this->colidx[c + 1] - 1;
    i1 = this->colidx[c];
    for (int idx = i1; idx <= cend; idx++) {
      y[(this->rowidx[idx - 1] + y.size(0) * c) - 1] = this->d[idx - 1];
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> &ridx
//                const coder::array<double, 2U> &cidx
//                double b_m
//                double b_n
//                double nzmaxval
// Return Type  : void
//
void gsa_coder_internal_sparse::gsa_init(const coder::array<double, 2U> &ridx,
  const coder::array<double, 2U> &cidx, double b_m, double b_n, double nzmaxval)
{
  int nc;
  int ns;
  coder::array<int, 1U> ridxInt;
  int k;
  coder::array<int, 1U> cidxInt;
  coder::array<int, 1U> sortedIndices;
  gsa_coder_internal_anonymous_fu b_this;
  int i;
  int ny;
  coder::array<int, 1U> t;
  int this_tmp;
  int c;
  double val;
  nc = cidx.size(1);
  ns = ridx.size(1);
  ridxInt.set_size(ridx.size(1));
  for (k = 0; k < ns; k++) {
    ridxInt[k] = static_cast<int>(ridx[k]);
  }

  ns = cidx.size(1);
  cidxInt.set_size(cidx.size(1));
  for (k = 0; k < ns; k++) {
    cidxInt[k] = static_cast<int>(cidx[k]);
  }

  sortedIndices.set_size(cidx.size(1));
  for (k = 0; k < nc; k++) {
    sortedIndices[k] = k + 1;
  }

  b_this.tunableEnvironment[0].f1.set_size(cidxInt.size(0));
  ns = cidxInt.size(0);
  for (i = 0; i < ns; i++) {
    b_this.tunableEnvironment[0].f1[i] = cidxInt[i];
  }

  b_this.tunableEnvironment[1].f1.set_size(ridxInt.size(0));
  ns = ridxInt.size(0);
  for (i = 0; i < ns; i++) {
    b_this.tunableEnvironment[1].f1[i] = ridxInt[i];
  }

  gsa_introsort(sortedIndices, cidxInt.size(0), &b_this);
  ny = cidxInt.size(0);
  t.set_size(cidxInt.size(0));
  ns = cidxInt.size(0);
  for (i = 0; i < ns; i++) {
    t[i] = cidxInt[i];
  }

  for (k = 0; k < ny; k++) {
    cidxInt[k] = t[sortedIndices[k] - 1];
  }

  ny = ridxInt.size(0);
  t.set_size(ridxInt.size(0));
  ns = ridxInt.size(0);
  for (i = 0; i < ns; i++) {
    t[i] = ridxInt[i];
  }

  for (k = 0; k < ny; k++) {
    ridxInt[k] = t[sortedIndices[k] - 1];
  }

  this->m = static_cast<int>(b_m);
  this_tmp = static_cast<int>(b_n);
  this->n = this_tmp;
  ns = static_cast<int>(nzmaxval);
  this->d.set_size(ns);
  this->colidx.set_size((this_tmp + 1));
  this->colidx[0] = 1;
  this->rowidx.set_size(ns);
  for (i = 0; i < ns; i++) {
    this->d[i] = 0.0;
    this->rowidx[i] = 0;
  }

  ns = 0;
  for (c = 0; c < this_tmp; c++) {
    ny = c + 1;
    while ((ns + 1 <= nc) && (cidxInt[ns] == ny)) {
      this->rowidx[ns] = ridxInt[ns];
      ns++;
    }

    this->colidx[ny] = ns + 1;
  }

  for (k = 0; k < nc; k++) {
    this->d[k] = 1.0;
  }

  ns = 1;
  i = this->colidx.size(0);
  for (c = 0; c <= i - 2; c++) {
    ny = this->colidx[c];
    this->colidx[c] = ns;
    int exitg1;
    do {
      exitg1 = 0;
      k = this->colidx[c + 1];
      if (ny < k) {
        val = 0.0;
        this_tmp = this->rowidx[ny - 1];
        while ((ny < k) && (this->rowidx[ny - 1] == this_tmp)) {
          val += this->d[ny - 1];
          ny++;
        }

        if (val != 0.0) {
          this->d[ns - 1] = val;
          this->rowidx[ns - 1] = this_tmp;
          ns++;
        }
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  this->colidx[this->colidx.size(0) - 1] = ns;
}

//
// File trailer for gsa_sparse.cpp
//
// [EOF]
//
