//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_chol.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_chol.h"
#include "ntf_ERADist.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : coder::array<double, 2U> *A
// Return Type  : int
//
int ntf_cholesky(coder::array<double, 2U> &A)
{
  int info;
  int n;
  double ssq;
  int ix;
  int iy;
  coder::array<double, 2U> b_A;
  int iac;
  n = A.size(1);
  info = 0;
  if (A.size(1) != 0) {
    int j;
    boolean_T exitg1;
    int jmax;
    int i;
    int b_i;
    int i1;
    info = 0;
    j = 0;
    exitg1 = false;
    while ((!exitg1) && (j <= n - 1)) {
      int idxAjj;
      idxAjj = j + j * n;
      ssq = 0.0;
      if (j >= 1) {
        ix = j;
        iy = j;
        for (jmax = 0; jmax < j; jmax++) {
          ssq += A[ix] * A[iy];
          ix += n;
          iy += n;
        }
      }

      ssq = A[idxAjj] - ssq;
      if (ssq > 0.0) {
        ssq = std::sqrt(ssq);
        A[idxAjj] = ssq;
        if (j + 1 < n) {
          int idxAjp1j;
          jmax = (n - j) - 1;
          i = j + 2;
          idxAjp1j = idxAjj + 2;
          if ((jmax != 0) && (j != 0)) {
            ix = j;
            b_i = (j + n * (j - 1)) + 2;
            for (iac = i; n < 0 ? iac >= b_i : iac <= b_i; iac += n) {
              double c;
              c = -A[ix];
              iy = idxAjj + 1;
              i1 = (iac + jmax) - 1;
              for (int ia = iac; ia <= i1; ia++) {
                A[iy] = A[iy] + A[ia - 1] * c;
                iy++;
              }

              ix += n;
            }
          }

          ssq = 1.0 / ssq;
          b_i = idxAjj + jmax;
          for (jmax = idxAjp1j; jmax <= b_i + 1; jmax++) {
            A[jmax - 1] = ssq * A[jmax - 1];
          }
        }

        j++;
      } else {
        A[idxAjj] = ssq;
        info = j + 1;
        exitg1 = true;
      }
    }

    if (info == 0) {
      jmax = n;
    } else {
      jmax = info - 1;
    }

    for (j = 2; j <= jmax; j++) {
      for (i = 0; i <= j - 2; i++) {
        A[i + A.size(0) * (j - 1)] = 0.0;
      }
    }

    if (1 > jmax) {
      i = 0;
      jmax = 0;
    } else {
      i = jmax;
    }

    b_A.set_size(i, jmax);
    for (b_i = 0; b_i < jmax; b_i++) {
      for (i1 = 0; i1 < i; i1++) {
        b_A[i1 + b_A.size(0) * b_i] = A[i1 + A.size(0) * b_i];
      }
    }

    A.set_size(b_A.size(0), b_A.size(1));
    i = b_A.size(1);
    for (b_i = 0; b_i < i; b_i++) {
      jmax = b_A.size(0);
      for (i1 = 0; i1 < jmax; i1++) {
        A[i1 + A.size(0) * b_i] = b_A[i1 + b_A.size(0) * b_i];
      }
    }
  }

  return info;
}

//
// File trailer for ntf_chol.cpp
//
// [EOF]
//
