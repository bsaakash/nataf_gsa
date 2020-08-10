//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_xzgeqp3.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 21:17:14
//

// Include Files
#include "gsa_xzgeqp3.h"
#include "gsa_mymvnpdf.h"
#include "gsa_runGSA.h"
#include "gsa_sum.h"
#include "gsa_xgetrf.h"
#include "gsa_xnrm2.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Declarations
static double gsa_rt_hypotd_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double gsa_rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  a = std::abs(u0);
  y = std::abs(u1);
  if (a < y) {
    a /= y;
    y *= std::sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = a * std::sqrt(y * y + 1.0);
  } else {
    if (!rtIsNaN(y)) {
      y = a * 1.4142135623730951;
    }
  }

  return y;
}

//
// Arguments    : coder::array<double, 2U> *A
//                int m
//                int n
//                coder::array<double, 1U> *tau
//                coder::array<int, 2U> *jpvt
// Return Type  : void
//
void gsa_qrpf(coder::array<double, 2U> &A, int m, int n, coder::array<double, 1U>
              &tau, coder::array<int, 2U> &jpvt)
{
  int ma;
  int minmn;
  coder::array<double, 1U> work;
  int itemp;
  int i;
  coder::array<double, 1U> vn1;
  coder::array<double, 1U> vn2;
  int j;
  double smax;
  int nmi;
  int pvt;
  double temp2;
  double s;
  int jA;
  ma = A.size(0);
  if (m < n) {
    minmn = m;
  } else {
    minmn = n;
  }

  work.set_size(A.size(1));
  itemp = A.size(1);
  for (i = 0; i < itemp; i++) {
    work[i] = 0.0;
  }

  vn1.set_size(A.size(1));
  itemp = A.size(1);
  for (i = 0; i < itemp; i++) {
    vn1[i] = 0.0;
  }

  vn2.set_size(A.size(1));
  itemp = A.size(1);
  for (i = 0; i < itemp; i++) {
    vn2[i] = 0.0;
  }

  for (j = 0; j < n; j++) {
    smax = gsa_xnrm2(m, A, j * ma + 1);
    vn1[j] = smax;
    vn2[j] = smax;
  }

  for (int b_i = 0; b_i < minmn; b_i++) {
    int ip1;
    int iy;
    int ii;
    int mmi;
    int ix;
    ip1 = b_i + 2;
    iy = b_i * ma;
    ii = iy + b_i;
    nmi = n - b_i;
    mmi = m - b_i;
    if (nmi < 1) {
      itemp = -1;
    } else {
      itemp = 0;
      if (nmi > 1) {
        ix = b_i;
        smax = std::abs(vn1[b_i]);
        for (j = 2; j <= nmi; j++) {
          ix++;
          s = std::abs(vn1[ix]);
          if (s > smax) {
            itemp = j - 1;
            smax = s;
          }
        }
      }
    }

    pvt = b_i + itemp;
    if (pvt + 1 != b_i + 1) {
      ix = pvt * ma;
      for (j = 0; j < m; j++) {
        smax = A[ix];
        A[ix] = A[iy];
        A[iy] = smax;
        ix++;
        iy++;
      }

      itemp = jpvt[pvt];
      jpvt[pvt] = jpvt[b_i];
      jpvt[b_i] = itemp;
      vn1[pvt] = vn1[b_i];
      vn2[pvt] = vn2[b_i];
    }

    if (b_i + 1 < m) {
      temp2 = A[ii];
      itemp = ii + 2;
      tau[b_i] = 0.0;
      if (mmi > 0) {
        smax = gsa_xnrm2(mmi - 1, A, ii + 2);
        if (smax != 0.0) {
          s = gsa_rt_hypotd_snf(A[ii], smax);
          if (A[ii] >= 0.0) {
            s = -s;
          }

          if (std::abs(s) < 1.0020841800044864E-292) {
            pvt = -1;
            i = ii + mmi;
            do {
              pvt++;
              for (j = itemp; j <= i; j++) {
                A[j - 1] = 9.9792015476736E+291 * A[j - 1];
              }

              s *= 9.9792015476736E+291;
              temp2 *= 9.9792015476736E+291;
            } while (!(std::abs(s) >= 1.0020841800044864E-292));

            s = gsa_rt_hypotd_snf(temp2, gsa_xnrm2(mmi - 1, A, ii + 2));
            if (temp2 >= 0.0) {
              s = -s;
            }

            tau[b_i] = (s - temp2) / s;
            smax = 1.0 / (temp2 - s);
            for (j = itemp; j <= i; j++) {
              A[j - 1] = smax * A[j - 1];
            }

            for (j = 0; j <= pvt; j++) {
              s *= 1.0020841800044864E-292;
            }

            temp2 = s;
          } else {
            tau[b_i] = (s - A[ii]) / s;
            smax = 1.0 / (A[ii] - s);
            i = ii + mmi;
            for (j = itemp; j <= i; j++) {
              A[j - 1] = smax * A[j - 1];
            }

            temp2 = s;
          }
        }
      }

      A[ii] = temp2;
    } else {
      tau[b_i] = 0.0;
    }

    if (b_i + 1 < n) {
      int lastv;
      temp2 = A[ii];
      A[ii] = 1.0;
      jA = (ii + ma) + 1;
      if (tau[b_i] != 0.0) {
        boolean_T exitg2;
        lastv = mmi - 1;
        itemp = (ii + mmi) - 1;
        while ((lastv + 1 > 0) && (A[itemp] == 0.0)) {
          lastv--;
          itemp--;
        }

        nmi -= 2;
        exitg2 = false;
        while ((!exitg2) && (nmi + 1 > 0)) {
          int exitg1;
          itemp = jA + nmi * ma;
          j = itemp;
          do {
            exitg1 = 0;
            if (j <= itemp + lastv) {
              if (A[j - 1] != 0.0) {
                exitg1 = 1;
              } else {
                j++;
              }
            } else {
              nmi--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = -1;
        nmi = -1;
      }

      if (lastv + 1 > 0) {
        if (nmi + 1 != 0) {
          for (iy = 0; iy <= nmi; iy++) {
            work[iy] = 0.0;
          }

          iy = 0;
          i = jA + ma * nmi;
          for (pvt = jA; ma < 0 ? pvt >= i : pvt <= i; pvt += ma) {
            ix = ii;
            smax = 0.0;
            itemp = pvt + lastv;
            for (j = pvt; j <= itemp; j++) {
              smax += A[j - 1] * A[ix];
              ix++;
            }

            work[iy] = work[iy] + smax;
            iy++;
          }
        }

        if (!(-tau[b_i] == 0.0)) {
          itemp = 0;
          for (j = 0; j <= nmi; j++) {
            if (work[itemp] != 0.0) {
              smax = work[itemp] * -tau[b_i];
              ix = ii;
              i = lastv + jA;
              for (pvt = jA; pvt <= i; pvt++) {
                A[pvt - 1] = A[pvt - 1] + A[ix] * smax;
                ix++;
              }
            }

            itemp++;
            jA += ma;
          }
        }
      }

      A[ii] = temp2;
    }

    for (j = ip1; j <= n; j++) {
      itemp = b_i + (j - 1) * ma;
      smax = vn1[j - 1];
      if (smax != 0.0) {
        s = std::abs(A[itemp]) / smax;
        s = 1.0 - s * s;
        if (s < 0.0) {
          s = 0.0;
        }

        temp2 = smax / vn2[j - 1];
        temp2 = s * (temp2 * temp2);
        if (temp2 <= 1.4901161193847656E-8) {
          if (b_i + 1 < m) {
            smax = gsa_xnrm2(mmi - 1, A, itemp + 2);
            vn1[j - 1] = smax;
            vn2[j - 1] = smax;
          } else {
            vn1[j - 1] = 0.0;
            vn2[j - 1] = 0.0;
          }
        } else {
          vn1[j - 1] = smax * std::sqrt(s);
        }
      }
    }
  }
}

//
// File trailer for gsa_xzgeqp3.cpp
//
// [EOF]
//
