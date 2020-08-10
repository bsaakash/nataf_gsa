//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_evfit.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_evfit.h"
#include "ntf_ERADist.h"
#include "ntf_fzero.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "ntf_std.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>

// Function Definitions

//
// Arguments    : const coder::array<double, 1U> *x
//                double parmhat[2]
// Return Type  : void
//
void ntf_evfit(const coder::array<double, 1U> &x, double parmhat[2])
{
  double tempMin;
  double tempMax;
  int k;
  int vlen;
  double rangex;
  coder::array<double, 1U> x0;
  double sigmahat;
  coder::array<double, 1U> wt;
  coder::array<double, 1U> b_x;
  double y;
  double upper;
  double lower[2];
  int exponent;
  tempMin = rtInf;
  tempMax = rtMinusInf;
  k = x.size(0);
  for (vlen = 0; vlen < k; vlen++) {
    if (x[vlen] > tempMax) {
      tempMax = x[vlen];
    }

    if (x[vlen] < tempMin) {
      tempMin = x[vlen];
    }
  }

  rangex = tempMax - tempMin;
  if ((x.size(0) == 0) || (rtIsInf(rangex) || rtIsNaN(rangex))) {
    parmhat[0] = rtNaN;
    parmhat[1] = rtNaN;
  } else if (rangex < 2.2250738585072014E-308) {
    parmhat[0] = x[0];
    parmhat[1] = 0.0;
  } else {
    int loop_ub;
    double wgtmeanUnc;
    x0.set_size(x.size(0));
    loop_ub = x.size(0);
    for (k = 0; k < loop_ub; k++) {
      x0[k] = (x[k] - tempMax) / rangex;
    }

    sigmahat = 2.4494897427831779 * ntf_std(x0) / 3.1415926535897931;
    vlen = x0.size(0);
    tempMin = x0[0];
    for (k = 2; k <= vlen; k++) {
      tempMin += x0[k - 1];
    }

    wgtmeanUnc = tempMin / static_cast<double>(x.size(0));
    wt.set_size(x0.size(0));
    loop_ub = x0.size(0);
    for (k = 0; k < loop_ub; k++) {
      wt[k] = x0[k] / sigmahat;
    }

    vlen = wt.size(0);
    for (k = 0; k < vlen; k++) {
      wt[k] = std::exp(wt[k]);
    }

    b_x.set_size(x0.size(0));
    loop_ub = x0.size(0);
    for (k = 0; k < loop_ub; k++) {
      b_x[k] = x0[k] * wt[k];
    }

    vlen = b_x.size(0);
    tempMin = b_x[0];
    for (k = 2; k <= vlen; k++) {
      tempMin += b_x[k - 1];
    }

    vlen = wt.size(0);
    y = wt[0];
    for (k = 2; k <= vlen; k++) {
      y += wt[k - 1];
    }

    if ((sigmahat + wgtmeanUnc) - tempMin / y > 0.0) {
      int b_loop_ub;
      upper = sigmahat;
      sigmahat *= 0.5;
      loop_ub = x0.size(0);
      b_loop_ub = x0.size(0);
      int exitg1;
      do {
        exitg1 = 0;
        wt.set_size(x0.size(0));
        for (k = 0; k < loop_ub; k++) {
          wt[k] = x0[k] / sigmahat;
        }

        vlen = wt.size(0);
        for (k = 0; k < vlen; k++) {
          wt[k] = std::exp(wt[k]);
        }

        b_x.set_size(x0.size(0));
        for (k = 0; k < b_loop_ub; k++) {
          b_x[k] = x0[k] * wt[k];
        }

        vlen = b_x.size(0);
        tempMin = b_x[0];
        for (k = 2; k <= vlen; k++) {
          tempMin += b_x[k - 1];
        }

        vlen = wt.size(0);
        y = wt[0];
        for (k = 2; k <= vlen; k++) {
          y += wt[k - 1];
        }

        if ((sigmahat + wgtmeanUnc) - tempMin / y > 0.0) {
          upper = sigmahat;
          sigmahat *= 0.5;
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    } else {
      int b_loop_ub;
      upper = 2.0 * sigmahat;
      loop_ub = x0.size(0);
      b_loop_ub = x0.size(0);
      int exitg1;
      do {
        exitg1 = 0;
        wt.set_size(x0.size(0));
        for (k = 0; k < loop_ub; k++) {
          wt[k] = x0[k] / upper;
        }

        vlen = wt.size(0);
        for (k = 0; k < vlen; k++) {
          wt[k] = std::exp(wt[k]);
        }

        b_x.set_size(x0.size(0));
        for (k = 0; k < b_loop_ub; k++) {
          b_x[k] = x0[k] * wt[k];
        }

        vlen = b_x.size(0);
        tempMin = b_x[0];
        for (k = 2; k <= vlen; k++) {
          tempMin += b_x[k - 1];
        }

        vlen = wt.size(0);
        y = wt[0];
        for (k = 2; k <= vlen; k++) {
          y += wt[k - 1];
        }

        if ((upper + wgtmeanUnc) - tempMin / y < 0.0) {
          sigmahat = upper;
          upper *= 2.0;
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }

    lower[0] = sigmahat;
    lower[1] = upper;
    ntf_c_fzero(lower, x0, wgtmeanUnc, &sigmahat, &tempMin, &y);
    tempMin = std::abs(tempMin);
    if ((!rtIsInf(tempMin)) && (!rtIsNaN(tempMin)) && (!(tempMin <=
          2.2250738585072014E-308))) {
      frexp(tempMin, &exponent);
    }

    loop_ub = x0.size(0);
    for (k = 0; k < loop_ub; k++) {
      x0[k] = x0[k] / sigmahat;
    }

    vlen = x0.size(0);
    for (k = 0; k < vlen; k++) {
      x0[k] = std::exp(x0[k]);
    }

    vlen = x0.size(0);
    tempMin = x0[0];
    for (k = 2; k <= vlen; k++) {
      tempMin += x0[k - 1];
    }

    parmhat[0] = rangex * (sigmahat * std::log(tempMin / static_cast<double>
      (x.size(0)))) + tempMax;
    parmhat[1] = rangex * sigmahat;
  }
}

//
// File trailer for ntf_evfit.cpp
//
// [EOF]
//
