//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_cdf.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 06-Jul-2020 21:30:41
//

// Include Files
#include "ntf_cdf.h"
#include "ntf_binopdf.h"
#include "ntf_expm1.h"
#include "ntf_gammainc.h"
#include "ntf_gammaln.h"
#include "ntf_inataf.h"
#include "ntf_inataf_data.h"
#include "ntf_inataf_rtwutil.h"
#include "ntf_nbinpdf.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>

// Function Declarations
static double ntf_c_eml_gammainc(double x, double a, double la, double lgap1);

// Function Definitions

//
// Arguments    : double x
//                double a
//                double la
//                double lgap1
// Return Type  : double
//
static double ntf_c_eml_gammainc(double x, double a, double la, double lgap1)
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
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_3
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_b_cdf(const coder::array<double, 1U> &varargin_1, double varargin_3,
               coder::array<double, 1U> &p)
{
  int i;
  double s;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    if ((0.0 < varargin_3) && (varargin_3 <= 1.0) && (!rtIsNaN(varargin_1[k])))
    {
      if (varargin_1[k] < 0.0) {
        p[k] = 0.0;
      } else if (rtIsInf(varargin_1[k])) {
        p[k] = 1.0;
      } else {
        int i1;
        s = 0.0;
        i1 = static_cast<int>(std::floor(varargin_1[k]) + 1.0);
        for (int j = 0; j < i1; j++) {
          s += ntf_b_nbinpdf(static_cast<double>(j), 1.0, varargin_3);
        }

        p[k] = s;
        if (s > 1.0) {
          p[k] = 1.0;
        }
      }
    } else {
      p[k] = rtNaN;
    }
  }
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
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_2
//                double varargin_3
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_c_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
               double varargin_3, coder::array<double, 1U> &p)
{
  int i;
  double s;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_2 > 0.0) && (!rtIsInf(varargin_2)) && (0.0 < varargin_3) &&
        (varargin_3 <= 1.0) && (!rtIsNaN(varargin_1[k]))) {
      if (varargin_1[k] < 0.0) {
        p[k] = 0.0;
      } else if (rtIsInf(varargin_1[k])) {
        p[k] = 1.0;
      } else {
        int i1;
        s = 0.0;
        i1 = static_cast<int>(std::floor(varargin_1[k]) + 1.0);
        for (int j = 0; j < i1; j++) {
          s += ntf_b_nbinpdf(static_cast<double>(j), varargin_2, varargin_3);
        }

        p[k] = s;
        if (s > 1.0) {
          p[k] = 1.0;
        }
      }
    } else {
      p[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_2
//                double varargin_3
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
             double varargin_3, coder::array<double, 1U> &p)
{
  int i;
  double t2;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_3 >= 0.0) && (varargin_3 <= 1.0) && (varargin_2 == std::floor
         (varargin_2)) && (!rtIsNaN(varargin_1[k]))) {
      if (varargin_1[k] >= varargin_2) {
        p[k] = 1.0;
      } else if ((varargin_3 == 0.0) && (varargin_1[k] >= 0.0)) {
        p[k] = 1.0;
      } else if (varargin_3 == 1.0) {
        p[k] = (varargin_1[k] >= varargin_2);
      } else if (varargin_1[k] >= 0.0) {
        double xf;
        xf = std::floor(varargin_1[k]);
        if (varargin_2 < 100000.0) {
          if ((varargin_1[k] <= varargin_2 * varargin_3) || (varargin_3 < 0.0001))
          {
            int i1;
            t2 = 0.0;
            i1 = static_cast<int>(xf + 1.0);
            for (int j = 0; j < i1; j++) {
              t2 += ntf_binopdf(static_cast<double>(j), varargin_2, varargin_3);
            }

            if (t2 > 1.0) {
              t2 = 1.0;
            }

            p[k] = t2;
          } else {
            int i1;
            t2 = 0.0;
            i1 = static_cast<int>(((varargin_2 - xf) - 1.0) + 1.0);
            for (int j = 0; j < i1; j++) {
              t2 += ntf_binopdf(static_cast<double>(j), varargin_2, 1.0 -
                                varargin_3);
            }

            if (t2 > 1.0) {
              t2 = 1.0;
            }

            p[k] = 1.0 - t2;
          }
        } else {
          double mu_tmp;
          double sd;
          double x2;
          mu_tmp = varargin_2 * varargin_3;
          sd = std::sqrt(mu_tmp * (1.0 - varargin_3));
          t2 = 10.0;
          x2 = std::ceil(mu_tmp + 10.0 * sd);
          while ((xf <= x2) && (ntf_binopdf(x2, varargin_2, varargin_3) > 0.0))
          {
            t2 *= 1.5;
            x2 = std::ceil(mu_tmp + t2 * sd);
          }

          if (xf >= x2) {
            t2 = 1.0;
          } else {
            t2 = 40.0;
            x2 = std::floor(mu_tmp - 40.0 * sd);
            while ((0.0 < x2) && (ntf_binopdf(x2, varargin_2, varargin_3) >
                                  2.2204460492503131E-16)) {
              t2 *= 1.5;
              x2 = std::floor(mu_tmp - t2 * sd);
            }

            if (x2 < 0.0) {
              x2 = 0.0;
            }

            if (xf < x2) {
              t2 = 0.0;
            } else {
              int i1;
              t2 = 0.0;
              i1 = static_cast<int>(xf + (1.0 - x2));
              for (int j = 0; j < i1; j++) {
                t2 += ntf_binopdf(x2 + static_cast<double>(j), varargin_2,
                                  varargin_3);
              }

              if (t2 > 1.0) {
                t2 = 1.0;
              }
            }
          }

          p[k] = t2;
        }
      } else {
        p[k] = 0.0;
      }
    } else {
      p[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_2
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_d_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
               coder::array<double, 1U> &p)
{
  int i;
  double d;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_2 >= 0.0) && (!rtIsInf(varargin_2)) && ((!rtIsInf(varargin_1[k]))
         && (!rtIsNaN(varargin_1[k])))) {
      double xkf;
      xkf = std::floor(varargin_1[k]);
      if (xkf < 0.0) {
        p[k] = 0.0;
      } else {
        d = (xkf + 1.0) + 1.0;
        ntf_gammaln(&d);
        p[k] = (ntf_scalar_gammainc(varargin_2, xkf + 1.0, std::log(xkf + 1.0),
                 d)).re;
      }
    } else if ((varargin_1[k] > 0.0) && rtIsInf(varargin_1[k]) && (varargin_2 >
                0.0) && (!rtIsInf(varargin_2))) {
      p[k] = 1.0;
    } else {
      p[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_2
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_e_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
               coder::array<double, 1U> &p)
{
  int i;
  double xk;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    xk = varargin_1[k];
    if ((varargin_2 > 0.0) && (!rtIsNaN(varargin_1[k]))) {
      if (varargin_1[k] < 0.0) {
        xk = 0.0;
      }

      xk = -(xk / varargin_2);
      ntf_expm1(&xk);
      p[k] = -xk;
    } else {
      p[k] = rtNaN;
    }
  }
}

