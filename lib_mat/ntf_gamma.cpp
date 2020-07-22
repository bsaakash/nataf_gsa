//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_gamma.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_gamma.h"
#include "ntf_cospiAndSinpi.h"
#include "ntf_inataf.h"
#include "ntf_inataf_data.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double *x
// Return Type  : void
//
void ntf_gamma(double *x)
{
  static const double gam[23] = { 1.0, 1.0, 2.0, 6.0, 24.0, 120.0, 720.0, 5040.0,
    40320.0, 362880.0, 3.6288E+6, 3.99168E+7, 4.790016E+8, 6.2270208E+9,
    8.71782912E+10, 1.307674368E+12, 2.0922789888E+13, 3.55687428096E+14,
    6.402373705728E+15, 1.21645100408832E+17, 2.43290200817664E+18,
    5.109094217170944E+19, 1.1240007277776077E+21 };

  double xden;
  double sum;
  static const double p[8] = { -1.716185138865495, 24.76565080557592,
    -379.80425647094563, 629.3311553128184, 866.96620279041326,
    -31451.272968848367, -36144.413418691176, 66456.143820240541 };

  static const double q[8] = { -30.840230011973897, 315.35062697960416,
    -1015.1563674902192, -3107.7716715723109, 22538.11842098015,
    4755.8462775278813, -134659.95986496931, -115132.25967555349 };

  if ((*x >= 1.0) && (*x <= 23.0) && (*x == std::floor(*x))) {
    *x = gam[static_cast<int>(*x) - 1];
  } else if ((*x < 1.0) && (*x == std::floor(*x))) {
    *x = rtInf;
  } else if (rtIsNaN(*x)) {
    *x = rtNaN;
  } else if (rtIsInf(*x)) {
    *x = rtInf;
  } else {
    double fact;
    double n;
    boolean_T parity;
    double yint;
    fact = 1.0;
    n = 0.0;
    parity = false;
    if (*x <= 0.0) {
      yint = std::floor(-*x);
      parity = (yint != std::floor(-*x / 2.0) * 2.0);
      ntf_cospiAndSinpi(-*x - yint, &xden, &sum);
      fact = -3.1415926535897931 / sum;
      *x = -*x + 1.0;
    }

    if (*x < 12.0) {
      double xkold;
      int i;
      xkold = *x;
      if (*x < 1.0) {
        sum = *x;
        (*x)++;
      } else {
        n = std::floor(*x) - 1.0;
        *x -= n;
        sum = *x - 1.0;
      }

      yint = 0.0 * sum;
      xden = 1.0;
      for (i = 0; i < 8; i++) {
        yint = (yint + p[i]) * sum;
        xden = xden * sum + q[i];
      }

      sum = yint / xden + 1.0;
      if (xkold < *x) {
        sum /= xkold;
      } else {
        if (xkold > *x) {
          i = static_cast<int>(n);
          for (int j = 0; j < i; j++) {
            sum *= *x;
            (*x)++;
          }
        }
      }
    } else {
      yint = *x * *x;
      sum = 0.0057083835261;
      for (int i = 0; i < 6; i++) {
        sum = sum / yint + ntf_dv1[i];
      }

      sum = (sum / *x - *x) + 0.91893853320467278;
      sum += (*x - 0.5) * std::log(*x);
      sum = std::exp(sum);
    }

    if (parity) {
      sum = -sum;
    }

    if (fact != 1.0) {
      sum = fact / sum;
    }

    *x = sum;
  }
}

//
// File trailer for ntf_gamma.cpp
//
// [EOF]
//
