//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_mymvnpdf.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:12:52
//

// Include Files
#include "gsa_mymvnpdf.h"
#include "gsa_combineVectorElements.h"
#include "gsa_mycholcov.h"
#include "gsa_qrsolve.h"
#include "gsa_runGSA.h"
#include "gsa_sum.h"
#include "gsa_vvarstd.h"
#include "gsa_xgeqp3.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<double, 1U> *X
//                const coder::array<double, 1U> *Mu
//                const coder::array<double, 2U> *Sigma
//                coder::array<double, 1U> *y
// Return Type  : void
//
void gsa_mymvnpdf(const coder::array<double, 1U> &X, const coder::array<double,
                  1U> &Mu, const coder::array<double, 2U> &Sigma, coder::array<
                  double, 1U> &y)
{
  int bcoef;
  int acoef;
  int csz_idx_0;
  coder::array<double, 1U> X0;
  coder::array<double, 2U> R;
  double wj;
  int mn;
  int k;
  coder::array<double, 2U> xRinv;
  coder::array<double, 1U> tau;
  coder::array<double, 2U> A;
  coder::array<int, 2U> jpvt;
  coder::array<double, 2U> Y;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  coder::array<double, 2U> z1;
  bcoef = Mu.size(0);
  acoef = X.size(0);
  if (bcoef < acoef) {
    acoef = bcoef;
  }

  if (Mu.size(0) == 1) {
    csz_idx_0 = X.size(0);
  } else if (X.size(0) == 1) {
    csz_idx_0 = Mu.size(0);
  } else if (X.size(0) == Mu.size(0)) {
    csz_idx_0 = X.size(0);
  } else {
    csz_idx_0 = acoef;
  }

  bcoef = Mu.size(0);
  acoef = X.size(0);
  if (bcoef < acoef) {
    acoef = bcoef;
  }

  if (Mu.size(0) == 1) {
    acoef = X.size(0);
  } else if (X.size(0) == 1) {
    acoef = Mu.size(0);
  } else {
    if (X.size(0) == Mu.size(0)) {
      acoef = X.size(0);
    }
  }

  X0.set_size(acoef);
  if (csz_idx_0 != 0) {
    acoef = (X.size(0) != 1);
    bcoef = (Mu.size(0) != 1);
    mn = csz_idx_0 - 1;
    for (k = 0; k <= mn; k++) {
      X0[k] = X[acoef * k] - Mu[bcoef * k];
    }
  }

  gsa_mycholcov(Sigma, R, &wj);

  //  Create array of standardized data, and compute log(sqrt(det(Sigma)))
  if ((X0.size(0) == 0) || (R.size(0) == 0)) {
    xRinv.set_size(X0.size(0), R.size(0));
    csz_idx_0 = X0.size(0) * R.size(0);
    for (mn = 0; mn < csz_idx_0; mn++) {
      xRinv[mn] = 0.0;
    }
  } else if (R.size(0) == 1) {
    csz_idx_0 = X0.size(0) - 1;
    tau.set_size(X0.size(0));
    for (mn = 0; mn <= csz_idx_0; mn++) {
      tau[mn] = X0[mn] / R[0];
    }

    X0.set_size(tau.size(0));
    csz_idx_0 = tau.size(0);
    for (mn = 0; mn < csz_idx_0; mn++) {
      X0[mn] = tau[mn];
    }

    xRinv.set_size(X0.size(0), 1);
    csz_idx_0 = X0.size(0);
    for (mn = 0; mn < csz_idx_0; mn++) {
      xRinv[mn] = X0[mn];
    }
  } else {
    int rankA;
    int nb;
    int j;
    xRinv.set_size(1, X0.size(0));
    csz_idx_0 = X0.size(0);
    for (mn = 0; mn < csz_idx_0; mn++) {
      xRinv[mn] = X0[mn];
    }

    A.set_size(R.size(1), R.size(0));
    csz_idx_0 = R.size(0);
    for (mn = 0; mn < csz_idx_0; mn++) {
      acoef = R.size(1);
      for (bcoef = 0; bcoef < acoef; bcoef++) {
        A[bcoef + A.size(0) * mn] = R[mn + R.size(0) * bcoef];
      }
    }

    gsa_xgeqp3(A, tau, jpvt);
    rankA = gsa_rankFromQR(A);
    nb = X0.size(0);
    Y.set_size(A.size(1), X0.size(0));
    csz_idx_0 = A.size(1) * X0.size(0);
    for (mn = 0; mn < csz_idx_0; mn++) {
      Y[mn] = 0.0;
    }

    csz_idx_0 = A.size(0);
    acoef = X0.size(0);
    bcoef = A.size(0);
    mn = A.size(1);
    if (bcoef < mn) {
      mn = bcoef;
    }

    for (j = 0; j < mn; j++) {
      if (tau[j] != 0.0) {
        for (k = 0; k < acoef; k++) {
          wj = xRinv[k];
          for (bcoef = 2; bcoef <= csz_idx_0; bcoef++) {
            wj += A[bcoef - 1] * xRinv[(bcoef + k) - 1];
          }

          wj *= tau[j];
          if (wj != 0.0) {
            xRinv[k] = xRinv[k] - wj;
            for (bcoef = 2; bcoef <= csz_idx_0; bcoef++) {
              xRinv[(bcoef + k) - 1] = xRinv[(bcoef + k) - 1] - A[bcoef - 1] *
                wj;
            }
          }
        }
      }
    }

    for (k = 0; k < nb; k++) {
      for (bcoef = 0; bcoef < rankA; bcoef++) {
        Y[(jpvt[bcoef] + Y.size(0) * k) - 1] = xRinv[k];
      }

      for (j = rankA; j >= 1; j--) {
        mn = jpvt[j - 1];
        Y[(mn + Y.size(0) * k) - 1] = Y[(mn + Y.size(0) * k) - 1] / A[(j +
          A.size(0) * (j - 1)) - 1];
        for (bcoef = 0; bcoef <= j - 2; bcoef++) {
          Y[(jpvt[bcoef] + Y.size(0) * k) - 1] = Y[(jpvt[bcoef] + Y.size(0) * k)
            - 1] - Y[(jpvt[j - 1] + Y.size(0) * k) - 1] * A[bcoef + A.size(0) *
            (j - 1)];
        }
      }
    }

    xRinv.set_size(Y.size(1), Y.size(0));
    csz_idx_0 = Y.size(0);
    for (mn = 0; mn < csz_idx_0; mn++) {
      acoef = Y.size(1);
      for (bcoef = 0; bcoef < acoef; bcoef++) {
        xRinv[bcoef + xRinv.size(0) * mn] = Y[mn + Y.size(0) * bcoef];
      }
    }
  }

  if ((R.size(0) == 1) && (R.size(1) == 1)) {
    X0.set_size(1);
    X0[0] = R[0];
  } else {
    bcoef = R.size(0);
    acoef = R.size(1);
    if (bcoef < acoef) {
      acoef = bcoef;
    }

    if (0 >= R.size(1)) {
      acoef = 0;
    }

    X0.set_size(acoef);
    mn = acoef - 1;
    for (k = 0; k <= mn; k++) {
      X0[k] = R[k + R.size(0) * k];
    }
  }

  acoef = X0.size(0);
  for (k = 0; k < acoef; k++) {
    X0[k] = std::log(X0[k]);
  }

  acoef = X0.size(0);
  if (X0.size(0) == 0) {
    wj = 0.0;
  } else {
    wj = X0[0];
    for (k = 2; k <= acoef; k++) {
      wj += X0[k - 1];
    }
  }

  //  The quadratic form is the inner products of the standardized data
  unnamed_idx_0 = static_cast<unsigned int>(xRinv.size(0));
  unnamed_idx_1 = static_cast<unsigned int>(xRinv.size(1));
  z1.set_size((static_cast<int>(unnamed_idx_0)), (static_cast<int>(unnamed_idx_1)));
  acoef = static_cast<int>(unnamed_idx_0) * static_cast<int>(unnamed_idx_1);
  for (k = 0; k < acoef; k++) {
    z1[k] = xRinv[k] * xRinv[k];
  }

  gsa_sum(z1, y);
  csz_idx_0 = y.size(0);
  for (mn = 0; mn < csz_idx_0; mn++) {
    y[mn] = (-0.5 * y[mn] - wj) - 0.91893853320467267;
  }

  acoef = y.size(0);
  for (k = 0; k < acoef; k++) {
    y[k] = std::exp(y[k]);
  }
}

//
// File trailer for gsa_mymvnpdf.cpp
//
// [EOF]
//
