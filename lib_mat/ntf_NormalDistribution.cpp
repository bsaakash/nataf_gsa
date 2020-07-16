//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_NormalDistribution.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//

// Include Files
#include "ntf_NormalDistribution.h"
#include "ntf_inataf.h"
#include "ntf_normfit.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : double mu
//                double sigma
// Return Type  : void
//
void ntf_prob_coder_NormalDistributi::ntf_init(double mu, double sigma)
{
  this->ParameterValues[0] = mu;
  this->ParameterValues[1] = sigma;
}

//
// Arguments    : const coder::array<double, 1U> &x
// Return Type  : ntf_prob_coder_NormalDistributi
//
ntf_prob_coder_NormalDistributi ntf_prob_coder_NormalDistributi::ntf_fit(const
  coder::array<double, 1U> &x)
{
  ntf_prob_coder_NormalDistributi pd;
  double m;
  double s;
  ntf_normfit(x, &m, &s);
  pd.ntf_init(m, s);
  return pd;
}

//
// File trailer for ntf_NormalDistribution.cpp
//
// [EOF]
//
