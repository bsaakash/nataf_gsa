//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_trapz.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_trapz.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const double x[5000]
//                const double y[5000]
// Return Type  : double
//
double ntf_b_trapz(const double x[5000], const double y[5000])
{
  double z;
  double c[5000];
  int ix;
  c[0] = 0.5 * (x[1] - x[0]);
  for (ix = 0; ix < 4998; ix++) {
    c[ix + 1] = 0.5 * (x[ix + 2] - x[ix]);
  }

  c[4999] = 0.5 * (x[4999] - x[4998]);
  z = 0.0;
  ix = 0;
  for (int iac = 0; iac < 5000; iac++) {
    int b_iac;
    b_iac = iac + 1;
    for (int ia = b_iac; ia <= b_iac; ia++) {
      z += y[ia - 1] * c[ix];
    }

    ix++;
  }

  return z;
}

//
// Arguments    : const double x[1000]
//                const double y[1000]
// Return Type  : double
//
double ntf_trapz(const double x[1000], const double y[1000])
{
  double z;
  double c[1000];
  int ix;
  c[0] = 0.5 * (x[1] - x[0]);
  for (ix = 0; ix < 998; ix++) {
    c[ix + 1] = 0.5 * (x[ix + 2] - x[ix]);
  }

  c[999] = 0.5 * (x[999] - x[998]);
  z = 0.0;
  ix = 0;
  for (int iac = 0; iac < 1000; iac++) {
    int b_iac;
    b_iac = iac + 1;
    for (int ia = b_iac; ia <= b_iac; ia++) {
      z += y[ia - 1] * c[ix];
    }

    ix++;
  }

  return z;
}

//
// File trailer for ntf_trapz.cpp
//
// [EOF]
//
