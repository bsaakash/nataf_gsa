//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_xaxpy.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 06-Jul-2020 21:30:41
//

// Include Files
#include "ntf_xaxpy.h"
#include "ntf_ERANataf.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : int n
//                double a
//                const coder::array<double, 2U> *x
//                int ix0
//                double y[2]
// Return Type  : void
//
void ntf_b_xaxpy(int n, double a, const coder::array<double, 2U> &x, int ix0,
                 double y[2])
{
  if ((n >= 1) && (!(a == 0.0))) {
    y[1] += a * x[ix0 - 1];
  }
}

//
// Arguments    : int n
//                double a
//                const double x[2]
//                coder::array<double, 2U> *y
//                int iy0
// Return Type  : void
//
void ntf_c_xaxpy(int n, double a, const double x[2], coder::array<double, 2U> &y,
                 int iy0)
{
  if ((n >= 1) && (!(a == 0.0))) {
    int iy;
    iy = iy0 - 1;
    y[iy] = y[iy] + a * x[1];
  }
}

//
// Arguments    : int n
//                double a
//                int ix0
//                coder::array<double, 2U> *y
//                int iy0
// Return Type  : void
//
void ntf_xaxpy(int n, double a, int ix0, coder::array<double, 2U> &y, int iy0)
{
  if (!(a == 0.0)) {
    int ix;
    int iy;
    int i;
    ix = ix0 - 1;
    iy = iy0 - 1;
    i = n - 1;
    for (int k = 0; k <= i; k++) {
      y[iy] = y[iy] + a * y[ix];
      ix++;
      iy++;
    }
  }
}

//
// File trailer for ntf_xaxpy.cpp
//
// [EOF]
//
