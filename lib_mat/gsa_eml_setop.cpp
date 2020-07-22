//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_eml_setop.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 01:50:34
//

// Include Files
#include "gsa_eml_setop.h"
#include "gsa_runGSA.h"
#include "gsa_sum.h"
#include "gsa_unique.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>

// Function Declarations
static double gsa_skip_to_last_equal_value(int *k, const coder::array<double, 2U>
  &x);

// Function Definitions

//
// Arguments    : int *k
//                const coder::array<double, 2U> &x
// Return Type  : double
//
static double gsa_skip_to_last_equal_value(int *k, const coder::array<double, 2U>
  &x)
{
  double xk;
  boolean_T exitg1;
  int exponent;
  xk = x[*k - 1];
  exitg1 = false;
  while ((!exitg1) && (*k < x.size(1))) {
    double absx;
    absx = std::abs(xk / 2.0);
    if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
      if (absx <= 2.2250738585072014E-308) {
        absx = 4.94065645841247E-324;
      } else {
        frexp(absx, &exponent);
        absx = std::ldexp(1.0, exponent - 53);
      }
    } else {
      absx = rtNaN;
    }

    if ((std::abs(xk - x[*k]) < absx) || (rtIsInf(x[*k]) && rtIsInf(xk) && ((x
           [*k] > 0.0) == (xk > 0.0)))) {
      (*k)++;
    } else {
      exitg1 = true;
    }
  }

  return xk;
}

//
// Arguments    : const coder::array<double, 2U> *a
//                const coder::array<double, 2U> *b
//                coder::array<double, 2U> *c
//                coder::array<int, 1U> *ia
//                int ib_size[1]
// Return Type  : void
//
void gsa_do_vectors(const coder::array<double, 2U> &a, const coder::array<double,
                    2U> &b, coder::array<double, 2U> &c, coder::array<int, 1U>
                    &ia, int ib_size[1])
{
  int na;
  int nc;
  int nia;
  int iafirst;
  int ialast;
  int iblast;
  int b_ialast;
  double ak;
  int exponent;
  na = a.size(1);
  c.set_size(1, a.size(1));
  ia.set_size(a.size(1));
  ib_size[0] = 0;
  nc = 0;
  nia = 0;
  iafirst = 0;
  ialast = 1;
  iblast = 1;
  while ((ialast <= na) && (iblast <= b.size(1))) {
    double bk;
    double absx;
    b_ialast = ialast;
    ak = gsa_skip_to_last_equal_value(&b_ialast, a);
    ialast = b_ialast;
    bk = gsa_skip_to_last_equal_value(&iblast, b);
    absx = std::abs(bk / 2.0);
    if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
      if (absx <= 2.2250738585072014E-308) {
        absx = 4.94065645841247E-324;
      } else {
        frexp(absx, &exponent);
        absx = std::ldexp(1.0, exponent - 53);
      }
    } else {
      absx = rtNaN;
    }

    if ((std::abs(bk - ak) < absx) || (rtIsInf(ak) && rtIsInf(bk) && ((ak > 0.0)
          == (bk > 0.0)))) {
      ialast = b_ialast + 1;
      iafirst = b_ialast;
      iblast++;
    } else {
      boolean_T b_b;
      if (rtIsNaN(bk)) {
        b_b = !rtIsNaN(ak);
      } else {
        b_b = ((!rtIsNaN(ak)) && (ak < bk));
      }

      if (b_b) {
        nc++;
        nia++;
        c[nc - 1] = ak;
        ia[nia - 1] = iafirst + 1;
        ialast = b_ialast + 1;
        iafirst = b_ialast;
      } else {
        iblast++;
      }
    }
  }

  while (ialast <= na) {
    iafirst = ialast;
    ak = gsa_skip_to_last_equal_value(&iafirst, a);
    nc++;
    nia++;
    c[nc - 1] = ak;
    ia[nia - 1] = ialast;
    ialast = iafirst + 1;
  }

  if (a.size(1) > 0) {
    if (1 > nia) {
      nia = 0;
    }

    ia.set_size(nia);
    if (1 > nc) {
      nc = 0;
    }

    c.set_size(c.size(0), nc);
  }
}

//
// File trailer for gsa_eml_setop.cpp
//
// [EOF]
//
