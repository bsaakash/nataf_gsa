//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_sqrt.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:09:55
//

// Include Files
#include "ntf_sqrt.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double x_data[]
//                const int x_size[2]
// Return Type  : void
//
void ntf_sqrt(double x_data[], const int x_size[2])
{
  int nx;
  nx = x_size[1];
  for (int k = 0; k < nx; k++) {
    x_data[k] = std::sqrt(x_data[k]);
  }
}

//
// File trailer for ntf_sqrt.cpp
//
// [EOF]
//
