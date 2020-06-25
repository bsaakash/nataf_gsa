//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_nbinpdf.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:09:55
//

// Include Files
#include "ntf_nbinpdf.h"
#include "ntf_gammaln.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double x
//                double r
//                double p
// Return Type  : double
//
double ntf_b_nbinpdf(double x, double r, double p)
{
  double y;
  double absz;
  double d;
  double d1;
  if ((!rtIsInf(r)) && (!rtIsNaN(r)) && (!rtIsNaN(x))) {
    if ((!rtIsInf(x)) && (x == std::floor(x))) {
      if (p < 1.0) {
        double b_x;
        b_x = -p;
        absz = std::abs(-p);
        if ((absz > 4.503599627370496E+15) || rtIsInf(-p)) {
          b_x = std::log(-p + 1.0);
        } else {
          if (!(absz < 2.2204460492503131E-16)) {
            b_x = std::log(-p + 1.0) * (-p / ((-p + 1.0) - 1.0));
          }
        }

        absz = r + x;
        ntf_gammaln(&absz);
        d = x + 1.0;
        ntf_gammaln(&d);
        d1 = r;
        ntf_gammaln(&d1);
        y = std::exp((((absz - d) - d1) + r * std::log(p)) + x * b_x);
      } else {
        y = (x == 0.0);
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
// Arguments    : double r
//                double p
// Return Type  : double
//
double ntf_nbinpdf(double r, double p)
{
  double y;
  double lognk_tmp;
  double absz;
  if ((!rtIsInf(r)) && (!rtIsNaN(r))) {
    if (p < 1.0) {
      double x;
      lognk_tmp = r;
      ntf_gammaln(&lognk_tmp);
      x = -p;
      absz = std::abs(-p);
      if ((absz > 4.503599627370496E+15) || rtIsInf(-p)) {
        x = std::log(-p + 1.0);
      } else {
        if (!(absz < 2.2204460492503131E-16)) {
          x = std::log(-p + 1.0) * (-p / ((-p + 1.0) - 1.0));
        }
      }

      absz = 1.0;
      ntf_gammaln(&absz);
      y = std::exp((((lognk_tmp - absz) - lognk_tmp) + r * std::log(p)) + 0.0 *
                   x);
    } else {
      y = 1.0;
    }
  } else {
    y = rtNaN;
  }

  return y;
}

//
// File trailer for ntf_nbinpdf.cpp
//
// [EOF]
//
