//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_gammainc.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_gammainc.h"
#include "ntf_cospiAndSinpi.h"
#include "ntf_gammaln.h"
#include "ntf_inataf.h"
#include "ntf_inataf_data.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Declarations
static double ntf_d_eml_gammainc(double x, double a, double la, double lgap1);

// Function Definitions

//
// Arguments    : double x
//                double a
//                double la
//                double lgap1
// Return Type  : double
//
static double ntf_d_eml_gammainc(double x, double a, double la, double lgap1)
{
  double rval;
  double asq;
  double xD0;
  double dj;
  if (!(a > 0.0)) {
    if (x == x) {
      rval = 1.0;
    } else {
      rval = rtNaN;
    }
  } else if (!(x > 0.0)) {
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
    double gold;
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

    gold = a - x;
    a1 = a + x;
    if (std::abs(gold) > 0.1 * a1) {
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
      xD0 = gold * asq;
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
      t = std::abs(gold - 1.0) / old;
      xD0 = t * t;
      if (t < 15.0) {
        asq = 0.70710678118654746 * t;
        dj = 3.97886080735226 / (asq + 3.97886080735226);
        a1 = 0.5 * ((((((((((((((((((((((0.0012710976495261409 * (dj - 0.5) +
          0.00011931402283834095) * (dj - 0.5) + -0.0039638509736051354) * (dj -
          0.5) + -0.00087077963531729586) * (dj - 0.5) + 0.0077367252831352668) *
          (dj - 0.5) + 0.0038333512626488732) * (dj - 0.5) +
          -0.012722381378212275) * (dj - 0.5) + -0.013382364453346007) * (dj -
          0.5) + 0.016131532973325226) * (dj - 0.5) + 0.039097684558848406) *
          (dj - 0.5) + 0.0024936720005350331) * (dj - 0.5) + -0.0838864557023002)
                              * (dj - 0.5) + -0.11946395996432542) * (dj - 0.5)
                             + 0.016620792496936737) * (dj - 0.5) +
                            0.35752427444953105) * (dj - 0.5) +
                           0.80527640875291062) * (dj - 0.5) +
                          1.1890298290927332) * (dj - 0.5) + 1.3704021768233816)
                        * (dj - 0.5) + 1.313146538310231) * (dj - 0.5) +
                       1.0792551515585667) * (dj - 0.5) + 0.77436819911953858) *
                     (dj - 0.5) + 0.49016508058531844) * (dj - 0.5) +
                    0.27537474159737679) * dj * std::exp(-asq * asq) *
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
      t = 1.0;
      if ((!(x < a)) && (a < 2.2250738585072014E-308) && (x >
           1.7976931348623157E+308 * a)) {
        rval = 1.0;
      } else {
        int i;
        if (x > 2.2204460492503131E-16 * a) {
          dj = x / a;
          t = 2.0;
          do {
            exitg1 = 0;
            dj = x * dj / (a + (t - 1.0));
            if (dj < 2.2204460492503131E-16) {
              exitg1 = 1;
            } else {
              t++;
            }
          } while (exitg1 == 0);
        }

        asq = 0.0;
        i = static_cast<int>(((-1.0 - (t - 1.0)) + 1.0) / -1.0);
        for (int afrac_tmp_tmp = 0; afrac_tmp_tmp < i; afrac_tmp_tmp++) {
          asq = x * (asq + 1.0) / (a + ((t - 1.0) + -static_cast<double>
            (afrac_tmp_tmp)));
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
      int i;
      int afrac_tmp_tmp;
      dj = 1.0;
      t = 1.0;
      do {
        exitg1 = 0;
        i = static_cast<int>(std::floor(a1));
        afrac_tmp_tmp = static_cast<int>(t);
        if (afrac_tmp_tmp <= i) {
          dj = (a - t) * dj / x;
          if (std::abs(dj) < 2.2204460492503131E-16) {
            exitg1 = 1;
          } else {
            t++;
          }
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);

      if (afrac_tmp_tmp <= i) {
        asq = 1.0;
      } else {
        afrac_tmp_tmp = static_cast<int>(std::floor(a));
        vsq = a - static_cast<double>(afrac_tmp_tmp);
        if (vsq == 0.0) {
          asq = 1.0;
          t = afrac_tmp_tmp;
        } else if (vsq == 0.5) {
          asq = 0.70710678118654746 * std::sqrt(2.0 * x);
          t = 3.97886080735226 / (asq + 3.97886080735226);
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
            std::exp(-asq * asq)));
          t = static_cast<double>(afrac_tmp_tmp) + 1.0;
        } else {
          xD0 = 1.0;
          a1 = x;
          old = 0.0;
          b_stirlerr = 1.0;
          dj = 1.0 / x;
          t = 1.0;
          asq = dj;
          gold = 0.0;
          while (std::abs(asq - gold) > 2.2204460492503131E-16 * asq) {
            gold = asq;
            asq = t - vsq;
            xD0 = (a1 + xD0 * asq) * dj;
            old = (b_stirlerr + old * asq) * dj;
            asq = t * dj;
            a1 = x * xD0 + asq * a1;
            b_stirlerr = x * old + asq * b_stirlerr;
            dj = 1.0 / a1;
            asq = b_stirlerr * dj;
            t++;
          }

          asq *= x;
          t = static_cast<double>(afrac_tmp_tmp) + 1.0;
        }
      }

      i = static_cast<int>(((-1.0 - (t - 1.0)) + 1.0) / -1.0);
      for (afrac_tmp_tmp = 0; afrac_tmp_tmp < i; afrac_tmp_tmp++) {
        asq = (a - ((t - 1.0) + -static_cast<double>(afrac_tmp_tmp))) * asq / x
          + 1.0;
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
// Arguments    : double x
//                double a
// Return Type  : creal_T
//
creal_T ntf_gammainc(double x, double a)
{
  creal_T b;
  double Iax;
  double i;
  Iax = a + 1.0;
  ntf_gammaln(&Iax);
  if (!(x < 0.0)) {
    b.re = ntf_d_eml_gammainc(x, a, std::log(a), Iax);
    b.im = 0.0;
  } else {
    double pax_modulus;
    if (x == rtMinusInf) {
      pax_modulus = rtNaN;
      Iax = rtNaN;
    } else if (a == rtInf) {
      pax_modulus = rtNaN;
      Iax = rtNaN;
    } else {
      double pax_r;
      double pax_i;
      double d;
      pax_modulus = std::exp((-x + a * std::log(-x)) - Iax);
      if (a == 1.0) {
        pax_r = -pax_modulus;
        pax_i = 0.0;
      } else {
        ntf_cospiAndSinpi(a, &Iax, &i);
        pax_r = pax_modulus * Iax;
        pax_i = pax_modulus * i;
      }

      Iax = 1.0;
      pax_modulus = 1.0;
      i = 1.0;
      int exitg1;
      do {
        exitg1 = 0;
        pax_modulus = pax_modulus * x / (a + i);
        Iax += pax_modulus;
        d = std::abs(Iax);
        if (std::abs(pax_modulus) <= 2.2204460492503131E-16 * d) {
          exitg1 = 1;
        } else {
          i++;
        }
      } while (exitg1 == 0);

      pax_modulus = d * pax_r;
      if (pax_i == 0.0) {
        Iax = 0.0;
      } else {
        Iax = d * pax_i;
      }
    }

    b.re = pax_modulus;
    b.im = Iax;
  }

  return b;
}

//
// Arguments    : double x
//                double a
//                double la
//                double lgap1
// Return Type  : creal_T
//
creal_T ntf_scalar_gammainc(double x, double a, double la, double lgap1)
{
  creal_T b;
  double asq;
  double xD0;
  double dj;
  if (!(a > 0.0)) {
    if (a == 0.0) {
      if (x == x) {
        asq = 0.0;
      } else {
        asq = rtNaN;
      }
    } else {
      asq = rtNaN;
    }
  } else if (!(x > 0.0)) {
    asq = 1.0;
  } else if (rtIsInf(a)) {
    if (rtIsInf(x)) {
      asq = rtNaN;
    } else {
      asq = 1.0;
    }
  } else if (rtIsInf(x)) {
    asq = 0.0;
  } else {
    double b_stirlerr;
    double gold;
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

    gold = a - x;
    a1 = a + x;
    if (std::abs(gold) > 0.1 * a1) {
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
      xD0 = gold * asq;
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
      t = std::abs(gold - 1.0) / old;
      xD0 = t * t;
      if (t < 15.0) {
        asq = 0.70710678118654746 * t;
        dj = 3.97886080735226 / (asq + 3.97886080735226);
        a1 = 0.5 * ((((((((((((((((((((((0.0012710976495261409 * (dj - 0.5) +
          0.00011931402283834095) * (dj - 0.5) + -0.0039638509736051354) * (dj -
          0.5) + -0.00087077963531729586) * (dj - 0.5) + 0.0077367252831352668) *
          (dj - 0.5) + 0.0038333512626488732) * (dj - 0.5) +
          -0.012722381378212275) * (dj - 0.5) + -0.013382364453346007) * (dj -
          0.5) + 0.016131532973325226) * (dj - 0.5) + 0.039097684558848406) *
          (dj - 0.5) + 0.0024936720005350331) * (dj - 0.5) + -0.0838864557023002)
                              * (dj - 0.5) + -0.11946395996432542) * (dj - 0.5)
                             + 0.016620792496936737) * (dj - 0.5) +
                            0.35752427444953105) * (dj - 0.5) +
                           0.80527640875291062) * (dj - 0.5) +
                          1.1890298290927332) * (dj - 0.5) + 1.3704021768233816)
                        * (dj - 0.5) + 1.313146538310231) * (dj - 0.5) +
                       1.0792551515585667) * (dj - 0.5) + 0.77436819911953858) *
                     (dj - 0.5) + 0.49016508058531844) * (dj - 0.5) +
                    0.27537474159737679) * dj * std::exp(-asq * asq) *
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
          logpax = std::exp(logpax) * asq;
        } else {
          logpax = std::exp(logpax + std::log(asq));
        }

        asq = 1.0 - logpax;
      } else {
        asq = a * (((a1 / old + dj / x) + vsq / (x * old)) + asq / (x * x));
        if (logpax < 709.782712893384) {
          asq *= std::exp(logpax);
        } else {
          asq = std::exp(logpax + std::log(asq));
        }
      }
    } else if (x < a) {
      int i;
      t = 1.0;
      if (x > 2.2204460492503131E-16 * a) {
        dj = x / a;
        t = 2.0;
        do {
          exitg1 = 0;
          dj = x * dj / (a + (t - 1.0));
          if (dj < 2.2204460492503131E-16) {
            exitg1 = 1;
          } else {
            t++;
          }
        } while (exitg1 == 0);
      }

      asq = 0.0;
      i = static_cast<int>(((-1.0 - (t - 1.0)) + 1.0) / -1.0);
      for (int afrac_tmp_tmp = 0; afrac_tmp_tmp < i; afrac_tmp_tmp++) {
        asq = x * (asq + 1.0) / (a + ((t - 1.0) + -static_cast<double>
          (afrac_tmp_tmp)));
      }

      asq++;
      if (logpax < 709.782712893384) {
        asq *= std::exp(logpax);
      } else {
        asq = std::exp(logpax + std::log(asq));
      }

      if (asq > 1.0) {
        asq = 1.0;
      }

      asq = 1.0 - asq;
    } else {
      int i;
      int afrac_tmp_tmp;
      dj = 1.0;
      t = 1.0;
      do {
        exitg1 = 0;
        i = static_cast<int>(std::floor(a1));
        afrac_tmp_tmp = static_cast<int>(t);
        if (afrac_tmp_tmp <= i) {
          dj = (a - t) * dj / x;
          if (std::abs(dj) < 2.2204460492503131E-16) {
            exitg1 = 1;
          } else {
            t++;
          }
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);

      if (afrac_tmp_tmp <= i) {
        asq = 1.0;
      } else {
        afrac_tmp_tmp = static_cast<int>(std::floor(a));
        vsq = a - static_cast<double>(afrac_tmp_tmp);
        if (vsq == 0.0) {
          asq = 1.0;
          t = afrac_tmp_tmp;
        } else if (vsq == 0.5) {
          asq = 0.70710678118654746 * std::sqrt(2.0 * x);
          t = 3.97886080735226 / (asq + 3.97886080735226);
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
            std::exp(-asq * asq)));
          t = static_cast<double>(afrac_tmp_tmp) + 1.0;
        } else {
          xD0 = 1.0;
          a1 = x;
          old = 0.0;
          b_stirlerr = 1.0;
          dj = 1.0 / x;
          t = 1.0;
          asq = dj;
          gold = 0.0;
          while (std::abs(asq - gold) > 2.2204460492503131E-16 * asq) {
            gold = asq;
            asq = t - vsq;
            xD0 = (a1 + xD0 * asq) * dj;
            old = (b_stirlerr + old * asq) * dj;
            asq = t * dj;
            a1 = x * xD0 + asq * a1;
            b_stirlerr = x * old + asq * b_stirlerr;
            dj = 1.0 / a1;
            asq = b_stirlerr * dj;
            t++;
          }

          asq *= x;
          t = static_cast<double>(afrac_tmp_tmp) + 1.0;
        }
      }

      i = static_cast<int>(((-1.0 - (t - 1.0)) + 1.0) / -1.0);
      for (afrac_tmp_tmp = 0; afrac_tmp_tmp < i; afrac_tmp_tmp++) {
        asq = (a - ((t - 1.0) + -static_cast<double>(afrac_tmp_tmp))) * asq / x
          + 1.0;
      }

      asq = asq * a / x;
      if (logpax < 709.782712893384) {
        asq *= std::exp(logpax);
      } else {
        asq = std::exp(logpax + std::log(asq));
      }

      if (asq > 1.0) {
        asq = 1.0;
      }
    }
  }

  b.re = asq;
  b.im = 0.0;
  return b;
}

//
// File trailer for ntf_gammainc.cpp
//
// [EOF]
//
