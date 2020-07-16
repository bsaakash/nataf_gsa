//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_fminsearch.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//

// Include Files
#include "ntf_fminsearch.h"
#include "ntf_ERADist.h"
#include "ntf_betafit.h"
#include "ntf_corrcoef.h"
#include "ntf_gampdf.h"
#include "ntf_gevinv.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "ntf_sortIdx.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>

// Function Declarations
static double ntf_b_getCheckFcn(const ntf_c_coder_internal_anonymous_ *fcn,
  const double x[3]);
static double ntf_getCheckFcn(const ntf_b_coder_internal_anonymous_ *fcn);

// Function Definitions

//
// Arguments    : const ntf_c_coder_internal_anonymous_ *fcn
//                const double x[3]
// Return Type  : double
//
static double ntf_b_getCheckFcn(const ntf_c_coder_internal_anonymous_ *fcn,
  const double x[3])
{
  double initialVal;
  double sigma;
  coder::array<double, 1U> z;
  int nx;
  int i;
  coder::array<double, 1U> u;
  double absz;
  sigma = std::exp(x[1]);
  z.set_size(fcn->tunableEnvironment[0].f1.size(0));
  nx = fcn->tunableEnvironment[0].f1.size(0);
  for (i = 0; i < nx; i++) {
    z[i] = (fcn->tunableEnvironment[0].f1[i] - x[2]) / sigma;
  }

  if (std::abs(x[0]) > 2.2204460492503131E-16) {
    int k;
    int n;
    nx = z.size(0);
    for (i = 0; i < nx; i++) {
      z[i] = x[0] * z[i];
    }

    u.set_size(z.size(0));
    nx = z.size(0);
    for (i = 0; i < nx; i++) {
      u[i] = z[i] + 1.0;
    }

    n = u.size(0);
    if (u.size(0) <= 2) {
      if (u.size(0) == 1) {
        sigma = u[0];
      } else if ((u[0] > u[1]) || (rtIsNaN(u[0]) && (!rtIsNaN(u[1])))) {
        sigma = u[1];
      } else {
        sigma = u[0];
      }
    } else {
      if (!rtIsNaN(u[0])) {
        nx = 1;
      } else {
        boolean_T exitg1;
        nx = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= u.size(0))) {
          if (!rtIsNaN(u[k - 1])) {
            nx = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (nx == 0) {
        sigma = u[0];
      } else {
        sigma = u[nx - 1];
        i = nx + 1;
        for (k = i; k <= n; k++) {
          absz = u[k - 1];
          if (sigma > absz) {
            sigma = absz;
          }
        }
      }
    }

    if (sigma > 0.0) {
      nx = z.size(0);
      for (k = 0; k < nx; k++) {
        sigma = z[k];
        absz = std::abs(z[k]);
        if ((absz > 4.503599627370496E+15) || (rtIsInf(z[k]) || rtIsNaN(z[k])))
        {
          sigma = std::log(z[k] + 1.0);
        } else {
          if (!(absz < 2.2204460492503131E-16)) {
            sigma = std::log(z[k] + 1.0) * (z[k] / ((z[k] + 1.0) - 1.0));
          }
        }

        z[k] = sigma;
      }

      //  log(1 + k.*z)
      sigma = -(1.0 / x[0]);
      u.set_size(z.size(0));
      nx = z.size(0);
      for (i = 0; i < nx; i++) {
        u[i] = sigma * z[i];
      }

      nx = u.size(0);
      for (k = 0; k < nx; k++) {
        u[k] = std::exp(u[k]);
      }

      //  (1 + k.*z).^(-1/k)
      nx = u.size(0);
      if (u.size(0) == 0) {
        sigma = 0.0;
      } else {
        sigma = u[0];
        for (k = 2; k <= nx; k++) {
          sigma += u[k - 1];
        }
      }

      nx = z.size(0);
      if (z.size(0) == 0) {
        absz = 0.0;
      } else {
        absz = z[0];
        for (k = 2; k <= nx; k++) {
          absz += z[k - 1];
        }
      }

      initialVal = (static_cast<double>(fcn->tunableEnvironment[0].f1.size(0)) *
                    x[1] + sigma) + (1.0 / x[0] + 1.0) * absz;
    } else {
      initialVal = rtInf;
    }
  } else {
    int k;
    u.set_size(z.size(0));
    nx = z.size(0);
    for (i = 0; i < nx; i++) {
      u[i] = -z[i];
    }

    nx = u.size(0);
    for (k = 0; k < nx; k++) {
      u[k] = std::exp(u[k]);
    }

    nx = u.size(0);
    for (i = 0; i < nx; i++) {
      u[i] = u[i] + z[i];
    }

    nx = u.size(0);
    if (u.size(0) == 0) {
      sigma = 0.0;
    } else {
      sigma = u[0];
      for (k = 2; k <= nx; k++) {
        sigma += u[k - 1];
      }
    }

    initialVal = static_cast<double>(fcn->tunableEnvironment[0].f1.size(0)) * x
      [1] + sigma;
  }

  return initialVal;
}

//
// Arguments    : const ntf_b_coder_internal_anonymous_ *fcn
// Return Type  : double
//
static double ntf_getCheckFcn(const ntf_b_coder_internal_anonymous_ *fcn)
{
  coder::array<double, 1U> x;
  int i;
  double b_dv[4];
  x.set_size(fcn->tunableEnvironment[1].f1.size(0));
  i = x.size(0);
  for (int j = 0; j < i; j++) {
    if ((0.0 <= fcn->tunableEnvironment[1].f1[j]) && (fcn->tunableEnvironment[1]
         .f1[j] <= 1.0)) {
      if (fcn->tunableEnvironment[1].f1[j] == 0.0) {
        x[j] = rtMinusInf;
      } else if (fcn->tunableEnvironment[1].f1[j] == 1.0) {
        x[j] = rtInf;
      } else {
        x[j] = -std::log(-std::log(fcn->tunableEnvironment[1].f1[j]));
      }
    } else {
      x[j] = rtNaN;
    }
  }

  ntf_corrcoef(fcn->tunableEnvironment[0].f1, x, b_dv);
  return 1.0 - ((b_dv[0] + 0.0 * b_dv[1]) * 0.0 + (b_dv[2] + 0.0 * b_dv[3]));
}

//
// Arguments    : const ntf_c_coder_internal_anonymous_ *funfcn
//                double x[2]
// Return Type  : void
//
void ntf_b_fminsearch(const ntf_c_coder_internal_anonymous_ *funfcn, double x[2])
{
  coder::array<double, 1U> b_x;
  int nx;
  int colIdx;
  double y;
  double fv[3];
  double v[6];
  int idx[3];
  int itercount;
  int fun_evals;
  int lastCol;
  int firstCol;
  boolean_T exitg1;
  double cfv;
  int exponent;
  int b_exponent;
  int c_exponent;
  double fvt[3];
  int idxb[3];
  ntf_gampdf(funfcn->tunableEnvironment[0].f1, x[0], x[1], b_x);
  nx = b_x.size(0);
  for (colIdx = 0; colIdx < nx; colIdx++) {
    b_x[colIdx] = std::log(b_x[colIdx]);
  }

  nx = b_x.size(0);
  if (b_x.size(0) == 0) {
    y = 0.0;
  } else {
    y = b_x[0];
    for (colIdx = 2; colIdx <= nx; colIdx++) {
      y += b_x[colIdx - 1];
    }
  }

  fv[0] = -y;
  for (colIdx = 0; colIdx < 3; colIdx++) {
    nx = colIdx << 1;
    v[nx] = x[0];
    v[nx + 1] = x[1];
  }

  if (x[0] != 0.0) {
    v[2] = 1.05 * x[0];
  } else {
    v[2] = 0.00025;
  }

  ntf_gampdf(funfcn->tunableEnvironment[0].f1, v[2], v[3], b_x);
  nx = b_x.size(0);
  for (colIdx = 0; colIdx < nx; colIdx++) {
    b_x[colIdx] = std::log(b_x[colIdx]);
  }

  nx = b_x.size(0);
  if (b_x.size(0) == 0) {
    y = 0.0;
  } else {
    y = b_x[0];
    for (colIdx = 2; colIdx <= nx; colIdx++) {
      y += b_x[colIdx - 1];
    }
  }

  fv[1] = -y;
  if (x[1] != 0.0) {
    v[5] = 1.05 * x[1];
  } else {
    v[5] = 0.00025;
  }

  ntf_gampdf(funfcn->tunableEnvironment[0].f1, v[4], v[5], b_x);
  nx = b_x.size(0);
  for (colIdx = 0; colIdx < nx; colIdx++) {
    b_x[colIdx] = std::log(b_x[colIdx]);
  }

  nx = b_x.size(0);
  if (b_x.size(0) == 0) {
    y = 0.0;
  } else {
    y = b_x[0];
    for (colIdx = 2; colIdx <= nx; colIdx++) {
      y += b_x[colIdx - 1];
    }
  }

  fv[2] = -y;
  ntf_sortIdx(fv, idx);
  itercount = 1;
  fun_evals = 3;
  lastCol = (idx[2] - 1) << 1;
  firstCol = (idx[0] - 1) << 1;
  exitg1 = false;
  while ((!exitg1) && ((fun_evals < 400) && (itercount < 400))) {
    double maxfv;
    double cfv_tmp_tmp;
    double b_cfv_tmp_tmp;
    double c_cfv_tmp_tmp;
    double maxv;
    boolean_T p;
    maxfv = 0.0;
    cfv_tmp_tmp = fv[idx[0] - 1];
    b_cfv_tmp_tmp = fv[idx[1] - 1];
    cfv = std::abs(cfv_tmp_tmp - b_cfv_tmp_tmp);
    if (cfv > 0.0) {
      maxfv = cfv;
    }

    c_cfv_tmp_tmp = fv[idx[2] - 1];
    cfv = std::abs(cfv_tmp_tmp - c_cfv_tmp_tmp);
    if (cfv > maxfv) {
      maxfv = cfv;
    }

    cfv = std::abs(cfv_tmp_tmp);
    if ((!rtIsInf(cfv)) && (!rtIsNaN(cfv))) {
      if (cfv <= 2.2250738585072014E-308) {
        cfv = 4.94065645841247E-324;
      } else {
        frexp(cfv, &exponent);
        cfv = std::ldexp(1.0, exponent - 53);
      }
    } else {
      cfv = rtNaN;
    }

    cfv *= 10.0;
    if ((!rtIsInf(cfv)) && (!rtIsNaN(cfv))) {
      if (cfv <= 2.2250738585072014E-308) {
        cfv = 4.94065645841247E-324;
      } else {
        frexp(cfv, &b_exponent);
        cfv = std::ldexp(1.0, b_exponent - 53);
      }
    } else {
      cfv = rtNaN;
    }

    cfv *= 10.0;
    if ((0.0001 > cfv) || rtIsNaN(cfv)) {
      cfv = 0.0001;
    }

    if (maxfv > cfv) {
      p = false;
    } else {
      maxv = 0.0;
      nx = (idx[0] - 1) << 1;
      colIdx = (idx[1] - 1) << 1;
      cfv = std::abs(v[nx] - v[colIdx]);
      if (cfv > 0.0) {
        maxv = cfv;
      }

      maxfv = v[nx + 1];
      cfv = std::abs(maxfv - v[colIdx + 1]);
      if (cfv > maxv) {
        maxv = cfv;
      }

      colIdx = (idx[2] - 1) << 1;
      cfv = std::abs(v[nx] - v[colIdx]);
      if (cfv > maxv) {
        maxv = cfv;
      }

      cfv = std::abs(maxfv - v[colIdx + 1]);
      if (cfv > maxv) {
        maxv = cfv;
      }

      cfv = v[nx];
      if (maxfv > v[nx]) {
        cfv = maxfv;
      }

      cfv = std::abs(cfv);
      if ((!rtIsInf(cfv)) && (!rtIsNaN(cfv))) {
        if (cfv <= 2.2250738585072014E-308) {
          cfv = 4.94065645841247E-324;
        } else {
          frexp(cfv, &c_exponent);
          cfv = std::ldexp(1.0, c_exponent - 53);
        }
      } else {
        cfv = rtNaN;
      }

      cfv *= 10.0;
      if ((0.0001 > cfv) || rtIsNaN(cfv)) {
        cfv = 0.0001;
      }

      p = (maxv <= cfv);
    }

    if (!p) {
      double xr_idx_0;
      double xr_idx_1_tmp;
      double xr_idx_1;
      boolean_T guard1 = false;
      boolean_T guard2 = false;
      colIdx = (idx[1] - 1) << 1;
      maxfv = (v[firstCol] + v[colIdx]) / 2.0;
      cfv = maxfv;
      xr_idx_0 = 2.0 * maxfv - v[lastCol];
      maxfv = (v[firstCol + 1] + v[colIdx + 1]) / 2.0;
      xr_idx_1_tmp = v[lastCol + 1];
      xr_idx_1 = 2.0 * maxfv - xr_idx_1_tmp;
      ntf_gampdf(funfcn->tunableEnvironment[0].f1, xr_idx_0, xr_idx_1, b_x);
      nx = b_x.size(0);
      for (colIdx = 0; colIdx < nx; colIdx++) {
        b_x[colIdx] = std::log(b_x[colIdx]);
      }

      nx = b_x.size(0);
      if (b_x.size(0) == 0) {
        y = 0.0;
      } else {
        y = b_x[0];
        for (colIdx = 2; colIdx <= nx; colIdx++) {
          y += b_x[colIdx - 1];
        }
      }

      fun_evals++;
      guard1 = false;
      guard2 = false;
      if (-y < cfv_tmp_tmp) {
        maxv = 3.0 * cfv - 2.0 * v[lastCol];
        maxfv = 3.0 * maxfv - 2.0 * xr_idx_1_tmp;
        ntf_gampdf(funfcn->tunableEnvironment[0].f1, maxv, maxfv, b_x);
        nx = b_x.size(0);
        for (colIdx = 0; colIdx < nx; colIdx++) {
          b_x[colIdx] = std::log(b_x[colIdx]);
        }

        nx = b_x.size(0);
        if (b_x.size(0) == 0) {
          cfv = 0.0;
        } else {
          cfv = b_x[0];
          for (colIdx = 2; colIdx <= nx; colIdx++) {
            cfv += b_x[colIdx - 1];
          }
        }

        fun_evals++;
        if (-cfv < -y) {
          v[lastCol] = maxv;
          v[lastCol + 1] = maxfv;
          fv[idx[2] - 1] = -cfv;
        } else {
          v[lastCol] = xr_idx_0;
          v[lastCol + 1] = xr_idx_1;
          fv[idx[2] - 1] = -y;
        }

        guard1 = true;
      } else if (-y < b_cfv_tmp_tmp) {
        v[lastCol] = xr_idx_0;
        v[lastCol + 1] = xr_idx_1;
        fv[idx[2] - 1] = -y;
        guard1 = true;
      } else if (-y < c_cfv_tmp_tmp) {
        x[0] = 1.5 * cfv - 0.5 * v[lastCol];
        x[1] = 1.5 * maxfv - 0.5 * v[lastCol + 1];
        ntf_gampdf(funfcn->tunableEnvironment[0].f1, x[0], x[1], b_x);
        nx = b_x.size(0);
        for (colIdx = 0; colIdx < nx; colIdx++) {
          b_x[colIdx] = std::log(b_x[colIdx]);
        }

        nx = b_x.size(0);
        if (b_x.size(0) == 0) {
          cfv = 0.0;
        } else {
          cfv = b_x[0];
          for (colIdx = 2; colIdx <= nx; colIdx++) {
            cfv += b_x[colIdx - 1];
          }
        }

        fun_evals++;
        if (-cfv <= -y) {
          v[lastCol] = x[0];
          v[lastCol + 1] = x[1];
          fv[idx[2] - 1] = -cfv;
          guard1 = true;
        } else {
          guard2 = true;
        }
      } else {
        x[0] = 0.5 * cfv + 0.5 * v[lastCol];
        x[1] = 0.5 * maxfv + 0.5 * xr_idx_1_tmp;
        ntf_gampdf(funfcn->tunableEnvironment[0].f1, x[0], x[1], b_x);
        nx = b_x.size(0);
        for (colIdx = 0; colIdx < nx; colIdx++) {
          b_x[colIdx] = std::log(b_x[colIdx]);
        }

        nx = b_x.size(0);
        if (b_x.size(0) == 0) {
          y = 0.0;
        } else {
          y = b_x[0];
          for (colIdx = 2; colIdx <= nx; colIdx++) {
            y += b_x[colIdx - 1];
          }
        }

        fun_evals++;
        if (-y < c_cfv_tmp_tmp) {
          v[lastCol] = x[0];
          v[lastCol + 1] = x[1];
          fv[idx[2] - 1] = -y;
          guard1 = true;
        } else {
          guard2 = true;
        }
      }

      if (guard2) {
        colIdx = ((idx[1] - 1) << 1) - 1;
        v[colIdx + 1] = v[firstCol] + 0.5 * (v[colIdx + 1] - v[firstCol]);
        x[0] = v[colIdx + 1];
        v[colIdx + 2] = v[firstCol + 1] + 0.5 * (v[colIdx + 2] - v[firstCol + 1]);
        x[1] = v[colIdx + 2];
        ntf_gampdf(funfcn->tunableEnvironment[0].f1, x[0], x[1], b_x);
        nx = b_x.size(0);
        for (colIdx = 0; colIdx < nx; colIdx++) {
          b_x[colIdx] = std::log(b_x[colIdx]);
        }

        nx = b_x.size(0);
        if (b_x.size(0) == 0) {
          y = 0.0;
        } else {
          y = b_x[0];
          for (colIdx = 2; colIdx <= nx; colIdx++) {
            y += b_x[colIdx - 1];
          }
        }

        fv[idx[1] - 1] = -y;
        colIdx = ((idx[2] - 1) << 1) - 1;
        v[colIdx + 1] = v[firstCol] + 0.5 * (v[colIdx + 1] - v[firstCol]);
        x[0] = v[colIdx + 1];
        v[colIdx + 2] = v[firstCol + 1] + 0.5 * (v[colIdx + 2] - v[firstCol + 1]);
        x[1] = v[colIdx + 2];
        ntf_gampdf(funfcn->tunableEnvironment[0].f1, x[0], x[1], b_x);
        nx = b_x.size(0);
        for (colIdx = 0; colIdx < nx; colIdx++) {
          b_x[colIdx] = std::log(b_x[colIdx]);
        }

        nx = b_x.size(0);
        if (b_x.size(0) == 0) {
          y = 0.0;
        } else {
          y = b_x[0];
          for (colIdx = 2; colIdx <= nx; colIdx++) {
            y += b_x[colIdx - 1];
          }
        }

        fv[idx[2] - 1] = -y;
        fun_evals += 2;
        fvt[0] = fv[idx[0] - 1];
        idxb[0] = idx[0];
        fvt[1] = fv[idx[1] - 1];
        idxb[1] = idx[1];
        fvt[2] = fv[idx[2] - 1];
        idxb[2] = idx[2];
        ntf_sortIdx(fvt, idx);
        idx[0] = idxb[idx[0] - 1];
        idx[1] = idxb[idx[1] - 1];
        idx[2] = idxb[idx[2] - 1];
      }

      if (guard1) {
        if (fv[idx[2] - 1] < fv[idx[1] - 1]) {
          nx = idx[2];
          idx[2] = idx[1];
          idx[1] = nx;
        }

        if (fv[idx[1] - 1] < fv[idx[0] - 1]) {
          nx = idx[1];
          idx[1] = idx[0];
          idx[0] = nx;
        }
      }

      itercount++;
      lastCol = (idx[2] - 1) << 1;
      firstCol = (idx[0] - 1) << 1;
    } else {
      exitg1 = true;
    }
  }

  colIdx = (idx[0] - 1) << 1;
  x[0] = v[colIdx];
  x[1] = v[colIdx + 1];
}

//
// Arguments    : double x[2]
// Return Type  : void
//
void ntf_c_fminsearch(double x[2])
{
  double xe[2];
  double fv[3];
  int lastCol;
  int firstCol;
  double v[6];
  double xr[2];
  int idx[3];
  int itercount;
  int fun_evals;
  boolean_T exitg1;
  int colIdx;
  double cfv;
  int exponent;
  int b_exponent;
  double b_xe[2];
  int c_exponent;
  double fvt[3];
  int idxb[3];
  xe[0] = x[0];
  xe[1] = x[1];
  fv[0] = ntf_negloglike(xe);
  for (lastCol = 0; lastCol < 3; lastCol++) {
    firstCol = lastCol << 1;
    v[firstCol] = x[0];
    v[firstCol + 1] = x[1];
  }

  if (x[0] != 0.0) {
    v[2] = 1.05 * x[0];
  } else {
    v[2] = 0.00025;
  }

  xr[0] = v[2];
  xr[1] = v[3];
  fv[1] = ntf_negloglike(xr);
  if (x[1] != 0.0) {
    v[5] = 1.05 * x[1];
  } else {
    v[5] = 0.00025;
  }

  xr[0] = v[4];
  xr[1] = v[5];
  fv[2] = ntf_negloglike(xr);
  ntf_sortIdx(fv, idx);
  itercount = 1;
  fun_evals = 3;
  lastCol = (idx[2] - 1) << 1;
  firstCol = (idx[0] - 1) << 1;
  exitg1 = false;
  while ((!exitg1) && ((fun_evals < 400) && (itercount < 400))) {
    double maxfv;
    double cfv_tmp_tmp;
    double b_cfv_tmp_tmp;
    double c_cfv_tmp_tmp;
    double maxv;
    boolean_T p;
    maxfv = 0.0;
    cfv_tmp_tmp = fv[idx[0] - 1];
    b_cfv_tmp_tmp = fv[idx[1] - 1];
    cfv = std::abs(cfv_tmp_tmp - b_cfv_tmp_tmp);
    if (cfv > 0.0) {
      maxfv = cfv;
    }

    c_cfv_tmp_tmp = fv[idx[2] - 1];
    cfv = std::abs(cfv_tmp_tmp - c_cfv_tmp_tmp);
    if (cfv > maxfv) {
      maxfv = cfv;
    }

    cfv = std::abs(cfv_tmp_tmp);
    if ((!rtIsInf(cfv)) && (!rtIsNaN(cfv))) {
      if (cfv <= 2.2250738585072014E-308) {
        cfv = 4.94065645841247E-324;
      } else {
        frexp(cfv, &exponent);
        cfv = std::ldexp(1.0, exponent - 53);
      }
    } else {
      cfv = rtNaN;
    }

    cfv *= 10.0;
    if ((!rtIsInf(cfv)) && (!rtIsNaN(cfv))) {
      if (cfv <= 2.2250738585072014E-308) {
        cfv = 4.94065645841247E-324;
      } else {
        frexp(cfv, &b_exponent);
        cfv = std::ldexp(1.0, b_exponent - 53);
      }
    } else {
      cfv = rtNaN;
    }

    cfv *= 10.0;
    if ((1.0E-6 > cfv) || rtIsNaN(cfv)) {
      cfv = 1.0E-6;
    }

    if (maxfv > cfv) {
      p = false;
    } else {
      int b_firstCol;
      maxv = 0.0;
      b_firstCol = (idx[0] - 1) << 1;
      colIdx = (idx[1] - 1) << 1;
      cfv = std::abs(v[b_firstCol] - v[colIdx]);
      if (cfv > 0.0) {
        maxv = cfv;
      }

      maxfv = v[b_firstCol + 1];
      cfv = std::abs(maxfv - v[colIdx + 1]);
      if (cfv > maxv) {
        maxv = cfv;
      }

      colIdx = (idx[2] - 1) << 1;
      cfv = std::abs(v[b_firstCol] - v[colIdx]);
      if (cfv > maxv) {
        maxv = cfv;
      }

      cfv = std::abs(maxfv - v[colIdx + 1]);
      if (cfv > maxv) {
        maxv = cfv;
      }

      cfv = v[b_firstCol];
      if (maxfv > v[b_firstCol]) {
        cfv = maxfv;
      }

      cfv = std::abs(cfv);
      if ((!rtIsInf(cfv)) && (!rtIsNaN(cfv))) {
        if (cfv <= 2.2250738585072014E-308) {
          cfv = 4.94065645841247E-324;
        } else {
          frexp(cfv, &c_exponent);
          cfv = std::ldexp(1.0, c_exponent - 53);
        }
      } else {
        cfv = rtNaN;
      }

      cfv *= 10.0;
      if ((1.0E-6 > cfv) || rtIsNaN(cfv)) {
        cfv = 1.0E-6;
      }

      p = (maxv <= cfv);
    }

    if (!p) {
      double fxr;
      boolean_T guard1 = false;
      boolean_T guard2 = false;
      colIdx = (idx[1] - 1) << 1;
      cfv = (v[firstCol] + v[colIdx]) / 2.0;
      maxfv = cfv;
      xr[0] = 2.0 * cfv - v[lastCol];
      cfv = (v[firstCol + 1] + v[colIdx + 1]) / 2.0;
      maxv = v[lastCol + 1];
      xr[1] = 2.0 * cfv - maxv;
      xe[0] = xr[0];
      xe[1] = xr[1];
      fxr = ntf_negloglike(xe);
      fun_evals++;
      guard1 = false;
      guard2 = false;
      if (fxr < cfv_tmp_tmp) {
        xe[0] = 3.0 * maxfv - 2.0 * v[lastCol];
        xe[1] = 3.0 * cfv - 2.0 * maxv;
        b_xe[0] = xe[0];
        b_xe[1] = xe[1];
        cfv = ntf_negloglike(b_xe);
        fun_evals++;
        if (cfv < fxr) {
          v[lastCol] = xe[0];
          v[lastCol + 1] = xe[1];
          fv[idx[2] - 1] = cfv;
        } else {
          v[lastCol] = xr[0];
          v[lastCol + 1] = xr[1];
          fv[idx[2] - 1] = fxr;
        }

        guard1 = true;
      } else if (fxr < b_cfv_tmp_tmp) {
        v[lastCol] = xr[0];
        v[lastCol + 1] = xr[1];
        fv[idx[2] - 1] = fxr;
        guard1 = true;
      } else if (fxr < c_cfv_tmp_tmp) {
        x[0] = 1.5 * maxfv - 0.5 * v[lastCol];
        x[1] = 1.5 * cfv - 0.5 * v[lastCol + 1];
        xe[0] = x[0];
        xe[1] = x[1];
        cfv = ntf_negloglike(xe);
        fun_evals++;
        if (cfv <= fxr) {
          v[lastCol] = x[0];
          v[lastCol + 1] = x[1];
          fv[idx[2] - 1] = cfv;
          guard1 = true;
        } else {
          guard2 = true;
        }
      } else {
        x[0] = 0.5 * maxfv + 0.5 * v[lastCol];
        x[1] = 0.5 * cfv + 0.5 * maxv;
        xe[0] = x[0];
        xe[1] = x[1];
        cfv = ntf_negloglike(xe);
        fun_evals++;
        if (cfv < c_cfv_tmp_tmp) {
          v[lastCol] = x[0];
          v[lastCol + 1] = x[1];
          fv[idx[2] - 1] = cfv;
          guard1 = true;
        } else {
          guard2 = true;
        }
      }

      if (guard2) {
        colIdx = ((idx[1] - 1) << 1) - 1;
        v[colIdx + 1] = v[firstCol] + 0.5 * (v[colIdx + 1] - v[firstCol]);
        x[0] = v[colIdx + 1];
        v[colIdx + 2] = v[firstCol + 1] + 0.5 * (v[colIdx + 2] - v[firstCol + 1]);
        x[1] = v[colIdx + 2];
        xe[0] = x[0];
        xe[1] = x[1];
        fv[idx[1] - 1] = ntf_negloglike(xe);
        colIdx = ((idx[2] - 1) << 1) - 1;
        v[colIdx + 1] = v[firstCol] + 0.5 * (v[colIdx + 1] - v[firstCol]);
        x[0] = v[colIdx + 1];
        v[colIdx + 2] = v[firstCol + 1] + 0.5 * (v[colIdx + 2] - v[firstCol + 1]);
        x[1] = v[colIdx + 2];
        xe[0] = x[0];
        xe[1] = x[1];
        fv[idx[2] - 1] = ntf_negloglike(xe);
        fun_evals += 2;
        fvt[0] = fv[idx[0] - 1];
        idxb[0] = idx[0];
        fvt[1] = fv[idx[1] - 1];
        idxb[1] = idx[1];
        fvt[2] = fv[idx[2] - 1];
        idxb[2] = idx[2];
        ntf_sortIdx(fvt, idx);
        idx[0] = idxb[idx[0] - 1];
        idx[1] = idxb[idx[1] - 1];
        idx[2] = idxb[idx[2] - 1];
      }

      if (guard1) {
        if (fv[idx[2] - 1] < fv[idx[1] - 1]) {
          firstCol = idx[2];
          idx[2] = idx[1];
          idx[1] = firstCol;
        }

        if (fv[idx[1] - 1] < fv[idx[0] - 1]) {
          firstCol = idx[1];
          idx[1] = idx[0];
          idx[0] = firstCol;
        }
      }

      itercount++;
      lastCol = (idx[2] - 1) << 1;
      firstCol = (idx[0] - 1) << 1;
    } else {
      exitg1 = true;
    }
  }

  colIdx = (idx[0] - 1) << 1;
  x[0] = v[colIdx];
  x[1] = v[colIdx + 1];
}

//
// Arguments    : const ntf_c_coder_internal_anonymous_ *funfcn
//                double x[3]
// Return Type  : void
//
void ntf_d_fminsearch(const ntf_c_coder_internal_anonymous_ *funfcn, double x[3])
{
  double fv[4];
  int k;
  double v[12];
  int idx[4];
  int colIdx;
  int itercount;
  int fun_evals;
  int lastCol;
  int firstCol;
  double xr[3];
  boolean_T exitg1;
  double maxfv;
  double cfv;
  int exponent;
  int b_exponent;
  double maxv;
  int c_exponent;
  double xe[3];
  double fvt[4];
  int idxb[4];
  fv[0] = ntf_b_getCheckFcn(funfcn, x);
  for (k = 0; k < 4; k++) {
    v[3 * k] = x[0];
    v[3 * k + 1] = x[1];
    v[3 * k + 2] = x[2];
  }

  for (k = 0; k < 3; k++) {
    colIdx = 3 * (k + 1);
    if (x[k] != 0.0) {
      v[k + colIdx] = 1.05 * x[k];
    } else {
      v[k + colIdx] = 0.00025;
    }

    xr[0] = v[colIdx];
    xr[1] = v[colIdx + 1];
    xr[2] = v[colIdx + 2];
    fv[k + 1] = ntf_ERADist::ntf___anon_fcn((funfcn->tunableEnvironment[0].f1),
      (xr));
  }

  ntf_b_sortIdx(fv, idx);
  itercount = 1;
  fun_evals = 4;
  lastCol = 3 * (idx[3] - 1);
  firstCol = 3 * (idx[0] - 1);
  exitg1 = false;
  while ((!exitg1) && ((fun_evals < 600) && (itercount < 600))) {
    double cfv_tmp_tmp;
    double b_cfv_tmp_tmp;
    double c_cfv_tmp_tmp;
    boolean_T p;
    int b_firstCol;
    maxfv = 0.0;
    cfv_tmp_tmp = fv[idx[0] - 1];
    cfv = std::abs(cfv_tmp_tmp - fv[idx[1] - 1]);
    if (cfv > 0.0) {
      maxfv = cfv;
    }

    b_cfv_tmp_tmp = fv[idx[2] - 1];
    cfv = std::abs(cfv_tmp_tmp - b_cfv_tmp_tmp);
    if (cfv > maxfv) {
      maxfv = cfv;
    }

    c_cfv_tmp_tmp = fv[idx[3] - 1];
    cfv = std::abs(cfv_tmp_tmp - c_cfv_tmp_tmp);
    if (cfv > maxfv) {
      maxfv = cfv;
    }

    cfv = std::abs(cfv_tmp_tmp);
    if ((!rtIsInf(cfv)) && (!rtIsNaN(cfv))) {
      if (cfv <= 2.2250738585072014E-308) {
        cfv = 4.94065645841247E-324;
      } else {
        frexp(cfv, &exponent);
        cfv = std::ldexp(1.0, exponent - 53);
      }
    } else {
      cfv = rtNaN;
    }

    cfv *= 10.0;
    if ((!rtIsInf(cfv)) && (!rtIsNaN(cfv))) {
      if (cfv <= 2.2250738585072014E-308) {
        cfv = 4.94065645841247E-324;
      } else {
        frexp(cfv, &b_exponent);
        cfv = std::ldexp(1.0, b_exponent - 53);
      }
    } else {
      cfv = rtNaN;
    }

    cfv *= 10.0;
    if ((0.0001 > cfv) || rtIsNaN(cfv)) {
      cfv = 0.0001;
    }

    if (maxfv > cfv) {
      p = false;
    } else {
      maxv = 0.0;
      b_firstCol = (idx[0] - 1) * 3;
      for (k = 0; k < 3; k++) {
        colIdx = (idx[k + 1] - 1) * 3;
        cfv = std::abs(v[b_firstCol] - v[colIdx]);
        if (cfv > maxv) {
          maxv = cfv;
        }

        cfv = std::abs(v[b_firstCol + 1] - v[colIdx + 1]);
        if (cfv > maxv) {
          maxv = cfv;
        }

        cfv = std::abs(v[b_firstCol + 2] - v[colIdx + 2]);
        if (cfv > maxv) {
          maxv = cfv;
        }
      }

      maxfv = v[b_firstCol];
      cfv = v[b_firstCol + 1];
      if (cfv > v[b_firstCol]) {
        maxfv = cfv;
      }

      cfv = v[b_firstCol + 2];
      if (cfv > maxfv) {
        maxfv = cfv;
      }

      cfv = std::abs(maxfv);
      if ((!rtIsInf(cfv)) && (!rtIsNaN(cfv))) {
        if (cfv <= 2.2250738585072014E-308) {
          cfv = 4.94065645841247E-324;
        } else {
          frexp(cfv, &c_exponent);
          cfv = std::ldexp(1.0, c_exponent - 53);
        }
      } else {
        cfv = rtNaN;
      }

      cfv *= 10.0;
      if ((0.0001 > cfv) || rtIsNaN(cfv)) {
        cfv = 0.0001;
      }

      p = (maxv <= cfv);
    }

    if (!p) {
      double d;
      double xr_tmp;
      double fxr;
      boolean_T guard1 = false;
      boolean_T guard2 = false;
      maxfv = v[firstCol];
      maxv = v[firstCol + 1];
      cfv = v[firstCol + 2];
      for (k = 0; k < 2; k++) {
        colIdx = 3 * (idx[k + 1] - 1);
        maxfv += v[colIdx];
        maxv += v[colIdx + 1];
        cfv += v[colIdx + 2];
      }

      d = maxfv / 3.0;
      maxfv = d;
      xr[0] = 2.0 * d - v[lastCol];
      d = maxv / 3.0;
      maxv = d;
      xr_tmp = v[lastCol + 1];
      xr[1] = 2.0 * d - xr_tmp;
      d = cfv / 3.0;
      cfv = v[lastCol + 2];
      xr[2] = 2.0 * d - cfv;
      fxr = ntf_ERADist::ntf___anon_fcn((funfcn->tunableEnvironment[0].f1), (xr));
      fun_evals++;
      guard1 = false;
      guard2 = false;
      if (fxr < cfv_tmp_tmp) {
        xe[0] = 3.0 * maxfv - 2.0 * v[lastCol];
        xe[1] = 3.0 * maxv - 2.0 * xr_tmp;
        xe[2] = 3.0 * d - 2.0 * cfv;
        cfv = ntf_ERADist::ntf___anon_fcn((funfcn->tunableEnvironment[0].f1),
          (xe));
        fun_evals++;
        if (cfv < fxr) {
          v[lastCol] = xe[0];
          v[lastCol + 1] = xe[1];
          v[lastCol + 2] = xe[2];
          fv[idx[3] - 1] = cfv;
        } else {
          v[lastCol] = xr[0];
          v[lastCol + 1] = xr[1];
          v[lastCol + 2] = xr[2];
          fv[idx[3] - 1] = fxr;
        }

        guard1 = true;
      } else if (fxr < b_cfv_tmp_tmp) {
        v[lastCol] = xr[0];
        v[lastCol + 1] = xr[1];
        v[lastCol + 2] = xr[2];
        fv[idx[3] - 1] = fxr;
        guard1 = true;
      } else if (fxr < c_cfv_tmp_tmp) {
        x[0] = 1.5 * maxfv - 0.5 * v[lastCol];
        x[1] = 1.5 * maxv - 0.5 * v[lastCol + 1];
        x[2] = 1.5 * d - 0.5 * v[lastCol + 2];
        cfv = ntf_ERADist::ntf___anon_fcn((funfcn->tunableEnvironment[0].f1), (x));
        fun_evals++;
        if (cfv <= fxr) {
          v[lastCol] = x[0];
          v[lastCol + 1] = x[1];
          v[lastCol + 2] = x[2];
          fv[idx[3] - 1] = cfv;
          guard1 = true;
        } else {
          guard2 = true;
        }
      } else {
        x[0] = 0.5 * maxfv + 0.5 * v[lastCol];
        x[1] = 0.5 * maxv + 0.5 * xr_tmp;
        x[2] = 0.5 * d + 0.5 * cfv;
        cfv = ntf_ERADist::ntf___anon_fcn((funfcn->tunableEnvironment[0].f1), (x));
        fun_evals++;
        if (cfv < c_cfv_tmp_tmp) {
          v[lastCol] = x[0];
          v[lastCol + 1] = x[1];
          v[lastCol + 2] = x[2];
          fv[idx[3] - 1] = cfv;
          guard1 = true;
        } else {
          guard2 = true;
        }
      }

      if (guard2) {
        for (k = 0; k < 3; k++) {
          b_firstCol = idx[k + 1] - 1;
          colIdx = 3 * b_firstCol - 1;
          v[colIdx + 1] = v[firstCol] + 0.5 * (v[colIdx + 1] - v[firstCol]);
          x[0] = v[colIdx + 1];
          v[colIdx + 2] = v[firstCol + 1] + 0.5 * (v[colIdx + 2] - v[firstCol +
            1]);
          x[1] = v[colIdx + 2];
          v[colIdx + 3] = v[firstCol + 2] + 0.5 * (v[colIdx + 3] - v[firstCol +
            2]);
          x[2] = v[colIdx + 3];
          fv[b_firstCol] = ntf_ERADist::ntf___anon_fcn
            ((funfcn->tunableEnvironment[0].f1), (x));
        }

        fun_evals += 3;
        fvt[0] = fv[idx[0] - 1];
        idxb[0] = idx[0];
        fvt[1] = fv[idx[1] - 1];
        idxb[1] = idx[1];
        fvt[2] = fv[idx[2] - 1];
        idxb[2] = idx[2];
        fvt[3] = fv[idx[3] - 1];
        idxb[3] = idx[3];
        ntf_b_sortIdx(fvt, idx);
        idx[0] = idxb[idx[0] - 1];
        idx[1] = idxb[idx[1] - 1];
        idx[2] = idxb[idx[2] - 1];
        idx[3] = idxb[idx[3] - 1];
      }

      if (guard1) {
        if (fv[idx[3] - 1] < fv[idx[2] - 1]) {
          b_firstCol = idx[3];
          idx[3] = idx[2];
          idx[2] = b_firstCol;
        }

        if (fv[idx[2] - 1] < fv[idx[1] - 1]) {
          b_firstCol = idx[2];
          idx[2] = idx[1];
          idx[1] = b_firstCol;
        }

        if (fv[idx[1] - 1] < fv[idx[0] - 1]) {
          b_firstCol = idx[1];
          idx[1] = idx[0];
          idx[0] = b_firstCol;
        }
      }

      itercount++;
      lastCol = 3 * (idx[3] - 1);
      firstCol = 3 * (idx[0] - 1);
    } else {
      exitg1 = true;
    }
  }

  colIdx = 3 * (idx[0] - 1);
  x[0] = v[colIdx];
  x[1] = v[colIdx + 1];
  x[2] = v[colIdx + 2];
}

//
// Arguments    : const ntf_b_coder_internal_anonymous_ *funfcn
// Return Type  : double
//
double ntf_fminsearch(const ntf_b_coder_internal_anonymous_ *funfcn)
{
  double x;
  double fv[2];
  double v[2];
  coder::array<double, 1U> r;
  double b[4];
  double xr;
  signed char idx_idx_0;
  signed char idx_idx_1;
  int itercount;
  int fun_evals;
  int lastCol;
  int firstCol;
  boolean_T exitg1;
  int exponent;
  int b_exponent;
  int c_exponent;
  signed char idxb[2];
  fv[0] = ntf_getCheckFcn(funfcn);
  v[0] = 0.0;
  v[1] = 0.00025;
  ntf_gevinv(funfcn->tunableEnvironment[1].f1, 0.00025, r);
  ntf_corrcoef(funfcn->tunableEnvironment[0].f1, r, b);
  xr = (b[0] + 0.0 * b[1]) * 0.0 + (b[2] + 0.0 * b[3]);
  fv[1] = 1.0 - xr;
  if ((fv[0] <= 1.0 - xr) || rtIsNaN(1.0 - xr)) {
    idx_idx_0 = 1;
    idx_idx_1 = 2;
  } else {
    idx_idx_0 = 2;
    idx_idx_1 = 1;
  }

  itercount = 1;
  fun_evals = 2;
  lastCol = idx_idx_1 - 1;
  firstCol = idx_idx_0 - 1;
  exitg1 = false;
  while ((!exitg1) && ((fun_evals < 200) && (itercount < 200))) {
    double xe;
    int cfv_tmp_tmp;
    int b_cfv_tmp_tmp;
    boolean_T p;
    xe = 0.0;
    cfv_tmp_tmp = idx_idx_0 - 1;
    b_cfv_tmp_tmp = idx_idx_1 - 1;
    xr = std::abs(fv[cfv_tmp_tmp] - fv[b_cfv_tmp_tmp]);
    if (xr > 0.0) {
      xe = xr;
    }

    xr = std::abs(fv[cfv_tmp_tmp]);
    if ((!rtIsInf(xr)) && (!rtIsNaN(xr))) {
      if (xr <= 2.2250738585072014E-308) {
        xr = 4.94065645841247E-324;
      } else {
        frexp(xr, &exponent);
        xr = std::ldexp(1.0, exponent - 53);
      }
    } else {
      xr = rtNaN;
    }

    xr *= 10.0;
    if ((!rtIsInf(xr)) && (!rtIsNaN(xr))) {
      if (xr <= 2.2250738585072014E-308) {
        xr = 4.94065645841247E-324;
      } else {
        frexp(xr, &b_exponent);
        xr = std::ldexp(1.0, b_exponent - 53);
      }
    } else {
      xr = rtNaN;
    }

    xr *= 10.0;
    if ((0.0001 > xr) || rtIsNaN(xr)) {
      xr = 0.0001;
    }

    if (xe > xr) {
      p = false;
    } else {
      xe = 0.0;
      xr = std::abs(v[cfv_tmp_tmp] - v[b_cfv_tmp_tmp]);
      if (xr > 0.0) {
        xe = xr;
      }

      xr = std::abs(v[cfv_tmp_tmp]);
      if ((!rtIsInf(xr)) && (!rtIsNaN(xr))) {
        if (xr <= 2.2250738585072014E-308) {
          xr = 4.94065645841247E-324;
        } else {
          frexp(xr, &c_exponent);
          xr = std::ldexp(1.0, c_exponent - 53);
        }
      } else {
        xr = rtNaN;
      }

      xr *= 10.0;
      if ((0.0001 > xr) || rtIsNaN(xr)) {
        xr = 0.0001;
      }

      p = (xe <= xr);
    }

    if (!p) {
      double fvt;
      boolean_T guard1 = false;
      boolean_T guard2 = false;
      xr = 2.0 * v[firstCol] - v[lastCol];
      ntf_gevinv(funfcn->tunableEnvironment[1].f1, xr, r);
      ntf_corrcoef(funfcn->tunableEnvironment[0].f1, r, b);
      fvt = (b[0] + 0.0 * b[1]) * 0.0 + (b[2] + 0.0 * b[3]);
      fun_evals++;
      guard1 = false;
      guard2 = false;
      if (1.0 - fvt < fv[cfv_tmp_tmp]) {
        double b_fvt;
        xe = 3.0 * v[firstCol] - 2.0 * v[lastCol];
        ntf_gevinv(funfcn->tunableEnvironment[1].f1, xe, r);
        ntf_corrcoef(funfcn->tunableEnvironment[0].f1, r, b);
        b_fvt = (b[0] + 0.0 * b[1]) * 0.0 + (b[2] + 0.0 * b[3]);
        fun_evals++;
        if (1.0 - b_fvt < 1.0 - fvt) {
          v[lastCol] = xe;
          fv[b_cfv_tmp_tmp] = 1.0 - b_fvt;
        } else {
          v[lastCol] = xr;
          fv[b_cfv_tmp_tmp] = 1.0 - fvt;
        }

        guard1 = true;
      } else if (1.0 - fvt < fv[cfv_tmp_tmp]) {
        v[lastCol] = xr;
        fv[b_cfv_tmp_tmp] = 1.0 - fvt;
        guard1 = true;
      } else if (1.0 - fvt < fv[b_cfv_tmp_tmp]) {
        double b_fvt;
        x = 1.5 * v[firstCol] - 0.5 * v[lastCol];
        ntf_gevinv(funfcn->tunableEnvironment[1].f1, x, r);
        ntf_corrcoef(funfcn->tunableEnvironment[0].f1, r, b);
        b_fvt = (b[0] + 0.0 * b[1]) * 0.0 + (b[2] + 0.0 * b[3]);
        fun_evals++;
        if (1.0 - b_fvt <= 1.0 - fvt) {
          v[lastCol] = x;
          fv[b_cfv_tmp_tmp] = 1.0 - b_fvt;
          guard1 = true;
        } else {
          guard2 = true;
        }
      } else {
        x = 0.5 * v[firstCol] + 0.5 * v[lastCol];
        ntf_gevinv(funfcn->tunableEnvironment[1].f1, x, r);
        ntf_corrcoef(funfcn->tunableEnvironment[0].f1, r, b);
        fvt = (b[0] + 0.0 * b[1]) * 0.0 + (b[2] + 0.0 * b[3]);
        fun_evals++;
        if (1.0 - fvt < fv[b_cfv_tmp_tmp]) {
          v[lastCol] = x;
          fv[b_cfv_tmp_tmp] = 1.0 - fvt;
          guard1 = true;
        } else {
          guard2 = true;
        }
      }

      if (guard2) {
        v[b_cfv_tmp_tmp] = v[firstCol] + 0.5 * (v[b_cfv_tmp_tmp] - v[firstCol]);
        ntf_gevinv(funfcn->tunableEnvironment[1].f1, v[idx_idx_1 - 1], r);
        ntf_corrcoef(funfcn->tunableEnvironment[0].f1, r, b);
        fv[b_cfv_tmp_tmp] = 1.0 - ((b[0] + 0.0 * b[1]) * 0.0 + (b[2] + 0.0 * b[3]));
        fun_evals++;
        idxb[0] = idx_idx_0;
        idxb[1] = idx_idx_1;
        if ((fv[cfv_tmp_tmp] <= fv[b_cfv_tmp_tmp]) || rtIsNaN(fv[b_cfv_tmp_tmp]))
        {
          idx_idx_0 = 1;
          idx_idx_1 = 2;
        } else {
          idx_idx_0 = 2;
          idx_idx_1 = 1;
        }

        idx_idx_0 = idxb[idx_idx_0 - 1];
        idx_idx_1 = idxb[idx_idx_1 - 1];
      }

      if (guard1 && (fv[b_cfv_tmp_tmp] < fv[cfv_tmp_tmp])) {
        lastCol = idx_idx_1;
        idx_idx_1 = idx_idx_0;
        idx_idx_0 = static_cast<signed char>(lastCol);
      }

      itercount++;
      lastCol = idx_idx_1 - 1;
      firstCol = idx_idx_0 - 1;
    } else {
      exitg1 = true;
    }
  }

  return v[idx_idx_0 - 1];
}

//
// File trailer for ntf_fminsearch.cpp
//
// [EOF]
//
