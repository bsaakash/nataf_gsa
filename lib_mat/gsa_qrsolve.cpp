//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_qrsolve.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 01:50:34
//

// Include Files
#include "gsa_qrsolve.h"
#include "gsa_runGSA.h"
#include "gsa_sum.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<double, 2U> *A
// Return Type  : int
//
int gsa_rankFromQR(const coder::array<double, 2U> &A)
{
  int r;
  int minmn;
  int maxmn;
  double tol;
  r = 0;
  if (A.size(0) < A.size(1)) {
    minmn = A.size(0);
    maxmn = A.size(1);
  } else {
    minmn = A.size(1);
    maxmn = A.size(0);
  }

  if (minmn > 0) {
    tol = 2.2204460492503131E-15 * static_cast<double>(maxmn);
    if (1.4901161193847656E-8 < tol) {
      tol = 1.4901161193847656E-8;
    }

    tol *= std::abs(A[0]);
    while ((r < minmn) && (!(std::abs(A[r + A.size(0) * r]) <= tol))) {
      r++;
    }
  }

  return r;
}

//
// File trailer for gsa_qrsolve.cpp
//
// [EOF]
//
