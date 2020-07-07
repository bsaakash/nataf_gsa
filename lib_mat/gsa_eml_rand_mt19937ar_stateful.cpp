//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_eml_rand_mt19937ar_stateful.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 06-Jul-2020 21:48:16
//

// Include Files
#include "gsa_eml_rand_mt19937ar_stateful.h"
#include "gsa_runGSA.h"
#include "gsa_runGSA_data.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void gsa_eml_rand_mt19937ar_stateful()
{
  unsigned int r;
  std::memset(&state[0], 0, 625U * sizeof(unsigned int));
  r = 5489U;
  state[0] = 5489U;
  for (int mti = 0; mti < 623; mti++) {
    r = ((r ^ r >> 30U) * 1812433253U + mti) + 1U;
    state[mti + 1] = r;
  }

  state[624] = 624U;
}

//
// File trailer for gsa_eml_rand_mt19937ar_stateful.cpp
//
// [EOF]
//
