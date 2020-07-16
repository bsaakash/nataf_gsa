//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_gammaincinv.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//

// Include Files
#include "ntf_gammaincinv.h"
#include "ntf_inataf.h"
#include "ntf_inataf_data.h"
#include "ntf_inataf_rtwutil.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double x
//                double a
//                double la
//                double lgap1
//                boolean_T upper
// Return Type  : double
//
double ntf_c_eml_gammainc(double x, double a, double la, double lgap1, boolean_T
  upper)
{
  double rval;
  double asq;
  double t;
  double xD0;
  double vsq;
  if (!(x > 0.0)) {
    if (x == 0.0) {
      rval = upper;
    } else {
      rval = rtNaN;
    }
  } else if (rtIsInf(a)) {
    if (rtIsInf(x)) {
      rval = rtNaN;
    } else {
      rval = upper;
    }
  } else if (rtIsInf(x)) {
    rval = 1.0 - static_cast<double>(upper);
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
          rval = std::exp(logpax) * asq;
        } else {
          rval = std::exp(logpax + std::log(asq));
        }

        if (upper) {
          rval = 1.0 - rval;
        }
      } else {
        asq = a * (((a1 / b_stirlerr + vsq / x) + xD0 / (x * b_stirlerr)) + asq /
                   (x * x));
        if (logpax < 709.782712893384) {
          rval = std::exp(logpax) * asq;
        } else {
          rval = std::exp(logpax + std::log(asq));
        }

        if (!upper) {
          rval = 1.0 - rval;
        }
      }
    } else if (upper && (x < 1.0) && (a < 1.0)) {
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
        rval = 1.0 - static_cast<double>(upper);
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

        if (upper) {
          rval = 1.0 - rval;
        }
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

      if (!upper) {
        rval = 1.0 - rval;
      }
    }
  }

  return rval;
}

