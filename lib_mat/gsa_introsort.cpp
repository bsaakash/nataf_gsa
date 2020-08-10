//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_introsort.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 21:17:14
//

// Include Files
#include "gsa_introsort.h"
#include "gsa_heapsort.h"
#include "gsa_insertionsort.h"
#include "gsa_runGSA.h"
#include "gsa_stack1.h"
#include "gsa_unique.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : coder::array<int, 1U> *x
//                int xend
//                const gsa_coder_internal_anonymous_fu *cmp
// Return Type  : void
//
void gsa_introsort(coder::array<int, 1U> &x, int xend, const
                   gsa_coder_internal_anonymous_fu *cmp)
{
  gsa_struct_T frame;
  gsa_coder_internal_stack st;
  if (1 < xend) {
    if (xend <= 32) {
      gsa_insertionsort(x, 1, xend, cmp);
    } else {
      int pmax;
      int pmin;
      boolean_T exitg1;
      int MAXDEPTH;
      int pow2p;
      pmax = 31;
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmax - pmin > 1)) {
        MAXDEPTH = (pmin + pmax) >> 1;
        pow2p = 1 << MAXDEPTH;
        if (pow2p == xend) {
          pmax = MAXDEPTH;
          exitg1 = true;
        } else if (pow2p > xend) {
          pmax = MAXDEPTH;
        } else {
          pmin = MAXDEPTH;
        }
      }

      MAXDEPTH = (pmax - 1) << 1;
      frame.xstart = 1;
      frame.xend = xend;
      frame.depth = 0;
      st.gsa_init(frame, (MAXDEPTH << 1));
      st.d.data[st.n] = frame;
      st.n++;
      while (st.n > 0) {
        int i;
        pow2p = st.n - 1;
        frame = st.d.data[pow2p];
        st.n = pow2p;
        i = st.d.data[pow2p].xend - st.d.data[pow2p].xstart;
        if (i + 1 <= 32) {
          gsa_insertionsort(x, st.d.data[pow2p].xstart, st.d.data[pow2p].xend,
                            cmp);
        } else if (st.d.data[pow2p].depth == MAXDEPTH) {
          gsa_heapsort(x, st.d.data[pow2p].xstart, st.d.data[pow2p].xend, cmp);
        } else {
          int b_i;
          boolean_T varargout_1;
          int pivot;
          pmax = (st.d.data[pow2p].xstart + i / 2) - 1;
          b_i = st.d.data[pow2p].xstart - 1;
          i = x[b_i] - 1;
          pmin = cmp->tunableEnvironment[0].f1[x[pmax] - 1];
          varargout_1 = ((pmin < cmp->tunableEnvironment[0].f1[i]) || ((pmin ==
            cmp->tunableEnvironment[0].f1[i]) && (cmp->tunableEnvironment[1]
            .f1[x[pmax] - 1] < cmp->tunableEnvironment[1].f1[i])));
          if (varargout_1) {
            pmin = x[b_i];
            x[b_i] = x[pmax];
            x[pmax] = pmin;
          }

          i = st.d.data[pow2p].xend - 1;
          varargout_1 = ((cmp->tunableEnvironment[0].f1[x[i] - 1] <
                          cmp->tunableEnvironment[0].f1[x[b_i] - 1]) ||
                         ((cmp->tunableEnvironment[0].f1[x[i] - 1] ==
                           cmp->tunableEnvironment[0].f1[x[b_i] - 1]) &&
                          (cmp->tunableEnvironment[1].f1[x[i] - 1] <
                           cmp->tunableEnvironment[1].f1[x[b_i] - 1])));
          if (varargout_1) {
            pmin = x[b_i];
            x[b_i] = x[i];
            x[i] = pmin;
          }

          varargout_1 = ((cmp->tunableEnvironment[0].f1[x[i] - 1] <
                          cmp->tunableEnvironment[0].f1[x[pmax] - 1]) ||
                         ((cmp->tunableEnvironment[0].f1[x[i] - 1] ==
                           cmp->tunableEnvironment[0].f1[x[pmax] - 1]) &&
                          (cmp->tunableEnvironment[1].f1[x[i] - 1] <
                           cmp->tunableEnvironment[1].f1[x[pmax] - 1])));
          if (varargout_1) {
            pmin = x[pmax];
            x[pmax] = x[i];
            x[i] = pmin;
          }

          pivot = x[pmax] - 1;
          i = st.d.data[pow2p].xend - 2;
          x[pmax] = x[i];
          x[i] = pivot + 1;
          pmax = i;
          int exitg2;
          do {
            int exitg3;
            exitg2 = 0;
            b_i++;
            do {
              exitg3 = 0;
              pmin = cmp->tunableEnvironment[0].f1[x[b_i] - 1];
              varargout_1 = ((pmin < cmp->tunableEnvironment[0].f1[pivot]) ||
                             ((pmin == cmp->tunableEnvironment[0].f1[pivot]) &&
                              (cmp->tunableEnvironment[1].f1[x[b_i] - 1] <
                               cmp->tunableEnvironment[1].f1[pivot])));
              if (varargout_1) {
                b_i++;
              } else {
                exitg3 = 1;
              }
            } while (exitg3 == 0);

            pmax--;
            do {
              exitg3 = 0;
              pmin = cmp->tunableEnvironment[0].f1[x[pmax] - 1];
              varargout_1 = ((cmp->tunableEnvironment[0].f1[pivot] < pmin) ||
                             ((cmp->tunableEnvironment[0].f1[pivot] == pmin) &&
                              (cmp->tunableEnvironment[1].f1[pivot] <
                               cmp->tunableEnvironment[1].f1[x[pmax] - 1])));
              if (varargout_1) {
                pmax--;
              } else {
                exitg3 = 1;
              }
            } while (exitg3 == 0);

            if (b_i + 1 >= pmax + 1) {
              exitg2 = 1;
            } else {
              pmin = x[b_i];
              x[b_i] = x[pmax];
              x[pmax] = pmin;
            }
          } while (exitg2 == 0);

          x[i] = x[b_i];
          x[b_i] = pivot + 1;
          if (b_i + 2 < st.d.data[pow2p].xend) {
            st.d.data[pow2p].xstart = b_i + 2;
            st.d.data[pow2p].xend = frame.xend;
            st.d.data[pow2p].depth = frame.depth + 1;
            st.n = pow2p + 1;
          }

          if (frame.xstart < b_i + 1) {
            st.d.data[st.n].xstart = frame.xstart;
            st.d.data[st.n].xend = b_i + 1;
            st.d.data[st.n].depth = frame.depth + 1;
            st.n++;
          }
        }
      }
    }
  }
}

//
// File trailer for gsa_introsort.cpp
//
// [EOF]
//
