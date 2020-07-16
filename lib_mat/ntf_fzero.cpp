//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_fzero.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//

// Include Files
#include "ntf_fzero.h"
#include "ntf_ERANataf.h"
#include "ntf_gamma.h"
#include "ntf_inataf.h"
#include "ntf_pdf.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const ntf_coder_internal_anonymous_fu FunFcn
//                double *b
//                double *fval
//                double *exitflag
// Return Type  : void
//
void ntf_b_fzero(const ntf_coder_internal_anonymous_fu FunFcn, double *b, double
                 *fval, double *exitflag)
{
  double a;
  double p;
  double q;
  double fa_tmp;
  double fa;
  double savefa;
  double savefb;
  *exitflag = 1.0;
  a = 0.02;
  *b = 1000.0;
  p = 51.0;
  ntf_gamma(&p);
  q = 101.0;
  ntf_gamma(&q);
  fa_tmp = FunFcn.tunableEnvironment[0].f1[1] / FunFcn.tunableEnvironment[0].f1
    [0];
  fa = std::sqrt(q - p * p) / p - fa_tmp;
  p = 1.001;
  ntf_gamma(&p);
  q = 1.002;
  ntf_gamma(&q);
  *fval = std::sqrt(q - p * p) / p - fa_tmp;
  savefa = fa;
  savefb = *fval;
  if (fa == 0.0) {
    *b = 0.02;
    *fval = fa;
  } else {
    if (!(*fval == 0.0)) {
      double fc;
      double c;
      double e;
      double d;
      boolean_T exitg1;
      fc = *fval;
      c = 1000.0;
      e = 0.0;
      d = 0.0;
      exitg1 = false;
      while ((!exitg1) && ((*fval != 0.0) && (a != *b))) {
        double m;
        double toler;
        if ((*fval > 0.0) == (fc > 0.0)) {
          c = a;
          fc = fa;
          d = *b - a;
          e = d;
        }

        if (std::abs(fc) < std::abs(*fval)) {
          a = *b;
          *b = c;
          c = a;
          fa = *fval;
          *fval = fc;
          fc = fa;
        }

        m = 0.5 * (c - *b);
        q = std::abs(*b);
        if (!(q > 1.0)) {
          q = 1.0;
        }

        toler = 4.4408920985006262E-16 * q;
        if ((std::abs(m) <= toler) || (*fval == 0.0)) {
          exitg1 = true;
        } else {
          if ((std::abs(e) < toler) || (std::abs(fa) <= std::abs(*fval))) {
            d = m;
            e = m;
          } else {
            double s;
            s = *fval / fa;
            if (a == c) {
              p = 2.0 * m * s;
              q = 1.0 - s;
            } else {
              q = fa / fc;
              fa = *fval / fc;
              p = s * (2.0 * m * q * (q - fa) - (*b - a) * (fa - 1.0));
              q = (q - 1.0) * (fa - 1.0) * (s - 1.0);
            }

            if (p > 0.0) {
              q = -q;
            } else {
              p = -p;
            }

            if ((2.0 * p < 3.0 * m * q - std::abs(toler * q)) && (p < std::abs
                 (0.5 * e * q))) {
              e = d;
              d = p / q;
            } else {
              d = m;
              e = m;
            }
          }

          a = *b;
          fa = *fval;
          if (std::abs(d) > toler) {
            *b += d;
          } else if (*b > c) {
            *b -= toler;
          } else {
            *b += toler;
          }

          p = 1.0 / *b + 1.0;
          ntf_gamma(&p);
          q = 2.0 / *b + 1.0;
          ntf_gamma(&q);
          *fval = std::sqrt(q - p * p) / p - fa_tmp;
        }
      }

      q = std::abs(savefa);
      p = std::abs(savefb);
      if ((q > p) || rtIsNaN(p)) {
        p = q;
      }

      if (!(std::abs(*fval) <= p)) {
        *exitflag = -5.0;
      }
    }
  }
}

