//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_mixGaussEm.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 01:50:34
//

// Include Files
#include "gsa_mixGaussEm.h"
#include "gsa_bsxfun.h"
#include "gsa_mymvnpdf.h"
#include "gsa_qrsolve.h"
#include "gsa_rand.h"
#include "gsa_runGSA.h"
#include "gsa_sparse.h"
#include "gsa_sum.h"
#include "gsa_unique.h"
#include "gsa_xgeqp3.h"
#include "gsa_xgetrf.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>

// Function Declarations
static void gsa_expectation(const coder::array<double, 2U> &X, const coder::
  array<double, 2U> &model_mu, const coder::array<double, 3U> &model_Sigma,
  const coder::array<double, 2U> &model_w, coder::array<double, 2U> &R, double
  *llh);
static void gsa_initialization(const coder::array<double, 2U> &X, double init,
  coder::array<double, 2U> &R);
static void gsa_loggausspdf(coder::array<double, 2U> &X, const coder::array<
  double, 1U> &mu, const coder::array<double, 2U> &Sigma, coder::array<double,
  2U> &y);

// Function Definitions

//
// Arguments    : const coder::array<double, 2U> &X
//                const coder::array<double, 2U> &model_mu
//                const coder::array<double, 3U> &model_Sigma
//                const coder::array<double, 2U> &model_w
//                coder::array<double, 2U> &R
//                double *llh
// Return Type  : void
//
static void gsa_expectation(const coder::array<double, 2U> &X, const coder::
  array<double, 2U> &model_mu, const coder::array<double, 3U> &model_Sigma,
  const coder::array<double, 2U> &model_w, coder::array<double, 2U> &R, double
  *llh)
{
  coder::array<double, 2U> w;
  int nx;
  int i;
  int bcoef;
  int k;
  coder::array<double, 1U> y;
  int i1;
  coder::array<double, 2U> b_model_Sigma;
  int csz_idx_0;
  int acoef;
  coder::array<double, 2U> b_X;
  coder::array<double, 2U> r;
  int b_acoef;
  double b;
  boolean_T p;
  coder::array<double, 1U> T;
  coder::array<boolean_T, 1U> b_i;
  boolean_T exitg1;

  //  elseif all(size(init)==[1,n])  % init with labels
  //      label = init;
  //      k = max(label);
  //      R = full(sparse(1:n,label,1,n,k,n));
  //  else
  //      error('ERROR: init is not valid.');
  //  end
  w.set_size(1, model_w.size(1));
  nx = model_w.size(0) * model_w.size(1);
  for (i = 0; i < nx; i++) {
    w[i] = model_w[i];
  }

  R.set_size(X.size(1), model_mu.size(1));
  nx = X.size(1) * model_mu.size(1);
  for (i = 0; i < nx; i++) {
    R[i] = 0.0;
  }

  i = model_mu.size(1);
  for (bcoef = 0; bcoef < i; bcoef++) {
    nx = model_mu.size(0);
    y.set_size(model_mu.size(0));
    for (i1 = 0; i1 < nx; i1++) {
      y[i1] = model_mu[i1 + model_mu.size(0) * bcoef];
    }

    nx = model_Sigma.size(0);
    csz_idx_0 = model_Sigma.size(1);
    b_model_Sigma.set_size(model_Sigma.size(0), model_Sigma.size(1));
    for (i1 = 0; i1 < csz_idx_0; i1++) {
      for (acoef = 0; acoef < nx; acoef++) {
        b_model_Sigma[acoef + b_model_Sigma.size(0) * i1] = model_Sigma[(acoef +
          model_Sigma.size(0) * i1) + model_Sigma.size(0) * model_Sigma.size(1) *
          bcoef];
      }
    }

    b_X.set_size(X.size(0), X.size(1));
    nx = X.size(0) * X.size(1) - 1;
    for (i1 = 0; i1 <= nx; i1++) {
      b_X[i1] = X[i1];
    }

    gsa_loggausspdf(b_X, y, b_model_Sigma, r);
    nx = R.size(0);
    for (i1 = 0; i1 < nx; i1++) {
      R[i1 + R.size(0) * bcoef] = r[i1];
    }
  }

  nx = model_w.size(1);
  for (k = 0; k < nx; k++) {
    w[k] = std::log(w[k]);
  }

  b_model_Sigma.set_size(R.size(0), R.size(1));
  nx = R.size(0) * R.size(1);
  for (i = 0; i < nx; i++) {
    b_model_Sigma[i] = R[i];
  }

  csz_idx_0 = R.size(0);
  nx = w.size(1);
  acoef = R.size(1);
  if (nx < acoef) {
    acoef = nx;
  }

  if (w.size(1) == 1) {
    nx = R.size(1);
  } else if (R.size(1) == 1) {
    nx = w.size(1);
  } else if (R.size(1) == w.size(1)) {
    nx = R.size(1);
  } else {
    nx = acoef;
  }

  R.set_size(csz_idx_0, nx);
  if ((csz_idx_0 != 0) && (nx != 0)) {
    b_acoef = (b_model_Sigma.size(1) != 1);
    bcoef = (w.size(1) != 1);
    i = nx - 1;
    for (k = 0; k <= i; k++) {
      nx = b_acoef * k;
      csz_idx_0 = bcoef * k;
      acoef = (b_model_Sigma.size(0) != 1);
      i1 = R.size(0) - 1;
      for (int b_k = 0; b_k <= i1; b_k++) {
        R[b_k + R.size(0) * k] = b_model_Sigma[acoef * b_k + b_model_Sigma.size
          (0) * nx] + w[csz_idx_0];
      }
    }
  }

  //  Compute log(sum(exp(X),dim)) while avoiding numerical underflow.
  //    By default dim = 1 (columns).
  //  Written by Mo Chen (sth4nth@gmail.com).
  //  if nargin == 1,
  //      % Determine which dimension sum will use
  //      dim = find(size(X)~=1,1);
  //      if isempty(dim), dim = 1; end
  //  end
  //  subtract the largest in each dim
  nx = R.size(0) - 1;
  acoef = R.size(1);
  y.set_size(R.size(0));
  if (R.size(0) >= 1) {
    for (bcoef = 0; bcoef <= nx; bcoef++) {
      y[bcoef] = R[bcoef];
    }

    for (b_acoef = 2; b_acoef <= acoef; b_acoef++) {
      for (bcoef = 0; bcoef <= nx; bcoef++) {
        b = R[bcoef + R.size(0) * (b_acoef - 1)];
        p = ((!rtIsNaN(b)) && (rtIsNaN(y[bcoef]) || (y[bcoef] < b)));
        if (p) {
          y[bcoef] = b;
        }
      }
    }
  }

  gsa_b_bsxfun(R, y, b_model_Sigma);
  nx = b_model_Sigma.size(0) * b_model_Sigma.size(1);
  for (k = 0; k < nx; k++) {
    b_model_Sigma[k] = std::exp(b_model_Sigma[k]);
  }

  nx = b_model_Sigma.size(1);
  if ((b_model_Sigma.size(0) == 0) || (b_model_Sigma.size(1) == 0)) {
    unsigned int sz_idx_0;
    sz_idx_0 = static_cast<unsigned int>(b_model_Sigma.size(0));
    T.set_size((static_cast<int>(sz_idx_0)));
    nx = static_cast<int>(sz_idx_0);
    for (i = 0; i < nx; i++) {
      T[i] = 0.0;
    }
  } else {
    csz_idx_0 = b_model_Sigma.size(0);
    T.set_size(b_model_Sigma.size(0));
    for (b_acoef = 0; b_acoef < csz_idx_0; b_acoef++) {
      T[b_acoef] = b_model_Sigma[b_acoef];
    }

    for (k = 2; k <= nx; k++) {
      acoef = (k - 1) * csz_idx_0;
      for (b_acoef = 0; b_acoef < csz_idx_0; b_acoef++) {
        T[b_acoef] = T[b_acoef] + b_model_Sigma[acoef + b_acoef];
      }
    }
  }

  nx = T.size(0);
  for (k = 0; k < nx; k++) {
    T[k] = std::log(T[k]);
  }

  T.set_size(y.size(0));
  nx = y.size(0);
  for (i = 0; i < nx; i++) {
    T[i] = y[i] + T[i];
  }

  //  TODO: use log1p
  b_i.set_size(y.size(0));
  nx = y.size(0);
  for (i = 0; i < nx; i++) {
    b_i[i] = rtIsInf(y[i]);
  }

  p = false;
  nx = 1;
  exitg1 = false;
  while ((!exitg1) && (nx <= b_i.size(0))) {
    if (!b_i[nx - 1]) {
      nx++;
    } else {
      p = true;
      exitg1 = true;
    }
  }

  if (p) {
    nx = b_i.size(0);
    for (bcoef = 0; bcoef < nx; bcoef++) {
      if (b_i[bcoef]) {
        T[bcoef] = y[bcoef];
      }
    }
  }

  nx = T.size(0);
  if (T.size(0) == 0) {
    b = 0.0;
  } else {
    b = T[0];
    for (k = 2; k <= nx; k++) {
      b += T[k - 1];
    }
  }

  *llh = b / static_cast<double>(X.size(1));

  //  loglikelihood
  b_model_Sigma.set_size(R.size(0), R.size(1));
  nx = R.size(0) * R.size(1) - 1;
  for (i = 0; i <= nx; i++) {
    b_model_Sigma[i] = R[i];
  }

  gsa_b_bsxfun(b_model_Sigma, T, R);
  nx = R.size(0) * R.size(1);
  for (k = 0; k < nx; k++) {
    R[k] = std::exp(R[k]);
  }
}

