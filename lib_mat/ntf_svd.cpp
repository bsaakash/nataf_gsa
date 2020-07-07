//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_svd.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 06-Jul-2020 21:30:41
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
#include <cstring>

// Function Definitions

//
// Arguments    : const coder::array<double, 2U> *A
//                double U_data[]
//                int U_size[1]
// Return Type  : void
//
void ntf_svd(const coder::array<double, 2U> &A, double U_data[], int U_size[1])
{
  coder::array<double, 2U> b_A;
  int ns;
  int i;
  int p;
  int minnp;
  double s_data[3];
  coder::array<double, 1U> e;
  double work[2];
  double nrm;
  double r;
  double sqds;
  double sm;
  b_A.set_size(2, A.size(1));
  ns = A.size(0) * A.size(1);
  for (i = 0; i < ns; i++) {
    b_A[i] = A[i];
  }

  p = A.size(1);
  ns = A.size(1);
  if (3 < ns) {
    ns = 3;
  }

  minnp = A.size(1);
  if (2 < minnp) {
    minnp = 2;
  }

  if (0 <= ns - 1) {
    std::memset(&s_data[0], 0, ns * sizeof(double));
  }

  e.set_size(A.size(1));
  ns = A.size(1);
  for (i = 0; i < ns; i++) {
    e[i] = 0.0;
  }

  work[0] = 0.0;
  if (A.size(1) != 0) {
    int nrt;
    int q;
    int m;
    int qp1;
    int qq;
    int nmqp1;
    double b;
    int ix;
    int iy;
    double snorm;
    int k;
    if (A.size(1) > 2) {
      nrt = A.size(1) - 2;
    } else {
      nrt = 0;
    }

    if (nrt >= 2) {
      nrt = 2;
    }

    if (1 > nrt) {
      i = 1;
    } else {
      i = nrt;
    }

    for (q = 0; q < i; q++) {
      boolean_T apply_transform;
      qp1 = q + 2;
      qq = (q + (q << 1)) + 1;
      nmqp1 = 1 - q;
      apply_transform = false;
      if (q + 1 <= 1) {
        nrm = ntf_xnrm2(2, b_A, qq);
        if (nrm > 0.0) {
          apply_transform = true;
          if (b_A[qq - 1] < 0.0) {
            b = -nrm;
            s_data[0] = -nrm;
          } else {
            b = nrm;
            s_data[0] = nrm;
          }

          if (std::abs(b) >= 1.0020841800044864E-292) {
            nrm = 1.0 / b;
            ns = qq + 1;
            for (k = qq; k <= ns; k++) {
              b_A[k - 1] = nrm * b_A[k - 1];
            }
          } else {
            ns = qq + 1;
            for (k = qq; k <= ns; k++) {
              b_A[k - 1] = b_A[k - 1] / s_data[0];
            }
          }

          b_A[qq - 1] = b_A[qq - 1] + 1.0;
          s_data[0] = -s_data[0];
        } else {
          s_data[0] = 0.0;
        }
      }

      for (m = qp1; m <= p; m++) {
        ns = q + ((m - 1) << 1);
        if (apply_transform) {
          ix = qq;
          iy = ns;
          nrm = 0.0;
          for (k = 0; k <= nmqp1; k++) {
            nrm += b_A[ix - 1] * b_A[iy];
            ix++;
            iy++;
          }

          nrm = -(nrm / b_A[q + 2 * q]);
          ntf_xaxpy(2 - q, nrm, qq, b_A, ns + 1);
        }

        e[m - 1] = b_A[ns];
      }

      if (q + 1 <= nrt) {
        ns = (p - q) - 1;
        nrm = ntf_b_xnrm2(ns, e, q + 2);
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
            ns = (q + ns) + 1;
            for (k = qp1; k <= ns; k++) {
              e[k - 1] = nrm * e[k - 1];
            }
          } else {
            ns = (q + ns) + 1;
            for (k = qp1; k <= ns; k++) {
              e[k - 1] = e[k - 1] / nrm;
            }
          }

          e[q + 1] = e[q + 1] + 1.0;
          e[q] = -e[q];
          if (q + 2 <= 2) {
            work[1] = 0.0;
            for (m = 2; m <= p; m++) {
              ntf_b_xaxpy(1 - q, e[m - 1], b_A, ((m - 1) << 1) + 2, work);
            }

            for (m = 2; m <= p; m++) {
              ntf_c_xaxpy(1 - q, -e[m - 1] / e[1], work, b_A, ((m - 1) << 1) + 2);
            }
          }
        }
      }
    }

    m = A.size(1);
    if (m >= 3) {
      m = 3;
    }

    if (1 < A.size(1)) {
      s_data[1] = b_A[3];
    }

    if (2 < m) {
      s_data[2] = 0.0;
    }

    if (nrt + 1 < m) {
      e[nrt] = b_A[nrt + 2 * (m - 1)];
    }

    e[m - 1] = 0.0;
    nmqp1 = m;
    iy = 0;
    snorm = 0.0;
    for (q = 0; q < m; q++) {
      b = s_data[q];
      if (s_data[q] != 0.0) {
        nrm = std::abs(s_data[q]);
        r = s_data[q] / nrm;
        b = nrm;
        s_data[q] = nrm;
        if (q + 1 < m) {
          e[q] = e[q] / r;
        }
      }

      if ((q + 1 < m) && (e[q] != 0.0)) {
        nrm = std::abs(e[q]);
        r = nrm / e[q];
        e[q] = nrm;
        s_data[q + 1] *= r;
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
      qq = m - 1;
      exitg1 = false;
      while (!(exitg1 || (qq == 0))) {
        nrm = std::abs(e[qq - 1]);
        if ((nrm <= 2.2204460492503131E-16 * (std::abs(s_data[qq - 1]) + std::
              abs(s_data[qq]))) || (nrm <= 1.0020841800044864E-292) || ((iy > 20)
             && (nrm <= 2.2204460492503131E-16 * snorm))) {
          e[qq - 1] = 0.0;
          exitg1 = true;
        } else {
          qq--;
        }
      }

      if (qq == m - 1) {
        ns = 4;
      } else {
        ix = m;
        ns = m;
        exitg1 = false;
        while ((!exitg1) && (ns >= qq)) {
          ix = ns;
          if (ns == qq) {
            exitg1 = true;
          } else {
            nrm = 0.0;
            if (ns < m) {
              nrm = std::abs(e[ns - 1]);
            }

            if (ns > qq + 1) {
              nrm += std::abs(e[ns - 2]);
            }

            r = std::abs(s_data[ns - 1]);
            if ((r <= 2.2204460492503131E-16 * nrm) || (r <=
                 1.0020841800044864E-292)) {
              s_data[ns - 1] = 0.0;
              exitg1 = true;
            } else {
              ns--;
            }
          }
        }

        if (ix == qq) {
          ns = 3;
        } else if (ix == m) {
          ns = 1;
        } else {
          ns = 2;
          qq = ix;
        }
      }

      switch (ns) {
       case 1:
        r = e[m - 2];
        e[m - 2] = 0.0;
        i = m - 1;
        for (k = i; k >= qq + 1; k--) {
          ntf_xrotg(&s_data[k - 1], &r, &sqds, &sm);
          if (k > qq + 1) {
            r = -sm * e[0];
            e[0] = e[0] * sqds;
          }
        }
        break;

       case 2:
        r = e[qq - 1];
        e[qq - 1] = 0.0;
        for (k = qq + 1; k <= m; k++) {
          ntf_xrotg(&s_data[k - 1], &r, &sqds, &sm);
          b = e[k - 1];
          r = -sm * b;
          e[k - 1] = b * sqds;
        }
        break;

       case 3:
        {
          double scale;
          ns = m - 1;
          nrm = s_data[m - 1];
          scale = std::abs(nrm);
          b = s_data[m - 2];
          r = std::abs(b);
          if ((!(scale > r)) && (!rtIsNaN(r))) {
            scale = r;
          }

          sqds = e[m - 2];
          r = std::abs(sqds);
          if ((!(scale > r)) && (!rtIsNaN(r))) {
            scale = r;
          }

          r = std::abs(s_data[qq]);
          if ((!(scale > r)) && (!rtIsNaN(r))) {
            scale = r;
          }

          r = std::abs(e[qq]);
          if ((!(scale > r)) && (!rtIsNaN(r))) {
            scale = r;
          }

          sm = nrm / scale;
          nrm = b / scale;
          r = sqds / scale;
          sqds = s_data[qq] / scale;
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
          nrm = sqds * (e[qq] / scale);
          for (k = qq + 1; k <= ns; k++) {
            ntf_xrotg(&r, &nrm, &sqds, &sm);
            if (k > qq + 1) {
              e[0] = r;
            }

            b = e[k - 1];
            nrm = s_data[k - 1];
            e[k - 1] = sqds * b - sm * nrm;
            r = sm * s_data[k];
            s_data[k] *= sqds;
            s_data[k - 1] = sqds * nrm + sm * b;
            ntf_xrotg(&s_data[k - 1], &r, &sqds, &sm);
            r = sqds * e[k - 1] + sm * s_data[k];
            s_data[k] = -sm * e[k - 1] + sqds * s_data[k];
            nrm = sm * e[k];
            e[k] = e[k] * sqds;
          }

          e[m - 2] = r;
          iy++;
        }
        break;

       default:
        if (s_data[qq] < 0.0) {
          s_data[qq] = -s_data[qq];
        }

        qp1 = qq + 1;
        while ((qq + 1 < nmqp1) && (s_data[qq] < s_data[qp1])) {
          nrm = s_data[qq];
          s_data[qq] = s_data[qp1];
          s_data[qp1] = nrm;
          qq = qp1;
          qp1++;
        }

        iy = 0;
        m--;
        break;
      }
    }
  }

  U_size[0] = minnp;
  if (0 <= minnp - 1) {
    std::memcpy(&U_data[0], &s_data[0], minnp * sizeof(double));
  }
}

//
// File trailer for ntf_svd.cpp
//
// [EOF]
//
