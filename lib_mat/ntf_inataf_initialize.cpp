//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_inataf_initialize.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_inataf_initialize.h"
#include "ntf_betafit.h"
#include "ntf_eml_rand_mt19937ar_stateful.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void inataf_initialize()
{
  rt_InitInfAndNaN();
  ntf_negloglike_init();
  ntf_eml_rand_mt19937ar_stateful();
}

//
// File trailer for ntf_inataf_initialize.cpp
//
// [EOF]
//
