//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_eml_rand_mt19937ar_stateful.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 06-Jul-2020 21:30:41
//

// Include Files
#include "ntf_eml_rand_mt19937ar_stateful.h"
#include "ntf_inataf.h"
#include "ntf_inataf_data.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void ntf_eml_rand_mt19937ar_stateful()
{
  unsigned int r;
  std::memset(&ntf_state[0], 0, 625U * sizeof(unsigned int));
  r = 5489U;
  ntf_state[0] = 5489U;
  for (int mti = 0; mti < 623; mti++) {
    r = ((r ^ r >> 30U) * 1812433253U + mti) + 1U;
    ntf_state[mti + 1] = r;
  }

  ntf_state[624] = 624U;
}

//
// File trailer for ntf_eml_rand_mt19937ar_stateful.cpp
//
// [EOF]
//
