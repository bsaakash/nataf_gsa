//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_betainc.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//

// Include Files
#include "ntf_betainc.h"
#include "ntf_gammaln.h"
#include "ntf_inataf.h"
#include "ntf_inataf_data.h"
#include "ntf_inataf_rtwutil.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Declarations
static double ntf_eml_gammainc(double x, double a, double la, double lgap1);

// Function Definitions

//
// Arguments    : double x
//                double a
//                double la
//                double lgap1
// Return Type  : double
//
static double ntf_eml_gammainc(double x, double a, double la, double lgap1)
{
  double rval;
  double asq;
  double t;
  double xD0;
  double vsq;
  if (!(x > 0.0)) {
    if (x == 0.0) {
      rval = 1.0;
    } else {
      rval = rtNaN;
    }
  } else if (rtIsInf(a)) {
    if (rtIsInf(x)) {
      rval = rtNaN;
    } else {
      rval = 1.0;
    }
  } else if (rtIsInf(x)) {
    rval = 0.0;
  } else {
    double b_stirlerr;
    double d;
    double a1;
    double old;
    double logpax;
    int exitg1;
    if (a <= 15.0) {
      asq = 2.0 * a;
      if (asq == std::floor(asq)) {
        b_stirlerr = ntf_dv[static_cast<int>(asq + 1.0) - 1];
      } else {
        b_stirlerr = ((lgap1 - (a + 0.5) * la) + a) - 0.91893853320467267;
      }
    } else {
      asq = a * a;
      b_stirlerr = ((((0.00084175084175084171 / asq + -0.00059523809523809529) /
                      asq + 0.00079365079365079365) / asq +
                     -0.0027777777777777779) / asq + 0.083333333333333329) / a;
    }

    d = a - x;
    a1 = a + x;
    if (std::abs(d) > 0.1 * a1) {
      if (a < 2.2250738585072014E-308 * x) {
        xD0 = x;
      } else if ((x < 1.0) && (a > 1.7976931348623157E+308 * x)) {
        xD0 = (a * la - a * std::log(x)) - a;
      } else {
        xD0 = (a * std::log(a / x) + x) - a;
      }
    } else {
      t = x / a;
      asq = (1.0 - t) / (t + 1.0);
      vsq = asq * asq;
      xD0 = d * asq;
      old = xD0;
      t = 2.0 * (a * asq);
      asq = 3.0;
      do {
        exitg1 = 0;
        t *= vsq;
        xD0 += t / asq;
        if (xD0 == old) {
          exitg1 = 1;
        } else {
          old = xD0;
          asq += 2.0;
        }
      } while (exitg1 == 0);
    }

    logpax = (-0.5 * (la + 1.8378770664093453) - b_stirlerr) - xD0;
    if (x > 1.0E+6) {
      b_stirlerr = std::sqrt(x);
      t = std::abs(d - 1.0) / b_stirlerr;
      old = t * t;
      if (t < 15.0) {
        xD0 = 0.70710678118654746 * t;
        asq = 3.97886080735226 / (xD0 + 3.97886080735226);
        a1 = 0.5 * ((((((((((((((((((((((0.0012710976495261409 * (asq - 0.5) +
          0.00011931402283834095) * (asq - 0.5) + -0.0039638509736051354) * (asq
          - 0.5) + -0.00087077963531729586) * (asq - 0.5) +
          0.0077367252831352668) * (asq - 0.5) + 0.0038333512626488732) * (asq -
          0.5) + -0.012722381378212275) * (asq - 0.5) + -0.013382364453346007) *
          (asq - 0.5) + 0.016131532973325226) * (asq - 0.5) +
          0.039097684558848406) * (asq - 0.5) + 0.0024936720005350331) * (asq -
          0.5) + -0.0838864557023002) * (asq - 0.5) + -0.11946395996432542) *
                             (asq - 0.5) + 0.016620792496936737) * (asq - 0.5) +
                            0.35752427444953105) * (asq - 0.5) +
                           0.80527640875291062) * (asq - 0.5) +
                          1.1890298290927332) * (asq - 0.5) + 1.3704021768233816)
                        * (asq - 0.5) + 1.313146538310231) * (asq - 0.5) +
                       1.0792551515585667) * (asq - 0.5) + 0.77436819911953858) *
                     (asq - 0.5) + 0.49016508058531844) * (asq - 0.5) +
                    0.27537474159737679) * asq * std::exp(-xD0 * xD0) *
          2.5066282746310002 * std::exp(0.5 * old);
        vsq = (a1 * ((old - 3.0) * t) - (old - 4.0)) / 6.0;
        xD0 = (a1 * ((old * old - 9.0) * old + 6.0) - ((old - 1.0) * old - 6.0) *
               t) / 72.0;
        asq = (a1 * (((((5.0 * old + 45.0) * old - 81.0) * old - 315.0) * old +
                      270.0) * t) - ((((5.0 * old + 40.0) * old - 111.0) * old -
                 174.0) * old + 192.0)) / 6480.0;
      } else {
        a1 = (((3.0 - 15.0 / old) / old + -1.0) / old + 1.0) / t;
        vsq = (((25.0 - 210.0 / old) / old + -4.0) / old + 1.0) / old;
        xD0 = (((130.0 - 1750.0 / old) / old + -11.0) / old + 1.0) / (old * t);
        asq = (((546.0 - 11368.0 / old) / old + -26.0) / old + 1.0) / (old * old);
      }

      if (x < a - 1.0) {
        asq = a * (((a1 / b_stirlerr - vsq / x) + xD0 / (x * b_stirlerr)) - asq /
                   (x * x));
        if (logpax < 709.782712893384) {
          logpax = std::exp(logpax) * asq;
        } else {
          logpax = std::exp(logpax + std::log(asq));
        }

        rval = 1.0 - logpax;
      } else {
        asq = a * (((a1 / b_stirlerr + vsq / x) + xD0 / (x * b_stirlerr)) + asq /
                   (x * x));
        if (logpax < 709.782712893384) {
          rval = std::exp(logpax) * asq;
        } else {
          rval = std::exp(logpax + std::log(asq));
        }
      }
    } else if ((x < 1.0) && (a < 1.0)) {
      double fac;
      double n;
      fac = a * -x;
      vsq = fac / (a + 1.0);
      n = 2.0;
      do {
        exitg1 = 0;
        fac = -x * fac / n;
        t = fac / (a + n);
        vsq += t;
        if (std::abs(t) <= std::abs(vsq) * 2.2204460492503131E-16) {
          exitg1 = 1;
        } else {
          n++;
        }
      } while (exitg1 == 0);

      asq = a * std::log(x) - lgap1;
      xD0 = std::exp(asq);
      if (!(xD0 == 1.0)) {
        if (xD0 - 1.0 == -1.0) {
          asq = -1.0;
        } else {
          asq = (xD0 - 1.0) * asq / std::log(xD0);
        }
      }

      rval = -((vsq + asq) + vsq * asq);
      if (rval < 0.0) {
        rval = 0.0;
      }
    } else if ((x < a) || (x < 1.0)) {
      double n;
      n = 1.0;
      if ((!(x < a)) && (a < 2.2250738585072014E-308) && (x >
           1.7976931348623157E+308 * a)) {
        rval = 0.0;
      } else {
        int i;
        if (x > 2.2204460492503131E-16 * a) {
          double fac;
          fac = x / a;
          n = 2.0;
          do {
            exitg1 = 0;
            fac = x * fac / (a + (n - 1.0));
            if (fac < 2.2204460492503131E-16) {
              exitg1 = 1;
            } else {
              n++;
            }
          } while (exitg1 == 0);
        }

        asq = 0.0;
        i = static_cast<int>(((-1.0 - (n - 1.0)) + 1.0) / -1.0);
        for (int b_i = 0; b_i < i; b_i++) {
          asq = x * (asq + 1.0) / (a + ((n - 1.0) + -static_cast<double>(b_i)));
        }

        asq++;
        if (logpax < 709.782712893384) {
          rval = std::exp(logpax) * asq;
        } else {
          rval = std::exp(logpax + std::log(asq));
        }

        if (rval > 1.0) {
          rval = 1.0;
        }

        rval = 1.0 - rval;
      }
    } else {
      double fac;
      double n;
      int i;
      fac = 1.0;
      n = 1.0;
      do {
        exitg1 = 0;
        d = std::floor(a1);
        if (n <= d) {
          fac = (a - n) * fac / x;
          if (std::abs(fac) < 2.2204460492503131E-16) {
            exitg1 = 1;
          } else {
            n++;
          }
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);

      if (n <= d) {
        asq = 1.0;
      } else {
        n = std::floor(a);
        vsq = a - n;
        if (vsq == 0.0) {
          asq = 1.0;
        } else if (vsq == 0.5) {
          xD0 = 0.70710678118654746 * std::sqrt(2.0 * x);
          t = 3.97886080735226 / (xD0 + 3.97886080735226);
          asq = std::sqrt(3.1415926535897931 * x) * std::exp(x) * (2.0 * (0.5 *
            ((((((((((((((((((((((0.0012710976495261409 * (t - 0.5) +
            0.00011931402283834095) * (t - 0.5) + -0.0039638509736051354) * (t -
            0.5) + -0.00087077963531729586) * (t - 0.5) + 0.0077367252831352668)
            * (t - 0.5) + 0.0038333512626488732) * (t - 0.5) +
                             -0.012722381378212275) * (t - 0.5) +
                            -0.013382364453346007) * (t - 0.5) +
                           0.016131532973325226) * (t - 0.5) +
                          0.039097684558848406) * (t - 0.5) +
                         0.0024936720005350331) * (t - 0.5) +
                        -0.0838864557023002) * (t - 0.5) + -0.11946395996432542)
                      * (t - 0.5) + 0.016620792496936737) * (t - 0.5) +
                     0.35752427444953105) * (t - 0.5) + 0.80527640875291062) *
                   (t - 0.5) + 1.1890298290927332) * (t - 0.5) +
                  1.3704021768233816) * (t - 0.5) + 1.313146538310231) * (t -
            0.5) + 1.0792551515585667) * (t - 0.5) + 0.77436819911953858) * (t -
            0.5) + 0.49016508058531844) * (t - 0.5) + 0.27537474159737679) * t *
            std::exp(-xD0 * xD0)));
          n++;
        } else {
          xD0 = 1.0;
          a1 = x;
          old = 0.0;
          b_stirlerr = 1.0;
          fac = 1.0 / x;
          n = 1.0;
          asq = fac;
          t = 0.0;
          while (std::abs(asq - t) > 2.2204460492503131E-16 * asq) {
            t = asq;
            asq = n - vsq;
            xD0 = (a1 + xD0 * asq) * fac;
            old = (b_stirlerr + old * asq) * fac;
            asq = n * fac;
            a1 = x * xD0 + asq * a1;
            b_stirlerr = x * old + asq * b_stirlerr;
            fac = 1.0 / a1;
            asq = b_stirlerr * fac;
            n++;
          }

          asq *= x;
          n = std::floor(a) + 1.0;
        }
      }

      i = static_cast<int>(((-1.0 - (n - 1.0)) + 1.0) / -1.0);
      for (int b_i = 0; b_i < i; b_i++) {
        asq = (a - ((n - 1.0) + -static_cast<double>(b_i))) * asq / x + 1.0;
      }

      asq = asq * a / x;
      if (logpax < 709.782712893384) {
        rval = std::exp(logpax) * asq;
      } else {
        rval = std::exp(logpax + std::log(asq));
      }

      if (rval > 1.0) {
        rval = 1.0;
      }
    }
  }

  return rval;
}

//
// Arguments    : double x
//                double a
//                double b
// Return Type  : creal_T
//
creal_T ntf_betainc(double x, double a, double b)
{
  creal_T y;
  double betai;
  double logx;
  double d;
  double log1mx;
  betai = a;
  ntf_gammaln(&betai);
  logx = b;
  ntf_gammaln(&logx);
  d = a + b;
  log1mx = d;
  ntf_gammaln(&log1mx);
  betai = (betai + logx) - log1mx;
  if (!(a >= 0.0)) {
    betai = rtNaN;
  } else if (!(b >= 0.0)) {
    betai = rtNaN;
  } else if ((0.0 < x) && (x < 1.0)) {
    if (a == 0.0) {
      if (b > 0.0) {
        betai = !(x == 0.0);
      } else if (x == 0.0) {
        betai = 0.0;
      } else if (x == 1.0) {
        betai = 1.0;
      } else {
        betai = rtNaN;
      }
    } else if (b == 0.0) {
      betai = !(x < 1.0);
    } else if (rtIsInf(a)) {
      if (!rtIsInf(b)) {
        betai = !(x < 1.0);
      } else if (x == 0.0) {
        betai = 0.0;
      } else if (x == 1.0) {
        betai = 1.0;
      } else {
        betai = rtNaN;
      }
    } else if (rtIsInf(b)) {
      betai = !(x == 0.0);
    } else {
      boolean_T guard1 = false;
      guard1 = false;
      if (d < 1.0E+7) {
        logx = std::log(x);
        if (1.0 - x != 1.0) {
          log1mx = std::log(1.0 - x) * (-x / ((1.0 - x) - 1.0));
        } else {
          log1mx = -x;
        }

        if (x < (a + 1.0) / (d + 2.0)) {
          betai = std::exp(((a * logx + b * log1mx) - std::log(a)) - betai) *
            ntf_betainc_cf(x, a, b);
        } else {
          betai = 1.0 - std::exp(((a * logx + b * log1mx) - std::log(b)) - betai)
            * ntf_betainc_cf(1.0 - x, b, a);
        }

        if (!(betai == betai)) {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        betai = ntf_rt_powd_snf(b * x, 0.33333333333333331);
        logx = ntf_rt_powd_snf(a * (1.0 - x), 0.33333333333333331);
        if ((d - 1.0) * (1.0 - x) > 0.8) {
          logx = 0.70710678118654746 * -(3.0 * ((1.0 - 1.0 / (9.0 * b)) * betai
            - (1.0 - 1.0 / (9.0 * a)) * logx) / std::sqrt(betai * betai / b +
            logx * logx / a));
          betai = 3.97886080735226 / (std::abs(logx) + 3.97886080735226);
          betai = 0.5 * ((((((((((((((((((((((0.0012710976495261409 * (betai -
            0.5) + 0.00011931402283834095) * (betai - 0.5) +
            -0.0039638509736051354) * (betai - 0.5) + -0.00087077963531729586) *
            (betai - 0.5) + 0.0077367252831352668) * (betai - 0.5) +
            0.0038333512626488732) * (betai - 0.5) + -0.012722381378212275) *
            (betai - 0.5) + -0.013382364453346007) * (betai - 0.5) +
            0.016131532973325226) * (betai - 0.5) + 0.039097684558848406) *
            (betai - 0.5) + 0.0024936720005350331) * (betai - 0.5) +
            -0.0838864557023002) * (betai - 0.5) + -0.11946395996432542) *
            (betai - 0.5) + 0.016620792496936737) * (betai - 0.5) +
            0.35752427444953105) * (betai - 0.5) + 0.80527640875291062) * (betai
            - 0.5) + 1.1890298290927332) * (betai - 0.5) + 1.3704021768233816) *
                             (betai - 0.5) + 1.313146538310231) * (betai - 0.5)
                            + 1.0792551515585667) * (betai - 0.5) +
                           0.77436819911953858) * (betai - 0.5) +
                          0.49016508058531844) * (betai - 0.5) +
                         0.27537474159737679) * betai * std::exp(-logx * logx);
          if (logx < 0.0) {
            betai = 1.0 - betai;
          }
        } else {
          betai = b;
          ntf_gammaln(&betai);
          betai = ntf_eml_gammainc(0.5 * (((a + b) - 1.0) * (3.0 - x) - (b - 1.0))
            * (1.0 - x), b, std::log(b), betai);
        }
      }
    }
  } else if (x == 0.0) {
    betai = 0.0;
  } else if (x == 1.0) {
    betai = 1.0;
  } else {
    betai = rtNaN;
  }

  y.re = betai;
  y.im = 0.0;
  return y;
}

//
// Arguments    : double x
//                double a
//                double b
// Return Type  : double
//
double ntf_betainc_cf(double x, double a, double b)
{
  double y;
  double aplusb;
  double C;
  double Dinv;
  int m;
  aplusb = a + b;
  C = 1.0;
  Dinv = 1.0 - aplusb * x / (a + 1.0);
  y = 1.0 / Dinv;
  m = 0;
  int exitg1;
  do {
    exitg1 = 0;
    if (m < 1000) {
      double yold;
      int twom;
      double d_tmp;
      double d;
      yold = y;
      twom = (m + 1) << 1;
      d_tmp = a + static_cast<double>(twom);
      d = (static_cast<double>(m) + 1.0) * (b - (static_cast<double>(m) + 1.0)) *
        x / (((a - 1.0) + static_cast<double>(twom)) * d_tmp);
      C = d / C + 1.0;
      Dinv = d / Dinv + 1.0;
      y *= C / Dinv;
      d = -(a + (static_cast<double>(m) + 1.0)) * (aplusb + (static_cast<double>
        (m) + 1.0)) * x / (d_tmp * ((a + 1.0) + static_cast<double>(twom)));
      C = d / C + 1.0;
      Dinv = d / Dinv + 1.0;
      y *= C / Dinv;
      if (std::abs(y - yold) < 2.2204460492503131E-15) {
        exitg1 = 1;
      } else {
        m++;
      }
    } else {
      y = rtNaN;
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return y;
}

//
// File trailer for ntf_betainc.cpp
//
// [EOF]
//
