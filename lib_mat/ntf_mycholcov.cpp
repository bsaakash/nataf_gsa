//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_mycholcov.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:09:55
//

// Include Files
#include "ntf_mycholcov.h"
#include "ntf_ERANataf.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>

// Function Definitions

//
// Test for square, symmetric
// Arguments    : const coder::array<double, 2U> *Sigma
//                coder::array<double, 2U> *T
//                double *p
// Return Type  : void
//
void ntf_mycholcov(const coder::array<double, 2U> &Sigma, coder::array<double,
                   2U> &T, double *p)
{
  int nx;
  coder::array<double, 1U> x;
  int idx;
  coder::array<double, 1U> varargin_1;
  int k;
  int n;
  int i;
  double ssq;
  boolean_T exitg1;
  int exponent;
  boolean_T guard1 = false;
  double c;
  coder::array<double, 2U> b_x;
  coder::array<double, 2U> y;
  coder::array<boolean_T, 2U> c_x;
  coder::array<boolean_T, 2U> b_y;
  int iy;
  if ((Sigma.size(0) == 1) && (Sigma.size(1) == 1)) {
    x.set_size(1);
    x[0] = Sigma[0];
  } else {
    nx = Sigma.size(0);
    idx = Sigma.size(1);
    if (nx < idx) {
      idx = nx;
    }

    if (0 < Sigma.size(1)) {
      nx = idx;
    } else {
      nx = 0;
    }

    x.set_size(nx);
    i = nx - 1;
    for (k = 0; k <= i; k++) {
      x[k] = Sigma[k + Sigma.size(0) * k];
    }
  }

  nx = x.size(0);
  varargin_1.set_size(x.size(0));
  for (k = 0; k < nx; k++) {
    varargin_1[k] = std::abs(x[k]);
  }

  n = varargin_1.size(0);
  if (varargin_1.size(0) <= 2) {
    if (varargin_1.size(0) == 1) {
      ssq = varargin_1[0];
    } else if ((varargin_1[0] < varargin_1[1]) || (rtIsNaN(varargin_1[0]) &&
                (!rtIsNaN(varargin_1[1])))) {
      ssq = varargin_1[1];
    } else {
      ssq = varargin_1[0];
    }
  } else {
    if (!rtIsNaN(varargin_1[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= varargin_1.size(0))) {
        if (!rtIsNaN(varargin_1[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      ssq = varargin_1[0];
    } else {
      ssq = varargin_1[idx - 1];
      i = idx + 1;
      for (k = i; k <= n; k++) {
        c = varargin_1[k - 1];
        if (ssq < c) {
          ssq = c;
        }
      }
    }
  }

  if ((!rtIsInf(ssq)) && (!rtIsNaN(ssq))) {
    if (ssq <= 2.2250738585072014E-308) {
      ssq = 4.94065645841247E-324;
    } else {
      frexp(ssq, &exponent);
      ssq = std::ldexp(1.0, exponent - 53);
    }
  } else {
    ssq = rtNaN;
  }

  guard1 = false;
  if (Sigma.size(0) == Sigma.size(1)) {
    int i1;
    int idxA1j;
    boolean_T c_y;
    int ix;
    b_x.set_size(Sigma.size(0), Sigma.size(1));
    idx = Sigma.size(1);
    for (i = 0; i < idx; i++) {
      nx = Sigma.size(0);
      for (i1 = 0; i1 < nx; i1++) {
        b_x[i1 + b_x.size(0) * i] = Sigma[i1 + Sigma.size(0) * i] - Sigma[i +
          Sigma.size(0) * i1];
      }
    }

    nx = b_x.size(0) * b_x.size(1);
    y.set_size(b_x.size(0), b_x.size(1));
    for (k = 0; k < nx; k++) {
      y[k] = std::abs(b_x[k]);
    }

    c_x.set_size(y.size(0), y.size(1));
    ssq = static_cast<double>(Sigma.size(0)) * (10.0 * ssq);
    idx = y.size(0) * y.size(1);
    for (i = 0; i < idx; i++) {
      c_x[i] = (y[i] < ssq);
    }

    unsigned int outsize_idx_1;
    outsize_idx_1 = static_cast<unsigned int>(c_x.size(1));
    b_y.set_size(1, (static_cast<int>(outsize_idx_1)));
    idx = static_cast<int>(outsize_idx_1);
    for (i = 0; i < idx; i++) {
      b_y[i] = true;
    }

    nx = c_x.size(1);
    idx = 0;
    iy = -1;
    for (idxA1j = 0; idxA1j < nx; idxA1j++) {
      exponent = idx + c_x.size(0);
      ix = idx;
      idx += c_x.size(0);
      iy++;
      exitg1 = false;
      while ((!exitg1) && (ix + 1 <= exponent)) {
        if (!c_x[ix]) {
          b_y[iy] = false;
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    c_y = true;
    ix = 1;
    exitg1 = false;
    while ((!exitg1) && (ix <= b_y.size(1))) {
      if (!b_y[ix - 1]) {
        c_y = false;
        exitg1 = true;
      } else {
        ix++;
      }
    }

    if (c_y) {
      T.set_size(Sigma.size(0), Sigma.size(1));
      idx = Sigma.size(0) * Sigma.size(1);
      for (i = 0; i < idx; i++) {
        T[i] = Sigma[i];
      }

      n = Sigma.size(1);
      exponent = 0;
      if (Sigma.size(1) != 0) {
        int info;
        int j;
        info = -1;
        j = 0;
        exitg1 = false;
        while ((!exitg1) && (j <= n - 1)) {
          idxA1j = j * n;
          nx = idxA1j + j;
          ssq = 0.0;
          if (j >= 1) {
            ix = idxA1j;
            iy = idxA1j;
            for (k = 0; k < j; k++) {
              ssq += T[ix] * T[iy];
              ix++;
              iy++;
            }
          }

          ssq = T[nx] - ssq;
          if (ssq > 0.0) {
            ssq = std::sqrt(ssq);
            T[nx] = ssq;
            if (j + 1 < n) {
              idx = (n - j) - 2;
              exponent = (idxA1j + n) + 1;
              nx += n;
              if ((j != 0) && (idx + 1 != 0)) {
                iy = nx;
                i = exponent + n * idx;
                for (k = exponent; n < 0 ? k >= i : k <= i; k += n) {
                  ix = idxA1j;
                  c = 0.0;
                  i1 = (k + j) - 1;
                  for (int ia = k; ia <= i1; ia++) {
                    c += T[ia - 1] * T[ix];
                    ix++;
                  }

                  T[iy] = T[iy] + -c;
                  iy += n;
                }
              }

              ssq = 1.0 / ssq;
              i = (nx + n * idx) + 1;
              for (k = nx + 1; n < 0 ? k >= i : k <= i; k += n) {
                T[k - 1] = ssq * T[k - 1];
              }
            }

            j++;
          } else {
            T[nx] = ssq;
            info = j;
            exitg1 = true;
          }
        }

        exponent = info + 1;
        if (info + 1 == 0) {
          nx = Sigma.size(1);
        } else {
          nx = info;
        }

        for (j = 0; j < nx; j++) {
          i = j + 2;
          for (idxA1j = i; idxA1j <= nx; idxA1j++) {
            T[(idxA1j + T.size(0) * j) - 1] = 0.0;
          }
        }

        if (1 > nx) {
          idx = 0;
          nx = 0;
        } else {
          idx = nx;
        }

        b_x.set_size(idx, nx);
        for (i = 0; i < nx; i++) {
          for (i1 = 0; i1 < idx; i1++) {
            b_x[i1 + b_x.size(0) * i] = T[i1 + T.size(0) * i];
          }
        }

        T.set_size(b_x.size(0), b_x.size(1));
        idx = b_x.size(0) * b_x.size(1);
        for (i = 0; i < idx; i++) {
          T[i] = b_x[i];
        }
      }

      *p = exponent;
      if (exponent > 0) {
        //  Test for positive definiteness
        T.set_size(0, 0);
      }
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    T.set_size(0, 0);
    *p = rtNaN;
  }
}

//
// File trailer for ntf_mycholcov.cpp
//
// [EOF]
//
