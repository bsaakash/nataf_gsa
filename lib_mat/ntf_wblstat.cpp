//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_wblstat.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 00:47:20
//

// Include Files
#include "ntf_wblstat.h"
#include "ntf_gamma.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : double A
//                double B
//                double *m
//                double *v
// Return Type  : void
//
void ntf_wblstat(double A, double B, double *m, double *v)
{
  double gam1;
  double gam2;
  if ((A > 0.0) && (B > 0.0)) {
    double gamdiff;
    gam1 = 1.0 / B + 1.0;
    ntf_gamma(&gam1);
    gam2 = 2.0 / B + 1.0;
    ntf_gamma(&gam2);
    gamdiff = gam2 - gam1 * gam1;
    *m = A * gam1;
    if (gam2 == rtInf) {
      *v = rtInf;
    } else if (gamdiff > 0.0) {
      *v = A * A * gamdiff;
    } else {
      *v = 0.0;
    }
  } else {
    *m = rtNaN;
    *v = rtNaN;
  }
}

//
// File trailer for ntf_wblstat.cpp
//
// [EOF]
//