//
// Arguments    : double x
// Return Type  : double
//
double ntf_eml_erfcore(double x)
{
  double y;
  double absx;
  int eint;

  // ========================== COPYRIGHT NOTICE ============================
  //  The algorithms for calculating ERF(X) and ERFC(X) are derived
  //  from FDLIBM, which has the following notice:
  //
  //  Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
  //
  //  Developed at SunSoft, a Sun Microsystems, Inc. business.
  //  Permission to use, copy, modify, and distribute this
  //  software is freely granted, provided that this notice
  //  is preserved.
  // =============================    END    ================================
  absx = std::abs(x);
  if (rtIsNaN(x)) {
    y = x;
  } else if (rtIsInf(x)) {
    if (x < 0.0) {
      y = 2.0;
    } else {
      y = 0.0;
    }
  } else if (absx < 0.84375) {
    if (absx < 1.3877787807814457E-17) {
      y = 1.0 - x;
    } else {
      double s;
      s = x * x;
      y = (s * (s * (s * (s * -2.3763016656650163E-5 + -0.0057702702964894416) +
                     -0.02848174957559851) + -0.3250421072470015) +
           0.12837916709551256) / (s * (s * (s * (s * (s *
        -3.9602282787753681E-6 + 0.00013249473800432164) + 0.0050813062818757656)
        + 0.0650222499887673) + 0.39791722395915535) + 1.0);
      if (x < 0.25) {
        y = 1.0 - (x + x * y);
      } else {
        y = 0.5 - (x * y + (x - 0.5));
      }
    }
  } else if (absx < 1.25) {
    double S;
    double s;
    S = (absx - 1.0) * ((absx - 1.0) * ((absx - 1.0) * ((absx - 1.0) * ((absx -
      1.0) * ((absx - 1.0) * -0.0021663755948687908 + 0.035478304325618236) +
      -0.11089469428239668) + 0.31834661990116175) + -0.37220787603570132) +
                        0.41485611868374833) + -0.0023621185607526594;
    s = (absx - 1.0) * ((absx - 1.0) * ((absx - 1.0) * ((absx - 1.0) * ((absx -
      1.0) * ((absx - 1.0) * 0.011984499846799107 + 0.013637083912029051) +
      0.12617121980876164) + 0.071828654414196266) + 0.540397917702171) +
                        0.10642088040084423) + 1.0;
    if (x >= 0.0) {
      y = 0.15493708848953247 - S / s;
    } else {
      y = (S / s + 0.84506291151046753) + 1.0;
    }
  } else if (x < -6.0) {
    y = 2.0;
  } else if (x >= 28.0) {
    y = 0.0;
  } else {
    double S;
    double s;
    double R;
    s = 1.0 / (absx * absx);
    if (absx < 2.8571414947509766) {
      R = s * (s * (s * (s * (s * (s * (s * -9.8143293441691455 +
        -81.2874355063066) + -184.60509290671104) + -162.39666946257347) +
                         -62.375332450326006) + -10.558626225323291) +
               -0.69385857270718176) + -0.0098649440348471482;
      S = s * (s * (s * (s * (s * (s * (s * (s * -0.0604244152148581 +
        6.5702497703192817) + 108.63500554177944) + 429.00814002756783) +
                  645.38727173326788) + 434.56587747522923) + 137.65775414351904)
               + 19.651271667439257) + 1.0;
    } else {
      R = s * (s * (s * (s * (s * (s * -483.5191916086514 + -1025.0951316110772)
                  + -637.56644336838963) + -160.63638485582192) +
                    -17.757954917754752) + -0.799283237680523) +
        -0.0098649429247001;
      S = s * (s * (s * (s * (s * (s * (s * -22.440952446585818 +
        474.52854120695537) + 2553.0504064331644) + 3199.8582195085955) +
                         1536.729586084437) + 325.79251299657392) +
               30.338060743482458) + 1.0;
    }

    if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
      s = frexp(absx, &eint);
    } else {
      s = absx;
      eint = 0;
    }

    s = std::floor(s * 2.097152E+6) / 2.097152E+6 * ntf_rt_powd_snf(2.0,
      static_cast<double>(eint));
    y = std::exp(-s * s - 0.5625) * std::exp((s - absx) * (s + absx) + R / S) /
      absx;
    if (x < 0.0) {
      y = 2.0 - y;
    }
  }

  return y;
}