//
// Arguments    : const coder::array<double, 2U> &X
//                double init
//                coder::array<double, 2U> &R
// Return Type  : void
//
static void gsa_initialization(const coder::array<double, 2U> &X, double init,
  coder::array<double, 2U> &R)
{
  coder::array<double, 2U> randval;
  int k;
  int nx;
  coder::array<double, 2U> y;
  gsa_coder_internal_sparse b_y;

  //  if isstruct(init)  % init with a model
  //      R  = expectation(X,init);
  //  elseif numel(init) == 1  % random init k
  randval.set_size(1, X.size(1));
  k = X.size(1);
  for (nx = 0; nx < k; nx++) {
    randval[nx] = gsa_rand();
  }

  k = randval.size(0) * randval.size(1);
  randval.set_size(1, randval.size(1));
  nx = k - 1;
  for (k = 0; k <= nx; k++) {
    randval[k] = init * randval[k];
  }

  nx = randval.size(1);
  for (k = 0; k < nx; k++) {
    randval[k] = std::ceil(randval[k]);
  }

  // label = ceil(k*rand(1,n));
  if (X.size(1) < 1) {
    y.set_size(1, 0);
  } else {
    y.set_size(1, (static_cast<int>(static_cast<double>(X.size(1)) - 1.0) + 1));
    nx = static_cast<int>(static_cast<double>(X.size(1)) - 1.0);
    for (k = 0; k <= nx; k++) {
      y[k] = static_cast<double>(k) + 1.0;
    }
  }

  b_y.gsa_init(y, randval, (static_cast<double>(X.size(1))), init, (static_cast<
    double>(X.size(1))));
  b_y.gsa_full(R);
}

