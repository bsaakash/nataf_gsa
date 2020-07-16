//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_svd.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//

// Include Files
#include "ntf_svd.h"
#include "ntf_ERANataf.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "ntf_xaxpy.h"
#include "ntf_xnrm2.h"
#include "ntf_xrotg.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<double, 2U> *A
//                coder::array<double, 1U> *U
// Return Type  : void
//
void ntf_svd(const coder::array<double, 2U> &A, coder::array<double, 1U> &U)
{
  coder::array<double, 2U> b_A;
  int ns;
  int i;
  int n;
  int p;
  int ix;
  int minnp;
  coder::array<double, 1U> s;
  coder::array<double, 1U> e;
  coder::array<double, 1U> work;
  int k;
  double nrm;
  double r;
  double sqds;
  double sm;
  b_A.set_size(A.size(0), A.size(1));
  ns = A.size(0) * A.size(1);
  for (i = 0; i < ns; i++) {
    b_A[i] = A[i];
  }

  n = A.size(0);
  p = A.size(1);
  ix = A.size(0) + 1;
  ns = A.size(1);
  if (ix < ns) {
    ns = ix;
  }

  ix = A.size(0);
  minnp = A.size(1);
  if (ix < minnp) {
    minnp = ix;
  }

  s.set_size(ns);
  for (i = 0; i < ns; i++) {
    s[i] = 0.0;
  }

  e.set_size(A.size(1));
  ns = A.size(1);
  for (i = 0; i < ns; i++) {
    e[i] = 0.0;
  }

  work.set_size(A.size(0));
  ns = A.size(0);
  for (i = 0; i < ns; i++) {
    work[i] = 0.0;
  }

  if ((A.size(0) != 0) && (A.size(1) != 0)) {
    int nrt;
    int nct;
    int q;
    int qp1;
    int m;
    int qq;
    double b;
    int iy;
    double snorm;
    int ii;
    if (A.size(1) > 2) {
      ix = A.size(1) - 2;
    } else {
      ix = 0;
    }

    nrt = A.size(0);
    if (ix < nrt) {
      nrt = ix;
    }

    if (A.size(0) > 1) {
      ix = A.size(0) - 1;
    } else {
      ix = 0;
    }

    nct = A.size(1);
    if (ix < nct) {
      nct = ix;
    }

    if (nct > nrt) {
      i = nct;
    } else {
      i = nrt;
    }

    for (q = 0; q < i; q++) {
      int nmq;
      boolean_T apply_transform;
      qp1 = q + 2;
      qq = (q + n * q) + 1;
      nmq = (n - q) - 1;
      apply_transform = false;
      if (q + 1 <= nct) {
        nrm = ntf_xnrm2(nmq + 1, b_A, qq);
        if (nrm > 0.0) {
          apply_transform = true;
          if (b_A[qq - 1] < 0.0) {
            b = -nrm;
            s[q] = -nrm;
          } else {
            b = nrm;
            s[q] = nrm;
          }

          if (std::abs(b) >= 1.0020841800044864E-292) {
            nrm = 1.0 / b;
            ns = qq + nmq;
            for (k = qq; k <= ns; k++) {
              b_A[k - 1] = nrm * b_A[k - 1];
            }
          } else {
            ns = qq + nmq;
            for (k = qq; k <= ns; k++) {
              b_A[k - 1] = b_A[k - 1] / s[q];
            }
          }

          b_A[qq - 1] = b_A[qq - 1] + 1.0;
          s[q] = -s[q];
        } else {
          s[q] = 0.0;
        }
      }

      for (m = qp1; m <= p; m++) {
        ns = q + n * (m - 1);
        if (apply_transform) {
          nrm = 0.0;
          if (nmq + 1 >= 1) {
            ix = qq;
            iy = ns;
            for (k = 0; k <= nmq; k++) {
              nrm += b_A[ix - 1] * b_A[iy];
              ix++;
              iy++;
            }
          }

          nrm = -(nrm / b_A[q + b_A.size(0) * q]);
          ntf_xaxpy(nmq + 1, nrm, qq, b_A, ns + 1);
        }

        e[m - 1] = b_A[ns];
      }

      if (q + 1 <= nrt) {
        ns = p - q;
        nrm = ntf_b_xnrm2(ns - 1, e, q + 2);
        if (nrm == 0.0) {
          e[q] = 0.0;
        } else {
          if (e[q + 1] < 0.0) {
            e[q] = -nrm;
          } else {
            e[q] = nrm;
          }

          nrm = e[q];
          if (std::abs(e[q]) >= 1.0020841800044864E-292) {
            nrm = 1.0 / e[q];
            ns += q;
            for (k = qp1; k <= ns; k++) {
              e[k - 1] = nrm * e[k - 1];
            }
          } else {
            ns += q;
            for (k = qp1; k <= ns; k++) {
              e[k - 1] = e[k - 1] / nrm;
            }
          }

          e[q + 1] = e[q + 1] + 1.0;
          e[q] = -e[q];
          if (q + 2 <= n) {
            for (ii = qp1; ii <= n; ii++) {
              work[ii - 1] = 0.0;
            }

            for (m = qp1; m <= p; m++) {
              ntf_b_xaxpy(nmq, e[m - 1], b_A, (q + n * (m - 1)) + 2, work, q + 2);
            }

            for (m = qp1; m <= p; m++) {
              ntf_c_xaxpy(nmq, -e[m - 1] / e[q + 1], work, q + 2, b_A, (q + n *
                (m - 1)) + 2);
            }
          }
        }
      }
    }

    ix = A.size(1);
    m = A.size(0) + 1;
    if (ix < m) {
      m = ix;
    }

    if (nct < A.size(1)) {
      s[nct] = b_A[nct + b_A.size(0) * nct];
    }

    if (A.size(0) < m) {
      s[m - 1] = 0.0;
    }

    if (nrt + 1 < m) {
      e[nrt] = b_A[nrt + b_A.size(0) * (m - 1)];
    }

    e[m - 1] = 0.0;
    qq = m;
    iy = 0;
    snorm = 0.0;
    for (q = 0; q < m; q++) {
      b = s[q];
      if (s[q] != 0.0) {
        nrm = std::abs(s[q]);
        r = s[q] / nrm;
        b = nrm;
        s[q] = nrm;
        if (q + 1 < m) {
          e[q] = e[q] / r;
        }
      }

      if ((q + 1 < m) && (e[q] != 0.0)) {
        nrm = std::abs(e[q]);
        r = nrm / e[q];
        e[q] = nrm;
        s[q + 1] = s[q + 1] * r;
      }

      nrm = std::abs(b);
      r = std::abs(e[q]);
      if ((nrm > r) || rtIsNaN(r)) {
        r = nrm;
      }

      if ((!(snorm > r)) && (!rtIsNaN(r))) {
        snorm = r;
      }
    }

    while ((m > 0) && (iy < 75)) {
      boolean_T exitg1;
      ii = m - 1;
      exitg1 = false;
      while (!(exitg1 || (ii == 0))) {
        nrm = std::abs(e[ii - 1]);
        if ((nrm <= 2.2204460492503131E-16 * (std::abs(s[ii - 1]) + std::abs
              (s[ii]))) || (nrm <= 1.0020841800044864E-292) || ((iy > 20) &&
             (nrm <= 2.2204460492503131E-16 * snorm))) {
          e[ii - 1] = 0.0;
          exitg1 = true;
        } else {
          ii--;
        }
      }

      if (ii == m - 1) {
        ns = 4;
      } else {
        ix = m;
        ns = m;
        exitg1 = false;
        while ((!exitg1) && (ns >= ii)) {
          ix = ns;
          if (ns == ii) {
            exitg1 = true;
          } else {
            nrm = 0.0;
            if (ns < m) {
              nrm = std::abs(e[ns - 1]);
            }

            if (ns > ii + 1) {
              nrm += std::abs(e[ns - 2]);
            }

            r = std::abs(s[ns - 1]);
            if ((r <= 2.2204460492503131E-16 * nrm) || (r <=
                 1.0020841800044864E-292)) {
              s[ns - 1] = 0.0;
              exitg1 = true;
            } else {
              ns--;
            }
          }
        }

        if (ix == ii) {
          ns = 3;
        } else if (ix == m) {
          ns = 1;
        } else {
          ns = 2;
          ii = ix;
        }
      }

      switch (ns) {
       case 1:
        r = e[m - 2];
        e[m - 2] = 0.0;
        i = m - 1;
        for (k = i; k >= ii + 1; k--) {
          ntf_xrotg(&s[k - 1], &r, &sqds, &sm);
          if (k > ii + 1) {
            b = e[k - 2];
            r = -sm * b;
            e[k - 2] = b * sqds;
          }
        }
        break;

       case 2:
        r = e[ii - 1];
        e[ii - 1] = 0.0;
        for (k = ii + 1; k <= m; k++) {
          ntf_xrotg(&s[k - 1], &r, &sqds, &sm);
          b = e[k - 1];
          r = -sm * b;
          e[k - 1] = b * sqds;
        }
        break;

       case 3:
        {
          double scale;
          ns = m - 1;
          nrm = s[m - 1];
          scale = std::abs(nrm);
          b = s[m - 2];
          r = std::abs(b);
          if ((!(scale > r)) && (!rtIsNaN(r))) {
            scale = r;
          }

          sqds = e[m - 2];
          r = std::abs(sqds);
          if ((!(scale > r)) && (!rtIsNaN(r))) {
            scale = r;
          }

          r = std::abs(s[ii]);
          if ((!(scale > r)) && (!rtIsNaN(r))) {
            scale = r;
          }

          r = std::abs(e[ii]);
          if ((!(scale > r)) && (!rtIsNaN(r))) {
            scale = r;
          }

          sm = nrm / scale;
          nrm = b / scale;
          r = sqds / scale;
          sqds = s[ii] / scale;
          b = ((nrm + sm) * (nrm - sm) + r * r) / 2.0;
          nrm = sm * r;
          nrm *= nrm;
          if ((b != 0.0) || (nrm != 0.0)) {
            r = std::sqrt(b * b + nrm);
            if (b < 0.0) {
              r = -r;
            }

            r = nrm / (b + r);
          } else {
            r = 0.0;
          }

          r += (sqds + sm) * (sqds - sm);
          nrm = sqds * (e[ii] / scale);
          for (k = ii + 1; k <= ns; k++) {
            ntf_xrotg(&r, &nrm, &sqds, &sm);
            if (k > ii + 1) {
              e[k - 2] = r;
            }

            b = e[k - 1];
            nrm = s[k - 1];
            e[k - 1] = sqds * b - sm * nrm;
            r = sm * s[k];
            s[k] = s[k] * sqds;
            s[k - 1] = sqds * nrm + sm * b;
            ntf_xrotg(&s[k - 1], &r, &sqds, &sm);
            r = sqds * e[k - 1] + sm * s[k];
            s[k] = -sm * e[k - 1] + sqds * s[k];
            nrm = sm * e[k];
            e[k] = e[k] * sqds;
          }

          e[m - 2] = r;
          iy++;
        }
        break;

       default:
        if (s[ii] < 0.0) {
          s[ii] = -s[ii];
        }

        qp1 = ii + 1;
        while ((ii + 1 < qq) && (s[ii] < s[qp1])) {
          nrm = s[ii];
          s[ii] = s[qp1];
          s[qp1] = nrm;
          ii = qp1;
          qp1++;
        }

        iy = 0;
        m--;
        break;
      }
    }
  }

  U.set_size(minnp);
  for (k = 0; k < minnp; k++) {
    U[k] = s[k];
  }
}

//
// File trailer for ntf_svd.cpp
//
// [EOF]
//
