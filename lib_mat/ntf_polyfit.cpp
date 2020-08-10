//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_polyfit.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_polyfit.h"
#include "ntf_ERADist.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "ntf_xzgeqp3.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : const coder::array<double, 1U> *x
//                const coder::array<double, 1U> *y
//                double p[2]
// Return Type  : void
//
void ntf_polyfit(const coder::array<double, 1U> &x, const coder::array<double,
                 1U> &y, double p[2])
{
  coder::array<double, 2U> V;
  int i;
  int u0;
  int minmana;
  double tau_data[2];
  boolean_T guard1 = false;
  int jpvt[2];
  coder::array<double, 1U> B;
  int mn;
  int j;
  int b_i;
  double wj;
  V.set_size(x.size(0), 2);
  if (x.size(0) != 0) {
    i = x.size(0);
    for (minmana = 0; minmana < i; minmana++) {
      V[minmana + V.size(0)] = 1.0;
    }

    i = x.size(0);
    for (minmana = 0; minmana < i; minmana++) {
      V[minmana] = x[minmana];
    }
  }

  u0 = V.size(0);
  if (u0 >= 2) {
    u0 = 2;
  }

  minmana = V.size(0);
  if (minmana >= 2) {
    minmana = 2;
  }

  if (0 <= minmana - 1) {
    std::memset(&tau_data[0], 0, minmana * sizeof(double));
  }

  guard1 = false;
  if (V.size(0) == 0) {
    guard1 = true;
  } else {
    minmana = V.size(0);
    if (minmana >= 2) {
      minmana = 2;
    }

    if (minmana < 1) {
      guard1 = true;
    } else {
      jpvt[0] = 1;
      jpvt[1] = 2;
      ntf_qrpf(V, V.size(0), tau_data, jpvt);
    }
  }

  if (guard1) {
    jpvt[0] = 1;
    jpvt[1] = 2;
  }

  B.set_size(y.size(0));
  minmana = y.size(0);
  for (i = 0; i < minmana; i++) {
    B[i] = y[i];
  }

  p[0] = 0.0;
  p[1] = 0.0;
  minmana = V.size(0);
  mn = V.size(0);
  if (mn >= 2) {
    mn = 2;
  }

  for (j = 0; j < mn; j++) {
    if (tau_data[j] != 0.0) {
      wj = B[j];
      i = j + 2;
      for (b_i = i; b_i <= minmana; b_i++) {
        wj += V[(b_i + V.size(0) * j) - 1] * B[b_i - 1];
      }

      wj *= tau_data[j];
      if (wj != 0.0) {
        B[j] = B[j] - wj;
        i = j + 2;
        for (b_i = i; b_i <= minmana; b_i++) {
          B[b_i - 1] = B[b_i - 1] - V[(b_i + V.size(0) * j) - 1] * wj;
        }
      }
    }
  }

  for (b_i = 0; b_i < u0; b_i++) {
    p[jpvt[b_i] - 1] = B[b_i];
  }

  for (j = u0; j >= 1; j--) {
    minmana = jpvt[j - 1] - 1;
    p[minmana] /= V[(j + V.size(0) * (j - 1)) - 1];
    for (b_i = 0; b_i <= j - 2; b_i++) {
      p[jpvt[0] - 1] -= p[minmana] * V[V.size(0) * (j - 1)];
    }
  }
}

//
// File trailer for ntf_polyfit.cpp
//
// [EOF]
//
