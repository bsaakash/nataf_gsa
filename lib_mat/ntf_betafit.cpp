//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_betafit.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_betafit.h"
#include "ntf_betainc.h"
#include "ntf_gammaln.h"
#include "ntf_inataf.h"
#include "ntf_inataf_data.h"
#include "ntf_inataf_rtwutil.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Declarations
static double ntf_b_eml_gammainc(double x, double a, double la, double lgap1);

// Function Definitions

//
// Arguments    : double x
//                double a
//                double la
//                double lgap1
// Return Type  : double
//
static double ntf_b_eml_gammainc(double x, double a, double la, double lgap1)
{
  double rval;
  double asq;
  double xD0;
  double dj;
  if (!(x > 0.0)) {
    if (x == 0.0) {
      rval = 0.0;
    } else {
      rval = rtNaN;
    }
  } else if (rtIsInf(a)) {
    if (rtIsInf(x)) {
      rval = rtNaN;
    } else {
      rval = 0.0;
    }
  } else if (rtIsInf(x)) {
    rval = 1.0;
  } else {
    double b_stirlerr;
    double d;
    double a1;
    double t;
    double vsq;
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
      asq = 2.0 * (a * asq);
      dj = 3.0;
      do {
        exitg1 = 0;
        asq *= vsq;
        xD0 += asq / dj;
        if (xD0 == old) {
          exitg1 = 1;
        } else {
          old = xD0;
          dj += 2.0;
        }
      } while (exitg1 == 0);
    }

    logpax = (-0.5 * (la + 1.8378770664093453) - b_stirlerr) - xD0;
    if (x > 1.0E+6) {
      old = std::sqrt(x);
      t = std::abs(d - 1.0) / old;
      xD0 = t * t;
      if (t < 15.0) {
        dj = 0.70710678118654746 * t;
        asq = 3.97886080735226 / (dj + 3.97886080735226);
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
                    0.27537474159737679) * asq * std::exp(-dj * dj) *
          2.5066282746310002 * std::exp(0.5 * xD0);
        dj = (a1 * ((xD0 - 3.0) * t) - (xD0 - 4.0)) / 6.0;
        vsq = (a1 * ((xD0 * xD0 - 9.0) * xD0 + 6.0) - ((xD0 - 1.0) * xD0 - 6.0) *
               t) / 72.0;
        asq = (a1 * (((((5.0 * xD0 + 45.0) * xD0 - 81.0) * xD0 - 315.0) * xD0 +
                      270.0) * t) - ((((5.0 * xD0 + 40.0) * xD0 - 111.0) * xD0 -
                 174.0) * xD0 + 192.0)) / 6480.0;
      } else {
        a1 = (((3.0 - 15.0 / xD0) / xD0 + -1.0) / xD0 + 1.0) / t;
        dj = (((25.0 - 210.0 / xD0) / xD0 + -4.0) / xD0 + 1.0) / xD0;
        vsq = (((130.0 - 1750.0 / xD0) / xD0 + -11.0) / xD0 + 1.0) / (xD0 * t);
        asq = (((546.0 - 11368.0 / xD0) / xD0 + -26.0) / xD0 + 1.0) / (xD0 * xD0);
      }

      if (x < a - 1.0) {
        asq = a * (((a1 / old - dj / x) + vsq / (x * old)) - asq / (x * x));
        if (logpax < 709.782712893384) {
          rval = std::exp(logpax) * asq;
        } else {
          rval = std::exp(logpax + std::log(asq));
        }
      } else {
        asq = a * (((a1 / old + dj / x) + vsq / (x * old)) + asq / (x * x));
        if (logpax < 709.782712893384) {
          logpax = std::exp(logpax) * asq;
        } else {
          logpax = std::exp(logpax + std::log(asq));
        }

        rval = 1.0 - logpax;
      }
    } else if ((x < a) || (x < 1.0)) {
      double n;
      n = 1.0;
      if ((!(x < a)) && (a < 2.2250738585072014E-308) && (x >
           1.7976931348623157E+308 * a)) {
        rval = 1.0;
      } else {
        int i;
        if (x > 2.2204460492503131E-16 * a) {
          t = x / a;
          n = 2.0;
          do {
            exitg1 = 0;
            t = x * t / (a + (n - 1.0));
            if (t < 2.2204460492503131E-16) {
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
      }
    } else {
      double n;
      int i;
      t = 1.0;
      n = 1.0;
      do {
        exitg1 = 0;
        d = std::floor(a1);
        if (n <= d) {
          t = (a - n) * t / x;
          if (std::abs(t) < 2.2204460492503131E-16) {
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
        dj = a - n;
        if (dj == 0.0) {
          asq = 1.0;
        } else if (dj == 0.5) {
          dj = 0.70710678118654746 * std::sqrt(2.0 * x);
          t = 3.97886080735226 / (dj + 3.97886080735226);
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
            std::exp(-dj * dj)));
          n++;
        } else {
          vsq = 1.0;
          a1 = x;
          xD0 = 0.0;
          old = 1.0;
          t = 1.0 / x;
          n = 1.0;
          asq = t;
          b_stirlerr = 0.0;
          while (std::abs(asq - b_stirlerr) > 2.2204460492503131E-16 * asq) {
            b_stirlerr = asq;
            asq = n - dj;
            vsq = (a1 + vsq * asq) * t;
            xD0 = (old + xD0 * asq) * t;
            asq = n * t;
            a1 = x * vsq + asq * a1;
            old = x * xD0 + asq * old;
            t = 1.0 / a1;
            asq = old * t;
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

      rval = 1.0 - rval;
    }
  }

  return rval;
}

//
// Arguments    : double p[2]
// Return Type  : double
//
double ntf_negloglike(double p[2])
{
  double nll;
  double betai;
  double logx;
  double d;
  double log1mx;
  p[0] = std::exp(p[0]);
  p[1] = std::exp(p[1]);
  betai = p[0];
  ntf_gammaln(&betai);
  logx = p[1];
  ntf_gammaln(&logx);
  d = p[0] + p[1];
  log1mx = d;
  ntf_gammaln(&log1mx);
  nll = (ntf_n2 * ((betai + logx) - log1mx) - (p[0] - 1.0) * ntf_sumlogx) - (p[1]
    - 1.0) * ntf_sumlog1mx;
  if (ntf_n0 > 0.0) {
    nll -= ntf_n0 * std::log((ntf_betainc(ntf_xl, p[0], p[1])).re);
  }

  if (ntf_n1 > 0.0) {
    betai = p[0];
    ntf_gammaln(&betai);
    logx = p[1];
    ntf_gammaln(&logx);
    log1mx = d;
    ntf_gammaln(&log1mx);
    betai = (betai + logx) - log1mx;
    if (!(p[0] >= 0.0)) {
      betai = rtNaN;
    } else if (!(p[1] >= 0.0)) {
      betai = rtNaN;
    } else if (!(0.0 < ntf_xu)) {
      if (ntf_xu == 0.0) {
        betai = 1.0;
      } else {
        betai = rtNaN;
      }
    } else if (p[0] == 0.0) {
      if (p[1] > 0.0) {
        betai = (ntf_xu == 0.0);
      } else if (ntf_xu == 0.0) {
        betai = 1.0;
      } else {
        betai = rtNaN;
      }
    } else if (p[1] == 0.0) {
      betai = 1.0;
    } else if (rtIsInf(p[0])) {
      if (!rtIsInf(p[1])) {
        betai = 1.0;
      } else if (ntf_xu == 0.0) {
        betai = 1.0;
      } else {
        betai = rtNaN;
      }
    } else if (rtIsInf(p[1])) {
      betai = (ntf_xu == 0.0);
    } else {
      boolean_T guard1 = false;
      guard1 = false;
      if (d < 1.0E+7) {
        logx = std::log(ntf_xu);
        if (1.0 - ntf_xu != 1.0) {
          log1mx = std::log(1.0 - ntf_xu) * (-ntf_xu / ((1.0 - ntf_xu) - 1.0));
        } else {
          log1mx = -ntf_xu;
        }

        if (ntf_xu < (p[0] + 1.0) / (d + 2.0)) {
          betai = 1.0 - std::exp(((p[0] * logx + p[1] * log1mx) - std::log(p[0]))
            - betai) * ntf_betainc_cf(ntf_xu, p[0], p[1]);
        } else {
          betai = std::exp(((p[0] * logx + p[1] * log1mx) - std::log(p[1])) -
                           betai) * ntf_betainc_cf(1.0 - ntf_xu, p[1], p[0]);
        }

        if (!(betai == betai)) {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        betai = ntf_rt_powd_snf(p[1] * ntf_xu, 0.33333333333333331);
        logx = ntf_rt_powd_snf(p[0] * (1.0 - ntf_xu), 0.33333333333333331);
        if ((d - 1.0) * (1.0 - ntf_xu) > 0.8) {
          logx = 0.70710678118654746 * (3.0 * ((1.0 - 1.0 / (9.0 * p[1])) *
            betai - (1.0 - 1.0 / (9.0 * p[0])) * logx) / std::sqrt(betai * betai
            / p[1] + logx * logx / p[0]));
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
          betai = p[1];
          ntf_gammaln(&betai);
          betai = ntf_b_eml_gammainc(0.5 * (((p[0] + p[1]) - 1.0) * (3.0 -
            ntf_xu) - (p[1] - 1.0)) * (1.0 - ntf_xu), p[1], std::log(p[1]),
            betai);
        }
      }
    }

    nll -= ntf_n1 * std::log(betai);
  }

  return nll;
}

//
// Arguments    : void
// Return Type  : void
//
void ntf_negloglike_init()
{
  ntf_sumlogx = 0.0;
  ntf_sumlog1mx = 0.0;
  ntf_n0 = 0.0;
  ntf_n1 = 0.0;
  ntf_n2 = 0.0;
  ntf_xl = 0.0;
  ntf_xu = 0.0;
}

//
// File trailer for ntf_betafit.cpp
//
// [EOF]
//
