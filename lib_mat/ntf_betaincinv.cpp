//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_betaincinv.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_betaincinv.h"
#include "ntf_betainc.h"
#include "ntf_gammaincinv.h"
#include "ntf_gammaln.h"
#include "ntf_inataf.h"
#include "ntf_inataf_rtwutil.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Declarations
static double ntf_eml_betainc(double x, double a, double b, double lbeta,
  boolean_T upper);

// Function Definitions

//
// Arguments    : double x
//                double a
//                double b
//                double lbeta
//                boolean_T upper
// Return Type  : double
//
static double ntf_eml_betainc(double x, double a, double b, double lbeta,
  boolean_T upper)
{
  double rval;
  double d;
  if ((0.0 < x) && (x < 1.0)) {
    if (rtIsInf(a)) {
      if (!rtIsInf(b)) {
        if (x < 1.0) {
          rval = upper;
        } else {
          rval = 1.0 - static_cast<double>(upper);
        }
      } else if (x == 0.0) {
        rval = upper;
      } else if (x == 1.0) {
        rval = 1.0 - static_cast<double>(upper);
      } else {
        rval = rtNaN;
      }
    } else if (rtIsInf(b)) {
      if (x == 0.0) {
        rval = upper;
      } else {
        rval = 1.0 - static_cast<double>(upper);
      }
    } else {
      boolean_T guard1 = false;
      double logx;
      double log1mx;
      d = a + b;
      guard1 = false;
      if (d < 1.0E+7) {
        logx = std::log(x);
        if (1.0 - x != 1.0) {
          log1mx = std::log(1.0 - x) * (-x / ((1.0 - x) - 1.0));
        } else {
          log1mx = -x;
        }

        if (x < (a + 1.0) / (d + 2.0)) {
          rval = std::exp(((a * logx + b * log1mx) - std::log(a)) - lbeta) *
            ntf_betainc_cf(x, a, b);
          if (upper) {
            rval = 1.0 - rval;
          }
        } else {
          rval = std::exp(((a * logx + b * log1mx) - std::log(b)) - lbeta) *
            ntf_betainc_cf(1.0 - x, b, a);
          if (!upper) {
            rval = 1.0 - rval;
          }
        }

        if (!(rval == rval)) {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        logx = ntf_rt_powd_snf(b * x, 0.33333333333333331);
        log1mx = ntf_rt_powd_snf(a * (1.0 - x), 0.33333333333333331);
        if ((d - 1.0) * (1.0 - x) > 0.8) {
          logx = 3.0 * ((1.0 - 1.0 / (9.0 * b)) * logx - (1.0 - 1.0 / (9.0 * a))
                        * log1mx) / std::sqrt(logx * logx / b + log1mx * log1mx /
            a);
          if (upper) {
            log1mx = 0.70710678118654746 * logx;
            logx = 3.97886080735226 / (std::abs(log1mx) + 3.97886080735226);
            rval = 0.5 * ((((((((((((((((((((((0.0012710976495261409 * (logx -
              0.5) + 0.00011931402283834095) * (logx - 0.5) +
              -0.0039638509736051354) * (logx - 0.5) + -0.00087077963531729586) *
              (logx - 0.5) + 0.0077367252831352668) * (logx - 0.5) +
              0.0038333512626488732) * (logx - 0.5) + -0.012722381378212275) *
              (logx - 0.5) + -0.013382364453346007) * (logx - 0.5) +
              0.016131532973325226) * (logx - 0.5) + 0.039097684558848406) *
              (logx - 0.5) + 0.0024936720005350331) * (logx - 0.5) +
              -0.0838864557023002) * (logx - 0.5) + -0.11946395996432542) *
              (logx - 0.5) + 0.016620792496936737) * (logx - 0.5) +
                                  0.35752427444953105) * (logx - 0.5) +
                                 0.80527640875291062) * (logx - 0.5) +
                                1.1890298290927332) * (logx - 0.5) +
                               1.3704021768233816) * (logx - 0.5) +
                              1.313146538310231) * (logx - 0.5) +
                             1.0792551515585667) * (logx - 0.5) +
                            0.77436819911953858) * (logx - 0.5) +
                           0.49016508058531844) * (logx - 0.5) +
                          0.27537474159737679) * logx * std::exp(-log1mx *
              log1mx);
            if (log1mx < 0.0) {
              rval = 1.0 - rval;
            }
          } else {
            log1mx = 0.70710678118654746 * -logx;
            logx = 3.97886080735226 / (std::abs(log1mx) + 3.97886080735226);
            rval = 0.5 * ((((((((((((((((((((((0.0012710976495261409 * (logx -
              0.5) + 0.00011931402283834095) * (logx - 0.5) +
              -0.0039638509736051354) * (logx - 0.5) + -0.00087077963531729586) *
              (logx - 0.5) + 0.0077367252831352668) * (logx - 0.5) +
              0.0038333512626488732) * (logx - 0.5) + -0.012722381378212275) *
              (logx - 0.5) + -0.013382364453346007) * (logx - 0.5) +
              0.016131532973325226) * (logx - 0.5) + 0.039097684558848406) *
              (logx - 0.5) + 0.0024936720005350331) * (logx - 0.5) +
              -0.0838864557023002) * (logx - 0.5) + -0.11946395996432542) *
              (logx - 0.5) + 0.016620792496936737) * (logx - 0.5) +
                                  0.35752427444953105) * (logx - 0.5) +
                                 0.80527640875291062) * (logx - 0.5) +
                                1.1890298290927332) * (logx - 0.5) +
                               1.3704021768233816) * (logx - 0.5) +
                              1.313146538310231) * (logx - 0.5) +
                             1.0792551515585667) * (logx - 0.5) +
                            0.77436819911953858) * (logx - 0.5) +
                           0.49016508058531844) * (logx - 0.5) +
                          0.27537474159737679) * logx * std::exp(-log1mx *
              log1mx);
            if (log1mx < 0.0) {
              rval = 1.0 - rval;
            }
          }
        } else {
          d = b;
          ntf_gammaln(&d);
          rval = ntf_c_eml_gammainc(0.5 * (((a + b) - 1.0) * (3.0 - x) - (b -
            1.0)) * (1.0 - x), b, std::log(b), d, !upper);
        }
      }
    }
  } else if (x == 0.0) {
    rval = upper;
  } else if (x == 1.0) {
    rval = 1.0 - static_cast<double>(upper);
  } else {
    rval = rtNaN;
  }

  return rval;
}

//
// Arguments    : double p
//                double a
//                double b
//                double lbeta
// Return Type  : double
//
double ntf_eml_betaincinv(double p, double a, double b, double lbeta)
{
  double rval;
  boolean_T upper;
  double t;
  upper = false;
  if ((0.0 < p) && (p < 1.0)) {
    if (a == rtInf) {
      if (b < rtInf) {
        rval = 1.0;
      } else {
        rval = rtNaN;
      }
    } else if (b == rtInf) {
      rval = 0.0;
    } else {
      double pLower;
      double r;
      double y;
      double h;
      int sgn;
      int i;
      boolean_T exitg1;
      if (p > 0.5) {
        p = 1.0 - p;
        upper = true;
        pLower = 1.0 - p;
      } else {
        pLower = p;
      }

      r = std::sqrt(-2.0 * std::log(pLower));
      y = r - (0.27061 * r + 2.30753) / ((0.04481 * r + 0.99229) * r + 1.0);
      if ((a > 1.0) && (b > 1.0)) {
        r = (y * y - 3.0) / 6.0;
        pLower = 1.0 / (2.0 * a - 1.0);
        t = 1.0 / (2.0 * b - 1.0);
        h = 2.0 / (pLower + t);
        rval = a / (a + b * std::exp(2.0 * (y * std::sqrt(h + r) / h - (t -
          pLower) * ((r + 0.83333333333333337) - 2.0 / (3.0 * h)))));
      } else {
        r = 2.0 * b;
        t = 1.0 / (9.0 * b);
        t = (1.0 - t) + y * std::sqrt(t);
        t *= r * t * t;
        if (t > 0.0) {
          t = ((4.0 * a + r) - 2.0) / t;
          if (t > 1.0) {
            rval = 1.0 - 2.0 / (t + 1.0);
          } else {
            rval = std::exp((std::log(pLower * a) + lbeta) / a);
          }
        } else {
          rval = 1.0 - std::exp((std::log((1.0 - pLower) * b) + lbeta) / b);
        }
      }

      if (!(rval > 0.0001)) {
        rval = 0.0001;
      }

      if (!(rval < 0.9999)) {
        rval = 0.9999;
      }

      pLower = rtInf;
      h = rtInf;
      if (p > 1.0021E-294) {
        r = 2.2204460492503131E-14 * p;
      } else {
        r = 2.2251089859537388E-308;
      }

      if (upper) {
        sgn = -1;
      } else {
        sgn = 1;
      }

      y = 0.0;
      t = 1.0;
      i = 0;
      exitg1 = false;
      while ((!exitg1) && (i < 1000)) {
        double f;
        f = static_cast<double>(sgn) * (ntf_eml_betainc(rval, a, b, lbeta, upper)
          - p);
        if ((f * pLower < 0.0) && (std::abs(pLower) <= std::abs(f))) {
          rval = 0.5 * (rval + h);
          f = static_cast<double>(sgn) * (ntf_eml_betainc(rval, a, b, lbeta,
            upper) - p);
        }

        if (f > 0.0) {
          t = rval;
        } else {
          y = rval;
        }

        if ((std::abs(f) < r) || (std::abs(rval - h) < 2.2204460492503131E-16 *
             rval + 2.2250738585072014E-308)) {
          exitg1 = true;
        } else {
          boolean_T guard1 = false;
          boolean_T guard2 = false;
          guard1 = false;
          guard2 = false;
          if (i < 200) {
            double log1mz;
            h = rval;
            pLower = f;
            if (1.0 - rval != 1.0) {
              log1mz = std::log(1.0 - rval) * (-rval / ((1.0 - rval) - 1.0));
            } else {
              log1mz = -rval;
            }

            rval -= f / std::exp(((a - 1.0) * std::log(rval) + (b - 1.0) *
                                  log1mz) - lbeta);
            if (rval <= y) {
              if (y == 0.0) {
                if (std::abs(static_cast<double>(upper) - p) < std::abs
                    (ntf_eml_betainc(2.2250738585072014E-308, a, b, lbeta, upper)
                     - p)) {
                  rval = 0.0;
                  exitg1 = true;
                } else {
                  y = 2.2250738585072014E-308;
                  guard2 = true;
                }
              } else {
                guard2 = true;
              }
            } else if (rval >= t) {
              if (t == 1.0) {
                if (std::abs((1.0 - static_cast<double>(upper)) - p) < std::abs
                    (ntf_eml_betainc(0.99999999999999989, a, b, lbeta, upper) -
                     p)) {
                  rval = 1.0;
                  exitg1 = true;
                } else {
                  t = 0.99999999999999989;
                  guard1 = true;
                }
              } else {
                guard1 = true;
              }
            } else {
              i++;
            }
          } else {
            rval = 0.5 * (y + t);
            i++;
          }

          if (guard2) {
            rval = 0.99 * y + 0.01 * t;
            i++;
          }

          if (guard1) {
            rval = 0.01 * y + 0.99 * t;
            i++;
          }
        }
      }
    }
  } else if (p == 0.0) {
    rval = 0.0;
  } else if (p == 1.0) {
    rval = 1.0;
  } else {
    rval = rtNaN;
  }

  return rval;
}

//
// File trailer for ntf_betaincinv.cpp
//
// [EOF]
//
