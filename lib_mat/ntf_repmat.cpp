//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_repmat.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:09:55
//

// Include Files
#include "ntf_repmat.h"
#include "ntf_ERANataf.h"
#include "ntf_inataf.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const double a_data[]
//                const int a_size[2]
//                coder::array<double, 2U> *b
// Return Type  : void
//
void ntf_repmat(const double a_data[], const int a_size[2], coder::array<double,
                2U> &b)
{
  int ncols;
  b.set_size(1048576, (static_cast<int>(static_cast<signed char>(a_size[1]))));
  ncols = a_size[1];
  for (int jcol = 0; jcol < ncols; jcol++) {
    int ibmat;
    ibmat = jcol << 20;
    for (int itilerow = 0; itilerow < 1048576; itilerow++) {
      b[ibmat + itilerow] = a_data[jcol];
    }
  }
}

//
// File trailer for ntf_repmat.cpp
//
// [EOF]
//
