//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_LognormalDistribution.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_LognormalDistribution.h"
#include "ntf_ERADist.h"
#include "ntf_inataf.h"
#include "ntf_normfit.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double mu
//                double sigma
// Return Type  : void
//
void ntf_prob_coder_LognormalDistrib::ntf_init(double mu, double sigma)
{
  this->ParameterValues[0] = mu;
  this->ParameterValues[1] = sigma;
}

//
// Arguments    : const coder::array<double, 1U> &x
// Return Type  : ntf_prob_coder_LognormalDistrib
//
ntf_prob_coder_LognormalDistrib ntf_prob_coder_LognormalDistrib::ntf_fit(const
  coder::array<double, 1U> &x)
{
  ntf_prob_coder_LognormalDistrib pd;
  coder::array<double, 1U> b_x;
  int nx;
  int k;
  double muhat;
  double sigmahat;
  b_x.set_size(x.size(0));
  nx = x.size(0);
  for (k = 0; k < nx; k++) {
    b_x[k] = x[k];
  }

  nx = x.size(0);
  for (k = 0; k < nx; k++) {
    b_x[k] = std::log(b_x[k]);
  }

  ntf_normfit(b_x, &muhat, &sigmahat);
  pd.ntf_init(muhat, sigmahat);
  return pd;
}

//
// File trailer for ntf_LognormalDistribution.cpp
//
// [EOF]
//