//
// Arguments    : coder::array<double, 2U> &X
//                const coder::array<double, 1U> &mu
//                const coder::array<double, 2U> &Sigma
//                coder::array<double, 2U> &y
// Return Type  : void
//
static void gsa_loggausspdf(coder::array<double, 2U> &X, const coder::array<
  double, 1U> &mu, const coder::array<double, 2U> &Sigma, coder::array<double,
  2U> &y)
{
  int d;
  coder::array<double, 2U> b_X;
  int LDA;
  int i;
  int n;
  coder::array<double, 2U> A;
  int j;
  int idxAjj;
  int idxA1j;
  coder::array<double, 2U> Q;
  int i1;
  coder::array<double, 1U> tau;
  coder::array<int, 2U> jpvt;
  double ssq;
  coder::array<double, 2U> B;
  int ix;
  int iy;
  int b_i;
  int k;
  int nmj;
  int nb;
  double c;
  d = X.size(0);
  b_X.set_size(X.size(0), X.size(1));
  LDA = X.size(0) * X.size(1) - 1;
  for (i = 0; i <= LDA; i++) {
    b_X[i] = X[i];
  }

  gsa_b_bsxfun(b_X, mu, X);
  b_X.set_size(Sigma.size(0), Sigma.size(1));
  LDA = Sigma.size(0) * Sigma.size(1);
  for (i = 0; i < LDA; i++) {
    b_X[i] = Sigma[i];
  }

  n = Sigma.size(1);
  if (Sigma.size(1) != 0) {
    boolean_T exitg1;
    LDA = -1;
    j = 0;
    exitg1 = false;
    while ((!exitg1) && (j <= n - 1)) {
      idxA1j = j * n;
      idxAjj = idxA1j + j;
      ssq = 0.0;
      if (j >= 1) {
        ix = idxA1j;
        iy = idxA1j;
        for (k = 0; k < j; k++) {
          ssq += b_X[ix] * b_X[iy];
          ix++;
          iy++;
        }
      }

      ssq = b_X[idxAjj] - ssq;
      if (ssq > 0.0) {
        ssq = std::sqrt(ssq);
        b_X[idxAjj] = ssq;
        if (j + 1 < n) {
          nmj = (n - j) - 2;
          nb = (idxA1j + n) + 1;
          idxAjj += n;
          if ((j != 0) && (nmj + 1 != 0)) {
            iy = idxAjj;
            i = nb + n * nmj;
            for (b_i = nb; n < 0 ? b_i >= i : b_i <= i; b_i += n) {
              ix = idxA1j;
              c = 0.0;
              i1 = (b_i + j) - 1;
              for (k = b_i; k <= i1; k++) {
                c += b_X[k - 1] * b_X[ix];
                ix++;
              }

              b_X[iy] = b_X[iy] + -c;
              iy += n;
            }
          }

          ssq = 1.0 / ssq;
          i = (idxAjj + n * nmj) + 1;
          for (k = idxAjj + 1; n < 0 ? k >= i : k <= i; k += n) {
            b_X[k - 1] = ssq * b_X[k - 1];
          }
        }

        j++;
      } else {
        b_X[idxAjj] = ssq;
        LDA = j;
        exitg1 = true;
      }
    }

    if (LDA + 1 == 0) {
      idxAjj = Sigma.size(1);
    } else {
      idxAjj = LDA;
    }

    for (j = 0; j < idxAjj; j++) {
      i = j + 2;
      for (b_i = i; b_i <= idxAjj; b_i++) {
        b_X[(b_i + b_X.size(0) * j) - 1] = 0.0;
      }
    }

    if (1 > idxAjj) {
      LDA = 0;
      idxAjj = 0;
    } else {
      LDA = idxAjj;
    }

    A.set_size(LDA, idxAjj);
    for (i = 0; i < idxAjj; i++) {
      for (i1 = 0; i1 < LDA; i1++) {
        A[i1 + A.size(0) * i] = b_X[i1 + b_X.size(0) * i];
      }
    }

    b_X.set_size(A.size(0), A.size(1));
    LDA = A.size(0) * A.size(1);
    for (i = 0; i < LDA; i++) {
      b_X[i] = A[i];
    }
  }

  A.set_size(b_X.size(1), b_X.size(0));
  LDA = b_X.size(0);
  for (i = 0; i < LDA; i++) {
    idxAjj = b_X.size(1);
    for (i1 = 0; i1 < idxAjj; i1++) {
      A[i1 + A.size(0) * i] = b_X[i + b_X.size(0) * i1];
    }
  }

  if ((A.size(0) == 0) || (A.size(1) == 0) || ((X.size(0) == 0) || (X.size(1) ==
        0))) {
    Q.set_size(A.size(1), X.size(1));
    LDA = A.size(1) * X.size(1);
    for (i = 0; i < LDA; i++) {
      Q[i] = 0.0;
    }
  } else if (A.size(0) == A.size(1)) {
    Q.set_size(X.size(0), X.size(1));
    LDA = X.size(0) * X.size(1);
    for (i = 0; i < LDA; i++) {
      Q[i] = X[i];
    }

    LDA = A.size(0);
    n = A.size(1);
    if (LDA < n) {
      n = LDA;
    }

    LDA = X.size(0);
    if (LDA < n) {
      n = LDA;
    }

    ix = X.size(1) - 1;
    B.set_size(A.size(0), A.size(1));
    LDA = A.size(0) * A.size(1);
    for (i = 0; i < LDA; i++) {
      B[i] = A[i];
    }

    gsa_xgetrf(n, n, B, A.size(0), jpvt, &LDA);
    LDA = B.size(0);
    idxAjj = X.size(0);
    for (b_i = 0; b_i <= n - 2; b_i++) {
      i = jpvt[b_i];
      if (i != b_i + 1) {
        for (j = 0; j <= ix; j++) {
          ssq = Q[b_i + Q.size(0) * j];
          Q[b_i + Q.size(0) * j] = Q[(i + Q.size(0) * j) - 1];
          Q[(i + Q.size(0) * j) - 1] = ssq;
        }
      }
    }

    for (j = 0; j <= ix; j++) {
      nmj = idxAjj * j;
      for (k = 0; k < n; k++) {
        nb = LDA * k;
        i = k + nmj;
        if (Q[i] != 0.0) {
          i1 = k + 2;
          for (b_i = i1; b_i <= n; b_i++) {
            idxA1j = (b_i + nmj) - 1;
            Q[idxA1j] = Q[idxA1j] - Q[i] * B[(b_i + nb) - 1];
          }
        }
      }
    }

    for (j = 0; j <= ix; j++) {
      nmj = idxAjj * j - 1;
      for (k = n; k >= 1; k--) {
        nb = LDA * (k - 1) - 1;
        i = k + nmj;
        if (Q[i] != 0.0) {
          Q[i] = Q[i] / B[k + nb];
          for (b_i = 0; b_i <= k - 2; b_i++) {
            i1 = (b_i + nmj) + 1;
            Q[i1] = Q[i1] - Q[i] * B[(b_i + nb) + 1];
          }
        }
      }
    }
  } else {
    gsa_xgeqp3(A, tau, jpvt);
    idxAjj = gsa_rankFromQR(A);
    B.set_size(X.size(0), X.size(1));
    LDA = X.size(0) * X.size(1);
    for (i = 0; i < LDA; i++) {
      B[i] = X[i];
    }

    ix = X.size(1);
    Q.set_size(A.size(1), X.size(1));
    LDA = A.size(1) * X.size(1);
    for (i = 0; i < LDA; i++) {
      Q[i] = 0.0;
    }

    nmj = A.size(0);
    nb = X.size(1);
    LDA = A.size(0);
    idxA1j = A.size(1);
    if (LDA < idxA1j) {
      idxA1j = LDA;
    }

    for (j = 0; j < idxA1j; j++) {
      if (tau[j] != 0.0) {
        for (k = 0; k < nb; k++) {
          ssq = B[j + B.size(0) * k];
          i = j + 2;
          for (b_i = i; b_i <= nmj; b_i++) {
            ssq += A[(b_i + A.size(0) * j) - 1] * B[(b_i + B.size(0) * k) - 1];
          }

          ssq *= tau[j];
          if (ssq != 0.0) {
            B[j + B.size(0) * k] = B[j + B.size(0) * k] - ssq;
            i = j + 2;
            for (b_i = i; b_i <= nmj; b_i++) {
              B[(b_i + B.size(0) * k) - 1] = B[(b_i + B.size(0) * k) - 1] - A
                [(b_i + A.size(0) * j) - 1] * ssq;
            }
          }
        }
      }
    }

    for (k = 0; k < ix; k++) {
      for (b_i = 0; b_i < idxAjj; b_i++) {
        Q[(jpvt[b_i] + Q.size(0) * k) - 1] = B[b_i + B.size(0) * k];
      }

      for (j = idxAjj; j >= 1; j--) {
        i = jpvt[j - 1];
        Q[(i + Q.size(0) * k) - 1] = Q[(i + Q.size(0) * k) - 1] / A[(j + A.size
          (0) * (j - 1)) - 1];
        for (b_i = 0; b_i <= j - 2; b_i++) {
          Q[(jpvt[b_i] + Q.size(0) * k) - 1] = Q[(jpvt[b_i] + Q.size(0) * k) - 1]
            - Q[(jpvt[j - 1] + Q.size(0) * k) - 1] * A[b_i + A.size(0) * (j - 1)];
        }
      }
    }
  }

  if (Q.size(0) == 1) {
    y.set_size(1, Q.size(1));
    i = Q.size(1);
    for (j = 0; j < i; j++) {
      y[j] = Q[j] * Q[j];
    }
  } else {
    y.set_size(1, Q.size(1));
    idxAjj = Q.size(0);
    LDA = Q.size(1);
    nmj = 1;
    nb = -1;
    for (b_i = 0; b_i < LDA; b_i++) {
      idxA1j = nmj - 1;
      nmj += idxAjj;
      nb++;
      c = 0.0;
      if (idxAjj >= 1) {
        iy = idxA1j;
        for (k = 0; k < idxAjj; k++) {
          c += Q[idxA1j] * Q[iy];
          idxA1j++;
          iy++;
        }
      }

      y[nb] = c;
    }
  }

  //  quadratic term (M distance)
  if ((b_X.size(0) == 1) && (b_X.size(1) == 1)) {
    tau.set_size(1);
    tau[0] = b_X[0];
  } else {
    LDA = b_X.size(0);
    idxAjj = b_X.size(1);
    if (LDA < idxAjj) {
      idxAjj = LDA;
    }

    if (0 >= b_X.size(1)) {
      idxAjj = 0;
    }

    tau.set_size(idxAjj);
    i = idxAjj - 1;
    for (k = 0; k <= i; k++) {
      tau[k] = b_X[k + b_X.size(0) * k];
    }
  }

  idxAjj = tau.size(0);
  for (k = 0; k < idxAjj; k++) {
    tau[k] = std::log(tau[k]);
  }

  idxAjj = tau.size(0);
  if (tau.size(0) == 0) {
    ssq = 0.0;
  } else {
    ssq = tau[0];
    for (k = 2; k <= idxAjj; k++) {
      ssq += tau[k - 1];
    }
  }

  c = static_cast<double>(d) * 1.8378770664093453 + 2.0 * ssq;

  //  normalization constant
  i = y.size(0) * y.size(1);
  y.set_size(1, y.size(1));
  LDA = i - 1;
  for (i = 0; i <= LDA; i++) {
    y[i] = -(c + y[i]) / 2.0;
  }
}

