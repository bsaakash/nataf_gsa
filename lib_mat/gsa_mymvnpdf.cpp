//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_mymvnpdf.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 06-Jul-2020 21:48:16
//

// Include Files
#include "gsa_mymvnpdf.h"
#include "gsa_combineVectorElements.h"
#include "gsa_mycholcov.h"
#include "gsa_qrsolve.h"
#include "gsa_runGSA.h"
#include "gsa_xgeqp3.h"
#include "gsa_xgetrf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<double, 2U> *X
//                const coder::array<double, 2U> *Mu
//                const coder::array<double, 2U> *Sigma
// Return Type  : double
//
double gsa_mymvnpdf(const coder::array<double, 2U> &X, const coder::array<double,
                    2U> &Mu, const coder::array<double, 2U> &Sigma)
{
  double y;
  int bcoef;
  int acoef;
  int csz_idx_1;
  coder::array<double, 2U> X0;
  coder::array<double, 2U> R;
  double wj;
  int i;
  int k;
  coder::array<double, 1U> B;
  coder::array<double, 2U> A;
  coder::array<int, 2U> jpvt;
  coder::array<double, 2U> z1;
  coder::array<double, 1U> tau;
  coder::array<double, 1U> Y;
  bcoef = Mu.size(1);
  acoef = X.size(1);
  if (bcoef < acoef) {
    acoef = bcoef;
  }

  if (Mu.size(1) == 1) {
    csz_idx_1 = X.size(1);
  } else if (X.size(1) == 1) {
    csz_idx_1 = Mu.size(1);
  } else if (X.size(1) == Mu.size(1)) {
    csz_idx_1 = X.size(1);
  } else {
    csz_idx_1 = acoef;
  }

  bcoef = Mu.size(1);
  acoef = X.size(1);
  if (bcoef < acoef) {
    acoef = bcoef;
  }

  if (Mu.size(1) == 1) {
    acoef = X.size(1);
  } else if (X.size(1) == 1) {
    acoef = Mu.size(1);
  } else {
    if (X.size(1) == Mu.size(1)) {
      acoef = X.size(1);
    }
  }

  X0.set_size(1, acoef);
  if (csz_idx_1 != 0) {
    acoef = (X.size(1) != 1);
    bcoef = (Mu.size(1) != 1);
    i = csz_idx_1 - 1;
    for (k = 0; k <= i; k++) {
      X0[k] = X[acoef * k] - Mu[bcoef * k];
    }
  }

  gsa_mycholcov(Sigma, R, &wj);

  //  Create array of standardized data, and compute log(sqrt(det(Sigma)))
  if ((X0.size(1) == 0) || ((R.size(0) == 0) || (R.size(1) == 0))) {
    X0.set_size(1, R.size(0));
    csz_idx_1 = R.size(0);
    for (i = 0; i < csz_idx_1; i++) {
      X0[i] = 0.0;
    }
  } else if (R.size(0) == R.size(1)) {
    int j;
    int rankA;
    bcoef = R.size(1);
    A.set_size(R.size(0), R.size(1));
    csz_idx_1 = R.size(0) * R.size(1);
    for (i = 0; i < csz_idx_1; i++) {
      A[i] = R[i];
    }

    gsa_xgetrf(R.size(1), R.size(1), A, R.size(1), jpvt, &acoef);
    for (j = 0; j < bcoef; j++) {
      csz_idx_1 = bcoef * j;
      for (k = 0; k < j; k++) {
        i = k + csz_idx_1;
        if (A[i] != 0.0) {
          X0[j] = X0[j] - A[i] * X0[k];
        }
      }

      X0[j] = 1.0 / A[j + csz_idx_1] * X0[j];
    }

    for (j = bcoef; j >= 1; j--) {
      csz_idx_1 = bcoef * (j - 1) - 1;
      i = j + 1;
      for (k = i; k <= bcoef; k++) {
        rankA = k + csz_idx_1;
        if (A[rankA] != 0.0) {
          X0[j - 1] = X0[j - 1] - A[rankA] * X0[k - 1];
        }
      }
    }

    i = R.size(1) - 1;
    for (j = i; j >= 1; j--) {
      rankA = jpvt[j - 1];
      if (rankA != j) {
        wj = X0[j - 1];
        X0[j - 1] = X0[rankA - 1];
        X0[rankA - 1] = wj;
      }
    }
  } else {
    int j;
    int rankA;
    B.set_size(X0.size(1));
    csz_idx_1 = X0.size(1);
    for (i = 0; i < csz_idx_1; i++) {
      B[i] = X0[i];
    }

    A.set_size(R.size(1), R.size(0));
    csz_idx_1 = R.size(0);
    for (i = 0; i < csz_idx_1; i++) {
      acoef = R.size(1);
      for (rankA = 0; rankA < acoef; rankA++) {
        A[rankA + A.size(0) * i] = R[i + R.size(0) * rankA];
      }
    }

    gsa_xgeqp3(A, tau, jpvt);
    rankA = gsa_rankFromQR(A);
    Y.set_size(A.size(1));
    csz_idx_1 = A.size(1);
    for (i = 0; i < csz_idx_1; i++) {
      Y[i] = 0.0;
    }

    csz_idx_1 = A.size(0);
    bcoef = A.size(0);
    acoef = A.size(1);
    if (bcoef < acoef) {
      acoef = bcoef;
    }

    for (j = 0; j < acoef; j++) {
      if (tau[j] != 0.0) {
        wj = B[j];
        i = j + 2;
        for (bcoef = i; bcoef <= csz_idx_1; bcoef++) {
          wj += A[(bcoef + A.size(0) * j) - 1] * B[bcoef - 1];
        }

        wj *= tau[j];
        if (wj != 0.0) {
          B[j] = B[j] - wj;
          i = j + 2;
          for (bcoef = i; bcoef <= csz_idx_1; bcoef++) {
            B[bcoef - 1] = B[bcoef - 1] - A[(bcoef + A.size(0) * j) - 1] * wj;
          }
        }
      }
    }

    for (bcoef = 0; bcoef < rankA; bcoef++) {
      Y[jpvt[bcoef] - 1] = B[bcoef];
    }

    for (j = rankA; j >= 1; j--) {
      i = jpvt[j - 1];
      Y[i - 1] = Y[i - 1] / A[(j + A.size(0) * (j - 1)) - 1];
      for (bcoef = 0; bcoef <= j - 2; bcoef++) {
        Y[jpvt[bcoef] - 1] = Y[jpvt[bcoef] - 1] - Y[jpvt[j - 1] - 1] * A[bcoef +
          A.size(0) * (j - 1)];
      }
    }

    X0.set_size(1, Y.size(0));
    csz_idx_1 = Y.size(0);
    for (i = 0; i < csz_idx_1; i++) {
      X0[i] = Y[i];
    }
  }

  //  The quadratic form is the inner products of the standardized data
  z1.set_size(1, X0.size(1));
  acoef = X0.size(1);
  for (k = 0; k < acoef; k++) {
    wj = X0[k];
    z1[k] = wj * wj;
  }

  acoef = z1.size(1);
  if (z1.size(1) == 0) {
    wj = 0.0;
  } else {
    wj = z1[0];
    for (k = 2; k <= acoef; k++) {
      wj += z1[k - 1];
    }
  }

  if ((R.size(0) == 1) && (R.size(1) == 1)) {
    Y.set_size(1);
    Y[0] = R[0];
  } else {
    bcoef = R.size(0);
    acoef = R.size(1);
    if (bcoef < acoef) {
      acoef = bcoef;
    }

    if (0 >= R.size(1)) {
      acoef = 0;
    }

    Y.set_size(acoef);
    i = acoef - 1;
    for (k = 0; k <= i; k++) {
      Y[k] = R[k + R.size(0) * k];
    }
  }

  acoef = Y.size(0);
  for (k = 0; k < acoef; k++) {
    Y[k] = std::log(Y[k]);
  }

  acoef = Y.size(0);
  if (Y.size(0) == 0) {
    y = 0.0;
  } else {
    y = Y[0];
    for (k = 2; k <= acoef; k++) {
      y += Y[k - 1];
    }
  }

  return std::exp((-0.5 * wj - y) - static_cast<double>(X.size(1)) *
                  1.8378770664093453 / 2.0);
}

//
// File trailer for gsa_mymvnpdf.cpp
//
// [EOF]
//
