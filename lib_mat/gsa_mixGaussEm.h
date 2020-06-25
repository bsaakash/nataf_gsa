//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_mixGaussEm.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:12:52
//
#ifndef GSA_MIXGAUSSEM_H
#define GSA_MIXGAUSSEM_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "gsa_runGSA_types.h"

// Function Declarations
extern void gsa_mixGaussEm(const coder::array<double, 2U> &X_temp, double init,
  coder::array<double, 1U> &label, coder::array<double, 2U> &model_mu, coder::
  array<double, 3U> &model_Sigma, coder::array<double, 2U> &model_w, double
  llh_data[], int llh_size[2]);

#endif

//
// File trailer for gsa_mixGaussEm.h
//
// [EOF]
//