//
// Perform EM algorithm for fitting the Gaussian mixture model.
//  Input:
//    X: d x n data matrix
//    init: k (1 x 1) number of components or label (1 x n, 1<=label(i)<=k) or model structure
//  Output:
//    label: 1 x n cluster label
//    model: trained model structure
//    llh: loglikelihood
//  Written by Mo Chen (sth4nth@gmail.com).
//  init
//  fprintf('EM for Gaussian mixture: running ... \n');
// Arguments    : const coder::array<double, 2U> *X_temp
//                double init
//                coder::array<double, 1U> *label
//                coder::array<double, 2U> *model_mu
//                coder::array<double, 3U> *model_Sigma
//                coder::array<double, 2U> *model_w
//                double llh_data[]
//                int llh_size[2]
// Return Type  : void
//
void gsa_mixGaussEm(const coder::array<double, 2U> &X_temp, double init, coder::
                    array<double, 1U> &label, coder::array<double, 2U> &model_mu,
                    coder::array<double, 3U> &model_Sigma, coder::array<double,
                    2U> &model_w, double llh_data[], int llh_size[2])
{
  coder::array<double, 2U> X;
  int acoef;
  int i;
  int m;
  int aoffset;
  coder::array<double, 2U> R;
  double llh[1000];
  int iter;
  int b_iter;
  boolean_T exitg1;
  coder::array<double, 1U> ex;
  coder::array<int, 1U> idx;
  coder::array<double, 2U> b_R;
  coder::array<double, 2U> nk;
  coder::array<double, 2U> c_R;
  coder::array<double, 2U> a;
  coder::array<double, 2U> Xo;
  X.set_size(X_temp.size(1), X_temp.size(0));
  acoef = X_temp.size(0);
  for (i = 0; i < acoef; i++) {
    m = X_temp.size(1);
    for (aoffset = 0; aoffset < m; aoffset++) {
      X[aoffset + X.size(0) * i] = X_temp[i + X_temp.size(0) * aoffset];
    }
  }

  for (i = 0; i < 1000; i++) {
    llh[i] = rtMinusInf;
  }

  gsa_initialization(X, init, R);
  iter = 1;
  b_iter = 1;
  exitg1 = false;
  while ((!exitg1) && (b_iter - 1 < 999)) {
    int n;
    int b_i;
    int j;
    double bkj;
    int d;
    int k;
    int bcoef;
    int coffset;
    int b_k;
    iter = b_iter;
    m = R.size(0) - 1;
    n = R.size(1);
    ex.set_size(R.size(0));
    idx.set_size(R.size(0));
    acoef = R.size(0);
    for (i = 0; i < acoef; i++) {
      idx[i] = 1;
    }

    if (R.size(0) >= 1) {
      for (b_i = 0; b_i <= m; b_i++) {
        ex[b_i] = R[b_i];
      }

      for (j = 2; j <= n; j++) {
        for (b_i = 0; b_i <= m; b_i++) {
          boolean_T p;
          bkj = R[b_i + R.size(0) * (j - 1)];
          p = ((!rtIsNaN(bkj)) && (rtIsNaN(ex[b_i]) || (ex[b_i] < bkj)));
          if (p) {
            ex[b_i] = bkj;
            idx[b_i] = j;
          }
        }
      }
    }

    label.set_size(idx.size(0));
    acoef = idx.size(0);
    for (i = 0; i < acoef; i++) {
      label[i] = idx[i];
    }

    gsa_unique_vector(label, ex);
    acoef = R.size(0) - 1;
    b_R.set_size(R.size(0), ex.size(0));
    m = ex.size(0);
    for (i = 0; i < m; i++) {
      for (aoffset = 0; aoffset <= acoef; aoffset++) {
        b_R[aoffset + b_R.size(0) * i] = R[aoffset + R.size(0) * (static_cast<
          int>(ex[i]) - 1)];
      }
    }

    R.set_size(b_R.size(0), b_R.size(1));
    acoef = b_R.size(0) * b_R.size(1);
    for (i = 0; i < acoef; i++) {
      R[i] = b_R[i];
    }

    //  remove empty clusters
    d = X.size(0);
    k = R.size(1) - 1;
    gsa_sum(R, nk);
    model_w.set_size(1, nk.size(1));
    acoef = nk.size(0) * nk.size(1);
    for (i = 0; i < acoef; i++) {
      model_w[i] = nk[i] / static_cast<double>(X.size(1));
    }

    n = X.size(0);
    acoef = X.size(1);
    bcoef = R.size(1);
    b_R.set_size(X.size(0), R.size(1));
    for (j = 0; j < bcoef; j++) {
      coffset = j * n;
      m = j * R.size(0);
      for (b_i = 0; b_i < n; b_i++) {
        b_R[coffset + b_i] = 0.0;
      }

      for (b_k = 0; b_k < acoef; b_k++) {
        aoffset = b_k * X.size(0);
        bkj = R[m + b_k];
        for (b_i = 0; b_i < n; b_i++) {
          i = coffset + b_i;
          b_R[i] = b_R[i] + X[aoffset + b_i] * bkj;
        }
      }
    }

    c_R.set_size(1, nk.size(1));
    acoef = nk.size(0) * nk.size(1);
    for (i = 0; i < acoef; i++) {
      c_R[i] = 1.0 / nk[i];
    }

    gsa_bsxfun(b_R, c_R, model_mu);
    model_Sigma.set_size(X.size(0), X.size(0), R.size(1));
    acoef = X.size(0) * X.size(0) * R.size(1);
    for (i = 0; i < acoef; i++) {
      model_Sigma[i] = 0.0;
    }

    m = R.size(0) * R.size(1);
    for (b_k = 0; b_k < m; b_k++) {
      R[b_k] = std::sqrt(R[b_k]);
    }

    for (b_i = 0; b_i <= k; b_i++) {
      acoef = model_mu.size(0);
      ex.set_size(model_mu.size(0));
      for (i = 0; i < acoef; i++) {
        ex[i] = model_mu[i + model_mu.size(0) * b_i];
      }

      acoef = R.size(0);
      c_R.set_size(1, R.size(0));
      for (i = 0; i < acoef; i++) {
        c_R[i] = R[i + R.size(0) * b_i];
      }

      m = ex.size(0);
      n = X.size(0);
      if (m < n) {
        n = m;
      }

      if (ex.size(0) == 1) {
        n = X.size(0);
      } else if (X.size(0) == 1) {
        n = ex.size(0);
      } else {
        if (X.size(0) == ex.size(0)) {
          n = X.size(0);
        }
      }

      a.set_size(n, X.size(1));
      m = ex.size(0);
      n = X.size(0);
      if (m < n) {
        n = m;
      }

      if (ex.size(0) == 1) {
        n = X.size(0);
      } else if (X.size(0) == 1) {
        n = ex.size(0);
      } else {
        if (X.size(0) == ex.size(0)) {
          n = X.size(0);
        }
      }

      if ((n != 0) && (X.size(1) != 0)) {
        m = (X.size(1) != 1);
        i = X.size(1) - 1;
        for (b_k = 0; b_k <= i; b_k++) {
          n = m * b_k;
          acoef = (X.size(0) != 1);
          bcoef = (ex.size(0) != 1);
          aoffset = a.size(0) - 1;
          for (coffset = 0; coffset <= aoffset; coffset++) {
            a[coffset + a.size(0) * b_k] = X[acoef * coffset + X.size(0) * n] -
              ex[bcoef * coffset];
          }
        }
      }

      gsa_bsxfun(a, c_R, Xo);
      n = Xo.size(0);
      acoef = Xo.size(1);
      bcoef = Xo.size(0);
      b_R.set_size(Xo.size(0), Xo.size(0));
      for (j = 0; j < bcoef; j++) {
        coffset = j * n;
        for (m = 0; m < n; m++) {
          b_R[coffset + m] = 0.0;
        }

        for (b_k = 0; b_k < acoef; b_k++) {
          aoffset = b_k * Xo.size(0);
          bkj = Xo[b_k * Xo.size(0) + j];
          for (m = 0; m < n; m++) {
            i = coffset + m;
            b_R[i] = b_R[i] + Xo[aoffset + m] * bkj;
          }
        }
      }

      a.set_size(d, d);
      acoef = d * d;
      for (i = 0; i < acoef; i++) {
        a[i] = 0.0;
      }

      if (d > 0) {
        for (b_k = 0; b_k < d; b_k++) {
          a[b_k + a.size(0) * b_k] = 1.0;
        }
      }

      bkj = nk[b_i];
      acoef = b_R.size(1);
      for (i = 0; i < acoef; i++) {
        m = b_R.size(0);
        for (aoffset = 0; aoffset < m; aoffset++) {
          model_Sigma[(aoffset + model_Sigma.size(0) * i) + model_Sigma.size(0) *
            model_Sigma.size(1) * b_i] = b_R[aoffset + b_R.size(0) * i] / bkj +
            a[aoffset + a.size(0) * i] * 1.0E-6;
        }
      }
    }

    gsa_expectation(X, model_mu, model_Sigma, model_w, R, &llh[b_iter]);
    if (std::abs(llh[b_iter] - llh[b_iter - 1]) < 1.0E-8 * std::abs(llh[b_iter]))
    {
      exitg1 = true;
    } else {
      b_iter++;
    }
  }

  llh_size[0] = 1;
  llh_size[1] = iter;
  if (0 <= iter - 1) {
    std::memcpy(&llh_data[0], &llh[1], iter * sizeof(double));
  }
}

//
// File trailer for gsa_mixGaussEm.cpp
//
// [EOF]
//