//
// Arguments    : double p
//                double a
//                double la
//                double lga
//                double lgap1
// Return Type  : double
//
double ntf_eml_gammaincinv(double p, double a, double la, double lga, double
  lgap1)
{
  double rval;
  boolean_T upper;
  double pLower;
  double r;
  upper = false;
  if (a == rtInf) {
    rval = rtInf;
  } else if (lga == rtInf) {
    rval = a;
  } else {
    double nu;
    double log1mpLower;
    int i;
    boolean_T exitg1;
    double p1;
    double oldz;
    int sgn;
    nu = 2.0 * a;
    if (p > 0.5) {
      p = 1.0 - p;
      upper = true;
      pLower = 1.0 - p;
      if (1.0 - p == 1.0) {
        pLower = 0.9999999999999778;
      }

      log1mpLower = std::log(p);
    } else {
      pLower = p;
      if (1.0 - p != 1.0) {
        log1mpLower = std::log(1.0 - p) * (-p / ((1.0 - p) - 1.0));
      } else {
        log1mpLower = -p;
      }
    }

    if (nu < -1.24 * std::log(pLower)) {
      pLower = ntf_rt_powd_snf(pLower * std::exp(lgap1 + a * 0.693147180559945),
        1.0 / a);
      if (pLower < 2.2250738585072014E-306) {
        pLower = 2.2250738585072014E-306;
      }
    } else if (nu <= 0.32) {
      pLower = 0.4;
      i = 0;
      exitg1 = false;
      while ((!exitg1) && (i < 200)) {
        oldz = pLower;
        p1 = pLower * (pLower + 4.67) + 1.0;
        r = pLower * (pLower * (pLower + 6.66) + 6.73);
        pLower -= (1.0 - std::exp(((log1mpLower + lga) + 0.5 * pLower) + (a -
          1.0) * 0.693147180559945) * r / p1) / (((2.0 * pLower + 4.67) / p1 +
          -0.5) - (pLower * (3.0 * pLower + 13.32) + 6.73) / r);
        if (std::abs(oldz - pLower) < 0.01 * pLower) {
          exitg1 = true;
        } else {
          i++;
        }
      }
    } else {
      if (std::abs(pLower - 0.5) <= 0.425) {
        r = 0.180625 - (pLower - 0.5) * (pLower - 0.5);
        rval = (pLower - 0.5) * (((((((2509.0809287301227 * r +
          33430.575583588128) * r + 67265.7709270087) * r + 45921.95393154987) *
          r + 13731.693765509461) * r + 1971.5909503065513) * r +
          133.14166789178438) * r + 3.3871328727963665) /
          (((((((5226.4952788528544 * r + 28729.085735721943) * r +
                39307.895800092709) * r + 21213.794301586597) * r +
              5394.1960214247511) * r + 687.18700749205789) * r +
            42.313330701600911) * r + 1.0);
      } else {
        if (pLower - 0.5 < 0.0) {
          r = std::sqrt(-std::log(pLower));
        } else {
          r = std::sqrt(-std::log(1.0 - pLower));
        }

        if (r <= 5.0) {
          r -= 1.6;
          rval = (((((((0.00077454501427834139 * r + 0.022723844989269184) * r +
                       0.24178072517745061) * r + 1.2704582524523684) * r +
                     3.6478483247632045) * r + 5.769497221460691) * r +
                   4.6303378461565456) * r + 1.4234371107496835) /
            (((((((1.0507500716444169E-9 * r + 0.00054759380849953455) * r +
                  0.015198666563616457) * r + 0.14810397642748008) * r +
                0.6897673349851) * r + 1.6763848301838038) * r +
              2.053191626637759) * r + 1.0);
        } else {
          r -= 5.0;
          rval = (((((((2.0103343992922881E-7 * r + 2.7115555687434876E-5) * r +
                       0.0012426609473880784) * r + 0.026532189526576124) * r +
                     0.29656057182850487) * r + 1.7848265399172913) * r +
                   5.4637849111641144) * r + 6.6579046435011033) /
            (((((((2.0442631033899397E-15 * r + 1.4215117583164459E-7) * r +
                  1.8463183175100548E-5) * r + 0.00078686913114561329) * r +
                0.014875361290850615) * r + 0.13692988092273581) * r +
              0.599832206555888) * r + 1.0);
        }

        if (pLower - 0.5 < 0.0) {
          rval = -rval;
        }
      }

      p1 = 0.222222 / nu;
      pLower = (rval * std::sqrt(p1) + 1.0) - p1;
      pLower *= nu * pLower * pLower;
      if (pLower > 2.2 * nu + 6.0) {
        pLower = -2.0 * ((log1mpLower - (a - 1.0) * std::log(0.5 * pLower)) +
                         lga);
      }
    }

    rval = 0.5 * pLower;
    r = rtInf;
    oldz = rtInf;
    if (p > 1.0021E-294) {
      pLower = 2.2204460492503131E-14 * p;
    } else {
      pLower = 2.2251089859537388E-308;
    }

    if (upper) {
      sgn = -1;
    } else {
      sgn = 1;
    }

    nu = 0.0;
    p1 = 1.7976931348623157E+308;
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i < 1000)) {
      log1mpLower = static_cast<double>(sgn) * (ntf_c_eml_gammainc(rval, a, la,
        lgap1, upper) - p);
      if ((log1mpLower * r < 0.0) && (std::abs(r) <= std::abs(log1mpLower))) {
        rval = 0.5 * rval + 0.5 * oldz;
        log1mpLower = static_cast<double>(sgn) * (ntf_c_eml_gammainc(rval, a, la,
          lgap1, upper) - p);
      }

      if (log1mpLower > 0.0) {
        p1 = rval;
      } else {
        nu = rval;
      }

      if ((std::abs(log1mpLower) < pLower) || (std::abs(rval - oldz) <
           2.2204460492503131E-16 * rval + 2.2250738585072014E-308)) {
        exitg1 = true;
      } else {
        boolean_T guard1 = false;
        oldz = rval;
        r = log1mpLower;
        guard1 = false;
        if (i < 500) {
          rval *= 1.0 - log1mpLower / (rval * std::exp(((a - 1.0) * std::log
            (rval) - rval) - lga) + log1mpLower * ((rval + 1.0) - a) / 2.0);
          if (rval <= nu) {
            if (nu == 0.0) {
              if (std::abs(static_cast<double>(upper) - p) < std::abs
                  (ntf_c_eml_gammainc(2.2250738585072014E-308, a, la, lgap1,
                                      upper) - p)) {
                rval = 0.0;
                exitg1 = true;
              } else {
                nu = 2.2250738585072014E-308;
                guard1 = true;
              }
            } else {
              guard1 = true;
            }
          } else {
            if (rval >= p1) {
              rval = 0.01 * nu + 0.99 * p1;
            }

            i++;
          }
        } else {
          if (1.0E+8 * nu < p1) {
            oldz = 1.0E+8 * nu;
            r = static_cast<double>(sgn) * (ntf_c_eml_gammainc(oldz, a, la,
              lgap1, upper) - p);
            if (r > 0.0) {
              p1 = oldz;
            } else {
              nu = oldz;
            }
          }

          rval = 0.5 * nu + 0.5 * p1;
          i++;
        }

        if (guard1) {
          rval = 0.99 * nu + 0.01 * p1;
          i++;
        }
      }
    }
  }

  return rval;
}

//
// File trailer for ntf_gammaincinv.cpp
//
// [EOF]
//
