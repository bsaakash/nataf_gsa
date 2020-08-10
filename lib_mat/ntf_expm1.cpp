//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_expm1.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_expm1.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : double *x
// Return Type  : void
//
void ntf_expm1(double *x)
{
  double u;
  u = std::exp(*x);
  if ((u < 1.1102230246251565E-16) || (rtIsInf(u) || rtIsNaN(u))) {
    *x = u - 1.0;
  } else if (u < 0.5) {
    *x = (u - 1.0) * (*x / std::log(u));
  } else {
    if (u != 1.0) {
      double z;
      double absz;
      z = u - 1.0;
      absz = std::abs(u - 1.0);
      if ((absz > 4.503599627370496E+15) || (rtIsInf(u - 1.0) || rtIsNaN(u - 1.0)))
      {
        z = std::log((u - 1.0) + 1.0);
      } else {
        if (!(absz < 2.2204460492503131E-16)) {
          z = std::log((u - 1.0) + 1.0) * ((u - 1.0) / (((u - 1.0) + 1.0) - 1.0));
        }
      }

      *x = (u - 1.0) * (*x / z);
    }
  }
}

//
// File trailer for ntf_expm1.cpp
//
// [EOF]
//
