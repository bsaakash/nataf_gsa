//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_mrdivide_helper.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 01:50:34
//

// Include Files
#include "gsa_mrdivide_helper.h"
#include "gsa_mymvnpdf.h"
#include "gsa_qrsolve.h"
#include "gsa_runGSA.h"
#include "gsa_sum.h"
#include "gsa_xgeqp3.h"
#include "gsa_xgetrf.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : coder::array<double, 2U> *A
//                const coder::array<double, 2U> *B
// Return Type  : void
//
void gsa_mrdiv(coder::array<double, 2U> &A, const coder::array<double, 2U> &B)
{
  coder::array<double, 1U> b_B;
  coder::array<double, 2U> b_A;
  coder::array<int, 2U> jpvt;
  int jAcol;
  coder::array<double, 1U> tau;
  coder::array<double, 1U> Y;
  double wj;
  if ((A.size(1) == 0) || ((B.size(0) == 0) || (B.size(1) == 0))) {
    int m;
    A.set_size(1, B.size(0));
    m = B.size(0);
    for (int i = 0; i < m; i++) {
      A[i] = 0.0;
    }
  } else if (B.size(0) == B.size(1)) {
    int mn;
    int m;
    int i;
    int j;
    int rankA;
    mn = B.size(1);
    b_A.set_size(B.size(0), B.size(1));
    m = B.size(0) * B.size(1);
    for (i = 0; i < m; i++) {
      b_A[i] = B[i];
    }

    gsa_xgetrf(B.size(1), B.size(1), b_A, B.size(1), jpvt, &jAcol);
    if (A.size(1) != 0) {
      for (j = 0; j < mn; j++) {
        jAcol = mn * j;
        for (m = 0; m < j; m++) {
          i = m + jAcol;
          if (b_A[i] != 0.0) {
            A[j] = A[j] - b_A[i] * A[m];
          }
        }

        A[j] = 1.0 / b_A[j + jAcol] * A[j];
      }
    }

    if (A.size(1) != 0) {
      for (j = mn; j >= 1; j--) {
        jAcol = mn * (j - 1) - 1;
        i = j + 1;
        for (m = i; m <= mn; m++) {
          rankA = m + jAcol;
          if (b_A[rankA] != 0.0) {
            A[j - 1] = A[j - 1] - b_A[rankA] * A[m - 1];
          }
        }
      }
    }

    i = B.size(1) - 1;
    for (j = i; j >= 1; j--) {
      rankA = jpvt[j - 1];
      if (rankA != j) {
        wj = A[j - 1];
        A[j - 1] = A[rankA - 1];
        A[rankA - 1] = wj;
      }
    }
  } else {
    int mn;
    int m;
    int i;
    int j;
    int rankA;
    b_B.set_size(A.size(1));
    m = A.size(1);
    for (i = 0; i < m; i++) {
      b_B[i] = A[i];
    }

    b_A.set_size(B.size(1), B.size(0));
    m = B.size(0);
    for (i = 0; i < m; i++) {
      jAcol = B.size(1);
      for (rankA = 0; rankA < jAcol; rankA++) {
        b_A[rankA + b_A.size(0) * i] = B[i + B.size(0) * rankA];
      }
    }

    gsa_xgeqp3(b_A, tau, jpvt);
    rankA = gsa_rankFromQR(b_A);
    Y.set_size(b_A.size(1));
    m = b_A.size(1);
    for (i = 0; i < m; i++) {
      Y[i] = 0.0;
    }

    m = b_A.size(0);
    jAcol = b_A.size(0);
    mn = b_A.size(1);
    if (jAcol < mn) {
      mn = jAcol;
    }

    for (j = 0; j < mn; j++) {
      if (tau[j] != 0.0) {
        wj = b_B[j];
        i = j + 2;
        for (jAcol = i; jAcol <= m; jAcol++) {
          wj += b_A[(jAcol + b_A.size(0) * j) - 1] * b_B[jAcol - 1];
        }

        wj *= tau[j];
        if (wj != 0.0) {
          b_B[j] = b_B[j] - wj;
          i = j + 2;
          for (jAcol = i; jAcol <= m; jAcol++) {
            b_B[jAcol - 1] = b_B[jAcol - 1] - b_A[(jAcol + b_A.size(0) * j) - 1]
              * wj;
          }
        }
      }
    }

    for (jAcol = 0; jAcol < rankA; jAcol++) {
      Y[jpvt[jAcol] - 1] = b_B[jAcol];
    }

    for (j = rankA; j >= 1; j--) {
      i = jpvt[j - 1];
      Y[i - 1] = Y[i - 1] / b_A[(j + b_A.size(0) * (j - 1)) - 1];
      for (jAcol = 0; jAcol <= j - 2; jAcol++) {
        Y[jpvt[jAcol] - 1] = Y[jpvt[jAcol] - 1] - Y[jpvt[j - 1] - 1] * b_A[jAcol
          + b_A.size(0) * (j - 1)];
      }
    }

    A.set_size(1, Y.size(0));
    m = Y.size(0);
    for (i = 0; i < m; i++) {
      A[i] = Y[i];
    }
  }
}

//
// File trailer for gsa_mrdivide_helper.cpp
//
// [EOF]
//
