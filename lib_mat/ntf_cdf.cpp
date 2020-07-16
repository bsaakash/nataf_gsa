//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_cdf.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//

// Include Files
#include "ntf_cdf.h"
#include "ntf_betainc.h"
#include "ntf_binopdf.h"
#include "ntf_expm1.h"
#include "ntf_gammainc.h"
#include "ntf_gammaln.h"
#include "ntf_inataf.h"
#include "ntf_inataf_rtwutil.h"
#include "ntf_nbinpdf.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>

// Function Definitions

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
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_2 > 0.0) && (varargin_3 > 0.0) && (!rtIsInf(varargin_2)) &&
        (!rtIsInf(varargin_3)) && (!rtIsNaN(varargin_1[k]))) {
      if (varargin_1[k] < 0.0) {
        p[k] = 0.0;
      } else if (varargin_1[k] <= 1.0) {
        creal_T dc;
        dc = ntf_betainc(varargin_1[k], varargin_2, varargin_3);
        p[k] = dc.re;
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
//                coder::array<double, 1U> *p
// Return Type  : void
//
void ntf_h_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
               double varargin_3, coder::array<double, 1U> &p)
{
  int i;
  double x;
  p.set_size(varargin_1.size(0));
  i = varargin_1.size(0);
  for (int k = 0; k < i; k++) {
    if (varargin_3 > 0.0) {
      x = (varargin_1[k] - varargin_2) / varargin_3;
      if (x > 3.62247112598261) {
        p[k] = 1.0;
      } else {
        x = -std::exp(x);
        ntf_expm1(&x);
        p[k] = -x;
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
void ntf_i_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
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
void ntf_j_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
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
void ntf_k_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
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
void ntf_l_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
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
void ntf_m_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
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
void ntf_n_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
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
void ntf_o_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
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
void ntf_p_cdf(const coder::array<double, 1U> &varargin_1, double varargin_2,
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
