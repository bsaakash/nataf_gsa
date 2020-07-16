//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_BetaDistribution.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//

// Include Files
#include "ntf_BetaDistribution.h"
#include "ntf_fminsearch.h"
#include "ntf_inataf.h"
#include "ntf_inataf_data.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>

// Function Definitions

//
// Arguments    : double a
//                double b
// Return Type  : void
//
void ntf_prob_coder_BetaDistribution::ntf_init(double a, double b)
{
  this->ParameterValues[0] = a;
  this->ParameterValues[1] = b;
}

//
// Arguments    : const coder::array<double, 1U> &x
// Return Type  : ntf_prob_coder_BetaDistribution
//
ntf_prob_coder_BetaDistribution ntf_prob_coder_BetaDistribution::ntf_fit(const
  coder::array<double, 1U> &x)
{
  ntf_prob_coder_BetaDistribution pd;
  double logphat[2];
  coder::array<double, 1U> xx;
  int b_n1;
  if (x.size(0) == 0) {
    logphat[0] = rtNaN;
    logphat[1] = rtNaN;
  } else {
    int n;
    double xmin;
    double xmax;
    int b_n0;
    int i;
    int k;
    double absx;
    double tmp1;
    double tmp2;
    double tmp3;
    double absz;
    n = 0;
    xmin = 2.0;
    xmax = -1.0;
    xx.set_size(x.size(0));
    b_n0 = x.size(0);
    for (i = 0; i < b_n0; i++) {
      xx[i] = 0.0;
    }

    i = x.size(0);
    for (k = 0; k < i; k++) {
      if (!rtIsNaN(x[k])) {
        if (x[k] < xmin) {
          xmin = x[k];
        }

        if (x[k] > xmax) {
          xmax = x[k];
        }

        n++;
        xx[n - 1] = x[k];
      }
    }

    absx = std::abs(xmax);
    if ((!rtIsInf(absx)) && (!rtIsNaN(absx)) && (!(absx <=
          2.2250738585072014E-308))) {
      frexp(absx, &b_n1);
    }

    ntf_sumlogx = 0.0;
    ntf_sumlog1mx = 0.0;
    for (k = 0; k < n; k++) {
      ntf_sumlogx += std::log(xx[k]);
      absx = -xx[k];
      absz = std::abs(-xx[k]);
      if ((absz > 4.503599627370496E+15) || (rtIsInf(-xx[k]) || rtIsNaN(-xx[k])))
      {
        absx = std::log(-xx[k] + 1.0);
      } else {
        if (!(absz < 2.2204460492503131E-16)) {
          absx = std::log(-xx[k] + 1.0) * (-xx[k] / ((-xx[k] + 1.0) - 1.0));
        }
      }

      ntf_sumlog1mx += absx;
    }

    tmp1 = std::exp(ntf_sumlog1mx / static_cast<double>(n));
    tmp2 = std::exp(ntf_sumlogx / static_cast<double>(n));
    tmp3 = (1.0 - tmp1) - tmp2;
    if ((xmin >= 1.4916681462400413E-154) && (xmax <= 0.99999999999999989)) {
      b_n0 = 0;
      b_n1 = 0;
    } else {
      b_n0 = 0;
      b_n1 = 0;
      ntf_sumlogx = 0.0;
      ntf_sumlog1mx = 0.0;
      for (k = 0; k < n; k++) {
        if (xx[k] < 1.4916681462400413E-154) {
          b_n0++;
        } else if (xx[k] > 0.99999999999999989) {
          b_n1++;
        } else {
          ntf_sumlogx += std::log(xx[k]);
          absx = -xx[k];
          absz = std::abs(-xx[k]);
          if ((absz > 4.503599627370496E+15) || (rtIsInf(-xx[k]) || rtIsNaN
               (-xx[k]))) {
            absx = std::log(-xx[k] + 1.0);
          } else {
            if (!(absz < 2.2204460492503131E-16)) {
              absx = std::log(-xx[k] + 1.0) * (-xx[k] / ((-xx[k] + 1.0) - 1.0));
            }
          }

          ntf_sumlog1mx += absx;
        }
      }

      n = (n - b_n0) - b_n1;
    }

    ntf_n0 = b_n0;
    ntf_n1 = b_n1;
    ntf_n2 = n;
    ntf_xl = 1.4916681462400413E-154;
    ntf_xu = 0.99999999999999989;
    logphat[0] = std::log(0.5 * (1.0 - tmp1) / tmp3);
    logphat[1] = std::log(0.5 * (1.0 - tmp2) / tmp3);
    ntf_c_fminsearch(logphat);
    logphat[0] = std::exp(logphat[0]);
    logphat[1] = std::exp(logphat[1]);
  }

  pd.ntf_init(logphat[0], logphat[1]);
  return pd;
}

//
// File trailer for ntf_BetaDistribution.cpp
//
// [EOF]
//
