//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_ExtremeValueDistribution.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_ExtremeValueDistribution.h"
#include "ntf_evfit.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : double mu
//                double sigma
// Return Type  : void
//
void ntf_prob_coder_ExtremeValueDist::ntf_init(double mu, double sigma)
{
  this->ParameterValues[0] = mu;
  this->ParameterValues[1] = sigma;
}

//
// Arguments    : const coder::array<double, 1U> &x
// Return Type  : ntf_prob_coder_ExtremeValueDist
//
ntf_prob_coder_ExtremeValueDist ntf_prob_coder_ExtremeValueDist::ntf_fit(const
  coder::array<double, 1U> &x)
{
  ntf_prob_coder_ExtremeValueDist pd;
  double p[2];
  ntf_evfit(x, p);
  pd.ntf_init(p[0], p[1]);
  return pd;
}

//
// File trailer for ntf_ExtremeValueDistribution.cpp
//
// [EOF]
//
