//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_heapsort.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:12:52
//

// Include Files
#include "gsa_heapsort.h"
#include "gsa_runGSA.h"
#include "gsa_unique.h"
#include "rt_nonfinite.h"

// Function Declarations
static void gsa_heapify(coder::array<int, 1U> &x, int idx, int xstart, int xend,
  const gsa_coder_internal_anonymous_fu *cmp);

// Function Definitions

//
// Arguments    : coder::array<int, 1U> &x
//                int idx
//                int xstart
//                int xend
//                const gsa_coder_internal_anonymous_fu *cmp
// Return Type  : void
//
static void gsa_heapify(coder::array<int, 1U> &x, int idx, int xstart, int xend,
  const gsa_coder_internal_anonymous_fu *cmp)
{
  boolean_T changed;
  int extremumIdx;
  int leftIdx;
  boolean_T exitg1;
  int extremum;
  int i;
  int i1;
  boolean_T varargout_1;
  changed = true;
  extremumIdx = (idx + xstart) - 2;
  leftIdx = ((idx << 1) + xstart) - 2;
  exitg1 = false;
  while ((!exitg1) && (leftIdx + 1 < xend)) {
    int cmpIdx;
    int xcmp;
    changed = false;
    extremum = x[extremumIdx];
    cmpIdx = leftIdx;
    xcmp = x[leftIdx];
    i = x[leftIdx + 1] - 1;
    i1 = cmp->tunableEnvironment[0].f1[x[leftIdx] - 1];
    varargout_1 = ((i1 < cmp->tunableEnvironment[0].f1[i]) || ((i1 ==
      cmp->tunableEnvironment[0].f1[i]) && (cmp->tunableEnvironment[1]
      .f1[x[leftIdx] - 1] < cmp->tunableEnvironment[1].f1[i])));
    if (varargout_1) {
      cmpIdx = leftIdx + 1;
      xcmp = x[leftIdx + 1];
    }

    i = cmp->tunableEnvironment[0].f1[x[extremumIdx] - 1];
    i1 = cmp->tunableEnvironment[0].f1[xcmp - 1];
    varargout_1 = ((i < i1) || ((i == i1) && (cmp->tunableEnvironment[1]
      .f1[x[extremumIdx] - 1] < cmp->tunableEnvironment[1].f1[xcmp - 1])));
    if (varargout_1) {
      x[extremumIdx] = xcmp;
      x[cmpIdx] = extremum;
      extremumIdx = cmpIdx;
      leftIdx = ((((cmpIdx - xstart) + 2) << 1) + xstart) - 2;
      changed = true;
    } else {
      exitg1 = true;
    }
  }

  if (changed && (leftIdx + 1 <= xend)) {
    extremum = x[extremumIdx];
    i = cmp->tunableEnvironment[0].f1[x[extremumIdx] - 1];
    i1 = cmp->tunableEnvironment[0].f1[x[leftIdx] - 1];
    varargout_1 = ((i < i1) || ((i == i1) && (cmp->tunableEnvironment[1]
      .f1[x[extremumIdx] - 1] < cmp->tunableEnvironment[1].f1[x[leftIdx] - 1])));
    if (varargout_1) {
      x[extremumIdx] = x[leftIdx];
      x[leftIdx] = extremum;
    }
  }
}

//
// Arguments    : coder::array<int, 1U> *x
//                int xstart
//                int xend
//                const gsa_coder_internal_anonymous_fu *cmp
// Return Type  : void
//
void gsa_heapsort(coder::array<int, 1U> &x, int xstart, int xend, const
                  gsa_coder_internal_anonymous_fu *cmp)
{
  int n;
  int t;
  n = (xend - xstart) - 1;
  for (t = n + 2; t >= 1; t--) {
    gsa_heapify(x, t, xstart, xend, cmp);
  }

  for (int k = 0; k <= n; k++) {
    t = x[xend - 1];
    x[xend - 1] = x[xstart - 1];
    x[xstart - 1] = t;
    xend--;
    gsa_heapify(x, 1, xstart, xend, cmp);
  }
}

//
// File trailer for gsa_heapsort.cpp
//
// [EOF]
//