//
// Arguments    : const ntf_coder_internal_anonymous_fu FunFcn
//                double x
//                double *b
//                double *fval
//                double *exitflag
// Return Type  : void
//
void ntf_c_fzero(const ntf_coder_internal_anonymous_fu FunFcn, double x, double *
                 b, double *fval, double *exitflag)
{
  double q;
  double dx;
  double r;
  double fx_tmp;
  double fx;
  *exitflag = 1.0;
  q = 1.0 - x;
  ntf_gamma(&q);
  dx = FunFcn.tunableEnvironment[0].f1[1] / (FunFcn.tunableEnvironment[0].f1[0]
    - FunFcn.tunableEnvironment[0].f1[2]);
  r = 1.0 - 2.0 * x;
  ntf_gamma(&r);
  fx_tmp = dx * dx;
  fx = (r - q * q) / ((q - 1.0) * (q - 1.0)) - fx_tmp;
  if (fx == 0.0) {
    *b = x;
    *fval = fx;
  } else {
    double a;
    boolean_T guard1 = false;
    if (x != 0.0) {
      dx = x / 50.0;
    } else {
      dx = 0.02;
    }

    a = x;
    *b = x;
    *fval = fx;
    guard1 = false;
    int exitg1;
    do {
      exitg1 = 0;
      if ((fx > 0.0) == (*fval > 0.0)) {
        dx *= 1.4142135623730951;
        a = x - dx;
        q = 1.0 - a;
        ntf_gamma(&q);
        r = 1.0 - 2.0 * a;
        ntf_gamma(&r);
        fx = (r - q * q) / ((q - 1.0) * (q - 1.0)) - fx_tmp;
        if (rtIsInf(fx) || rtIsNaN(fx)) {
          *exitflag = -3.0;
          *b = rtNaN;
          *fval = rtNaN;
          exitg1 = 1;
        } else if (rtIsInf(a) || rtIsNaN(a)) {
          *exitflag = -6.0;
          *b = rtNaN;
          *fval = rtNaN;
          exitg1 = 1;
        } else if ((fx > 0.0) != (*fval > 0.0)) {
          guard1 = true;
          exitg1 = 1;
        } else {
          *b = x + dx;
          q = 1.0 - *b;
          ntf_gamma(&q);
          r = 1.0 - 2.0 * *b;
          ntf_gamma(&r);
          *fval = (r - q * q) / ((q - 1.0) * (q - 1.0)) - fx_tmp;
          if (rtIsInf(*fval) || rtIsNaN(*fval)) {
            *exitflag = -3.0;
            *b = rtNaN;
            *fval = rtNaN;
            exitg1 = 1;
          } else if (rtIsInf(*b) || rtIsNaN(*b)) {
            *exitflag = -6.0;
            *b = rtNaN;
            *fval = rtNaN;
            exitg1 = 1;
          } else {
            guard1 = false;
          }
        }
      } else {
        guard1 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);

    if (guard1) {
      double b_x;
      double c_x;
      double fc;
      double c;
      double e;
      double d;
      boolean_T exitg2;
      b_x = fx;
      c_x = *fval;
      fc = *fval;
      c = *b;
      e = 0.0;
      d = 0.0;
      exitg2 = false;
      while ((!exitg2) && ((*fval != 0.0) && (a != *b))) {
        double m;
        double toler;
        if ((*fval > 0.0) == (fc > 0.0)) {
          c = a;
          fc = fx;
          d = *b - a;
          e = d;
        }

        if (std::abs(fc) < std::abs(*fval)) {
          a = *b;
          *b = c;
          c = a;
          fx = *fval;
          *fval = fc;
          fc = fx;
        }

        m = 0.5 * (c - *b);
        q = std::abs(*b);
        if (!(q > 1.0)) {
          q = 1.0;
        }

        toler = 4.4408920985006262E-16 * q;
        if ((std::abs(m) <= toler) || (*fval == 0.0)) {
          exitg2 = true;
        } else {
          if ((std::abs(e) < toler) || (std::abs(fx) <= std::abs(*fval))) {
            d = m;
            e = m;
          } else {
            double s;
            s = *fval / fx;
            if (a == c) {
              dx = 2.0 * m * s;
              q = 1.0 - s;
            } else {
              q = fx / fc;
              r = *fval / fc;
              dx = s * (2.0 * m * q * (q - r) - (*b - a) * (r - 1.0));
              q = (q - 1.0) * (r - 1.0) * (s - 1.0);
            }

            if (dx > 0.0) {
              q = -q;
            } else {
              dx = -dx;
            }

            if ((2.0 * dx < 3.0 * m * q - std::abs(toler * q)) && (dx < std::abs
                 (0.5 * e * q))) {
              e = d;
              d = dx / q;
            } else {
              d = m;
              e = m;
            }
          }

          a = *b;
          fx = *fval;
          if (std::abs(d) > toler) {
            *b += d;
          } else if (*b > c) {
            *b -= toler;
          } else {
            *b += toler;
          }

          q = 1.0 - *b;
          ntf_gamma(&q);
          r = 1.0 - 2.0 * *b;
          ntf_gamma(&r);
          *fval = (r - q * q) / ((q - 1.0) * (q - 1.0)) - fx_tmp;
        }
      }

      q = std::abs(b_x);
      dx = std::abs(c_x);
      if ((q > dx) || rtIsNaN(dx)) {
        dx = q;
      }

      if (!(std::abs(*fval) <= dx)) {
        *exitflag = -5.0;
      }
    }
  }
}

//
// Arguments    : const ntf_coder_internal_anonymous_fu FunFcn
//                double x
//                double *b
//                double *fval
//                double *exitflag
// Return Type  : void
//
void ntf_d_fzero(const ntf_coder_internal_anonymous_fu FunFcn, double x, double *
                 b, double *fval, double *exitflag)
{
  double q;
  double dx;
  double r;
  double fx_tmp;
  double fx;
  *exitflag = 1.0;
  q = 1.0 - x;
  ntf_gamma(&q);
  dx = FunFcn.tunableEnvironment[0].f1[1] / (-FunFcn.tunableEnvironment[0].f1[0]
    + FunFcn.tunableEnvironment[0].f1[2]);
  r = 1.0 - 2.0 * x;
  ntf_gamma(&r);
  fx_tmp = dx * dx;
  fx = (r - q * q) / ((q - 1.0) * (q - 1.0)) - fx_tmp;
  if (fx == 0.0) {
    *b = x;
    *fval = fx;
  } else {
    double a;
    boolean_T guard1 = false;
    if (x != 0.0) {
      dx = x / 50.0;
    } else {
      dx = 0.02;
    }

    a = x;
    *b = x;
    *fval = fx;
    guard1 = false;
    int exitg1;
    do {
      exitg1 = 0;
      if ((fx > 0.0) == (*fval > 0.0)) {
        dx *= 1.4142135623730951;
        a = x - dx;
        q = 1.0 - a;
        ntf_gamma(&q);
        r = 1.0 - 2.0 * a;
        ntf_gamma(&r);
        fx = (r - q * q) / ((q - 1.0) * (q - 1.0)) - fx_tmp;
        if (rtIsInf(fx) || rtIsNaN(fx)) {
          *exitflag = -3.0;
          *b = rtNaN;
          *fval = rtNaN;
          exitg1 = 1;
        } else if (rtIsInf(a) || rtIsNaN(a)) {
          *exitflag = -6.0;
          *b = rtNaN;
          *fval = rtNaN;
          exitg1 = 1;
        } else if ((fx > 0.0) != (*fval > 0.0)) {
          guard1 = true;
          exitg1 = 1;
        } else {
          *b = x + dx;
          q = 1.0 - *b;
          ntf_gamma(&q);
          r = 1.0 - 2.0 * *b;
          ntf_gamma(&r);
          *fval = (r - q * q) / ((q - 1.0) * (q - 1.0)) - fx_tmp;
          if (rtIsInf(*fval) || rtIsNaN(*fval)) {
            *exitflag = -3.0;
            *b = rtNaN;
            *fval = rtNaN;
            exitg1 = 1;
          } else if (rtIsInf(*b) || rtIsNaN(*b)) {
            *exitflag = -6.0;
            *b = rtNaN;
            *fval = rtNaN;
            exitg1 = 1;
          } else {
            guard1 = false;
          }
        }
      } else {
        guard1 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);

    if (guard1) {
      double b_x;
      double c_x;
      double fc;
      double c;
      double e;
      double d;
      boolean_T exitg2;
      b_x = fx;
      c_x = *fval;
      fc = *fval;
      c = *b;
      e = 0.0;
      d = 0.0;
      exitg2 = false;
      while ((!exitg2) && ((*fval != 0.0) && (a != *b))) {
        double m;
        double toler;
        if ((*fval > 0.0) == (fc > 0.0)) {
          c = a;
          fc = fx;
          d = *b - a;
          e = d;
        }

        if (std::abs(fc) < std::abs(*fval)) {
          a = *b;
          *b = c;
          c = a;
          fx = *fval;
          *fval = fc;
          fc = fx;
        }

        m = 0.5 * (c - *b);
        q = std::abs(*b);
        if (!(q > 1.0)) {
          q = 1.0;
        }

        toler = 4.4408920985006262E-16 * q;
        if ((std::abs(m) <= toler) || (*fval == 0.0)) {
          exitg2 = true;
        } else {
          if ((std::abs(e) < toler) || (std::abs(fx) <= std::abs(*fval))) {
            d = m;
            e = m;
          } else {
            double s;
            s = *fval / fx;
            if (a == c) {
              dx = 2.0 * m * s;
              q = 1.0 - s;
            } else {
              q = fx / fc;
              r = *fval / fc;
              dx = s * (2.0 * m * q * (q - r) - (*b - a) * (r - 1.0));
              q = (q - 1.0) * (r - 1.0) * (s - 1.0);
            }

            if (dx > 0.0) {
              q = -q;
            } else {
              dx = -dx;
            }

            if ((2.0 * dx < 3.0 * m * q - std::abs(toler * q)) && (dx < std::abs
                 (0.5 * e * q))) {
              e = d;
              d = dx / q;
            } else {
              d = m;
              e = m;
            }
          }

          a = *b;
          fx = *fval;
          if (std::abs(d) > toler) {
            *b += d;
          } else if (*b > c) {
            *b -= toler;
          } else {
            *b += toler;
          }

          q = 1.0 - *b;
          ntf_gamma(&q);
          r = 1.0 - 2.0 * *b;
          ntf_gamma(&r);
          *fval = (r - q * q) / ((q - 1.0) * (q - 1.0)) - fx_tmp;
        }
      }

      q = std::abs(b_x);
      dx = std::abs(c_x);
      if ((q > dx) || rtIsNaN(dx)) {
        dx = q;
      }

      if (!(std::abs(*fval) <= dx)) {
        *exitflag = -5.0;
      }
    }
  }
}

//
// Arguments    : const double x[2]
//                const coder::array<double, 1U> *varargin_1
//                double varargin_3
//                double *b
//                double *fval
//                double *exitflag
// Return Type  : void
//
void ntf_e_fzero(const double x[2], const coder::array<double, 1U> &varargin_1,
                 double varargin_3, double *b, double *fval, double *exitflag)
{
  double a;
  coder::array<double, 1U> wt;
  int nx;
  int k;
  coder::array<double, 1U> b_x;
  double p;
  double q;
  double fa;
  double savefa;
  double savefb;
  *exitflag = 1.0;
  a = x[0];
  *b = x[1];
  wt.set_size(varargin_1.size(0));
  nx = varargin_1.size(0);
  for (k = 0; k < nx; k++) {
    wt[k] = varargin_1[k] / x[0];
  }

  nx = wt.size(0);
  for (k = 0; k < nx; k++) {
    wt[k] = std::exp(wt[k]);
  }

  b_x.set_size(varargin_1.size(0));
  nx = varargin_1.size(0);
  for (k = 0; k < nx; k++) {
    b_x[k] = varargin_1[k] * wt[k];
  }

  nx = b_x.size(0);
  if (b_x.size(0) == 0) {
    p = 0.0;
  } else {
    p = b_x[0];
    for (k = 2; k <= nx; k++) {
      p += b_x[k - 1];
    }
  }

  nx = wt.size(0);
  if (wt.size(0) == 0) {
    q = 0.0;
  } else {
    q = wt[0];
    for (k = 2; k <= nx; k++) {
      q += wt[k - 1];
    }
  }

  fa = (x[0] + varargin_3) - p / q;
  wt.set_size(varargin_1.size(0));
  nx = varargin_1.size(0);
  for (k = 0; k < nx; k++) {
    wt[k] = varargin_1[k] / x[1];
  }

  nx = wt.size(0);
  for (k = 0; k < nx; k++) {
    wt[k] = std::exp(wt[k]);
  }

  b_x.set_size(varargin_1.size(0));
  nx = varargin_1.size(0);
  for (k = 0; k < nx; k++) {
    b_x[k] = varargin_1[k] * wt[k];
  }

  nx = b_x.size(0);
  if (b_x.size(0) == 0) {
    p = 0.0;
  } else {
    p = b_x[0];
    for (k = 2; k <= nx; k++) {
      p += b_x[k - 1];
    }
  }

  nx = wt.size(0);
  if (wt.size(0) == 0) {
    q = 0.0;
  } else {
    q = wt[0];
    for (k = 2; k <= nx; k++) {
      q += wt[k - 1];
    }
  }

  *fval = (x[1] + varargin_3) - p / q;
  savefa = fa;
  savefb = *fval;
  if (fa == 0.0) {
    *b = x[0];
    *fval = fa;
  } else {
    if (!(*fval == 0.0)) {
      double fc;
      double c;
      double e;
      double d;
      boolean_T exitg1;
      fc = *fval;
      c = x[1];
      e = 0.0;
      d = 0.0;
      exitg1 = false;
      while ((!exitg1) && ((*fval != 0.0) && (a != *b))) {
        double m;
        double toler;
        if ((*fval > 0.0) == (fc > 0.0)) {
          c = a;
          fc = fa;
          d = *b - a;
          e = d;
        }

        if (std::abs(fc) < std::abs(*fval)) {
          a = *b;
          *b = c;
          c = a;
          fa = *fval;
          *fval = fc;
          fc = fa;
        }

        m = 0.5 * (c - *b);
        q = std::abs(*b);
        if (!(q > 1.0)) {
          q = 1.0;
        }

        toler = 2.0E-6 * q;
        if ((std::abs(m) <= toler) || (*fval == 0.0)) {
          exitg1 = true;
        } else {
          if ((std::abs(e) < toler) || (std::abs(fa) <= std::abs(*fval))) {
            d = m;
            e = m;
          } else {
            double s;
            s = *fval / fa;
            if (a == c) {
              p = 2.0 * m * s;
              q = 1.0 - s;
            } else {
              q = fa / fc;
              fa = *fval / fc;
              p = s * (2.0 * m * q * (q - fa) - (*b - a) * (fa - 1.0));
              q = (q - 1.0) * (fa - 1.0) * (s - 1.0);
            }

            if (p > 0.0) {
              q = -q;
            } else {
              p = -p;
            }

            if ((2.0 * p < 3.0 * m * q - std::abs(toler * q)) && (p < std::abs
                 (0.5 * e * q))) {
              e = d;
              d = p / q;
            } else {
              d = m;
              e = m;
            }
          }

          a = *b;
          fa = *fval;
          if (std::abs(d) > toler) {
            *b += d;
          } else if (*b > c) {
            *b -= toler;
          } else {
            *b += toler;
          }

          wt.set_size(varargin_1.size(0));
          nx = varargin_1.size(0);
          for (k = 0; k < nx; k++) {
            wt[k] = varargin_1[k] / *b;
          }

          nx = wt.size(0);
          for (k = 0; k < nx; k++) {
            wt[k] = std::exp(wt[k]);
          }

          b_x.set_size(varargin_1.size(0));
          nx = varargin_1.size(0);
          for (k = 0; k < nx; k++) {
            b_x[k] = varargin_1[k] * wt[k];
          }

          nx = b_x.size(0);
          if (b_x.size(0) == 0) {
            p = 0.0;
          } else {
            p = b_x[0];
            for (k = 2; k <= nx; k++) {
              p += b_x[k - 1];
            }
          }

          nx = wt.size(0);
          if (wt.size(0) == 0) {
            q = 0.0;
          } else {
            q = wt[0];
            for (k = 2; k <= nx; k++) {
              q += wt[k - 1];
            }
          }

          *fval = (*b + varargin_3) - p / q;
        }
      }

      q = std::abs(savefa);
      p = std::abs(savefb);
      if ((q > p) || rtIsNaN(p)) {
        p = q;
      }

      if (!(std::abs(*fval) <= p)) {
        *exitflag = -5.0;
      }
    }
  }
}

//
// Arguments    : const ntf_d_coder_internal_anonymous_ *FunFcn
//                double x
//                double *b
//                double *fval
//                double *exitflag
// Return Type  : void
//
void ntf_f_fzero(const ntf_d_coder_internal_anonymous_ *FunFcn, double x, double
                 *b, double *fval, double *exitflag)
{
  double fx;
  double dx;
  *exitflag = 1.0;
  fx = ntf_ERANataf::ntf___anon_fcn((FunFcn->tunableEnvironment.f1),
    (FunFcn->tunableEnvironment.f2), (FunFcn->tunableEnvironment.f3),
    (&FunFcn->tunableEnvironment.f4), (FunFcn->tunableEnvironment.f5),
    (FunFcn->tunableEnvironment.f6), (x));
  if (fx == 0.0) {
    *b = x;
    *fval = fx;
  } else {
    double a;
    boolean_T guard1 = false;
    if (x != 0.0) {
      dx = x / 50.0;
    } else {
      dx = 0.02;
    }

    a = x;
    *b = x;
    *fval = fx;
    guard1 = false;
    int exitg1;
    do {
      exitg1 = 0;
      if ((fx > 0.0) == (*fval > 0.0)) {
        dx *= 1.4142135623730951;
        a = x - dx;
        fx = ntf_ERANataf::ntf___anon_fcn((FunFcn->tunableEnvironment.f1),
          (FunFcn->tunableEnvironment.f2), (FunFcn->tunableEnvironment.f3),
          (&FunFcn->tunableEnvironment.f4), (FunFcn->tunableEnvironment.f5),
          (FunFcn->tunableEnvironment.f6), (a));
        if (rtIsInf(fx) || rtIsNaN(fx)) {
          *exitflag = -3.0;
          *b = rtNaN;
          *fval = rtNaN;
          exitg1 = 1;
        } else if (rtIsInf(a) || rtIsNaN(a)) {
          *exitflag = -6.0;
          *b = rtNaN;
          *fval = rtNaN;
          exitg1 = 1;
        } else if ((fx > 0.0) != (*fval > 0.0)) {
          guard1 = true;
          exitg1 = 1;
        } else {
          *b = x + dx;
          *fval = ntf_ERANataf::ntf___anon_fcn((FunFcn->tunableEnvironment.f1),
            (FunFcn->tunableEnvironment.f2), (FunFcn->tunableEnvironment.f3),
            (&FunFcn->tunableEnvironment.f4), (FunFcn->tunableEnvironment.f5),
            (FunFcn->tunableEnvironment.f6), (*b));
          if (rtIsInf(*fval) || rtIsNaN(*fval)) {
            *exitflag = -3.0;
            *b = rtNaN;
            *fval = rtNaN;
            exitg1 = 1;
          } else if (rtIsInf(*b) || rtIsNaN(*b)) {
            *exitflag = -6.0;
            *b = rtNaN;
            *fval = rtNaN;
            exitg1 = 1;
          } else {
            guard1 = false;
          }
        }
      } else {
        guard1 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);

    if (guard1) {
      double b_x;
      double c_x;
      double fc;
      double c;
      double e;
      double d;
      boolean_T exitg2;
      double q;
      b_x = fx;
      c_x = *fval;
      fc = *fval;
      c = *b;
      e = 0.0;
      d = 0.0;
      exitg2 = false;
      while ((!exitg2) && ((*fval != 0.0) && (a != *b))) {
        double m;
        double toler;
        if ((*fval > 0.0) == (fc > 0.0)) {
          c = a;
          fc = fx;
          d = *b - a;
          e = d;
        }

        if (std::abs(fc) < std::abs(*fval)) {
          a = *b;
          *b = c;
          c = a;
          fx = *fval;
          *fval = fc;
          fc = fx;
        }

        m = 0.5 * (c - *b);
        q = std::abs(*b);
        if (!(q > 1.0)) {
          q = 1.0;
        }

        toler = 4.4408920985006262E-16 * q;
        if ((std::abs(m) <= toler) || (*fval == 0.0)) {
          exitg2 = true;
        } else {
          if ((std::abs(e) < toler) || (std::abs(fx) <= std::abs(*fval))) {
            d = m;
            e = m;
          } else {
            double s;
            s = *fval / fx;
            if (a == c) {
              dx = 2.0 * m * s;
              q = 1.0 - s;
            } else {
              q = fx / fc;
              fx = *fval / fc;
              dx = s * (2.0 * m * q * (q - fx) - (*b - a) * (fx - 1.0));
              q = (q - 1.0) * (fx - 1.0) * (s - 1.0);
            }

            if (dx > 0.0) {
              q = -q;
            } else {
              dx = -dx;
            }

            if ((2.0 * dx < 3.0 * m * q - std::abs(toler * q)) && (dx < std::abs
                 (0.5 * e * q))) {
              e = d;
              d = dx / q;
            } else {
              d = m;
              e = m;
            }
          }

          a = *b;
          fx = *fval;
          if (std::abs(d) > toler) {
            *b += d;
          } else if (*b > c) {
            *b -= toler;
          } else {
            *b += toler;
          }

          *fval = ntf_ERANataf::ntf___anon_fcn((FunFcn->tunableEnvironment.f1),
            (FunFcn->tunableEnvironment.f2), (FunFcn->tunableEnvironment.f3),
            (&FunFcn->tunableEnvironment.f4), (FunFcn->tunableEnvironment.f5),
            (FunFcn->tunableEnvironment.f6), (*b));
        }
      }

      q = std::abs(b_x);
      dx = std::abs(c_x);
      if ((q > dx) || rtIsNaN(dx)) {
        dx = q;
      }

      if (!(std::abs(*fval) <= dx)) {
        *exitflag = -5.0;
      }
    }
  }
}

//
// Arguments    : const ntf_coder_internal_anonymous_fu FunFcn
//                double *b
//                double *fval
//                double *exitflag
// Return Type  : void
//
void ntf_fzero(const ntf_coder_internal_anonymous_fu FunFcn, double *b, double
               *fval, double *exitflag)
{
  double a;
  double p;
  double q;
  double fa_tmp;
  double fa;
  double savefa;
  double savefb;
  *exitflag = 1.0;
  a = 2.001;
  *b = 1000.0;
  p = 0.50024987506246876;
  ntf_gamma(&p);
  q = 0.0004997501249375258;
  ntf_gamma(&q);
  fa_tmp = FunFcn.tunableEnvironment[0].f1[1] / FunFcn.tunableEnvironment[0].f1
    [0];
  fa = std::sqrt(q - p * p) / p - fa_tmp;
  p = 0.999;
  ntf_gamma(&p);
  q = 0.998;
  ntf_gamma(&q);
  *fval = std::sqrt(q - p * p) / p - fa_tmp;
  savefa = fa;
  savefb = *fval;
  if (fa == 0.0) {
    *b = 2.001;
    *fval = fa;
  } else {
    if (!(*fval == 0.0)) {
      double fc;
      double c;
      double e;
      double d;
      boolean_T exitg1;
      fc = *fval;
      c = 1000.0;
      e = 0.0;
      d = 0.0;
      exitg1 = false;
      while ((!exitg1) && ((*fval != 0.0) && (a != *b))) {
        double m;
        double toler;
        if ((*fval > 0.0) == (fc > 0.0)) {
          c = a;
          fc = fa;
          d = *b - a;
          e = d;
        }

        if (std::abs(fc) < std::abs(*fval)) {
          a = *b;
          *b = c;
          c = a;
          fa = *fval;
          *fval = fc;
          fc = fa;
        }

        m = 0.5 * (c - *b);
        q = std::abs(*b);
        if (!(q > 1.0)) {
          q = 1.0;
        }

        toler = 4.4408920985006262E-16 * q;
        if ((std::abs(m) <= toler) || (*fval == 0.0)) {
          exitg1 = true;
        } else {
          if ((std::abs(e) < toler) || (std::abs(fa) <= std::abs(*fval))) {
            d = m;
            e = m;
          } else {
            double s;
            s = *fval / fa;
            if (a == c) {
              p = 2.0 * m * s;
              q = 1.0 - s;
            } else {
              q = fa / fc;
              fa = *fval / fc;
              p = s * (2.0 * m * q * (q - fa) - (*b - a) * (fa - 1.0));
              q = (q - 1.0) * (fa - 1.0) * (s - 1.0);
            }

            if (p > 0.0) {
              q = -q;
            } else {
              p = -p;
            }

            if ((2.0 * p < 3.0 * m * q - std::abs(toler * q)) && (p < std::abs
                 (0.5 * e * q))) {
              e = d;
              d = p / q;
            } else {
              d = m;
              e = m;
            }
          }

          a = *b;
          fa = *fval;
          if (std::abs(d) > toler) {
            *b += d;
          } else if (*b > c) {
            *b -= toler;
          } else {
            *b += toler;
          }

          p = 1.0 - 1.0 / *b;
          ntf_gamma(&p);
          q = 1.0 - 2.0 / *b;
          ntf_gamma(&q);
          *fval = std::sqrt(q - p * p) / p - fa_tmp;
        }
      }

      q = std::abs(savefa);
      p = std::abs(savefb);
      if ((q > p) || rtIsNaN(p)) {
        p = q;
      }

      if (!(std::abs(*fval) <= p)) {
        *exitflag = -5.0;
      }
    }
  }
}

//
// File trailer for ntf_fzero.cpp
//
// [EOF]
//
