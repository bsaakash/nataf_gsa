//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_runGSA_types.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 06-Jul-2020 21:48:16
//
#ifndef GSA_RUNGSA_TYPES_H
#define GSA_RUNGSA_TYPES_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#ifdef _MSC_VER

#pragma warning(push)
#pragma warning(disable : 4251)

#endif

// Type Definitions
struct gsa_cell_wrap_6
{
  coder::array<int, 1U> f1;
};

class gsa_coder_internal_anonymous_fu
{
 public:
  gsa_cell_wrap_6 tunableEnvironment[2];
};

class gsa_coder_internal_sparse
{
 public:
  void gsa_init(const coder::array<double, 2U> &ridx, const coder::array<double,
                2U> &cidx, double b_m, double b_n, double nzmaxval);
  void gsa_full(coder::array<double, 2U> &y) const;
  coder::array<double, 1U> d;
  coder::array<int, 1U> colidx;
  coder::array<int, 1U> rowidx;
  int m;
  int n;
};

struct gsa_struct_T
{
  int xstart;
  int xend;
  int depth;
};

struct gsa_emxArray_struct_T_120
{
  gsa_struct_T data[120];
  int size[1];
};

class gsa_coder_internal_stack
{
 public:
  void gsa_init(const gsa_struct_T eg, int b_n);
  gsa_emxArray_struct_T_120 d;
  int n;
};

struct gsa_cell_wrap_0
{
  coder::array<double, 2U> f1;
};

#ifdef _MSC_VER

#pragma warning(pop)

#endif
#endif

//
// File trailer for gsa_runGSA_types.h
//
// [EOF]
//
