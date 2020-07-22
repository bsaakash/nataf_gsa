//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_normfit.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_normfit.h"
#include "ntf_ERADist.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<double, 1U> *x
//                double *muhat
//                double *sigmahat
// Return Type  : void
//
void ntf_normfit(const coder::array<double, 1U> &x, double *muhat, double
                 *sigmahat)
{
  double y;
  coder::array<double, 1U> xc;
  if (x.size(0) == 0) {
    *muhat = rtNaN;
    *sigmahat = rtNaN;
  } else {
    int vlen;
    int k;
    vlen = x.size(0);
    y = x[0];
    for (k = 2; k <= vlen; k++) {
      y += x[k - 1];
    }

    *muhat = y / static_cast<double>(x.size(0));
    if (x.size(0) > 1) {
      xc.set_size(x.size(0));
      vlen = x.size(0);
      for (k = 0; k < vlen; k++) {
        xc[k] = x[k] - *muhat;
      }

      vlen = xc.size(0);
      for (k = 0; k < vlen; k++) {
        xc[k] = xc[k] * xc[k];
      }

      vlen = xc.size(0);
      y = xc[0];
      for (k = 2; k <= vlen; k++) {
        y += xc[k - 1];
      }

      *sigmahat = std::sqrt(y / (static_cast<double>(x.size(0)) - 1.0));
    } else {
      *sigmahat = 0.0;
    }
  }
}

//
// File trailer for ntf_normfit.cpp
//
// [EOF]
//
