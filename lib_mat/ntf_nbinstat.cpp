//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_nbinstat.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_nbinstat.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : double r
//                double p
//                double *m
//                double *v
// Return Type  : void
//
void ntf_nbinstat(double r, double p, double *m, double *v)
{
  if ((0.0 < r) && (!rtIsInf(r)) && (0.0 < p) && (p <= 1.0)) {
    double m_tmp;
    m_tmp = r * (1.0 - p);
    *m = m_tmp / p;
    *v = m_tmp / (p * p);
  } else {
    *m = rtNaN;
    *v = rtNaN;
  }
}

//
// File trailer for ntf_nbinstat.cpp
//
// [EOF]
//
