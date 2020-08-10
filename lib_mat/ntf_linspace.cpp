//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_linspace.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_linspace.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double d1
//                double d2
//                double y[5000]
// Return Type  : void
//
void ntf_b_linspace(double d1, double d2, double y[5000])
{
  y[4999] = d2;
  y[0] = d1;
  if (d1 == -d2) {
    for (int k = 0; k < 4998; k++) {
      y[k + 1] = d2 * ((2.0 * (static_cast<double>(k) + 2.0) - 5001.0) / 4999.0);
    }
  } else if (((d1 < 0.0) != (d2 < 0.0)) && ((std::abs(d1) >
               8.9884656743115785E+307) || (std::abs(d2) >
               8.9884656743115785E+307))) {
    double delta1;
    double delta2;
    delta1 = d1 / 4999.0;
    delta2 = d2 / 4999.0;
    for (int k = 0; k < 4998; k++) {
      y[k + 1] = (d1 + delta2 * (static_cast<double>(k) + 1.0)) - delta1 * (
        static_cast<double>(k) + 1.0);
    }
  } else {
    double delta1;
    delta1 = (d2 - d1) / 4999.0;
    for (int k = 0; k < 4998; k++) {
      y[k + 1] = d1 + (static_cast<double>(k) + 1.0) * delta1;
    }
  }
}

//
// Arguments    : double d1
//                double d2
//                double y[1000]
// Return Type  : void
//
void ntf_linspace(double d1, double d2, double y[1000])
{
  y[999] = d2;
  y[0] = d1;
  if (d1 == -d2) {
    for (int k = 0; k < 998; k++) {
      y[k + 1] = d2 * ((2.0 * (static_cast<double>(k) + 2.0) - 1001.0) / 999.0);
    }
  } else if (((d1 < 0.0) != (d2 < 0.0)) && ((std::abs(d1) >
               8.9884656743115785E+307) || (std::abs(d2) >
               8.9884656743115785E+307))) {
    double delta1;
    double delta2;
    delta1 = d1 / 999.0;
    delta2 = d2 / 999.0;
    for (int k = 0; k < 998; k++) {
      y[k + 1] = (d1 + delta2 * (static_cast<double>(k) + 1.0)) - delta1 * (
        static_cast<double>(k) + 1.0);
    }
  } else {
    double delta1;
    delta1 = (d2 - d1) / 999.0;
    for (int k = 0; k < 998; k++) {
      y[k + 1] = d1 + (static_cast<double>(k) + 1.0) * delta1;
    }
  }
}

//
// File trailer for ntf_linspace.cpp
//
// [EOF]
//
