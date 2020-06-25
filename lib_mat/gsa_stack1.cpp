//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_stack1.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:12:52
//

// Include Files
#include "gsa_stack1.h"
#include "gsa_runGSA.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const gsa_struct_T eg
//                int b_n
// Return Type  : void
//
void gsa_coder_internal_stack::gsa_init(const gsa_struct_T eg, int b_n)
{
  this->n = 0;
  this->d.size[0] = b_n;
  for (int i = 0; i < b_n; i++) {
    this->d.data[i] = eg;
  }
}

//
// File trailer for gsa_stack1.cpp
//
// [EOF]
//
