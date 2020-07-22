//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_xzgeqp3.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_xzgeqp3.h"
#include "ntf_ERADist.h"
#include "ntf_inataf.h"
#include "ntf_mrdivide_helper.h"
#include "ntf_pdf.h"
#include "ntf_xnrm2.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Declarations
static double ntf_rt_hypotd_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double ntf_rt_hypotd_snf(double u0, double u1)
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
void ntf_b_qrpf(coder::array<double, 2U> &A, int m, int n, coder::array<double,
                1U> &tau, coder::array<int, 2U> &jpvt)
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
    smax = ntf_xnrm2(m, A, j * ma + 1);
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
        smax = ntf_xnrm2(mmi - 1, A, ii + 2);
        if (smax != 0.0) {
          s = ntf_rt_hypotd_snf(A[ii], smax);
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

            s = ntf_rt_hypotd_snf(temp2, ntf_xnrm2(mmi - 1, A, ii + 2));
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
            smax = ntf_xnrm2(mmi - 1, A, itemp + 2);
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
// Arguments    : coder::array<double, 2U> *A
//                int m
//                double tau_data[]
//                int jpvt[2]
// Return Type  : void
//
void ntf_qrpf(coder::array<double, 2U> &A, int m, double tau_data[], int jpvt[2])
{
  int ma;
  int minmn;
  double work[2];
  double temp;
  double vn1[2];
  double vn2[2];
  int k;
  double atmp;
  int jA;
  double beta1;
  ma = A.size(0);
  if (m < 2) {
    minmn = m;
  } else {
    minmn = 2;
  }

  work[0] = 0.0;
  temp = ntf_xnrm2(m, A, 1);
  vn1[0] = temp;
  vn2[0] = temp;
  work[1] = 0.0;
  temp = ntf_xnrm2(m, A, ma + 1);
  vn1[1] = temp;
  vn2[1] = temp;
  for (int i = 0; i < minmn; i++) {
    int ip1;
    int iy;
    int ii;
    int mmi;
    int itemp;
    int pvt;
    int ix;
    int b_i;
    ip1 = i + 2;
    iy = i * ma;
    ii = iy + i;
    mmi = m - i;
    itemp = 0;
    if ((2 - i > 1) && (std::abs(vn1[1]) > std::abs(vn1[i]))) {
      itemp = 1;
    }

    pvt = i + itemp;
    if (pvt + 1 != i + 1) {
      ix = pvt * ma;
      for (k = 0; k < m; k++) {
        temp = A[ix];
        A[ix] = A[iy];
        A[iy] = temp;
        ix++;
        iy++;
      }

      itemp = jpvt[pvt];
      jpvt[pvt] = jpvt[i];
      jpvt[i] = itemp;
      vn1[pvt] = vn1[i];
      vn2[pvt] = vn2[i];
    }

    if (i + 1 < m) {
      atmp = A[ii];
      itemp = ii + 2;
      tau_data[i] = 0.0;
      if (mmi > 0) {
        temp = ntf_xnrm2(mmi - 1, A, ii + 2);
        if (temp != 0.0) {
          beta1 = ntf_rt_hypotd_snf(A[ii], temp);
          if (A[ii] >= 0.0) {
            beta1 = -beta1;
          }

          if (std::abs(beta1) < 1.0020841800044864E-292) {
            pvt = -1;
            b_i = ii + mmi;
            do {
              pvt++;
              for (k = itemp; k <= b_i; k++) {
                A[k - 1] = 9.9792015476736E+291 * A[k - 1];
              }

              beta1 *= 9.9792015476736E+291;
              atmp *= 9.9792015476736E+291;
            } while (!(std::abs(beta1) >= 1.0020841800044864E-292));

            beta1 = ntf_rt_hypotd_snf(atmp, ntf_xnrm2(mmi - 1, A, ii + 2));
            if (atmp >= 0.0) {
              beta1 = -beta1;
            }

            tau_data[i] = (beta1 - atmp) / beta1;
            temp = 1.0 / (atmp - beta1);
            for (k = itemp; k <= b_i; k++) {
              A[k - 1] = temp * A[k - 1];
            }

            for (k = 0; k <= pvt; k++) {
              beta1 *= 1.0020841800044864E-292;
            }

            atmp = beta1;
          } else {
            tau_data[i] = (beta1 - A[ii]) / beta1;
            temp = 1.0 / (A[ii] - beta1);
            b_i = ii + mmi;
            for (k = itemp; k <= b_i; k++) {
              A[k - 1] = temp * A[k - 1];
            }

            atmp = beta1;
          }
        }
      }

      A[ii] = atmp;
    } else {
      tau_data[i] = 0.0;
    }

    if (i + 1 < 2) {
      int lastv;
      atmp = A[ii];
      A[ii] = 1.0;
      jA = (ii + ma) + 1;
      if (tau_data[0] != 0.0) {
        boolean_T exitg2;
        lastv = mmi - 1;
        itemp = (ii + mmi) - 1;
        while ((lastv + 1 > 0) && (A[itemp] == 0.0)) {
          lastv--;
          itemp--;
        }

        pvt = 1 - i;
        exitg2 = false;
        while ((!exitg2) && (pvt > 0)) {
          int exitg1;
          itemp = jA;
          do {
            exitg1 = 0;
            if (itemp <= jA + lastv) {
              if (A[itemp - 1] != 0.0) {
                exitg1 = 1;
              } else {
                itemp++;
              }
            } else {
              pvt = 0;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = -1;
        pvt = 0;
      }

      if (lastv + 1 > 0) {
        if (pvt != 0) {
          work[0] = 0.0;
          iy = 0;
          for (k = jA; ma < 0 ? k >= jA : k <= jA; k += ma) {
            ix = ii;
            temp = 0.0;
            b_i = k + lastv;
            for (itemp = k; itemp <= b_i; itemp++) {
              temp += A[itemp - 1] * A[ix];
              ix++;
            }

            work[iy] += temp;
            iy++;
          }
        }

        if (!(-tau_data[0] == 0.0)) {
          itemp = 0;
          for (iy = 0; iy < pvt; iy++) {
            if (work[itemp] != 0.0) {
              temp = work[itemp] * -tau_data[0];
              ix = ii;
              b_i = lastv + jA;
              for (k = jA; k <= b_i; k++) {
                A[k - 1] = A[k - 1] + A[ix] * temp;
                ix++;
              }
            }

            itemp++;
            jA += ma;
          }
        }
      }

      A[ii] = atmp;
    }

    for (iy = ip1; iy < 3; iy++) {
      itemp = i + ma;
      if (vn1[1] != 0.0) {
        temp = std::abs(A[itemp]) / vn1[1];
        temp = 1.0 - temp * temp;
        if (temp < 0.0) {
          temp = 0.0;
        }

        beta1 = vn1[1] / vn2[1];
        beta1 = temp * (beta1 * beta1);
        if (beta1 <= 1.4901161193847656E-8) {
          if (i + 1 < m) {
            temp = ntf_xnrm2(mmi - 1, A, itemp + 2);
            vn1[1] = temp;
            vn2[1] = temp;
          } else {
            vn1[1] = 0.0;
            vn2[1] = 0.0;
          }
        } else {
          vn1[1] *= std::sqrt(temp);
        }
      }
    }
  }
}

//
// File trailer for ntf_xzgeqp3.cpp
//
// [EOF]
//
