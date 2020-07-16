//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_WeibullDistribution.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//

// Include Files
#include "ntf_WeibullDistribution.h"
#include "ntf_evfit.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double a
//                double b
// Return Type  : void
//
void ntf_prob_coder_WeibullDistribut::ntf_init(double a, double b)
{
  this->ParameterValues[0] = a;
  this->ParameterValues[1] = b;
}

//
// Arguments    : const coder::array<double, 1U> &x
// Return Type  : ntf_prob_coder_WeibullDistribut
//
ntf_prob_coder_WeibullDistribut ntf_prob_coder_WeibullDistribut::ntf_fit(const
  coder::array<double, 1U> &x)
{
  ntf_prob_coder_WeibullDistribut pd;
  coder::array<double, 1U> b_x;
  int nx;
  int k;
  double parmhatEV[2];
  b_x.set_size(x.size(0));
  nx = x.size(0);
  for (k = 0; k < nx; k++) {
    b_x[k] = x[k];
  }

  nx = x.size(0);
  for (k = 0; k < nx; k++) {
    b_x[k] = std::log(b_x[k]);
  }

  double b;
  ntf_evfit(b_x, parmhatEV);
  b = std::exp(parmhatEV[0]);
  pd.ntf_init(b, (1.0 / parmhatEV[1]));
  return pd;
}

//
// File trailer for ntf_WeibullDistribution.cpp
//
// [EOF]
//
