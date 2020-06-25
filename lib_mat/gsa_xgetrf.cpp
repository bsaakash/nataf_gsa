//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_xgetrf.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:12:52
//

// Include Files
#include "gsa_xgetrf.h"
#include "gsa_combineVectorElements.h"
#include "gsa_runGSA.h"
#include "gsa_xgeqp3.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : int m
//                int n
//                coder::array<double, 2U> *A
//                int lda
//                coder::array<int, 2U> *ipiv
//                int *info
// Return Type  : void
//
void gsa_xgetrf(int m, int n, coder::array<double, 2U> &A, int lda, coder::array<
                int, 2U> &ipiv, int *info)
{
  int yk;
  int b_n;
  int k;
  int jp1j;
  int ix;
  if (m < n) {
    yk = m;
  } else {
    yk = n;
  }

  if (yk < 1) {
    b_n = 0;
  } else {
    b_n = yk;
  }

  ipiv.set_size(1, b_n);
  if (b_n > 0) {
    ipiv[0] = 1;
    yk = 1;
    for (k = 2; k <= b_n; k++) {
      yk++;
      ipiv[k - 1] = yk;
    }
  }

  *info = 0;
  if ((m >= 1) && (n >= 1)) {
    int u0;
    u0 = m - 1;
    if (u0 >= n) {
      u0 = n;
    }

    for (int j = 0; j < u0; j++) {
      int mmj;
      int b_tmp;
      double smax;
      int i;
      mmj = m - j;
      b_tmp = j * (lda + 1);
      jp1j = b_tmp + 2;
      if (mmj < 1) {
        yk = -1;
      } else {
        yk = 0;
        if (mmj > 1) {
          ix = b_tmp;
          smax = std::abs(A[b_tmp]);
          for (k = 2; k <= mmj; k++) {
            double s;
            ix++;
            s = std::abs(A[ix]);
            if (s > smax) {
              yk = k - 1;
              smax = s;
            }
          }
        }
      }

      if (A[b_tmp + yk] != 0.0) {
        if (yk != 0) {
          yk += j;
          ipiv[j] = yk + 1;
          ix = j;
          for (k = 0; k < n; k++) {
            smax = A[ix];
            A[ix] = A[yk];
            A[yk] = smax;
            ix += lda;
            yk += lda;
          }
        }

        i = b_tmp + mmj;
        for (yk = jp1j; yk <= i; yk++) {
          A[yk - 1] = A[yk - 1] / A[b_tmp];
        }
      } else {
        *info = j + 1;
      }

      b_n = n - j;
      yk = b_tmp + lda;
      jp1j = yk;
      for (int b_j = 0; b_j <= b_n - 2; b_j++) {
        smax = A[yk];
        if (A[yk] != 0.0) {
          ix = b_tmp + 1;
          i = jp1j + 2;
          k = mmj + jp1j;
          for (int ijA = i; ijA <= k; ijA++) {
            A[ijA - 1] = A[ijA - 1] + A[ix] * -smax;
            ix++;
          }
        }

        yk += lda;
        jp1j += lda;
      }
    }

    if ((*info == 0) && (m <= n) && (!(A[(m + A.size(0) * (m - 1)) - 1] != 0.0)))
    {
      *info = m;
    }
  }
}

//
// File trailer for gsa_xgetrf.cpp
//
// [EOF]
//
