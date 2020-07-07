//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_binopdf.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 06-Jul-2020 21:30:41
//

// Include Files
#include "ntf_binopdf.h"
#include "ntf_binodeviance.h"
#include "ntf_gammaln.h"
#include "ntf_inataf.h"
#include "ntf_stirlerr.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double x
//                double n
//                double p
// Return Type  : double
//
double ntf_binopdf(double x, double n, double p)
{
  double y;
  double absz;
  double d;
  double d2;
  if ((n == std::floor(n)) && (!rtIsNaN(x))) {
    if ((x >= 0.0) && (x == std::floor(x)) && (x <= n)) {
      if (p == 0.0) {
        y = (x == 0.0);
      } else if (p == 1.0) {
        y = (x == n);
      } else if (x == 0.0) {
        y = std::exp(n * std::log(1.0 - p));
      } else if (x == n) {
        y = std::exp(n * std::log(p));
      } else if (n < 10.0) {
        double b_x;
        double d1;
        b_x = -p;
        absz = std::abs(-p);
        if ((absz > 4.503599627370496E+15) || (rtIsInf(-p) || rtIsNaN(-p))) {
          b_x = std::log(-p + 1.0);
        } else {
          if (!(absz < 2.2204460492503131E-16)) {
            b_x = std::log(-p + 1.0) * (-p / ((-p + 1.0) - 1.0));
          }
        }

        absz = n + 1.0;
        ntf_gammaln(&absz);
        d = x + 1.0;
        ntf_gammaln(&d);
        d1 = n - x;
        d2 = d1 + 1.0;
        ntf_gammaln(&d2);
        y = std::exp((((absz - d) - d2) + x * std::log(p)) + d1 * b_x);
      } else {
        double b_x;
        b_x = (((ntf_stirlerr(n) - ntf_stirlerr(x)) - ntf_stirlerr(n - x)) -
               ntf_binodeviance(x, n * p)) - ntf_binodeviance(n - x, n * (1.0 -
          p));
        b_x = std::exp(b_x);
        y = b_x * std::sqrt(n / (6.2831853071795862 * x * (n - x)));
      }
    } else {
      y = 0.0;
    }
  } else {
    y = rtNaN;
  }

  return y;
}

//
// File trailer for ntf_binopdf.cpp
//
// [EOF]
//