//
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_2
//                double varargin_3
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_f_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
               double varargin_3, coder::array<double, 1U> &p)
{
  int i;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    double xk;
    xk = varargin_1[k];
    if ((varargin_2 >= 0.0) && (varargin_3 > 0.0) && (!rtIsNaN(varargin_1[k])))
    {
      if (varargin_1[k] < 0.0) {
        xk = 0.0;
      }

      p[k] = (ntf_gammainc(xk / varargin_3, varargin_2)).re;
    } else {
      p[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_2
//                double varargin_3
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_g_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
               double varargin_3, coder::array<double, 1U> &p)
{
  int i;
  double betai;
  double logx;
  double log1mx;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_2 > 0.0) && (varargin_3 > 0.0) && (!rtIsInf(varargin_2)) &&
        (!rtIsInf(varargin_3)) && (!rtIsNaN(varargin_1[k]))) {
      if (varargin_1[k] < 0.0) {
        p[k] = 0.0;
      } else if (varargin_1[k] <= 1.0) {
        double x;
        double d;
        x = varargin_1[k];
        betai = varargin_2;
        ntf_gammaln(&betai);
        logx = varargin_3;
        ntf_gammaln(&logx);
        d = varargin_2 + varargin_3;
        log1mx = d;
        ntf_gammaln(&log1mx);
        betai = (betai + logx) - log1mx;
        if ((0.0 < x) && (x < 1.0)) {
          if (rtIsInf(varargin_2)) {
            if (!rtIsInf(varargin_3)) {
              betai = !(x < 1.0);
            } else if (x == 0.0) {
              betai = 0.0;
            } else if (x == 1.0) {
              betai = 1.0;
            } else {
              betai = rtNaN;
            }
          } else if (rtIsInf(varargin_3)) {
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

              if (x < (varargin_2 + 1.0) / (d + 2.0)) {
                betai = std::exp(((varargin_2 * logx + varargin_3 * log1mx) -
                                  std::log(varargin_2)) - betai) *
                  ntf_betainc_cf(x, varargin_2, varargin_3);
              } else {
                betai = 1.0 - std::exp(((varargin_2 * logx + varargin_3 * log1mx)
                  - std::log(varargin_3)) - betai) * ntf_betainc_cf(1.0 - x,
                  varargin_3, varargin_2);
              }

              if (!(betai == betai)) {
                guard1 = true;
              }
            } else {
              guard1 = true;
            }

            if (guard1) {
              betai = ntf_rt_powd_snf(varargin_3 * x, 0.33333333333333331);
              logx = ntf_rt_powd_snf(varargin_2 * (1.0 - x), 0.33333333333333331);
              if ((d - 1.0) * (1.0 - x) > 0.8) {
                x = 0.70710678118654746 * -(3.0 * ((1.0 - 1.0 / (9.0 *
                  varargin_3)) * betai - (1.0 - 1.0 / (9.0 * varargin_2)) * logx)
                  / std::sqrt(betai * betai / varargin_3 + logx * logx /
                              varargin_2));
                betai = 3.97886080735226 / (std::abs(x) + 3.97886080735226);
                betai = 0.5 * ((((((((((((((((((((((0.0012710976495261409 *
                  (betai - 0.5) + 0.00011931402283834095) * (betai - 0.5) +
                  -0.0039638509736051354) * (betai - 0.5) +
                  -0.00087077963531729586) * (betai - 0.5) +
                  0.0077367252831352668) * (betai - 0.5) + 0.0038333512626488732)
                  * (betai - 0.5) + -0.012722381378212275) * (betai - 0.5) +
                  -0.013382364453346007) * (betai - 0.5) + 0.016131532973325226)
                  * (betai - 0.5) + 0.039097684558848406) * (betai - 0.5) +
                  0.0024936720005350331) * (betai - 0.5) + -0.0838864557023002) *
                  (betai - 0.5) + -0.11946395996432542) * (betai - 0.5) +
                  0.016620792496936737) * (betai - 0.5) + 0.35752427444953105) *
                                      (betai - 0.5) + 0.80527640875291062) *
                                     (betai - 0.5) + 1.1890298290927332) *
                                    (betai - 0.5) + 1.3704021768233816) * (betai
                  - 0.5) + 1.313146538310231) * (betai - 0.5) +
                                  1.0792551515585667) * (betai - 0.5) +
                                 0.77436819911953858) * (betai - 0.5) +
                                0.49016508058531844) * (betai - 0.5) +
                               0.27537474159737679) * betai * std::exp(-x * x);
                if (x < 0.0) {
                  betai = 1.0 - betai;
                }
              } else {
                betai = varargin_3;
                ntf_gammaln(&betai);
                betai = ntf_c_eml_gammainc(0.5 * (((varargin_2 + varargin_3) -
                  1.0) * (3.0 - x) - (varargin_3 - 1.0)) * (1.0 - x), varargin_3,
                  std::log(varargin_3), betai);
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

        p[k] = betai;
      } else {
        p[k] = 1.0;
      }
    } else {
      p[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_2
//                double varargin_3
//                double varargin_4
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_h_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
               double varargin_3, double varargin_4, coder::array<double, 1U> &p)
{
  int i;
  double zj;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int j = 0; j < i; j++) {
    if (varargin_3 > 0.0) {
      zj = (varargin_1[j] - varargin_4) / varargin_3;
      if (std::abs(varargin_2) < 2.2204460492503131E-16) {
        p[j] = std::exp(-std::exp(-zj));
      } else {
        zj *= varargin_2;
        if (zj <= -1.0) {
          p[j] = (varargin_2 < 0.0);
        } else {
          double absz;
          absz = std::abs(zj);
          if ((absz > 4.503599627370496E+15) || (rtIsInf(zj) || rtIsNaN(zj))) {
            zj = std::log(zj + 1.0);
          } else {
            if (!(absz < 2.2204460492503131E-16)) {
              zj = std::log(zj + 1.0) * (zj / ((zj + 1.0) - 1.0));
            }
          }

          p[j] = std::exp(-std::exp(-(1.0 / varargin_2) * zj));
        }
      }
    } else {
      p[j] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_2
//                double varargin_3
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_i_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
               double varargin_3, coder::array<double, 1U> &p)
{
  int i;
  double d;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_2 > 0.0) && (varargin_3 > 0.0) && (!rtIsNaN(varargin_1[k]))) {
      if (varargin_1[k] < 0.0) {
        p[k] = 0.0;
      } else {
        d = -ntf_rt_powd_snf(varargin_1[k] / varargin_2, varargin_3);
        ntf_expm1(&d);
        p[k] = -d;
      }
    } else {
      p[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_2
//                double varargin_3
//                double varargin_4
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_j_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
               double varargin_3, double varargin_4, coder::array<double, 1U> &p)
{
  int i;
  double zj;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int j = 0; j < i; j++) {
    if (varargin_3 > 0.0) {
      zj = (varargin_1[j] - varargin_4) / varargin_3;
      if (zj < 0.0) {
        p[j] = 0.0;
      } else if (std::abs(varargin_2) < 2.2204460492503131E-16) {
        zj = -zj;
        ntf_expm1(&zj);
        p[j] = -zj;
      } else {
        zj *= varargin_2;
        if ((zj <= -1.0) && (varargin_2 < -2.2204460492503131E-16)) {
          p[j] = 1.0;
        } else {
          double absz;
          absz = std::abs(zj);
          if ((absz > 4.503599627370496E+15) || (rtIsInf(zj) || rtIsNaN(zj))) {
            zj = std::log(zj + 1.0);
          } else {
            if (!(absz < 2.2204460492503131E-16)) {
              zj = std::log(zj + 1.0) * (zj / ((zj + 1.0) - 1.0));
            }
          }

          zj = -zj / varargin_2;
          ntf_expm1(&zj);
          p[j] = -zj;
        }
      }
    } else {
      p[j] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_2
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_k_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
               coder::array<double, 1U> &p)
{
  int i;
  double d;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_2 > 0.0) && (!rtIsNaN(varargin_1[k]))) {
      if (varargin_1[k] < 0.0) {
        p[k] = 0.0;
      } else {
        d = -varargin_1[k] * varargin_1[k] / (2.0 * (varargin_2 * varargin_2));
        ntf_expm1(&d);
        p[k] = -d;
      }
    } else {
      p[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_2
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_l_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
               coder::array<double, 1U> &p)
{
  int i;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    double xk;
    xk = varargin_1[k];
    if ((varargin_2 >= 0.0) && (!rtIsNaN(varargin_1[k]))) {
      if (varargin_1[k] < 0.0) {
        xk = 0.0;
      }

      p[k] = (ntf_gammainc(xk / 2.0, varargin_2)).re;
    } else {
      p[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_2
//                double varargin_3
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_m_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
               double varargin_3, coder::array<double, 1U> &p)
{
  int i;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    if (varargin_2 < varargin_3) {
      if (varargin_1[k] >= varargin_3) {
        p[k] = 1.0;
      } else if ((varargin_1[k] > varargin_2) && (varargin_1[k] < varargin_3)) {
        p[k] = (varargin_1[k] - varargin_2) / (varargin_3 - varargin_2);
      } else {
        p[k] = 0.0;
      }
    } else {
      p[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_2
//                double varargin_3
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_n_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
               double varargin_3, coder::array<double, 1U> &p)
{
  int i;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    if (varargin_3 == 0.0) {
      p[k] = !(varargin_1[k] < varargin_2);
    } else if (varargin_3 > 0.0) {
      double y;
      y = ntf_eml_erfcore(-((varargin_1[k] - varargin_2) / varargin_3) /
                          1.4142135623730951);
      p[k] = 0.5 * y;
    } else {
      p[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *varargin_1
//                double varargin_2
//                double varargin_3
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_o_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
               double varargin_3, coder::array<double, 1U> &p)
{
  int i;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    double xk;
    xk = varargin_1[k];
    if (varargin_1[k] < 0.0) {
      xk = 0.0;
    }

    if ((varargin_3 > 0.0) && (!rtIsNaN(xk))) {
      if (xk <= 0.0) {
        p[k] = 0.0;
      } else {
        xk = ntf_eml_erfcore(-((std::log(xk) - varargin_2) / varargin_3) /
                             1.4142135623730951);
        p[k] = 0.5 * xk;
      }
    } else {
      p[k] = rtNaN;
    }
  }
}

//
// File trailer for ntf_cdf.cpp
//
// [EOF]
//
