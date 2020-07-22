//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_icdf.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_icdf.h"
#include "ntf_ERADist.h"
#include "ntf_betaincinv.h"
#include "ntf_binopdf.h"
#include "ntf_erfcinv.h"
#include "ntf_expm1.h"
#include "ntf_gammainc.h"
#include "ntf_gammaincinv.h"
#include "ntf_gammaln.h"
#include "ntf_inataf.h"
#include "ntf_inataf_rtwutil.h"
#include "ntf_nbinpdf.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_ab_icdf(const coder::array<double, 2U> &p, double varargin_1, coder::
                 array<double, 2U> &x)
{
  int i;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 > 0.0) && (0.0 <= p[k]) && (p[k] <= 1.0)) {
      if (p[k] == 0.0) {
        x[k] = 0.0;
      } else if (p[k] == 1.0) {
        x[k] = rtInf;
      } else {
        x[k] = std::sqrt(-2.0 * (varargin_1 * varargin_1) * std::log(1.0 - p[k]));
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const double p[1048576]
//                double varargin_1
//                double varargin_2
//                double x[1048576]
// Return Type  : void
//
void ntf_b_icdf(const double p[1048576], double varargin_1, double varargin_2,
                double x[1048576])
{
  double cumdist;
  for (int k = 0; k < 1048576; k++) {
    if ((varargin_1 > 0.0) && (!rtIsInf(varargin_1)) && (0.0 < varargin_2) &&
        (varargin_2 <= 1.0) && (0.0 <= p[k]) && (p[k] <= 1.0)) {
      if (p[k] == 1.0) {
        x[k] = rtInf;
      } else if (p[k] == 0.0) {
        x[k] = 0.0;
      } else {
        double count;
        x[k] = 0.0;
        count = 0.0;
        for (cumdist = ntf_nbinpdf(varargin_1, varargin_2); cumdist < p[k];
             cumdist += ntf_b_nbinpdf(count, varargin_1, varargin_2)) {
          x[k]++;
          count++;
        }
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_bb_icdf(const coder::array<double, 2U> &p, double varargin_1, coder::
                 array<double, 2U> &x)
{
  int i;
  double d;
  double d1;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    if ((0.0 <= varargin_1) && (!rtIsInf(varargin_1)) && (p[k] >= 0.0) && (p[k] <=
         1.0)) {
      if ((p[k] > 0.0) && (p[k] < 1.0) && (varargin_1 > 0.0)) {
        d = varargin_1;
        ntf_gammaln(&d);
        d1 = varargin_1 + 1.0;
        ntf_gammaln(&d1);
        x[k] = ntf_eml_gammaincinv(p[k], varargin_1, std::log(varargin_1), d, d1)
          * 2.0;
      } else if ((varargin_1 == 0.0) || (p[k] == 0.0)) {
        x[k] = 0.0;
      } else if (p[k] == 1.0) {
        x[k] = rtInf;
      } else {
        x[k] = rtNaN;
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const double p[1048576]
//                double varargin_1
//                double x[1048576]
// Return Type  : void
//
void ntf_c_icdf(const double p[1048576], double varargin_1, double x[1048576])
{
  double d1;
  for (int k = 0; k < 1048576; k++) {
    double d;
    d = p[k];
    if ((0.0 <= p[k]) && (p[k] <= 1.0) && (varargin_1 >= 0.0)) {
      if ((varargin_1 == 0.0) || (p[k] == 0.0)) {
        x[k] = 0.0;
      } else if (p[k] == 1.0) {
        x[k] = rtInf;
      } else if (varargin_1 > 10.0) {
        double count;
        creal_T y;
        count = -1.4142135623730951 * ntf_erfcinv(2.0 * p[k]);
        count = std::ceil(std::sqrt(varargin_1) * count + varargin_1);
        if (count < 0.0) {
          count = 0.0;
        }

        d1 = (count + 1.0) + 1.0;
        ntf_gammaln(&d1);
        y = ntf_scalar_gammainc(varargin_1, count + 1.0, std::log(count + 1.0),
          d1);
        if (y.re < p[k]) {
          do {
            count++;
            d1 = (count + 1.0) + 1.0;
            ntf_gammaln(&d1);
          } while (!!((ntf_scalar_gammainc(varargin_1, count + 1.0, std::log
                      (count + 1.0), d1)).re < d));
        } else {
          if (y.re > p[k]) {
            int exitg1;
            do {
              exitg1 = 0;
              d1 = count + 1.0;
              ntf_gammaln(&d1);
              if ((ntf_scalar_gammainc(varargin_1, count, std::log(count), d1)).
                  re >= d) {
                count--;
              } else {
                exitg1 = 1;
              }
            } while (exitg1 == 0);
          }
        }

        x[k] = count;
      } else {
        double count;
        count = 0.0;
        int exitg1;
        do {
          exitg1 = 0;
          d1 = (count + 1.0) + 1.0;
          ntf_gammaln(&d1);
          if ((ntf_scalar_gammainc(varargin_1, count + 1.0, std::log(count + 1.0),
                d1)).re < d) {
            count++;
          } else {
            exitg1 = 1;
          }
        } while (exitg1 == 0);

        x[k] = count;
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                double varargin_2
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_cb_icdf(const coder::array<double, 2U> &p, double varargin_1, double
                 varargin_2, coder::array<double, 2U> &x)
{
  int i;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 < varargin_2) && (0.0 <= p[k]) && (p[k] <= 1.0)) {
      x[k] = varargin_1 + p[k] * (varargin_2 - varargin_1);
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const double p[1048576]
//                double varargin_1
//                double x[1048576]
// Return Type  : void
//
void ntf_d_icdf(const double p[1048576], double varargin_1, double x[1048576])
{
  for (int k = 0; k < 1048576; k++) {
    if ((varargin_1 > 0.0) && (p[k] >= 0.0) && (p[k] <= 1.0)) {
      if (p[k] > 0.0) {
        if (p[k] < 1.0) {
          x[k] = -varargin_1 * std::log(1.0 - p[k]);
        } else {
          x[k] = rtInf;
        }
      } else {
        x[k] = 0.0;
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_db_icdf(const coder::array<double, 2U> &p, coder::array<double, 2U> &x)
{
  int i;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    double d;
    d = p[k];
    if ((d >= 0.0) && (d <= 1.0)) {
      x[k] = -1.4142135623730951 * ntf_erfcinv(2.0 * d);
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const double p[1048576]
//                double varargin_1
//                double varargin_2
//                double x[1048576]
// Return Type  : void
//
void ntf_e_icdf(const double p[1048576], double varargin_1, double varargin_2,
                double x[1048576])
{
  double d;
  double d1;
  for (int k = 0; k < 1048576; k++) {
    if ((0.0 <= varargin_1) && (!rtIsInf(varargin_1)) && (0.0 < varargin_2) &&
        (p[k] >= 0.0) && (p[k] <= 1.0)) {
      if ((p[k] > 0.0) && (p[k] < 1.0) && (varargin_1 > 0.0)) {
        d = varargin_1;
        ntf_gammaln(&d);
        d1 = varargin_1 + 1.0;
        ntf_gammaln(&d1);
        x[k] = ntf_eml_gammaincinv(p[k], varargin_1, std::log(varargin_1), d, d1)
          * varargin_2;
      } else if ((varargin_1 == 0.0) || (p[k] == 0.0)) {
        x[k] = 0.0;
      } else if (p[k] == 1.0) {
        x[k] = rtInf;
      } else {
        x[k] = rtNaN;
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                double varargin_2
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_eb_icdf(const coder::array<double, 2U> &p, double varargin_1, double
                 varargin_2, coder::array<double, 2U> &x)
{
  int i;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    if ((varargin_2 > 0.0) && (p[k] >= 0.0) && (p[k] <= 1.0)) {
      double zk;
      zk = -1.4142135623730951 * ntf_erfcinv(2.0 * p[k]);
      x[k] = varargin_2 * zk + varargin_1;
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const double p[1048576]
//                double varargin_1
//                double varargin_2
//                double x[1048576]
// Return Type  : void
//
void ntf_f_icdf(const double p[1048576], double varargin_1, double varargin_2,
                double x[1048576])
{
  double d;
  double d1;
  double d2;
  for (int k = 0; k < 1048576; k++) {
    if ((varargin_1 > 0.0) && (varargin_2 > 0.0) && (!rtIsInf(varargin_1)) &&
        (!rtIsInf(varargin_2)) && (p[k] >= 0.0) && (p[k] <= 1.0)) {
      d = varargin_1;
      ntf_gammaln(&d);
      d1 = varargin_2;
      ntf_gammaln(&d1);
      d2 = varargin_1 + varargin_2;
      ntf_gammaln(&d2);
      x[k] = ntf_eml_betaincinv(p[k], varargin_1, varargin_2, (d + d1) - d2);
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                double varargin_2
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_fb_icdf(const coder::array<double, 2U> &p, double varargin_1, double
                 varargin_2, coder::array<double, 2U> &x)
{
  int i;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    if ((varargin_2 > 0.0) && (p[k] >= 0.0) && (p[k] <= 1.0)) {
      double logx0;
      logx0 = -1.4142135623730951 * ntf_erfcinv(2.0 * p[k]);
      x[k] = std::exp(varargin_2 * logx0 + varargin_1);
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const double p[1048576]
//                double varargin_1
//                double varargin_2
//                double x[1048576]
// Return Type  : void
//
void ntf_g_icdf(const double p[1048576], double varargin_1, double varargin_2,
                double x[1048576])
{
  for (int k = 0; k < 1048576; k++) {
    if ((varargin_2 > 0.0) && (p[k] >= 0.0) && (p[k] <= 1.0)) {
      double q;
      if (p[k] > 0.0) {
        q = std::log(1.0 - p[k]);
        if (-q > 0.0) {
          q = std::log(-q);
        } else {
          q = rtInf;
        }
      } else {
        q = rtMinusInf;
      }

      x[k] = varargin_2 * q + varargin_1;
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const double p[1048576]
//                double varargin_1
//                double varargin_2
//                double varargin_3
//                double x[1048576]
// Return Type  : void
//
void ntf_h_icdf(const double p[1048576], double varargin_1, double varargin_2,
                double varargin_3, double x[1048576])
{
  double d;
  for (int j = 0; j < 1048576; j++) {
    if ((varargin_2 > 0.0) && (0.0 <= p[j]) && (p[j] <= 1.0)) {
      if (p[j] == 0.0) {
        if (varargin_1 <= 0.0) {
          x[j] = rtMinusInf;
        } else {
          x[j] = varargin_3 - varargin_2 / varargin_1;
        }
      } else if (p[j] == 1.0) {
        if (varargin_1 < 0.0) {
          x[j] = varargin_3 - varargin_2 / varargin_1;
        } else {
          x[j] = rtInf;
        }
      } else {
        if (std::abs(varargin_1) < 2.2204460492503131E-16) {
          d = -std::log(-std::log(p[j]));
        } else {
          d = -varargin_1 * std::log(-std::log(p[j]));
          ntf_expm1(&d);
          d /= varargin_1;
        }

        d = varargin_2 * d + varargin_3;
        x[j] = d;
      }
    } else {
      x[j] = rtNaN;
    }
  }
}

//
// Arguments    : const double p[1048576]
//                double varargin_1
//                double varargin_2
//                double x[1048576]
// Return Type  : void
//
void ntf_i_icdf(const double p[1048576], double varargin_1, double varargin_2,
                double x[1048576])
{
  for (int k = 0; k < 1048576; k++) {
    if ((varargin_1 > 0.0) && (varargin_2 > 0.0) && (0.0 <= p[k]) && (p[k] <=
         1.0)) {
      if (p[k] == 0.0) {
        x[k] = 0.0;
      } else if (p[k] == 1.0) {
        x[k] = rtInf;
      } else {
        x[k] = varargin_1 * ntf_rt_powd_snf(-std::log(1.0 - p[k]), 1.0 /
          varargin_2);
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const double p[1048576]
//                double varargin_1
//                double varargin_2
//                double x[1048576]
// Return Type  : void
//
void ntf_icdf(const double p[1048576], double varargin_1, double varargin_2,
              double x[1048576])
{
  double cumdist;
  for (int k = 0; k < 1048576; k++) {
    if ((varargin_1 >= 0.0) && (varargin_2 >= 0.0) && (varargin_2 <= 1.0) &&
        (p[k] >= 0.0) && (p[k] <= 1.0) && (std::floor(varargin_1) == varargin_1))
    {
      if (p[k] == 1.0) {
        x[k] = varargin_1;
      } else {
        double xk;
        xk = 0.0;
        cumdist = 0.0;
        int exitg1;
        do {
          exitg1 = 0;
          cumdist += ntf_binopdf(xk, varargin_1, varargin_2);
          if ((cumdist > p[k]) || (xk >= varargin_1)) {
            exitg1 = 1;
          } else {
            xk++;
          }
        } while (exitg1 == 0);

        x[k] = xk;
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const double p[1048576]
//                double varargin_1
//                double varargin_2
//                double varargin_3
//                double x[1048576]
// Return Type  : void
//
void ntf_j_icdf(const double p[1048576], double varargin_1, double varargin_2,
                double varargin_3, double x[1048576])
{
  double b_x;
  for (int j = 0; j < 1048576; j++) {
    if ((varargin_2 > 0.0) && (0.0 <= p[j]) && (p[j] <= 1.0)) {
      if (p[j] == 0.0) {
        x[j] = varargin_3;
      } else if (p[j] == 1.0) {
        if (varargin_1 < 0.0) {
          x[j] = varargin_3 - varargin_2 / varargin_1;
        } else {
          x[j] = varargin_3 + rtInf;
        }
      } else if (std::abs(varargin_1) < 2.2204460492503131E-16) {
        double absz;
        b_x = -p[j];
        absz = std::abs(-p[j]);
        if ((absz > 4.503599627370496E+15) || (rtIsInf(-p[j]) || rtIsNaN(-p[j])))
        {
          b_x = std::log(-p[j] + 1.0);
        } else {
          if (!(absz < 2.2204460492503131E-16)) {
            b_x = std::log(-p[j] + 1.0) * (-p[j] / ((-p[j] + 1.0) - 1.0));
          }
        }

        x[j] = varargin_3 - varargin_2 * b_x;
      } else {
        double absz;
        b_x = -p[j];
        absz = std::abs(-p[j]);
        if ((absz > 4.503599627370496E+15) || (rtIsInf(-p[j]) || rtIsNaN(-p[j])))
        {
          b_x = std::log(-p[j] + 1.0);
        } else {
          if (!(absz < 2.2204460492503131E-16)) {
            b_x = std::log(-p[j] + 1.0) * (-p[j] / ((-p[j] + 1.0) - 1.0));
          }
        }

        b_x *= -varargin_1;
        ntf_expm1(&b_x);
        x[j] = varargin_3 + varargin_2 * b_x / varargin_1;
      }
    } else {
      x[j] = rtNaN;
    }
  }
}

//
// Arguments    : const double p[1048576]
//                double varargin_1
//                double x[1048576]
// Return Type  : void
//
void ntf_k_icdf(const double p[1048576], double varargin_1, double x[1048576])
{
  for (int k = 0; k < 1048576; k++) {
    if ((varargin_1 > 0.0) && (0.0 <= p[k]) && (p[k] <= 1.0)) {
      if (p[k] == 0.0) {
        x[k] = 0.0;
      } else if (p[k] == 1.0) {
        x[k] = rtInf;
      } else {
        x[k] = std::sqrt(-2.0 * (varargin_1 * varargin_1) * std::log(1.0 - p[k]));
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const double p[1048576]
//                double varargin_1
//                double varargin_2
//                double x[1048576]
// Return Type  : void
//
void ntf_l_icdf(const double p[1048576], double varargin_1, double varargin_2,
                double x[1048576])
{
  for (int k = 0; k < 1048576; k++) {
    if ((varargin_2 > 0.0) && (p[k] >= 0.0) && (p[k] <= 1.0)) {
      double zk;
      zk = -1.4142135623730951 * ntf_erfcinv(2.0 * p[k]);
      x[k] = varargin_2 * zk + varargin_1;
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const double p[1048576]
//                double varargin_1
//                double varargin_2
//                double x[1048576]
// Return Type  : void
//
void ntf_m_icdf(const double p[1048576], double varargin_1, double varargin_2,
                double x[1048576])
{
  for (int k = 0; k < 1048576; k++) {
    if ((varargin_2 > 0.0) && (p[k] >= 0.0) && (p[k] <= 1.0)) {
      double logx0;
      logx0 = -1.4142135623730951 * ntf_erfcinv(2.0 * p[k]);
      x[k] = std::exp(varargin_2 * logx0 + varargin_1);
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                double varargin_2
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_n_icdf(const coder::array<double, 2U> &p, double varargin_1, double
                varargin_2, coder::array<double, 2U> &x)
{
  int i;
  double cumdist;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 >= 0.0) && (varargin_2 >= 0.0) && (varargin_2 <= 1.0)) {
      double xk;
      xk = p[k];
      if ((xk >= 0.0) && (xk <= 1.0) && (std::floor(varargin_1) == varargin_1))
      {
        if (xk == 1.0) {
          x[k] = varargin_1;
        } else {
          xk = 0.0;
          cumdist = 0.0;
          int exitg1;
          do {
            exitg1 = 0;
            cumdist += ntf_binopdf(xk, varargin_1, varargin_2);
            if ((cumdist > p[k]) || (xk >= varargin_1)) {
              exitg1 = 1;
            } else {
              xk++;
            }
          } while (exitg1 == 0);

          x[k] = xk;
        }
      } else {
        x[k] = rtNaN;
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_2
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_o_icdf(const coder::array<double, 2U> &p, double varargin_2, coder::
                array<double, 2U> &x)
{
  int i;
  double cumdist;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    if ((0.0 < varargin_2) && (varargin_2 <= 1.0)) {
      cumdist = p[k];
      if ((0.0 <= cumdist) && (cumdist <= 1.0)) {
        if (cumdist == 1.0) {
          x[k] = rtInf;
        } else if (cumdist == 0.0) {
          x[k] = 0.0;
        } else {
          double count;
          x[k] = 0.0;
          count = 0.0;
          if (varargin_2 < 1.0) {
            cumdist = -varargin_2;
            if (!(std::abs(-varargin_2) < 2.2204460492503131E-16)) {
              cumdist = std::log(-varargin_2 + 1.0) * (-varargin_2 /
                ((-varargin_2 + 1.0) - 1.0));
            }

            cumdist = std::exp(std::log(varargin_2) + 0.0 * cumdist);
          } else {
            cumdist = 1.0;
          }

          while (cumdist < p[k]) {
            x[k] = x[k] + 1.0;
            count++;
            cumdist += ntf_b_nbinpdf(count, 1.0, varargin_2);
          }
        }
      } else {
        x[k] = rtNaN;
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                double varargin_2
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_p_icdf(const coder::array<double, 2U> &p, double varargin_1, double
                varargin_2, coder::array<double, 2U> &x)
{
  int i;
  double cumdist;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 > 0.0) && (!rtIsInf(varargin_1)) && (0.0 < varargin_2) &&
        (varargin_2 <= 1.0)) {
      double count;
      count = p[k];
      if ((0.0 <= count) && (count <= 1.0)) {
        if (count == 1.0) {
          x[k] = rtInf;
        } else if (count == 0.0) {
          x[k] = 0.0;
        } else {
          x[k] = 0.0;
          count = 0.0;
          for (cumdist = ntf_nbinpdf(varargin_1, varargin_2); cumdist < p[k];
               cumdist += ntf_b_nbinpdf(count, varargin_1, varargin_2)) {
            x[k] = x[k] + 1.0;
            count++;
          }
        }
      } else {
        x[k] = rtNaN;
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_q_icdf(const coder::array<double, 2U> &p, double varargin_1, coder::
                array<double, 2U> &x)
{
  int i;
  double d1;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    double d;
    d = p[k];
    if ((0.0 <= d) && (d <= 1.0) && (varargin_1 >= 0.0)) {
      if ((varargin_1 == 0.0) || (d == 0.0)) {
        x[k] = 0.0;
      } else if (d == 1.0) {
        x[k] = rtInf;
      } else if (varargin_1 > 10.0) {
        double count;
        creal_T y;
        count = -1.4142135623730951 * ntf_erfcinv(2.0 * d);
        count = std::ceil(std::sqrt(varargin_1) * count + varargin_1);
        if (count < 0.0) {
          count = 0.0;
        }

        d1 = (count + 1.0) + 1.0;
        ntf_gammaln(&d1);
        y = ntf_scalar_gammainc(varargin_1, count + 1.0, std::log(count + 1.0),
          d1);
        if (y.re < d) {
          do {
            count++;
            d1 = (count + 1.0) + 1.0;
            ntf_gammaln(&d1);
          } while (!!((ntf_scalar_gammainc(varargin_1, count + 1.0, std::log
                      (count + 1.0), d1)).re < d));
        } else {
          if (y.re > d) {
            int exitg1;
            do {
              exitg1 = 0;
              d1 = count + 1.0;
              ntf_gammaln(&d1);
              if ((ntf_scalar_gammainc(varargin_1, count, std::log(count), d1)).
                  re >= d) {
                count--;
              } else {
                exitg1 = 1;
              }
            } while (exitg1 == 0);
          }
        }

        x[k] = count;
      } else {
        double count;
        count = 0.0;
        int exitg1;
        do {
          exitg1 = 0;
          d1 = (count + 1.0) + 1.0;
          ntf_gammaln(&d1);
          if ((ntf_scalar_gammainc(varargin_1, count + 1.0, std::log(count + 1.0),
                d1)).re < d) {
            count++;
          } else {
            exitg1 = 1;
          }
        } while (exitg1 == 0);

        x[k] = count;
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_r_icdf(const coder::array<double, 2U> &p, double varargin_1, coder::
                array<double, 2U> &x)
{
  int i;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 > 0.0) && (p[k] >= 0.0) && (p[k] <= 1.0)) {
      if (p[k] > 0.0) {
        if (p[k] < 1.0) {
          x[k] = -varargin_1 * std::log(1.0 - p[k]);
        } else {
          x[k] = rtInf;
        }
      } else {
        x[k] = 0.0;
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                double varargin_2
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_s_icdf(const coder::array<double, 2U> &p, double varargin_1, double
                varargin_2, coder::array<double, 2U> &x)
{
  int i;
  double d;
  double d1;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    if ((0.0 <= varargin_1) && (!rtIsInf(varargin_1)) && (0.0 < varargin_2) &&
        (p[k] >= 0.0) && (p[k] <= 1.0)) {
      if ((p[k] > 0.0) && (p[k] < 1.0) && (varargin_1 > 0.0)) {
        d = varargin_1;
        ntf_gammaln(&d);
        d1 = varargin_1 + 1.0;
        ntf_gammaln(&d1);
        x[k] = ntf_eml_gammaincinv(p[k], varargin_1, std::log(varargin_1), d, d1)
          * varargin_2;
      } else if ((varargin_1 == 0.0) || (p[k] == 0.0)) {
        x[k] = 0.0;
      } else if (p[k] == 1.0) {
        x[k] = rtInf;
      } else {
        x[k] = rtNaN;
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                double varargin_2
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_t_icdf(const coder::array<double, 2U> &p, double varargin_1, double
                varargin_2, coder::array<double, 2U> &x)
{
  int i;
  double d;
  double d1;
  double d2;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 > 0.0) && (varargin_2 > 0.0) && (!rtIsInf(varargin_1)) &&
        (!rtIsInf(varargin_2)) && (p[k] >= 0.0) && (p[k] <= 1.0)) {
      d = varargin_1;
      ntf_gammaln(&d);
      d1 = varargin_2;
      ntf_gammaln(&d1);
      d2 = varargin_1 + varargin_2;
      ntf_gammaln(&d2);
      x[k] = ntf_eml_betaincinv(p[k], varargin_1, varargin_2, (d + d1) - d2);
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                double varargin_2
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_u_icdf(const coder::array<double, 2U> &p, double varargin_1, double
                varargin_2, coder::array<double, 2U> &x)
{
  int i;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    if ((varargin_2 > 0.0) && (p[k] >= 0.0) && (p[k] <= 1.0)) {
      double q;
      if (p[k] > 0.0) {
        q = std::log(1.0 - p[k]);
        if (-q > 0.0) {
          q = std::log(-q);
        } else {
          q = rtInf;
        }
      } else {
        q = rtMinusInf;
      }

      x[k] = varargin_2 * q + varargin_1;
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_2
//                double varargin_3
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_v_icdf(const coder::array<double, 2U> &p, double varargin_2, double
                varargin_3, coder::array<double, 2U> &x)
{
  int i;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int j = 0; j < i; j++) {
    if ((varargin_2 > 0.0) && (0.0 <= p[j]) && (p[j] <= 1.0)) {
      if (p[j] == 0.0) {
        x[j] = rtMinusInf;
      } else if (p[j] == 1.0) {
        x[j] = rtInf;
      } else {
        x[j] = varargin_2 * -std::log(-std::log(p[j])) + varargin_3;
      }
    } else {
      x[j] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                double varargin_2
//                double varargin_3
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_w_icdf(const coder::array<double, 2U> &p, double varargin_1, double
                varargin_2, double varargin_3, coder::array<double, 2U> &x)
{
  int i;
  double d;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int j = 0; j < i; j++) {
    if ((varargin_2 > 0.0) && (0.0 <= p[j]) && (p[j] <= 1.0)) {
      if (p[j] == 0.0) {
        if (varargin_1 <= 0.0) {
          x[j] = rtMinusInf;
        } else {
          x[j] = varargin_3 - varargin_2 / varargin_1;
        }
      } else if (p[j] == 1.0) {
        if (varargin_1 < 0.0) {
          x[j] = varargin_3 - varargin_2 / varargin_1;
        } else {
          x[j] = rtInf;
        }
      } else {
        if (std::abs(varargin_1) < 2.2204460492503131E-16) {
          d = -std::log(-std::log(p[j]));
        } else {
          d = -varargin_1 * std::log(-std::log(p[j]));
          ntf_expm1(&d);
          d /= varargin_1;
        }

        d = varargin_2 * d + varargin_3;
        x[j] = d;
      }
    } else {
      x[j] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                double varargin_2
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_x_icdf(const coder::array<double, 2U> &p, double varargin_1, double
                varargin_2, coder::array<double, 2U> &x)
{
  int i;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 > 0.0) && (varargin_2 > 0.0) && (0.0 <= p[k]) && (p[k] <=
         1.0)) {
      if (p[k] == 0.0) {
        x[k] = 0.0;
      } else if (p[k] == 1.0) {
        x[k] = rtInf;
      } else {
        x[k] = varargin_1 * ntf_rt_powd_snf(-std::log(1.0 - p[k]), 1.0 /
          varargin_2);
      }
    } else {
      x[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *p
//                double varargin_1
//                double varargin_2
//                double varargin_3
//                coder::array<double, 2U> *x
// Return Type  : void
//
void ntf_y_icdf(const coder::array<double, 2U> &p, double varargin_1, double
                varargin_2, double varargin_3, coder::array<double, 2U> &x)
{
  int i;
  double b_x;
  x.set_size(1, p.size(1));
  i = p.size(1);
  for (int j = 0; j < i; j++) {
    if ((varargin_2 > 0.0) && (0.0 <= p[j]) && (p[j] <= 1.0)) {
      if (p[j] == 0.0) {
        x[j] = varargin_3;
      } else if (p[j] == 1.0) {
        if (varargin_1 < 0.0) {
          x[j] = varargin_3 - varargin_2 / varargin_1;
        } else {
          x[j] = varargin_3 + rtInf;
        }
      } else if (std::abs(varargin_1) < 2.2204460492503131E-16) {
        double absz;
        b_x = -p[j];
        absz = std::abs(-p[j]);
        if ((absz > 4.503599627370496E+15) || (rtIsInf(-p[j]) || rtIsNaN(-p[j])))
        {
          b_x = std::log(-p[j] + 1.0);
        } else {
          if (!(absz < 2.2204460492503131E-16)) {
            b_x = std::log(-p[j] + 1.0) * (-p[j] / ((-p[j] + 1.0) - 1.0));
          }
        }

        x[j] = varargin_3 - varargin_2 * b_x;
      } else {
        double absz;
        b_x = -p[j];
        absz = std::abs(-p[j]);
        if ((absz > 4.503599627370496E+15) || (rtIsInf(-p[j]) || rtIsNaN(-p[j])))
        {
          b_x = std::log(-p[j] + 1.0);
        } else {
          if (!(absz < 2.2204460492503131E-16)) {
            b_x = std::log(-p[j] + 1.0) * (-p[j] / ((-p[j] + 1.0) - 1.0));
          }
        }

        b_x *= -varargin_1;
        ntf_expm1(&b_x);
        x[j] = varargin_3 + varargin_2 * b_x / varargin_1;
      }
    } else {
      x[j] = rtNaN;
    }
  }
}

//
// File trailer for ntf_icdf.cpp
//
// [EOF]
//
