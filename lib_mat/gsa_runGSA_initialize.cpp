//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_runGSA_initialize.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 21:17:14
//

// Include Files
#include "gsa_runGSA_initialize.h"
#include "gsa_eml_rand_mt19937ar_stateful.h"
#include "gsa_runGSA.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void runGSA_initialize()
{
  rt_InitInfAndNaN();
  gsa_eml_rand_mt19937ar_stateful();
}

//
// File trailer for gsa_runGSA_initialize.cpp
//
// [EOF]
//
