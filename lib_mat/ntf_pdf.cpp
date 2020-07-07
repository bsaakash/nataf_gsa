//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_pdf.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 06-Jul-2020 21:30:41
//

// Include Files
#include "ntf_pdf.h"
#include "ntf_binodeviance.h"
#include "ntf_gammaln.h"
#include "ntf_inataf.h"
#include "ntf_inataf_rtwutil.h"
#include "ntf_stirlerr.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_2
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_b_pdf(const coder::array<double, 1U> &x, double varargin_2, coder::
               array<double, 1U> &y)
{
  int i;
  double lognk_tmp;
  double d;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int k = 0; k < i; k++) {
    if ((0.0 < varargin_2) && (varargin_2 <= 1.0)) {
      boolean_T b;
      b = rtIsNaN(x[k]);
      if (!b) {
        if ((x[k] >= 0.0) && (!rtIsInf(x[k])) && (x[k] == std::floor(x[k]))) {
          if (varargin_2 < 1.0) {
            double b_x;
            lognk_tmp = x[k] + 1.0;
            ntf_gammaln(&lognk_tmp);
            b_x = -varargin_2;
            if (!(std::abs(-varargin_2) < 2.2204460492503131E-16)) {
              b_x = std::log(-varargin_2 + 1.0) * (-varargin_2 / ((-varargin_2 +
                1.0) - 1.0));
            }

            d = 1.0;
            ntf_gammaln(&d);
            y[k] = std::exp((((lognk_tmp - lognk_tmp) - d) + std::log(varargin_2))
                            + x[k] * b_x);
          } else {
            y[k] = (x[k] == 0.0);
          }
        } else {
          y[k] = 0.0;
        }
      } else {
        y[k] = rtNaN;
      }
    } else {
      y[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_1
//                double varargin_2
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_c_pdf(const coder::array<double, 1U> &x, double varargin_1, double
               varargin_2, coder::array<double, 1U> &y)
{
  int i;
  double d;
  double d1;
  double d2;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 > 0.0) && (!rtIsInf(varargin_1)) && (0.0 < varargin_2) &&
        (varargin_2 <= 1.0)) {
      boolean_T b;
      b = rtIsNaN(x[k]);
      if (!b) {
        if ((x[k] >= 0.0) && (!rtIsInf(x[k])) && (x[k] == std::floor(x[k]))) {
          if (varargin_2 < 1.0) {
            double b_x;
            b_x = -varargin_2;
            if (!(std::abs(-varargin_2) < 2.2204460492503131E-16)) {
              b_x = std::log(-varargin_2 + 1.0) * (-varargin_2 / ((-varargin_2 +
                1.0) - 1.0));
            }

            d = varargin_1 + x[k];
            ntf_gammaln(&d);
            d1 = x[k] + 1.0;
            ntf_gammaln(&d1);
            d2 = varargin_1;
            ntf_gammaln(&d2);
            y[k] = std::exp((((d - d1) - d2) + varargin_1 * std::log(varargin_2))
                            + x[k] * b_x);
          } else {
            y[k] = (x[k] == 0.0);
          }
        } else {
          y[k] = 0.0;
        }
      } else {
        y[k] = rtNaN;
      }
    } else {
      y[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_1
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_d_pdf(const coder::array<double, 1U> &x, double varargin_1, coder::
               array<double, 1U> &y)
{
  int i;
  double b_x;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 >= 0.0) && (!rtIsNaN(x[k]))) {
      if ((varargin_1 == 0.0) && (x[k] == 0.0)) {
        y[k] = 1.0;
      } else if ((x[k] >= 0.0) && (x[k] == std::floor(x[k]))) {
        if (x[k] <= varargin_1 * 2.2250738585072014E-308) {
          y[k] = std::exp(-varargin_1);
        } else if (varargin_1 <= x[k] * 2.2250738585072014E-308) {
          b_x = x[k] + 1.0;
          ntf_gammaln(&b_x);
          y[k] = std::exp((-varargin_1 + x[k] * std::log(varargin_1)) - b_x);
        } else {
          b_x = ((-0.91893853320467267 - 0.5 * std::log(x[k])) - ntf_stirlerr
                 (x[k])) - ntf_binodeviance(x[k], varargin_1);
          y[k] = std::exp(b_x);
        }
      } else {
        y[k] = 0.0;
      }
    } else {
      y[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_1
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_e_pdf(const coder::array<double, 1U> &x, double varargin_1, coder::
               array<double, 1U> &y)
{
  int i;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 > 0.0) && (!rtIsNaN(x[k]))) {
      if (x[k] < 0.0) {
        y[k] = 0.0;
      } else {
        y[k] = std::exp(-x[k] / varargin_1) / varargin_1;
      }
    } else {
      y[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_1
//                double varargin_2
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_f_pdf(const coder::array<double, 1U> &x, double varargin_1, double
               varargin_2, coder::array<double, 1U> &y)
{
  int i;
  double b_y;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 >= 0.0) && (varargin_2 > 0.0) && (!rtIsNaN(x[k]))) {
      double zk;
      zk = x[k] / varargin_2;
      if (zk == 0.0) {
        if (varargin_1 < 1.0) {
          y[k] = rtInf;
        } else if (varargin_1 > 1.0) {
          y[k] = 0.0;
        } else {
          y[k] = 1.0 / varargin_2;
        }
      } else if ((zk < 0.0) || rtIsInf(zk) || rtIsInf(varargin_1)) {
        y[k] = 0.0;
      } else if (varargin_1 < 1.0) {
        if (varargin_1 <= 2.2250738585072014E-308 * zk) {
          b_y = std::exp(-zk);
        } else if (zk < 2.2250738585072014E-308 * varargin_1) {
          b_y = varargin_1 + 1.0;
          ntf_gammaln(&b_y);
          b_y = std::exp((varargin_1 * std::log(zk) - zk) - b_y);
        } else {
          b_y = ((-0.91893853320467267 - 0.5 * std::log(varargin_1)) -
                 ntf_stirlerr(varargin_1)) - ntf_binodeviance(varargin_1, zk);
          b_y = std::exp(b_y);
        }

        y[k] = b_y * std::exp(std::log(varargin_1) - std::log(zk)) / varargin_2;
      } else {
        if (varargin_1 - 1.0 <= 2.2250738585072014E-308 * zk) {
          b_y = std::exp(-zk);
        } else if (zk < 2.2250738585072014E-308 * (varargin_1 - 1.0)) {
          b_y = (varargin_1 - 1.0) + 1.0;
          ntf_gammaln(&b_y);
          b_y = std::exp(((varargin_1 - 1.0) * std::log(zk) - zk) - b_y);
        } else {
          b_y = ((-0.91893853320467267 - 0.5 * std::log(varargin_1 - 1.0)) -
                 ntf_stirlerr(varargin_1 - 1.0)) - ntf_binodeviance(varargin_1 -
            1.0, zk);
          b_y = std::exp(b_y);
        }

        y[k] = b_y / varargin_2;
      }
    } else {
      y[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_1
//                double varargin_2
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_g_pdf(const coder::array<double, 1U> &x, double varargin_1, double
               varargin_2, coder::array<double, 1U> &y)
{
  int i;
  double b_logb;
  double absz;
  double d;
  double d1;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 > 0.0) && (varargin_2 > 0.0) && (!rtIsNaN(x[k]))) {
      if ((x[k] > 0.0) && (x[k] < 1.0)) {
        if (x[k] < 0.1) {
          b_logb = -x[k];
          absz = std::abs(-x[k]);
          if ((absz > 4.503599627370496E+15) || (rtIsInf(-x[k]) || rtIsNaN(-x[k])))
          {
            b_logb = std::log(-x[k] + 1.0);
          } else {
            if (!(absz < 2.2204460492503131E-16)) {
              b_logb = std::log(-x[k] + 1.0) * (-x[k] / ((-x[k] + 1.0) - 1.0));
            }
          }

          b_logb *= varargin_2 - 1.0;
        } else {
          b_logb = (varargin_2 - 1.0) * std::log(1.0 - x[k]);
        }

        absz = varargin_1;
        ntf_gammaln(&absz);
        d = varargin_2;
        ntf_gammaln(&d);
        d1 = varargin_1 + varargin_2;
        ntf_gammaln(&d1);
        y[k] = std::exp(((varargin_1 - 1.0) * std::log(x[k]) + b_logb) - ((absz
          + d) - d1));
      } else if ((varargin_1 == 1.0) && (x[k] == 0.0)) {
        y[k] = varargin_2;
      } else if ((varargin_2 == 1.0) && (x[k] == 1.0)) {
        y[k] = varargin_1;
      } else if (((varargin_1 < 1.0) && (x[k] == 0.0)) || ((varargin_2 < 1.0) &&
                  (x[k] == 1.0))) {
        y[k] = rtInf;
      } else {
        y[k] = 0.0;
      }
    } else {
      y[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_2
//                double varargin_3
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_h_pdf(const coder::array<double, 1U> &x, double varargin_2, double
               varargin_3, coder::array<double, 1U> &y)
{
  int i;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int j = 0; j < i; j++) {
    if (varargin_2 > 0.0) {
      double zj;
      zj = (x[j] - varargin_3) / varargin_2;
      if (rtIsInf(zj)) {
        y[j] = 0.0;
      } else {
        y[j] = std::exp(-std::exp(-zj) - zj) / varargin_2;
      }
    } else {
      y[j] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_1
//                double varargin_2
//                double varargin_3
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_i_pdf(const coder::array<double, 1U> &x, double varargin_1, double
               varargin_2, double varargin_3, coder::array<double, 1U> &y)
{
  int i;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int j = 0; j < i; j++) {
    if (varargin_2 > 0.0) {
      double zj;
      zj = (x[j] - varargin_3) / varargin_2;
      if (rtIsInf(zj)) {
        y[j] = 0.0;
      } else if (std::abs(varargin_1) < 2.2204460492503131E-16) {
        y[j] = std::exp(-std::exp(-zj) - zj) / varargin_2;
      } else {
        double tj;
        tj = zj * varargin_1;
        if (tj <= -1.0) {
          y[j] = 0.0;
        } else {
          zj = std::abs(tj);
          if ((zj > 4.503599627370496E+15) || (rtIsInf(tj) || rtIsNaN(tj))) {
            tj = std::log(tj + 1.0);
          } else {
            if (!(zj < 2.2204460492503131E-16)) {
              tj = std::log(tj + 1.0) * (tj / ((tj + 1.0) - 1.0));
            }
          }

          zj = 1.0 / varargin_1;
          y[j] = std::exp(-std::exp(-zj * tj) - (zj + 1.0) * tj) / varargin_2;
        }
      }
    } else {
      y[j] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_1
//                double varargin_2
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_j_pdf(const coder::array<double, 1U> &x, double varargin_1, double
               varargin_2, coder::array<double, 1U> &y)
{
  int i;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 > 0.0) && (varargin_2 > 0.0)) {
      if (x[k] < 0.0) {
        y[k] = 0.0;
      } else {
        double zk;
        double wk;
        zk = x[k] / varargin_1;
        wk = std::exp(-ntf_rt_powd_snf(zk, varargin_2));
        if (rtIsNaN(wk)) {
          y[k] = rtNaN;
        } else if (wk > 0.0) {
          y[k] = ntf_rt_powd_snf(zk, varargin_2 - 1.0) * wk * varargin_2 /
            varargin_1;
        } else {
          y[k] = 0.0;
        }
      }
    } else {
      y[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_1
//                double varargin_2
//                double varargin_3
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_k_pdf(const coder::array<double, 1U> &x, double varargin_1, double
               varargin_2, double varargin_3, coder::array<double, 1U> &y)
{
  int i;
  double zj;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int j = 0; j < i; j++) {
    if (varargin_2 > 0.0) {
      zj = (x[j] - varargin_3) / varargin_2;
      if (zj < 0.0) {
        y[j] = 0.0;
      } else if (std::abs(varargin_1) < 2.2204460492503131E-16) {
        y[j] = std::exp(-zj) / varargin_2;
      } else {
        zj *= varargin_1;
        if ((zj <= -1.0) && (varargin_1 < 0.0)) {
          y[j] = 0.0;
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

          y[j] = std::exp((-1.0 - 1.0 / varargin_1) * zj) / varargin_2;
        }
      }
    } else {
      y[j] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_1
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_l_pdf(const coder::array<double, 1U> &x, double varargin_1, coder::
               array<double, 1U> &y)
{
  int i;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 > 0.0) && (!rtIsNaN(x[k]))) {
      if (x[k] >= 0.0) {
        y[k] = x[k] / (varargin_1 * varargin_1) * std::exp(-x[k] * x[k] / (2.0 *
          varargin_1 * varargin_1));
      } else {
        y[k] = 0.0;
      }
    } else {
      y[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_1
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_m_pdf(const coder::array<double, 1U> &x, double varargin_1, coder::
               array<double, 1U> &y)
{
  int i;
  double b_y;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_1 >= 0.0) && (!rtIsNaN(x[k]))) {
      double zk;
      zk = x[k] / 2.0;
      if (zk == 0.0) {
        if (varargin_1 < 1.0) {
          y[k] = rtInf;
        } else if (varargin_1 > 1.0) {
          y[k] = 0.0;
        } else {
          y[k] = 0.5;
        }
      } else if ((zk < 0.0) || rtIsInf(zk) || rtIsInf(varargin_1)) {
        y[k] = 0.0;
      } else if (varargin_1 < 1.0) {
        if (varargin_1 <= 2.2250738585072014E-308 * zk) {
          b_y = std::exp(-zk);
        } else if (zk < 2.2250738585072014E-308 * varargin_1) {
          b_y = varargin_1 + 1.0;
          ntf_gammaln(&b_y);
          b_y = std::exp((varargin_1 * std::log(zk) - zk) - b_y);
        } else {
          b_y = ((-0.91893853320467267 - 0.5 * std::log(varargin_1)) -
                 ntf_stirlerr(varargin_1)) - ntf_binodeviance(varargin_1, zk);
          b_y = std::exp(b_y);
        }

        y[k] = b_y * std::exp(std::log(varargin_1) - std::log(zk)) / 2.0;
      } else {
        if (varargin_1 - 1.0 <= 2.2250738585072014E-308 * zk) {
          b_y = std::exp(-zk);
        } else if (zk < 2.2250738585072014E-308 * (varargin_1 - 1.0)) {
          b_y = (varargin_1 - 1.0) + 1.0;
          ntf_gammaln(&b_y);
          b_y = std::exp(((varargin_1 - 1.0) * std::log(zk) - zk) - b_y);
        } else {
          b_y = ((-0.91893853320467267 - 0.5 * std::log(varargin_1 - 1.0)) -
                 ntf_stirlerr(varargin_1 - 1.0)) - ntf_binodeviance(varargin_1 -
            1.0, zk);
          b_y = std::exp(b_y);
        }

        y[k] = b_y / 2.0;
      }
    } else {
      y[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_1
//                double varargin_2
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_n_pdf(const coder::array<double, 1U> &x, double varargin_1, double
               varargin_2, coder::array<double, 1U> &y)
{
  int i;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int k = 0; k < i; k++) {
    if (varargin_1 < varargin_2) {
      if ((x[k] >= varargin_1) && (x[k] <= varargin_2)) {
        y[k] = 1.0 / (varargin_2 - varargin_1);
      } else {
        y[k] = 0.0;
      }
    } else {
      y[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_1
//                double varargin_2
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_o_pdf(const coder::array<double, 1U> &x, double varargin_1, double
               varargin_2, coder::array<double, 1U> &y)
{
  int i;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int k = 0; k < i; k++) {
    if (varargin_2 > 0.0) {
      double t;
      t = (x[k] - varargin_1) / varargin_2;
      y[k] = std::exp(-0.5 * t * t) / (2.5066282746310002 * varargin_2);
    } else {
      y[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_1
//                double varargin_2
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_p_pdf(const coder::array<double, 1U> &x, double varargin_1, double
               varargin_2, coder::array<double, 1U> &y)
{
  int i;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int k = 0; k < i; k++) {
    if (varargin_2 > 0.0) {
      if (x[k] <= 0.0) {
        y[k] = 0.0;
      } else {
        double t;
        t = (std::log(x[k]) - varargin_1) / varargin_2;
        y[k] = std::exp(-0.5 * t * t) / (x[k] * 2.5066282746310002 * varargin_2);
      }
    } else {
      y[k] = rtNaN;
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> *x
//                double varargin_1
//                double varargin_2
//                coder::array<double, 1U> *y
// Return Type  : void
//
void ntf_pdf(const coder::array<double, 1U> &x, double varargin_1, double
             varargin_2, coder::array<double, 1U> &y)
{
  int i;
  double d;
  double d1;
  double d3;
  y.set_size(x.size(0));
  i = x.size(0);
  for (int k = 0; k < i; k++) {
    if ((varargin_2 >= 0.0) && (varargin_2 <= 1.0) && (varargin_1 == std::floor
         (varargin_1)) && (!rtIsNaN(x[k]))) {
      if ((x[k] >= 0.0) && (x[k] == std::floor(x[k])) && (x[k] <= varargin_1)) {
        if (varargin_2 == 0.0) {
          y[k] = (x[k] == 0.0);
        } else if (varargin_2 == 1.0) {
          y[k] = (x[k] == varargin_1);
        } else if (x[k] == 0.0) {
          y[k] = std::exp(varargin_1 * std::log(1.0 - varargin_2));
        } else if (x[k] == varargin_1) {
          y[k] = std::exp(varargin_1 * std::log(varargin_2));
        } else if (varargin_1 < 10.0) {
          double b_x;
          double d2;
          b_x = -varargin_2;
          if (!(std::abs(-varargin_2) < 2.2204460492503131E-16)) {
            b_x = std::log(-varargin_2 + 1.0) * (-varargin_2 / ((-varargin_2 +
              1.0) - 1.0));
          }

          d = varargin_1 + 1.0;
          ntf_gammaln(&d);
          d1 = x[k] + 1.0;
          ntf_gammaln(&d1);
          d2 = varargin_1 - x[k];
          d3 = d2 + 1.0;
          ntf_gammaln(&d3);
          y[k] = std::exp((((d - d1) - d3) + x[k] * std::log(varargin_2)) + d2 *
                          b_x);
        } else {
          double b_x;
          b_x = (((ntf_stirlerr(varargin_1) - ntf_stirlerr(x[k])) - ntf_stirlerr
                  (varargin_1 - x[k])) - ntf_binodeviance(x[k], varargin_1 *
                  varargin_2)) - ntf_binodeviance(varargin_1 - x[k], varargin_1 *
            (1.0 - varargin_2));
          b_x = std::exp(b_x);
          y[k] = b_x * std::sqrt(varargin_1 / (6.2831853071795862 * x[k] *
            (varargin_1 - x[k])));
        }
      } else {
        y[k] = 0.0;
      }
    } else {
      y[k] = rtNaN;
    }
  }
}

//
// File trailer for ntf_pdf.cpp
//
// [EOF]
//
