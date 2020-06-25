//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_xgeqp3.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:12:52
//

// Include Files
#include "gsa_xgeqp3.h"
#include "gsa_runGSA.h"
#include "gsa_sum.h"
#include "gsa_xzgeqp3.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : coder::array<double, 2U> *A
//                coder::array<double, 1U> *tau
//                coder::array<int, 2U> *jpvt
// Return Type  : void
//
void gsa_xgeqp3(coder::array<double, 2U> &A, coder::array<double, 1U> &tau,
                coder::array<int, 2U> &jpvt)
{
  int n;
  int u0;
  int minmana;
  boolean_T guard1 = false;
  n = A.size(1) - 1;
  u0 = A.size(0);
  minmana = A.size(1);
  if (u0 < minmana) {
    minmana = u0;
  }

  tau.set_size(minmana);
  for (u0 = 0; u0 < minmana; u0++) {
    tau[u0] = 0.0;
  }

  guard1 = false;
  if ((A.size(0) == 0) || (A.size(1) == 0)) {
    guard1 = true;
  } else {
    u0 = A.size(0);
    minmana = A.size(1);
    if (u0 < minmana) {
      minmana = u0;
    }

    if (minmana < 1) {
      guard1 = true;
    } else {
      jpvt.set_size(1, A.size(1));
      minmana = A.size(1);
      for (u0 = 0; u0 < minmana; u0++) {
        jpvt[u0] = 0;
      }

      for (u0 = 0; u0 <= n; u0++) {
        jpvt[u0] = u0 + 1;
      }

      gsa_qrpf(A, A.size(0), A.size(1), tau, jpvt);
    }
  }

  if (guard1) {
    jpvt.set_size(1, A.size(1));
    minmana = A.size(1);
    for (u0 = 0; u0 < minmana; u0++) {
      jpvt[u0] = 0;
    }

    for (u0 = 0; u0 <= n; u0++) {
      jpvt[u0] = u0 + 1;
    }
  }
}

//
// File trailer for gsa_xgeqp3.cpp
//
// [EOF]
//
