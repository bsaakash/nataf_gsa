//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_ExponentialDistribution.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//

// Include Files
#include "ntf_ExponentialDistribution.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : double mu
// Return Type  : void
//
void ntf_prob_coder_ExponentialDistr::ntf_init(double mu)
{
  this->ParameterValues = mu;
}

//
// Arguments    : const coder::array<double, 1U> &x
// Return Type  : ntf_prob_coder_ExponentialDistr
//
ntf_prob_coder_ExponentialDistr ntf_prob_coder_ExponentialDistr::ntf_fit(const
  coder::array<double, 1U> &x)
{
  ntf_prob_coder_ExponentialDistr pd;
  double mu;
  if (x.size(0) > 0) {
    int vlen;
    vlen = x.size(0);
    mu = x[0];
    for (int k = 2; k <= vlen; k++) {
      mu += x[k - 1];
    }

    mu /= static_cast<double>(x.size(0));
  } else {
    mu = rtNaN;
  }

  pd.ntf_init(mu);
  return pd;
}

//
// File trailer for ntf_ExponentialDistribution.cpp
//
// [EOF]
//
