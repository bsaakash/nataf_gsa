//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_ERADist.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 10-Aug-2020 16:42:46
//

// Include Files
#include "ntf_ERADist.h"
#include "ntf_BetaDistribution.h"
#include "ntf_ExponentialDistribution.h"
#include "ntf_ExtremeValueDistribution.h"
#include "ntf_LognormalDistribution.h"
#include "ntf_NormalDistribution.h"
#include "ntf_WeibullDistribution.h"
#include "ntf_binostat.h"
#include "ntf_cdf.h"
#include "ntf_colon.h"
#include "ntf_evfit.h"
#include "ntf_expm1.h"
#include "ntf_find.h"
#include "ntf_fminsearch.h"
#include "ntf_fzero.h"
#include "ntf_gamma.h"
#include "ntf_gampdf.h"
#include "ntf_gevinv.h"
#include "ntf_gevstat.h"
#include "ntf_icdf.h"
#include "ntf_inataf.h"
#include "ntf_inataf_data.h"
#include "ntf_inataf_rtwutil.h"
#include "ntf_linspace.h"
#include "ntf_lognstat.h"
#include "ntf_minOrMax.h"
#include "ntf_mod.h"
#include "ntf_mod1.h"
#include "ntf_mrdivide_helper.h"
#include "ntf_mycholcov.h"
#include "ntf_nbinstat.h"
#include "ntf_pdf.h"
#include "ntf_polyfit.h"
#include "ntf_sort.h"
#include "ntf_std.h"
#include "ntf_strcmp.h"
#include "ntf_trapz.h"
#include "ntf_unique.h"
#include "ntf_var.h"
#include "ntf_wblstat.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>

// Variable Definitions
static const char ntf_cv[128] = { '\x00', '\x01', '\x02', '\x03', '\x04', '\x05',
  '\x06', '\x07', '\x08', '	', '\x0a', '\x0b', '\x0c', '\x0d', '\x0e', '\x0f',
  '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19',
  '\x1a', '\x1b', '\x1c', '\x1d', '\x1e', '\x1f', ' ', '!', '\"', '#', '$', '%',
  '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4',
  '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'a', 'b', 'c', 'd',
  'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
  'u', 'v', 'w', 'x', 'y', 'z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c',
  'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
  't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', '\x7f' };

// Function Declarations
static int ntf_div_s32_floor(int numerator, int denominator);
static double ntf_rt_roundd_snf(double u);

// Function Definitions

//
// Arguments    : const double x[1000]
//                double PDF[1000]
// Return Type  : void
//
void ntf_ERADist::ntf_fb_pdf(const double x[1000], double PDF[1000]) const
{
  coder::array<char, 2U> switch_expression;
  int i;
  int k;
  boolean_T b_bool;
  int vlen;
  int exitg1;
  static const char b_cv[8] = { 'b', 'i', 'n', 'o', 'm', 'i', 'a', 'l' };

  double xk;
  double b_x[1000];
  static const char b_cv1[7] = { 'p', 'o', 'i', 's', 's', 'o', 'n' };

  coder::array<double, 2U> c_x;
  static const char b_cv2[5] = { 'g', 'a', 'm', 'm', 'a' };

  static const char b_cv3[4] = { 'b', 'e', 't', 'a' };

  static const char t3_f1[6] = { 'n', 'o', 'r', 'm', 'a', 'l' };

  static const char t3_f2[8] = { 'g', 'a', 'u', 's', 's', 'i', 'a', 'n' };

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
  //     function CDF = cdf(Obj,x)
  //        switch lower(Obj.Name)
  //           case 'geometric'
  //              CDF = Obj.Dist.cdf(x-1);
  //           case 'negativebinomial'
  //              CDF = Obj.Dist.cdf(x-Obj.Par(1));
  //           case 'beta'
  //              CDF = Obj.Dist.cdf((x-Obj.Par(3))/(Obj.Par(4)-Obj.Par(3)));
  //           case 'gumbelmin'
  //              CDF = Obj.Dist.cdf(-x);
  //           case 'gevmin'
  //              CDF = Obj.Dist.cdf(-x);
  //           otherwise
  //              CDF = Obj.Dist.cdf(x);
  //        end
  //     end
  std::memset(&PDF[0], 0, 1000U * sizeof(double));
  switch_expression.set_size(this->Name.size(0), this->Name.size(1));
  i = this->Name.size(1);
  for (k = 0; k < i; k++) {
    switch_expression[k] = ntf_cv[static_cast<unsigned char>(this->Name[k]) &
      127];
  }

  b_bool = false;
  if (switch_expression.size(1) == 8) {
    vlen = 0;
    do {
      exitg1 = 0;
      if (vlen < 8) {
        if (switch_expression[vlen] != b_cv[vlen]) {
          exitg1 = 1;
        } else {
          vlen++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  if (b_bool) {
    vlen = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      vlen = 0;
      do {
        exitg1 = 0;
        if (vlen < 9) {
          if (switch_expression[vlen] != ntf_cv3[vlen]) {
            exitg1 = 1;
          } else {
            vlen++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }

    if (b_bool) {
      vlen = 1;
    } else {
      b_bool = false;
      if (switch_expression.size(1) == 16) {
        vlen = 0;
        do {
          exitg1 = 0;
          if (vlen < 16) {
            if (switch_expression[vlen] != ntf_cv4[vlen]) {
              exitg1 = 1;
            } else {
              vlen++;
            }
          } else {
            b_bool = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }

      if (b_bool) {
        vlen = 2;
      } else {
        b_bool = false;
        if (switch_expression.size(1) == 7) {
          vlen = 0;
          do {
            exitg1 = 0;
            if (vlen < 7) {
              if (switch_expression[vlen] != b_cv1[vlen]) {
                exitg1 = 1;
              } else {
                vlen++;
              }
            } else {
              b_bool = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (b_bool) {
          vlen = 3;
        } else {
          b_bool = false;
          if (switch_expression.size(1) == 11) {
            vlen = 0;
            do {
              exitg1 = 0;
              if (vlen < 11) {
                if (switch_expression[vlen] != ntf_cv5[vlen]) {
                  exitg1 = 1;
                } else {
                  vlen++;
                }
              } else {
                b_bool = true;
                exitg1 = 1;
              }
            } while (exitg1 == 0);
          }

          if (b_bool) {
            vlen = 4;
          } else {
            b_bool = false;
            if (switch_expression.size(1) == 5) {
              vlen = 0;
              do {
                exitg1 = 0;
                if (vlen < 5) {
                  if (switch_expression[vlen] != b_cv2[vlen]) {
                    exitg1 = 1;
                  } else {
                    vlen++;
                  }
                } else {
                  b_bool = true;
                  exitg1 = 1;
                }
              } while (exitg1 == 0);
            }

            if (b_bool) {
              vlen = 5;
            } else {
              b_bool = false;
              if (switch_expression.size(1) == 4) {
                vlen = 0;
                do {
                  exitg1 = 0;
                  if (vlen < 4) {
                    if (switch_expression[vlen] != b_cv3[vlen]) {
                      exitg1 = 1;
                    } else {
                      vlen++;
                    }
                  } else {
                    b_bool = true;
                    exitg1 = 1;
                  }
                } while (exitg1 == 0);
              }

              if (b_bool) {
                vlen = 6;
              } else if (ntf_m_strcmp(switch_expression)) {
                vlen = 7;
              } else if (ntf_n_strcmp(switch_expression)) {
                vlen = 8;
              } else if (ntf_o_strcmp(switch_expression)) {
                vlen = 9;
              } else if (ntf_p_strcmp(switch_expression)) {
                vlen = 10;
              } else if (ntf_q_strcmp(switch_expression)) {
                vlen = 11;
              } else if (ntf_r_strcmp(switch_expression)) {
                vlen = 12;
              } else {
                b_bool = false;
                if (switch_expression.size(1) == 14) {
                  vlen = 0;
                  do {
                    exitg1 = 0;
                    if (vlen < 14) {
                      if (switch_expression[vlen] != ntf_cv1[vlen]) {
                        exitg1 = 1;
                      } else {
                        vlen++;
                      }
                    } else {
                      b_bool = true;
                      exitg1 = 1;
                    }
                  } while (exitg1 == 0);
                }

                if (b_bool) {
                  vlen = 13;
                } else {
                  b_bool = false;
                  if (switch_expression.size(1) == 16) {
                    vlen = 0;
                    do {
                      exitg1 = 0;
                      if (vlen < 16) {
                        if (switch_expression[vlen] != ntf_cv2[vlen]) {
                          exitg1 = 1;
                        } else {
                          vlen++;
                        }
                      } else {
                        b_bool = true;
                        exitg1 = 1;
                      }
                    } while (exitg1 == 0);
                  }

                  if (b_bool) {
                    vlen = 13;
                  } else if (ntf_u_strcmp(switch_expression, t3_f1)) {
                    vlen = 14;
                  } else if (ntf_v_strcmp(switch_expression, t3_f2)) {
                    vlen = 14;
                  } else if (ntf_w_strcmp(switch_expression)) {
                    vlen = 15;
                  } else if (ntf_x_strcmp(switch_expression)) {
                    vlen = 16;
                  } else if (ntf_y_strcmp(switch_expression)) {
                    vlen = 17;
                  } else {
                    vlen = -1;
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  switch (vlen) {
   case 0:
    ntf_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 1:
    for (i = 0; i < 1000; i++) {
      b_x[i] = x[i] - 1.0;
    }

    ntf_b_pdf(b_x, 1.0, this->Par[0], PDF);
    break;

   case 2:
    for (i = 0; i < 1000; i++) {
      b_x[i] = x[i] - this->Par[0];
    }

    ntf_b_pdf(b_x, this->Par[0], this->Par[1], PDF);
    break;

   case 3:
    if (this->Par[1] == 0.0) {
      ntf_c_pdf(x, this->Par[0], PDF);
    } else {
      ntf_c_pdf(x, this->Par[0] * this->Par[1], PDF);
    }
    break;

   case 4:
    xk = 1.0 / this->Par[0];
    for (k = 0; k < 1000; k++) {
      if ((xk > 0.0) && (!rtIsNaN(x[k]))) {
        if (x[k] < 0.0) {
          PDF[k] = 0.0;
        } else {
          PDF[k] = std::exp(-x[k] / xk) / xk;
        }
      } else {
        PDF[k] = rtNaN;
      }
    }
    break;

   case 5:
    ntf_d_pdf(x, this->Par[1], 1.0 / this->Par[0], PDF);
    break;

   case 6:
    //                  PDF  = pdf('beta',(x-Obj.Par(3))/(Obj.Par(4)-Obj.Par(3)),Obj.Par(1),Obj.Par(2))./(Obj.Par(4)-Obj.Par(3)); 
    xk = this->Par[3] - this->Par[2];
    for (i = 0; i < 1000; i++) {
      b_x[i] = (x[i] - this->Par[2]) / xk;
    }

    ntf_e_pdf(b_x, this->Par[0], this->Par[1], PDF);
    for (i = 0; i < 1000; i++) {
      PDF[i] /= xk;
    }

    //              case 'gumbelmin'  % this distribution can be used to model minima 
    //                  PDF  = pdf('Extreme Value',x,Obj.Par(2),Obj.Par(1));
    break;

   case 7:
    //  mirror image of this distribution can be used to model maxima
    ntf_f_pdf(x, 0.0, this->Par[0], this->Par[1], PDF);

    //             case 'frechet'
    //                 PDF  = pdf('Generalized Extreme Value',x,1/Obj.Par(2),Obj.Par(1)/Obj.Par(2),Obj.Par(1)); 
    break;

   case 8:
    ntf_g_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 9:
    ntf_f_pdf(x, this->Par[0], this->Par[1], this->Par[2], PDF);

    //              case 'gevmin'
    //                  PDF = pdf('Generalized Extreme Value',-x,Obj.Par(1),Obj.Par(2),-Obj.Par(3)); 
    //              case 'pareto'
    //                  PDF = pdf('Generalized Pareto',x,1/Obj.Par(2),Obj.Par(1)/Obj.Par(2),Obj.Par(1)); 
    break;

   case 10:
    xk = this->Par[0];
    for (k = 0; k < 1000; k++) {
      if ((xk > 0.0) && (!rtIsNaN(x[k]))) {
        if (x[k] >= 0.0) {
          PDF[k] = x[k] / (xk * xk) * std::exp(-x[k] * x[k] / (2.0 * xk * xk));
        } else {
          PDF[k] = 0.0;
        }
      } else {
        PDF[k] = rtNaN;
      }
    }
    break;

   case 11:
    ntf_d_pdf(x, this->Par[0] / 2.0, 2.0, PDF);
    break;

   case 12:
    {
      double t;
      t = this->Par[0];
      xk = this->Par[1];
      for (k = 0; k < 1000; k++) {
        if (t < xk) {
          if ((x[k] >= t) && (x[k] <= xk)) {
            PDF[k] = 1.0 / (xk - t);
          } else {
            PDF[k] = 0.0;
          }
        } else {
          PDF[k] = rtNaN;
        }
      }
    }
    break;

   case 13:
    for (k = 0; k < 1000; k++) {
      PDF[k] = std::exp(-0.5 * x[k] * x[k]) / 2.5066282746310002;
    }
    break;

   case 14:
    {
      xk = this->Par[1];
      for (k = 0; k < 1000; k++) {
        if (xk > 0.0) {
          double t;
          t = (x[k] - this->Par[0]) / xk;
          PDF[k] = std::exp(-0.5 * t * t) / (2.5066282746310002 * xk);
        } else {
          PDF[k] = rtNaN;
        }
      }
    }
    break;

   case 15:
    ntf_h_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 16:
    {
      double t;
      double CDF_min;
      xk = 1.0 / this->Par[0];
      for (k = 0; k < 1000; k++) {
        if ((xk > 0.0) && (!rtIsNaN(x[k]))) {
          if (x[k] < 0.0) {
            PDF[k] = 0.0;
          } else {
            PDF[k] = std::exp(-x[k] / xk) / xk;
          }
        } else {
          PDF[k] = rtNaN;
        }
      }

      t = 1.0 / this->Par[0];
      xk = this->Par[1];
      if ((t > 0.0) && (!rtIsNaN(this->Par[1]))) {
        if (this->Par[1] < 0.0) {
          xk = 0.0;
        }

        xk = -(xk / t);
        ntf_expm1(&xk);
        CDF_min = -xk;
      } else {
        CDF_min = rtNaN;
      }

      t = 1.0 / this->Par[0];
      xk = this->Par[2];
      if ((t > 0.0) && (!rtIsNaN(this->Par[2]))) {
        if (this->Par[2] < 0.0) {
          xk = 0.0;
        }

        xk = -(xk / t);
        ntf_expm1(&xk);
        xk = -xk;
      } else {
        xk = rtNaN;
      }

      xk -= CDF_min;
      for (i = 0; i < 1000; i++) {
        PDF[i] /= xk;
      }
    }
    break;

   case 17:
    {
      int i1;
      int i2;
      int loop_ub_tmp;
      if (1 > this->Multinomial.size(1)) {
        i = 1;
        vlen = -1;
      } else {
        i = 2;
        vlen = this->Multinomial.size(1) - 1;
      }

      if (2 > this->Multinomial.size(1)) {
        i1 = 0;
        i2 = 1;
      } else {
        i1 = 1;
        i2 = 2;
      }

      loop_ub_tmp = ntf_div_s32_floor(vlen, i);
      for (int ns = 0; ns < 1000; ns++) {
        c_x.set_size(1, (loop_ub_tmp + 1));
        for (vlen = 0; vlen <= loop_ub_tmp; vlen++) {
          c_x[vlen] = static_cast<double>(x[ns] == this->Multinomial[i * vlen]) *
            this->Multinomial[i1 + i2 * vlen];
        }

        vlen = c_x.size(1);
        if (c_x.size(1) == 0) {
          xk = 0.0;
        } else {
          xk = c_x[0];
          for (k = 2; k <= vlen; k++) {
            xk += c_x[k - 1];
          }
        }

        PDF[ns] = xk;
      }
    }
    break;
  }
}

//
// Arguments    : const double x[5000]
//                double PDF[5000]
// Return Type  : void
//
void ntf_ERADist::ntf_gb_pdf(const double x[5000], double PDF[5000]) const
{
  coder::array<char, 2U> switch_expression;
  int i;
  int k;
  boolean_T b_bool;
  int vlen;
  int exitg1;
  static const char b_cv[8] = { 'b', 'i', 'n', 'o', 'm', 'i', 'a', 'l' };

  double xk;
  double b_x[5000];
  static const char b_cv1[7] = { 'p', 'o', 'i', 's', 's', 'o', 'n' };

  coder::array<double, 2U> c_x;
  static const char b_cv2[5] = { 'g', 'a', 'm', 'm', 'a' };

  static const char b_cv3[4] = { 'b', 'e', 't', 'a' };

  static const char t5_f1[6] = { 'n', 'o', 'r', 'm', 'a', 'l' };

  static const char t5_f2[8] = { 'g', 'a', 'u', 's', 's', 'i', 'a', 'n' };

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
  //     function CDF = cdf(Obj,x)
  //        switch lower(Obj.Name)
  //           case 'geometric'
  //              CDF = Obj.Dist.cdf(x-1);
  //           case 'negativebinomial'
  //              CDF = Obj.Dist.cdf(x-Obj.Par(1));
  //           case 'beta'
  //              CDF = Obj.Dist.cdf((x-Obj.Par(3))/(Obj.Par(4)-Obj.Par(3)));
  //           case 'gumbelmin'
  //              CDF = Obj.Dist.cdf(-x);
  //           case 'gevmin'
  //              CDF = Obj.Dist.cdf(-x);
  //           otherwise
  //              CDF = Obj.Dist.cdf(x);
  //        end
  //     end
  std::memset(&PDF[0], 0, 5000U * sizeof(double));
  switch_expression.set_size(this->Name.size(0), this->Name.size(1));
  i = this->Name.size(1);
  for (k = 0; k < i; k++) {
    switch_expression[k] = ntf_cv[static_cast<unsigned char>(this->Name[k]) &
      127];
  }

  b_bool = false;
  if (switch_expression.size(1) == 8) {
    vlen = 0;
    do {
      exitg1 = 0;
      if (vlen < 8) {
        if (switch_expression[vlen] != b_cv[vlen]) {
          exitg1 = 1;
        } else {
          vlen++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  if (b_bool) {
    vlen = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      vlen = 0;
      do {
        exitg1 = 0;
        if (vlen < 9) {
          if (switch_expression[vlen] != ntf_cv3[vlen]) {
            exitg1 = 1;
          } else {
            vlen++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }

    if (b_bool) {
      vlen = 1;
    } else {
      b_bool = false;
      if (switch_expression.size(1) == 16) {
        vlen = 0;
        do {
          exitg1 = 0;
          if (vlen < 16) {
            if (switch_expression[vlen] != ntf_cv4[vlen]) {
              exitg1 = 1;
            } else {
              vlen++;
            }
          } else {
            b_bool = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }

      if (b_bool) {
        vlen = 2;
      } else {
        b_bool = false;
        if (switch_expression.size(1) == 7) {
          vlen = 0;
          do {
            exitg1 = 0;
            if (vlen < 7) {
              if (switch_expression[vlen] != b_cv1[vlen]) {
                exitg1 = 1;
              } else {
                vlen++;
              }
            } else {
              b_bool = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (b_bool) {
          vlen = 3;
        } else {
          b_bool = false;
          if (switch_expression.size(1) == 11) {
            vlen = 0;
            do {
              exitg1 = 0;
              if (vlen < 11) {
                if (switch_expression[vlen] != ntf_cv5[vlen]) {
                  exitg1 = 1;
                } else {
                  vlen++;
                }
              } else {
                b_bool = true;
                exitg1 = 1;
              }
            } while (exitg1 == 0);
          }

          if (b_bool) {
            vlen = 4;
          } else {
            b_bool = false;
            if (switch_expression.size(1) == 5) {
              vlen = 0;
              do {
                exitg1 = 0;
                if (vlen < 5) {
                  if (switch_expression[vlen] != b_cv2[vlen]) {
                    exitg1 = 1;
                  } else {
                    vlen++;
                  }
                } else {
                  b_bool = true;
                  exitg1 = 1;
                }
              } while (exitg1 == 0);
            }

            if (b_bool) {
              vlen = 5;
            } else {
              b_bool = false;
              if (switch_expression.size(1) == 4) {
                vlen = 0;
                do {
                  exitg1 = 0;
                  if (vlen < 4) {
                    if (switch_expression[vlen] != b_cv3[vlen]) {
                      exitg1 = 1;
                    } else {
                      vlen++;
                    }
                  } else {
                    b_bool = true;
                    exitg1 = 1;
                  }
                } while (exitg1 == 0);
              }

              if (b_bool) {
                vlen = 6;
              } else if (ntf_m_strcmp(switch_expression)) {
                vlen = 7;
              } else if (ntf_n_strcmp(switch_expression)) {
                vlen = 8;
              } else if (ntf_o_strcmp(switch_expression)) {
                vlen = 9;
              } else if (ntf_p_strcmp(switch_expression)) {
                vlen = 10;
              } else if (ntf_q_strcmp(switch_expression)) {
                vlen = 11;
              } else if (ntf_r_strcmp(switch_expression)) {
                vlen = 12;
              } else {
                b_bool = false;
                if (switch_expression.size(1) == 14) {
                  vlen = 0;
                  do {
                    exitg1 = 0;
                    if (vlen < 14) {
                      if (switch_expression[vlen] != ntf_cv1[vlen]) {
                        exitg1 = 1;
                      } else {
                        vlen++;
                      }
                    } else {
                      b_bool = true;
                      exitg1 = 1;
                    }
                  } while (exitg1 == 0);
                }

                if (b_bool) {
                  vlen = 13;
                } else {
                  b_bool = false;
                  if (switch_expression.size(1) == 16) {
                    vlen = 0;
                    do {
                      exitg1 = 0;
                      if (vlen < 16) {
                        if (switch_expression[vlen] != ntf_cv2[vlen]) {
                          exitg1 = 1;
                        } else {
                          vlen++;
                        }
                      } else {
                        b_bool = true;
                        exitg1 = 1;
                      }
                    } while (exitg1 == 0);
                  }

                  if (b_bool) {
                    vlen = 13;
                  } else if (ntf_u_strcmp(switch_expression, t5_f1)) {
                    vlen = 14;
                  } else if (ntf_v_strcmp(switch_expression, t5_f2)) {
                    vlen = 14;
                  } else if (ntf_w_strcmp(switch_expression)) {
                    vlen = 15;
                  } else if (ntf_x_strcmp(switch_expression)) {
                    vlen = 16;
                  } else if (ntf_y_strcmp(switch_expression)) {
                    vlen = 17;
                  } else {
                    vlen = -1;
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  switch (vlen) {
   case 0:
    ntf_i_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 1:
    for (i = 0; i < 5000; i++) {
      b_x[i] = x[i] - 1.0;
    }

    ntf_j_pdf(b_x, 1.0, this->Par[0], PDF);
    break;

   case 2:
    for (i = 0; i < 5000; i++) {
      b_x[i] = x[i] - this->Par[0];
    }

    ntf_j_pdf(b_x, this->Par[0], this->Par[1], PDF);
    break;

   case 3:
    if (this->Par[1] == 0.0) {
      ntf_k_pdf(x, this->Par[0], PDF);
    } else {
      ntf_k_pdf(x, this->Par[0] * this->Par[1], PDF);
    }
    break;

   case 4:
    xk = 1.0 / this->Par[0];
    for (k = 0; k < 5000; k++) {
      if ((xk > 0.0) && (!rtIsNaN(x[k]))) {
        if (x[k] < 0.0) {
          PDF[k] = 0.0;
        } else {
          PDF[k] = std::exp(-x[k] / xk) / xk;
        }
      } else {
        PDF[k] = rtNaN;
      }
    }
    break;

   case 5:
    ntf_l_pdf(x, this->Par[1], 1.0 / this->Par[0], PDF);
    break;

   case 6:
    //                  PDF  = pdf('beta',(x-Obj.Par(3))/(Obj.Par(4)-Obj.Par(3)),Obj.Par(1),Obj.Par(2))./(Obj.Par(4)-Obj.Par(3)); 
    for (i = 0; i < 5000; i++) {
      b_x[i] = (x[i] - this->Par[2]) / (0.0 - this->Par[2]);
    }

    ntf_m_pdf(b_x, this->Par[0], this->Par[1], PDF);
    for (i = 0; i < 5000; i++) {
      PDF[i] /= 0.0 - this->Par[2];
    }

    //              case 'gumbelmin'  % this distribution can be used to model minima 
    //                  PDF  = pdf('Extreme Value',x,Obj.Par(2),Obj.Par(1));
    break;

   case 7:
    //  mirror image of this distribution can be used to model maxima
    ntf_n_pdf(x, 0.0, this->Par[0], this->Par[1], PDF);

    //             case 'frechet'
    //                 PDF  = pdf('Generalized Extreme Value',x,1/Obj.Par(2),Obj.Par(1)/Obj.Par(2),Obj.Par(1)); 
    break;

   case 8:
    ntf_o_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 9:
    ntf_n_pdf(x, this->Par[0], this->Par[1], this->Par[2], PDF);

    //              case 'gevmin'
    //                  PDF = pdf('Generalized Extreme Value',-x,Obj.Par(1),Obj.Par(2),-Obj.Par(3)); 
    //              case 'pareto'
    //                  PDF = pdf('Generalized Pareto',x,1/Obj.Par(2),Obj.Par(1)/Obj.Par(2),Obj.Par(1)); 
    break;

   case 10:
    xk = this->Par[0];
    for (k = 0; k < 5000; k++) {
      if ((xk > 0.0) && (!rtIsNaN(x[k]))) {
        if (x[k] >= 0.0) {
          PDF[k] = x[k] / (xk * xk) * std::exp(-x[k] * x[k] / (2.0 * xk * xk));
        } else {
          PDF[k] = 0.0;
        }
      } else {
        PDF[k] = rtNaN;
      }
    }
    break;

   case 11:
    ntf_l_pdf(x, this->Par[0] / 2.0, 2.0, PDF);
    break;

   case 12:
    {
      double t;
      t = this->Par[0];
      xk = this->Par[1];
      for (k = 0; k < 5000; k++) {
        if (t < xk) {
          if ((x[k] >= t) && (x[k] <= xk)) {
            PDF[k] = 1.0 / (xk - t);
          } else {
            PDF[k] = 0.0;
          }
        } else {
          PDF[k] = rtNaN;
        }
      }
    }
    break;

   case 13:
    for (k = 0; k < 5000; k++) {
      PDF[k] = std::exp(-0.5 * x[k] * x[k]) / 2.5066282746310002;
    }
    break;

   case 14:
    {
      xk = this->Par[1];
      for (k = 0; k < 5000; k++) {
        if (xk > 0.0) {
          double t;
          t = (x[k] - this->Par[0]) / xk;
          PDF[k] = std::exp(-0.5 * t * t) / (2.5066282746310002 * xk);
        } else {
          PDF[k] = rtNaN;
        }
      }
    }
    break;

   case 15:
    ntf_p_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 16:
    {
      double t;
      double CDF_min;
      xk = 1.0 / this->Par[0];
      for (k = 0; k < 5000; k++) {
        if ((xk > 0.0) && (!rtIsNaN(x[k]))) {
          if (x[k] < 0.0) {
            PDF[k] = 0.0;
          } else {
            PDF[k] = std::exp(-x[k] / xk) / xk;
          }
        } else {
          PDF[k] = rtNaN;
        }
      }

      t = 1.0 / this->Par[0];
      xk = this->Par[1];
      if ((t > 0.0) && (!rtIsNaN(this->Par[1]))) {
        if (this->Par[1] < 0.0) {
          xk = 0.0;
        }

        xk = -(xk / t);
        ntf_expm1(&xk);
        CDF_min = -xk;
      } else {
        CDF_min = rtNaN;
      }

      t = 1.0 / this->Par[0];
      xk = this->Par[2];
      if ((t > 0.0) && (!rtIsNaN(this->Par[2]))) {
        if (this->Par[2] < 0.0) {
          xk = 0.0;
        }

        xk = -(xk / t);
        ntf_expm1(&xk);
        xk = -xk;
      } else {
        xk = rtNaN;
      }

      xk -= CDF_min;
      for (i = 0; i < 5000; i++) {
        PDF[i] /= xk;
      }
    }
    break;

   case 17:
    {
      int i1;
      int i2;
      int loop_ub_tmp;
      if (1 > this->Multinomial.size(1)) {
        i = 1;
        vlen = -1;
      } else {
        i = 2;
        vlen = this->Multinomial.size(1) - 1;
      }

      if (2 > this->Multinomial.size(1)) {
        i1 = 0;
        i2 = 1;
      } else {
        i1 = 1;
        i2 = 2;
      }

      loop_ub_tmp = ntf_div_s32_floor(vlen, i);
      for (int ns = 0; ns < 5000; ns++) {
        c_x.set_size(1, (loop_ub_tmp + 1));
        for (vlen = 0; vlen <= loop_ub_tmp; vlen++) {
          c_x[vlen] = static_cast<double>(x[ns] == this->Multinomial[i * vlen]) *
            this->Multinomial[i1 + i2 * vlen];
        }

        vlen = c_x.size(1);
        if (c_x.size(1) == 0) {
          xk = 0.0;
        } else {
          xk = c_x[0];
          for (k = 2; k <= vlen; k++) {
            xk += c_x[k - 1];
          }
        }

        PDF[ns] = xk;
      }
    }
    break;
  }
}

//
// Arguments    : int numerator
//                int denominator
// Return Type  : int
//
static int ntf_div_s32_floor(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    unsigned int absDenominator;
    boolean_T quotientNeedsNegation;
    unsigned int tempAbsQuotient;
    if (numerator < 0) {
      absNumerator = ~static_cast<unsigned int>(numerator) + 1U;
    } else {
      absNumerator = static_cast<unsigned int>(numerator);
    }

    if (denominator < 0) {
      absDenominator = ~static_cast<unsigned int>(denominator) + 1U;
    } else {
      absDenominator = static_cast<unsigned int>(denominator);
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }

      quotient = -static_cast<int>(tempAbsQuotient);
    } else {
      quotient = static_cast<int>(tempAbsQuotient);
    }
  }

  return quotient;
}

//
// Arguments    : double u
// Return Type  : double
//
static double ntf_rt_roundd_snf(double u)
{
  double y;
  if (std::abs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = std::floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = std::ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

//
// Arguments    : const coder::array<double, 1U> &val
//                const double b[3]
// Return Type  : double
//
double ntf_ERADist::ntf___anon_fcn(const coder::array<double, 1U> &val, const
  double b[3])
{
  double varargout_1;
  double sigma;
  coder::array<double, 1U> z;
  int nx;
  int i;
  coder::array<double, 1U> u;
  double absz;
  sigma = std::exp(b[1]);
  z.set_size(val.size(0));
  nx = val.size(0);
  for (i = 0; i < nx; i++) {
    z[i] = (val[i] - b[2]) / sigma;
  }

  if (std::abs(b[0]) > 2.2204460492503131E-16) {
    int k;
    int n;
    nx = z.size(0);
    for (i = 0; i < nx; i++) {
      z[i] = b[0] * z[i];
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
      sigma = -(1.0 / b[0]);
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

      varargout_1 = (static_cast<double>(val.size(0)) * b[1] + sigma) + (1.0 /
        b[0] + 1.0) * absz;
    } else {
      varargout_1 = rtInf;
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

    varargout_1 = static_cast<double>(val.size(0)) * b[1] + sigma;
  }

  return varargout_1;
}

//
// Arguments    : const coder::array<double, 2U> &p
//                coder::array<double, 2U> &InverseCDF
// Return Type  : void
//
void ntf_ERADist::ntf_cb_icdf(const coder::array<double, 2U> &p, coder::array<
  double, 2U> &InverseCDF) const
{
  unsigned int unnamed_idx_1;
  int loop_ub;
  int i;
  coder::array<char, 2U> switch_expression;
  boolean_T b_bool;
  int exitg1;
  static const char b_cv[8] = { 'b', 'i', 'n', 'o', 'm', 'i', 'a', 'l' };

  double maxpf;
  coder::array<double, 2U> xvals_temp;
  static const char b_cv1[7] = { 'p', 'o', 'i', 's', 's', 'o', 'n' };

  coder::array<int, 2U> iidx;
  coder::array<double, 2U> pvals;
  static const char b_cv2[5] = { 'g', 'a', 'm', 'm', 'a' };

  coder::array<boolean_T, 2U> x;
  int ii_data_idx_0;
  static const char t13_f2[8] = { 'g', 'a', 'u', 's', 's', 'i', 'a', 'n' };

  static const char t13_f1[6] = { 'n', 'o', 'r', 'm', 'a', 'l' };

  // -----------------------------------------------------------------------
  //     function PDF = pdf(Obj,x)
  //        switch lower(Obj.Name)
  //           case 'geometric'
  //              PDF = Obj.Dist.pdf(x-1);
  //           case 'negativebinomial'
  //              PDF = Obj.Dist.pdf(x-Obj.Par(1));
  //           case 'beta'
  //              PDF = Obj.Dist.pdf((x-Obj.Par(3))/(Obj.Par(4)-Obj.Par(3)));
  //           case 'gumbelmin'
  //              PDF = Obj.Dist.pdf(-x);
  //           case 'gevmin'
  //              PDF = Obj.Dist.pdf(-x);
  //           otherwise
  //              PDF = Obj.Dist.pdf(x);
  //        end
  //     end
  // -----------------------------------------------------------------------
  unnamed_idx_1 = static_cast<unsigned int>(p.size(1));
  InverseCDF.set_size(1, (static_cast<int>(unnamed_idx_1)));
  loop_ub = static_cast<int>(unnamed_idx_1);
  for (i = 0; i < loop_ub; i++) {
    InverseCDF[i] = 0.0;
  }

  // InverseCDF = icdf('binomial',p,Obj.Par(1),Obj.Par(2));
  switch_expression.set_size(this->Name.size(0), this->Name.size(1));
  i = this->Name.size(1);
  for (loop_ub = 0; loop_ub < i; loop_ub++) {
    switch_expression[loop_ub] = ntf_cv[static_cast<unsigned char>(this->
      Name[loop_ub]) & 127];
  }

  b_bool = false;
  if (switch_expression.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (switch_expression[loop_ub] != b_cv[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  if (b_bool) {
    loop_ub = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (switch_expression[loop_ub] != ntf_cv3[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }

    if (b_bool) {
      loop_ub = 1;
    } else {
      b_bool = false;
      if (switch_expression.size(1) == 16) {
        loop_ub = 0;
        do {
          exitg1 = 0;
          if (loop_ub < 16) {
            if (switch_expression[loop_ub] != ntf_cv4[loop_ub]) {
              exitg1 = 1;
            } else {
              loop_ub++;
            }
          } else {
            b_bool = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }

      if (b_bool) {
        loop_ub = 2;
      } else {
        b_bool = false;
        if (switch_expression.size(1) == 7) {
          loop_ub = 0;
          do {
            exitg1 = 0;
            if (loop_ub < 7) {
              if (switch_expression[loop_ub] != b_cv1[loop_ub]) {
                exitg1 = 1;
              } else {
                loop_ub++;
              }
            } else {
              b_bool = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (b_bool) {
          loop_ub = 3;
        } else {
          b_bool = false;
          if (switch_expression.size(1) == 11) {
            loop_ub = 0;
            do {
              exitg1 = 0;
              if (loop_ub < 11) {
                if (switch_expression[loop_ub] != ntf_cv5[loop_ub]) {
                  exitg1 = 1;
                } else {
                  loop_ub++;
                }
              } else {
                b_bool = true;
                exitg1 = 1;
              }
            } while (exitg1 == 0);
          }

          if (b_bool) {
            loop_ub = 4;
          } else {
            b_bool = false;
            if (switch_expression.size(1) == 5) {
              loop_ub = 0;
              do {
                exitg1 = 0;
                if (loop_ub < 5) {
                  if (switch_expression[loop_ub] != b_cv2[loop_ub]) {
                    exitg1 = 1;
                  } else {
                    loop_ub++;
                  }
                } else {
                  b_bool = true;
                  exitg1 = 1;
                }
              } while (exitg1 == 0);
            }

            if (b_bool) {
              loop_ub = 5;
            } else if (ntf_l_strcmp(switch_expression)) {
              loop_ub = 6;
            } else if (ntf_m_strcmp(switch_expression)) {
              loop_ub = 7;
            } else if (ntf_n_strcmp(switch_expression)) {
              loop_ub = 8;
            } else if (ntf_o_strcmp(switch_expression)) {
              loop_ub = 9;
            } else if (ntf_p_strcmp(switch_expression)) {
              loop_ub = 10;
            } else if (ntf_q_strcmp(switch_expression)) {
              loop_ub = 11;
            } else if (ntf_r_strcmp(switch_expression)) {
              loop_ub = 12;
            } else {
              b_bool = false;
              if (switch_expression.size(1) == 14) {
                loop_ub = 0;
                do {
                  exitg1 = 0;
                  if (loop_ub < 14) {
                    if (switch_expression[loop_ub] != ntf_cv1[loop_ub]) {
                      exitg1 = 1;
                    } else {
                      loop_ub++;
                    }
                  } else {
                    b_bool = true;
                    exitg1 = 1;
                  }
                } while (exitg1 == 0);
              }

              if (b_bool) {
                loop_ub = 13;
              } else {
                b_bool = false;
                if (switch_expression.size(1) == 16) {
                  loop_ub = 0;
                  do {
                    exitg1 = 0;
                    if (loop_ub < 16) {
                      if (switch_expression[loop_ub] != ntf_cv2[loop_ub]) {
                        exitg1 = 1;
                      } else {
                        loop_ub++;
                      }
                    } else {
                      b_bool = true;
                      exitg1 = 1;
                    }
                  } while (exitg1 == 0);
                }

                if (b_bool) {
                  loop_ub = 13;
                } else {
                  b_bool = false;
                  if (switch_expression.size(1) == 6) {
                    loop_ub = 0;
                    do {
                      exitg1 = 0;
                      if (loop_ub < 6) {
                        if (switch_expression[loop_ub] != t13_f1[loop_ub]) {
                          exitg1 = 1;
                        } else {
                          loop_ub++;
                        }
                      } else {
                        b_bool = true;
                        exitg1 = 1;
                      }
                    } while (exitg1 == 0);
                  }

                  if (b_bool) {
                    loop_ub = 14;
                  } else if (ntf_v_strcmp(switch_expression, t13_f2)) {
                    loop_ub = 14;
                  } else if (ntf_w_strcmp(switch_expression)) {
                    loop_ub = 15;
                  } else if (ntf_x_strcmp(switch_expression)) {
                    loop_ub = 16;
                  } else if (ntf_y_strcmp(switch_expression)) {
                    loop_ub = 17;
                  } else {
                    loop_ub = -1;
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  switch (loop_ub) {
   case 0:
    ntf_l_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 1:
    ntf_m_icdf(p, this->Par[0], InverseCDF);
    i = InverseCDF.size(0) * InverseCDF.size(1);
    InverseCDF.set_size(1, InverseCDF.size(1));
    loop_ub = i - 1;
    for (i = 0; i <= loop_ub; i++) {
      InverseCDF[i] = InverseCDF[i] + 1.0;
    }
    break;

   case 2:
    ntf_n_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    i = InverseCDF.size(0) * InverseCDF.size(1);
    InverseCDF.set_size(1, InverseCDF.size(1));
    loop_ub = i - 1;
    for (i = 0; i <= loop_ub; i++) {
      InverseCDF[i] = InverseCDF[i] + this->Par[0];
    }
    break;

   case 3:
    if (this->Par[1] == 0.0) {
      ntf_o_icdf(p, this->Par[0], InverseCDF);
    } else {
      ntf_o_icdf(p, this->Par[0] * this->Par[1], InverseCDF);
    }
    break;

   case 4:
    ntf_p_icdf(p, 1.0 / this->Par[0], InverseCDF);
    break;

   case 5:
    ntf_q_icdf(p, this->Par[1], 1.0 / this->Par[0], InverseCDF);
    break;

   case 6:
    ntf_r_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    maxpf = this->Par[3] - this->Par[2];
    i = InverseCDF.size(0) * InverseCDF.size(1);
    InverseCDF.set_size(1, InverseCDF.size(1));
    loop_ub = i - 1;
    for (i = 0; i <= loop_ub; i++) {
      InverseCDF[i] = InverseCDF[i] * maxpf + this->Par[2];
    }

    //              case 'gumbelmin'  % this distribution can be used to model minima 
    // InverseCDF  = -icdf('Generalized Extreme Value',p,0,Obj.Par(1),-Obj.Par(2)); 
    // InverseCDF  = -icdf('Generalized Extreme Value',p,0,Obj.Par(1),-Obj.Par(2)); 
    //  InverseCDF  = icdf('Extreme Value',p,Obj.Par(2),Obj.Par(1));
    break;

   case 7:
    //  mirror image of this distribution can be used to model maxima
    ntf_s_icdf(p, this->Par[0], this->Par[1], InverseCDF);

    //             case 'frechet'
    //                 InverseCDF  = icdf('Generalized Extreme Value',p,1/Obj.Par(2),Obj.Par(1)/Obj.Par(2),Obj.Par(1)); 
    break;

   case 8:
    ntf_t_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 9:
    ntf_u_icdf(p, this->Par[0], this->Par[1], this->Par[2], InverseCDF);

    //              case 'gevmin'
    //                  InverseCDF = -icdf('Generalized Extreme Value',p,Obj.Par(1),Obj.Par(2),-Obj.Par(3)); 
    //              case 'pareto'
    //                  InverseCDF = icdf('Generalized Pareto',p,1/Obj.Par(2),Obj.Par(1)/Obj.Par(2),Obj.Par(1)); 
    break;

   case 10:
    ntf_v_icdf(p, this->Par[0], InverseCDF);
    break;

   case 11:
    ntf_w_icdf(p, this->Par[0] / 2.0, InverseCDF);
    break;

   case 12:
    ntf_x_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 13:
    ntf_y_icdf(p, InverseCDF);
    break;

   case 14:
    ntf_ab_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 15:
    ntf_bb_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 16:
    {
      double xk;
      double minpf;

      // InverseCDF_temp = icdf('exponential',p,1/Obj.Par(1));
      maxpf = 1.0 / this->Par[0];
      xk = this->Par[1];
      if ((maxpf > 0.0) && (!rtIsNaN(this->Par[1]))) {
        if (this->Par[1] < 0.0) {
          xk = 0.0;
        }

        maxpf = -(xk / maxpf);
        ntf_expm1(&maxpf);
        minpf = -maxpf;
      } else {
        minpf = rtNaN;
      }

      maxpf = 1.0 / this->Par[0];
      xk = this->Par[2];
      if ((maxpf > 0.0) && (!rtIsNaN(this->Par[2]))) {
        if (this->Par[2] < 0.0) {
          xk = 0.0;
        }

        maxpf = -(xk / maxpf);
        ntf_expm1(&maxpf);
        maxpf = -maxpf;
      } else {
        maxpf = rtNaN;
      }

      maxpf -= minpf;

      // InverseCDF=InverseCDF_temp(minpf + p*(maxpf-minpf));
      xvals_temp.set_size(1, p.size(1));
      loop_ub = p.size(0) * p.size(1);
      for (i = 0; i < loop_ub; i++) {
        xvals_temp[i] = minpf + p[i] * maxpf;
      }

      ntf_p_icdf(xvals_temp, 1.0 / this->Par[0], InverseCDF);
    }
    break;

   case 17:
    {
      int i1;
      int ns;
      int i2;
      if (2 > this->Multinomial.size(1)) {
        i = 0;
        i1 = 1;
      } else {
        i = 1;
        i1 = 2;
      }

      if (1 > this->Multinomial.size(1)) {
        ns = 1;
        i2 = -1;
      } else {
        ns = 2;
        i2 = this->Multinomial.size(1) - 1;
      }

      loop_ub = ntf_div_s32_floor(i2, ns);
      xvals_temp.set_size(1, (loop_ub + 1));
      for (i2 = 0; i2 <= loop_ub; i2++) {
        xvals_temp[i2] = this->Multinomial[ns * i2];
      }

      ntf_b_sort(xvals_temp, iidx);
      pvals.set_size(1, iidx.size(1));
      loop_ub = iidx.size(1);
      for (ns = 0; ns < loop_ub; ns++) {
        pvals[ns] = this->Multinomial[i + i1 * (iidx[ns] - 1)];
      }

      if ((iidx.size(1) != 0) && (iidx.size(1) != 1)) {
        i = iidx.size(1);
        for (loop_ub = 0; loop_ub <= i - 2; loop_ub++) {
          pvals[loop_ub + 1] = pvals[loop_ub] + pvals[loop_ub + 1];
        }
      }

      i = p.size(1);
      for (ns = 0; ns < i; ns++) {
        boolean_T exitg2;
        x.set_size(1, pvals.size(1));
        maxpf = p[ns];
        loop_ub = pvals.size(0) * pvals.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
          x[i1] = (pvals[i1] - maxpf >= 0.0);
        }

        loop_ub = 0;
        exitg2 = false;
        while ((!exitg2) && (loop_ub <= x.size(1) - 1)) {
          if (x[loop_ub]) {
            ii_data_idx_0 = loop_ub + 1;
            exitg2 = true;
          } else {
            loop_ub++;
          }
        }

        InverseCDF[ns] = xvals_temp[ii_data_idx_0 - 1];
      }
    }
    break;
  }

  // {
  // alternative way for creating ERADist Objects
  // methods(Static)
  //    function Obj = normal(mean, std)
  //        Obj = ERADist("normal", "PAR", [mean,std]);
  //    end
  //
  //    function Obj = lognormal_PAR(mu_lnX, signma_lnX)
  //        Obj = ERADist("lognormal", "PAR", [mu_lnX, signma_lnX]);
  //    end
  //
  //    function Obj = lognormal_MOM(mean, std)
  //        Obj = ERADist("lognormal", "MOM", [mean, std]);
  //    end
  //
  //    function Obj = exponential_PAR(lambda)
  //        Obj = ERADist('exponential','PAR',[lambda]);
  //    end
  //
  //    function Obj = exponential_MOM(mean)
  //        Obj = ERADist('exponential','MOM',[mean]);
  //    end
  //
  // end
  // }
}

//
// Arguments    : const double p[1048576]
//                double InverseCDF[1048576]
// Return Type  : void
//
void ntf_ERADist::ntf_cb_icdf(const double p[1048576], double InverseCDF[1048576])
  const
{
  coder::array<char, 2U> switch_expression;
  int i;
  int k;
  boolean_T b_bool;
  int exitg1;
  static const char b_cv[8] = { 'b', 'i', 'n', 'o', 'm', 'i', 'a', 'l' };

  double maxpf;
  coder::array<double, 2U> xvals_temp;
  static const char b_cv1[7] = { 'p', 'o', 'i', 's', 's', 'o', 'n' };

  coder::array<int, 2U> iidx;
  coder::array<double, 2U> pvals;
  static double b_minpf[1048576];
  static const char b_cv2[5] = { 'g', 'a', 'm', 'm', 'a' };

  coder::array<boolean_T, 2U> x;
  static const char b_cv3[4] = { 'b', 'e', 't', 'a' };

  static const char b_cv4[6] = { 'g', 'u', 'm', 'b', 'e', 'l' };

  int ii_data_idx_0;
  static const char t1_f1[6] = { 'n', 'o', 'r', 'm', 'a', 'l' };

  static const char t1_f2[8] = { 'g', 'a', 'u', 's', 's', 'i', 'a', 'n' };

  // -----------------------------------------------------------------------
  //     function PDF = pdf(Obj,x)
  //        switch lower(Obj.Name)
  //           case 'geometric'
  //              PDF = Obj.Dist.pdf(x-1);
  //           case 'negativebinomial'
  //              PDF = Obj.Dist.pdf(x-Obj.Par(1));
  //           case 'beta'
  //              PDF = Obj.Dist.pdf((x-Obj.Par(3))/(Obj.Par(4)-Obj.Par(3)));
  //           case 'gumbelmin'
  //              PDF = Obj.Dist.pdf(-x);
  //           case 'gevmin'
  //              PDF = Obj.Dist.pdf(-x);
  //           otherwise
  //              PDF = Obj.Dist.pdf(x);
  //        end
  //     end
  // -----------------------------------------------------------------------
  std::memset(&InverseCDF[0], 0, 1048576U * sizeof(double));

  // InverseCDF = icdf('binomial',p,Obj.Par(1),Obj.Par(2));
  switch_expression.set_size(this->Name.size(0), this->Name.size(1));
  i = this->Name.size(1);
  for (k = 0; k < i; k++) {
    switch_expression[k] = ntf_cv[static_cast<unsigned char>(this->Name[k]) &
      127];
  }

  b_bool = false;
  if (switch_expression.size(1) == 8) {
    k = 0;
    do {
      exitg1 = 0;
      if (k < 8) {
        if (switch_expression[k] != b_cv[k]) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  if (b_bool) {
    k = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      k = 0;
      do {
        exitg1 = 0;
        if (k < 9) {
          if (switch_expression[k] != ntf_cv3[k]) {
            exitg1 = 1;
          } else {
            k++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }

    if (b_bool) {
      k = 1;
    } else {
      b_bool = false;
      if (switch_expression.size(1) == 16) {
        k = 0;
        do {
          exitg1 = 0;
          if (k < 16) {
            if (switch_expression[k] != ntf_cv4[k]) {
              exitg1 = 1;
            } else {
              k++;
            }
          } else {
            b_bool = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }

      if (b_bool) {
        k = 2;
      } else {
        b_bool = false;
        if (switch_expression.size(1) == 7) {
          k = 0;
          do {
            exitg1 = 0;
            if (k < 7) {
              if (switch_expression[k] != b_cv1[k]) {
                exitg1 = 1;
              } else {
                k++;
              }
            } else {
              b_bool = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (b_bool) {
          k = 3;
        } else {
          b_bool = false;
          if (switch_expression.size(1) == 11) {
            k = 0;
            do {
              exitg1 = 0;
              if (k < 11) {
                if (switch_expression[k] != ntf_cv5[k]) {
                  exitg1 = 1;
                } else {
                  k++;
                }
              } else {
                b_bool = true;
                exitg1 = 1;
              }
            } while (exitg1 == 0);
          }

          if (b_bool) {
            k = 4;
          } else {
            b_bool = false;
            if (switch_expression.size(1) == 5) {
              k = 0;
              do {
                exitg1 = 0;
                if (k < 5) {
                  if (switch_expression[k] != b_cv2[k]) {
                    exitg1 = 1;
                  } else {
                    k++;
                  }
                } else {
                  b_bool = true;
                  exitg1 = 1;
                }
              } while (exitg1 == 0);
            }

            if (b_bool) {
              k = 5;
            } else {
              b_bool = false;
              if (switch_expression.size(1) == 4) {
                k = 0;
                do {
                  exitg1 = 0;
                  if (k < 4) {
                    if (switch_expression[k] != b_cv3[k]) {
                      exitg1 = 1;
                    } else {
                      k++;
                    }
                  } else {
                    b_bool = true;
                    exitg1 = 1;
                  }
                } while (exitg1 == 0);
              }

              if (b_bool) {
                k = 6;
              } else {
                b_bool = false;
                if (switch_expression.size(1) == 6) {
                  k = 0;
                  do {
                    exitg1 = 0;
                    if (k < 6) {
                      if (switch_expression[k] != b_cv4[k]) {
                        exitg1 = 1;
                      } else {
                        k++;
                      }
                    } else {
                      b_bool = true;
                      exitg1 = 1;
                    }
                  } while (exitg1 == 0);
                }

                if (b_bool) {
                  k = 7;
                } else if (ntf_n_strcmp(switch_expression)) {
                  k = 8;
                } else if (ntf_o_strcmp(switch_expression)) {
                  k = 9;
                } else if (ntf_p_strcmp(switch_expression)) {
                  k = 10;
                } else if (ntf_q_strcmp(switch_expression)) {
                  k = 11;
                } else if (ntf_r_strcmp(switch_expression)) {
                  k = 12;
                } else {
                  b_bool = false;
                  if (switch_expression.size(1) == 14) {
                    k = 0;
                    do {
                      exitg1 = 0;
                      if (k < 14) {
                        if (switch_expression[k] != ntf_cv1[k]) {
                          exitg1 = 1;
                        } else {
                          k++;
                        }
                      } else {
                        b_bool = true;
                        exitg1 = 1;
                      }
                    } while (exitg1 == 0);
                  }

                  if (b_bool) {
                    k = 13;
                  } else {
                    b_bool = false;
                    if (switch_expression.size(1) == 16) {
                      k = 0;
                      do {
                        exitg1 = 0;
                        if (k < 16) {
                          if (switch_expression[k] != ntf_cv2[k]) {
                            exitg1 = 1;
                          } else {
                            k++;
                          }
                        } else {
                          b_bool = true;
                          exitg1 = 1;
                        }
                      } while (exitg1 == 0);
                    }

                    if (b_bool) {
                      k = 13;
                    } else if (ntf_u_strcmp(switch_expression, t1_f1)) {
                      k = 14;
                    } else if (ntf_v_strcmp(switch_expression, t1_f2)) {
                      k = 14;
                    } else if (ntf_w_strcmp(switch_expression)) {
                      k = 15;
                    } else if (ntf_x_strcmp(switch_expression)) {
                      k = 16;
                    } else if (ntf_y_strcmp(switch_expression)) {
                      k = 17;
                    } else {
                      k = -1;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  switch (k) {
   case 0:
    ntf_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 1:
    ntf_b_icdf(p, 1.0, this->Par[0], InverseCDF);
    for (i = 0; i < 1048576; i++) {
      InverseCDF[i]++;
    }
    break;

   case 2:
    ntf_b_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    for (i = 0; i < 1048576; i++) {
      InverseCDF[i] += this->Par[0];
    }
    break;

   case 3:
    if (this->Par[1] == 0.0) {
      ntf_c_icdf(p, this->Par[0], InverseCDF);
    } else {
      ntf_c_icdf(p, this->Par[0] * this->Par[1], InverseCDF);
    }
    break;

   case 4:
    ntf_d_icdf(p, 1.0 / this->Par[0], InverseCDF);
    break;

   case 5:
    ntf_e_icdf(p, this->Par[1], 1.0 / this->Par[0], InverseCDF);
    break;

   case 6:
    {
      double xk;
      xk = this->Par[3] - this->Par[2];
      ntf_f_icdf(p, this->Par[0], this->Par[1], InverseCDF);
      for (i = 0; i < 1048576; i++) {
        InverseCDF[i] = InverseCDF[i] * xk + this->Par[2];
      }

      //              case 'gumbelmin'  % this distribution can be used to model minima 
      // InverseCDF  = -icdf('Generalized Extreme Value',p,0,Obj.Par(1),-Obj.Par(2)); 
      // InverseCDF  = -icdf('Generalized Extreme Value',p,0,Obj.Par(1),-Obj.Par(2)); 
      //  InverseCDF  = icdf('Extreme Value',p,Obj.Par(2),Obj.Par(1));
    }
    break;

   case 7:
    //  mirror image of this distribution can be used to model maxima
    ntf_g_icdf(p, 0.0, this->Par[0], this->Par[1], InverseCDF);

    //             case 'frechet'
    //                 InverseCDF  = icdf('Generalized Extreme Value',p,1/Obj.Par(2),Obj.Par(1)/Obj.Par(2),Obj.Par(1)); 
    break;

   case 8:
    ntf_h_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 9:
    ntf_g_icdf(p, this->Par[0], this->Par[1], this->Par[2], InverseCDF);

    //              case 'gevmin'
    //                  InverseCDF = -icdf('Generalized Extreme Value',p,Obj.Par(1),Obj.Par(2),-Obj.Par(3)); 
    //              case 'pareto'
    //                  InverseCDF = icdf('Generalized Pareto',p,1/Obj.Par(2),Obj.Par(1)/Obj.Par(2),Obj.Par(1)); 
    break;

   case 10:
    ntf_i_icdf(p, this->Par[0], InverseCDF);
    break;

   case 11:
    ntf_e_icdf(p, this->Par[0] / 2.0, 2.0, InverseCDF);
    break;

   case 12:
    {
      double xk;
      maxpf = this->Par[0];
      xk = this->Par[1];
      for (k = 0; k < 1048576; k++) {
        if ((maxpf < xk) && (0.0 <= p[k]) && (p[k] <= 1.0)) {
          InverseCDF[k] = maxpf + p[k] * (xk - maxpf);
        } else {
          InverseCDF[k] = rtNaN;
        }
      }
    }
    break;

   case 13:
    ntf_j_icdf(p, 0.0, 1.0, InverseCDF);
    break;

   case 14:
    ntf_j_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 15:
    ntf_k_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 16:
    {
      double xk;
      double minpf;

      // InverseCDF_temp = icdf('exponential',p,1/Obj.Par(1));
      maxpf = 1.0 / this->Par[0];
      xk = this->Par[1];
      if ((maxpf > 0.0) && (!rtIsNaN(this->Par[1]))) {
        if (this->Par[1] < 0.0) {
          xk = 0.0;
        }

        maxpf = -(xk / maxpf);
        ntf_expm1(&maxpf);
        minpf = -maxpf;
      } else {
        minpf = rtNaN;
      }

      maxpf = 1.0 / this->Par[0];
      xk = this->Par[2];
      if ((maxpf > 0.0) && (!rtIsNaN(this->Par[2]))) {
        if (this->Par[2] < 0.0) {
          xk = 0.0;
        }

        maxpf = -(xk / maxpf);
        ntf_expm1(&maxpf);
        maxpf = -maxpf;
      } else {
        maxpf = rtNaN;
      }

      xk = maxpf - minpf;

      // InverseCDF=InverseCDF_temp(minpf + p*(maxpf-minpf));
      for (i = 0; i < 1048576; i++) {
        b_minpf[i] = minpf + p[i] * xk;
      }

      ntf_d_icdf(b_minpf, 1.0 / this->Par[0], InverseCDF);
    }
    break;

   case 17:
    {
      int ns;
      int i1;
      int loop_ub;
      if (2 > this->Multinomial.size(1)) {
        i = 0;
        k = 1;
      } else {
        i = 1;
        k = 2;
      }

      if (1 > this->Multinomial.size(1)) {
        ns = 1;
        i1 = -1;
      } else {
        ns = 2;
        i1 = this->Multinomial.size(1) - 1;
      }

      loop_ub = ntf_div_s32_floor(i1, ns);
      xvals_temp.set_size(1, (loop_ub + 1));
      for (i1 = 0; i1 <= loop_ub; i1++) {
        xvals_temp[i1] = this->Multinomial[ns * i1];
      }

      ntf_b_sort(xvals_temp, iidx);
      pvals.set_size(1, iidx.size(1));
      loop_ub = iidx.size(1);
      for (ns = 0; ns < loop_ub; ns++) {
        pvals[ns] = this->Multinomial[i + k * (iidx[ns] - 1)];
      }

      if ((iidx.size(1) != 0) && (iidx.size(1) != 1)) {
        i = iidx.size(1);
        for (k = 0; k <= i - 2; k++) {
          pvals[k + 1] = pvals[k] + pvals[k + 1];
        }
      }

      loop_ub = pvals.size(0) * pvals.size(1);
      for (ns = 0; ns < 1048576; ns++) {
        boolean_T exitg2;
        x.set_size(1, pvals.size(1));
        for (i = 0; i < loop_ub; i++) {
          x[i] = (pvals[i] - p[ns] >= 0.0);
        }

        k = 0;
        exitg2 = false;
        while ((!exitg2) && (k <= x.size(1) - 1)) {
          if (x[k]) {
            ii_data_idx_0 = k + 1;
            exitg2 = true;
          } else {
            k++;
          }
        }

        InverseCDF[ns] = xvals_temp[ii_data_idx_0 - 1];
      }
    }
    break;
  }

  // {
  // alternative way for creating ERADist Objects
  // methods(Static)
  //    function Obj = normal(mean, std)
  //        Obj = ERADist("normal", "PAR", [mean,std]);
  //    end
  //
  //    function Obj = lognormal_PAR(mu_lnX, signma_lnX)
  //        Obj = ERADist("lognormal", "PAR", [mu_lnX, signma_lnX]);
  //    end
  //
  //    function Obj = lognormal_MOM(mean, std)
  //        Obj = ERADist("lognormal", "MOM", [mean, std]);
  //    end
  //
  //    function Obj = exponential_PAR(lambda)
  //        Obj = ERADist('exponential','PAR',[lambda]);
  //    end
  //
  //    function Obj = exponential_MOM(mean)
  //        Obj = ERADist('exponential','MOM',[mean]);
  //    end
  //
  // end
  // }
}

//
// Arguments    : const coder::array<double, 1U> &x
//                coder::array<double, 1U> &PDF
// Return Type  : void
//
void ntf_ERADist::ntf_fb_pdf(const coder::array<double, 1U> &x, coder::array<
  double, 1U> &PDF) const
{
  int vlen;
  int i;
  coder::array<char, 2U> switch_expression;
  int k;
  boolean_T b_bool;
  int exitg1;
  static const char b_cv[8] = { 'b', 'i', 'n', 'o', 'm', 'i', 'a', 'l' };

  coder::array<double, 1U> b_x;
  double CDF_max;
  int i1;
  int i2;
  coder::array<double, 2U> c_x;
  int loop_ub;
  int i3;
  int i4;
  static const char b_cv1[7] = { 'p', 'o', 'i', 's', 's', 'o', 'n' };

  static const char b_cv2[4] = { 'b', 'e', 't', 'a' };

  static const char b_cv3[3] = { 'g', 'e', 'v' };

  static const char t9_f1[6] = { 'n', 'o', 'r', 'm', 'a', 'l' };

  static const char t9_f2[8] = { 'g', 'a', 'u', 's', 's', 'i', 'a', 'n' };

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
  //     function CDF = cdf(Obj,x)
  //        switch lower(Obj.Name)
  //           case 'geometric'
  //              CDF = Obj.Dist.cdf(x-1);
  //           case 'negativebinomial'
  //              CDF = Obj.Dist.cdf(x-Obj.Par(1));
  //           case 'beta'
  //              CDF = Obj.Dist.cdf((x-Obj.Par(3))/(Obj.Par(4)-Obj.Par(3)));
  //           case 'gumbelmin'
  //              CDF = Obj.Dist.cdf(-x);
  //           case 'gevmin'
  //              CDF = Obj.Dist.cdf(-x);
  //           otherwise
  //              CDF = Obj.Dist.cdf(x);
  //        end
  //     end
  PDF.set_size(x.size(0));
  vlen = x.size(0);
  for (i = 0; i < vlen; i++) {
    PDF[i] = 0.0;
  }

  switch_expression.set_size(this->Name.size(0), this->Name.size(1));
  i = this->Name.size(1);
  for (k = 0; k < i; k++) {
    switch_expression[k] = ntf_cv[static_cast<unsigned char>(this->Name[k]) &
      127];
  }

  b_bool = false;
  if (switch_expression.size(1) == 8) {
    vlen = 0;
    do {
      exitg1 = 0;
      if (vlen < 8) {
        if (switch_expression[vlen] != b_cv[vlen]) {
          exitg1 = 1;
        } else {
          vlen++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  if (b_bool) {
    vlen = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      vlen = 0;
      do {
        exitg1 = 0;
        if (vlen < 9) {
          if (switch_expression[vlen] != ntf_cv3[vlen]) {
            exitg1 = 1;
          } else {
            vlen++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }

    if (b_bool) {
      vlen = 1;
    } else {
      b_bool = false;
      if (switch_expression.size(1) == 16) {
        vlen = 0;
        do {
          exitg1 = 0;
          if (vlen < 16) {
            if (switch_expression[vlen] != ntf_cv4[vlen]) {
              exitg1 = 1;
            } else {
              vlen++;
            }
          } else {
            b_bool = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }

      if (b_bool) {
        vlen = 2;
      } else {
        b_bool = false;
        if (switch_expression.size(1) == 7) {
          vlen = 0;
          do {
            exitg1 = 0;
            if (vlen < 7) {
              if (switch_expression[vlen] != b_cv1[vlen]) {
                exitg1 = 1;
              } else {
                vlen++;
              }
            } else {
              b_bool = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (b_bool) {
          vlen = 3;
        } else {
          b_bool = false;
          if (switch_expression.size(1) == 11) {
            vlen = 0;
            do {
              exitg1 = 0;
              if (vlen < 11) {
                if (switch_expression[vlen] != ntf_cv5[vlen]) {
                  exitg1 = 1;
                } else {
                  vlen++;
                }
              } else {
                b_bool = true;
                exitg1 = 1;
              }
            } while (exitg1 == 0);
          }

          if (b_bool) {
            vlen = 4;
          } else if (ntf_k_strcmp(switch_expression)) {
            vlen = 5;
          } else {
            b_bool = false;
            if (switch_expression.size(1) == 4) {
              vlen = 0;
              do {
                exitg1 = 0;
                if (vlen < 4) {
                  if (switch_expression[vlen] != b_cv2[vlen]) {
                    exitg1 = 1;
                  } else {
                    vlen++;
                  }
                } else {
                  b_bool = true;
                  exitg1 = 1;
                }
              } while (exitg1 == 0);
            }

            if (b_bool) {
              vlen = 6;
            } else if (ntf_m_strcmp(switch_expression)) {
              vlen = 7;
            } else if (ntf_n_strcmp(switch_expression)) {
              vlen = 8;
            } else {
              b_bool = false;
              if (switch_expression.size(1) == 3) {
                vlen = 0;
                do {
                  exitg1 = 0;
                  if (vlen < 3) {
                    if (switch_expression[vlen] != b_cv3[vlen]) {
                      exitg1 = 1;
                    } else {
                      vlen++;
                    }
                  } else {
                    b_bool = true;
                    exitg1 = 1;
                  }
                } while (exitg1 == 0);
              }

              if (b_bool) {
                vlen = 9;
              } else if (ntf_p_strcmp(switch_expression)) {
                vlen = 10;
              } else if (ntf_q_strcmp(switch_expression)) {
                vlen = 11;
              } else if (ntf_r_strcmp(switch_expression)) {
                vlen = 12;
              } else {
                b_bool = false;
                if (switch_expression.size(1) == 14) {
                  vlen = 0;
                  do {
                    exitg1 = 0;
                    if (vlen < 14) {
                      if (switch_expression[vlen] != ntf_cv1[vlen]) {
                        exitg1 = 1;
                      } else {
                        vlen++;
                      }
                    } else {
                      b_bool = true;
                      exitg1 = 1;
                    }
                  } while (exitg1 == 0);
                }

                if (b_bool) {
                  vlen = 13;
                } else {
                  b_bool = false;
                  if (switch_expression.size(1) == 16) {
                    vlen = 0;
                    do {
                      exitg1 = 0;
                      if (vlen < 16) {
                        if (switch_expression[vlen] != ntf_cv2[vlen]) {
                          exitg1 = 1;
                        } else {
                          vlen++;
                        }
                      } else {
                        b_bool = true;
                        exitg1 = 1;
                      }
                    } while (exitg1 == 0);
                  }

                  if (b_bool) {
                    vlen = 13;
                  } else {
                    b_bool = false;
                    if (switch_expression.size(1) == 6) {
                      vlen = 0;
                      do {
                        exitg1 = 0;
                        if (vlen < 6) {
                          if (switch_expression[vlen] != t9_f1[vlen]) {
                            exitg1 = 1;
                          } else {
                            vlen++;
                          }
                        } else {
                          b_bool = true;
                          exitg1 = 1;
                        }
                      } while (exitg1 == 0);
                    }

                    if (b_bool) {
                      vlen = 14;
                    } else {
                      b_bool = false;
                      if (switch_expression.size(1) == 8) {
                        vlen = 0;
                        do {
                          exitg1 = 0;
                          if (vlen < 8) {
                            if (switch_expression[vlen] != t9_f2[vlen]) {
                              exitg1 = 1;
                            } else {
                              vlen++;
                            }
                          } else {
                            b_bool = true;
                            exitg1 = 1;
                          }
                        } while (exitg1 == 0);
                      }

                      if (b_bool) {
                        vlen = 14;
                      } else if (ntf_w_strcmp(switch_expression)) {
                        vlen = 15;
                      } else if (ntf_x_strcmp(switch_expression)) {
                        vlen = 16;
                      } else if (ntf_y_strcmp(switch_expression)) {
                        vlen = 17;
                      } else {
                        vlen = -1;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  switch (vlen) {
   case 0:
    ntf_q_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 1:
    b_x.set_size(x.size(0));
    vlen = x.size(0);
    for (i = 0; i < vlen; i++) {
      b_x[i] = x[i] - 1.0;
    }

    ntf_r_pdf(b_x, this->Par[0], PDF);
    break;

   case 2:
    b_x.set_size(x.size(0));
    vlen = x.size(0);
    for (i = 0; i < vlen; i++) {
      b_x[i] = x[i] - this->Par[0];
    }

    ntf_s_pdf(b_x, this->Par[0], this->Par[1], PDF);
    break;

   case 3:
    if (this->Par[1] == 0.0) {
      ntf_t_pdf(x, this->Par[0], PDF);
    } else {
      ntf_t_pdf(x, this->Par[0] * this->Par[1], PDF);
    }
    break;

   case 4:
    ntf_u_pdf(x, 1.0 / this->Par[0], PDF);
    break;

   case 5:
    ntf_gampdf(x, this->Par[1], 1.0 / this->Par[0], PDF);
    break;

   case 6:
    //                  PDF  = pdf('beta',(x-Obj.Par(3))/(Obj.Par(4)-Obj.Par(3)),Obj.Par(1),Obj.Par(2))./(Obj.Par(4)-Obj.Par(3)); 
    CDF_max = this->Par[3] - this->Par[2];
    b_x.set_size(x.size(0));
    vlen = x.size(0);
    for (i = 0; i < vlen; i++) {
      b_x[i] = (x[i] - this->Par[2]) / CDF_max;
    }

    ntf_v_pdf(b_x, this->Par[0], this->Par[1], PDF);
    vlen = PDF.size(0);
    for (i = 0; i < vlen; i++) {
      PDF[i] = PDF[i] / CDF_max;
    }

    //              case 'gumbelmin'  % this distribution can be used to model minima 
    //                  PDF  = pdf('Extreme Value',x,Obj.Par(2),Obj.Par(1));
    break;

   case 7:
    //  mirror image of this distribution can be used to model maxima
    ntf_w_pdf(x, this->Par[0], this->Par[1], PDF);

    //             case 'frechet'
    //                 PDF  = pdf('Generalized Extreme Value',x,1/Obj.Par(2),Obj.Par(1)/Obj.Par(2),Obj.Par(1)); 
    break;

   case 8:
    ntf_x_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 9:
    ntf_y_pdf(x, this->Par[0], this->Par[1], this->Par[2], PDF);

    //              case 'gevmin'
    //                  PDF = pdf('Generalized Extreme Value',-x,Obj.Par(1),Obj.Par(2),-Obj.Par(3)); 
    //              case 'pareto'
    //                  PDF = pdf('Generalized Pareto',x,1/Obj.Par(2),Obj.Par(1)/Obj.Par(2),Obj.Par(1)); 
    break;

   case 10:
    ntf_ab_pdf(x, this->Par[0], PDF);
    break;

   case 11:
    ntf_bb_pdf(x, this->Par[0] / 2.0, PDF);
    break;

   case 12:
    ntf_cb_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 13:
    PDF.set_size(x.size(0));
    i = x.size(0);
    for (k = 0; k < i; k++) {
      PDF[k] = std::exp(-0.5 * x[k] * x[k]) / 2.5066282746310002;
    }
    break;

   case 14:
    ntf_db_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 15:
    ntf_eb_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 16:
    {
      double xk;
      double CDF_min;
      ntf_u_pdf(x, 1.0 / this->Par[0], PDF);
      CDF_max = 1.0 / this->Par[0];
      xk = this->Par[1];
      if ((CDF_max > 0.0) && (!rtIsNaN(this->Par[1]))) {
        if (this->Par[1] < 0.0) {
          xk = 0.0;
        }

        CDF_max = -(xk / CDF_max);
        ntf_expm1(&CDF_max);
        CDF_min = -CDF_max;
      } else {
        CDF_min = rtNaN;
      }

      CDF_max = 1.0 / this->Par[0];
      xk = this->Par[2];
      if ((CDF_max > 0.0) && (!rtIsNaN(this->Par[2]))) {
        if (this->Par[2] < 0.0) {
          xk = 0.0;
        }

        CDF_max = -(xk / CDF_max);
        ntf_expm1(&CDF_max);
        CDF_max = -CDF_max;
      } else {
        CDF_max = rtNaN;
      }

      CDF_max -= CDF_min;
      vlen = PDF.size(0);
      for (i = 0; i < vlen; i++) {
        PDF[i] = PDF[i] / CDF_max;
      }
    }
    break;

   case 17:
    i = x.size(0);
    if (0 <= x.size(0) - 1) {
      if (1 > this->Multinomial.size(1)) {
        i1 = 1;
        i2 = -1;
      } else {
        i1 = 2;
        i2 = this->Multinomial.size(1) - 1;
      }

      if (2 > this->Multinomial.size(1)) {
        i3 = 0;
        i4 = 1;
      } else {
        i3 = 1;
        i4 = 2;
      }

      loop_ub = ntf_div_s32_floor(i2, i1);
    }

    for (int ns = 0; ns < i; ns++) {
      c_x.set_size(1, (ntf_div_s32_floor(i2, i1) + 1));
      for (vlen = 0; vlen <= loop_ub; vlen++) {
        c_x[vlen] = static_cast<double>(x[ns] == this->Multinomial[i1 * vlen]) *
          this->Multinomial[i3 + i4 * vlen];
      }

      vlen = c_x.size(1);
      if (c_x.size(1) == 0) {
        CDF_max = 0.0;
      } else {
        CDF_max = c_x[0];
        for (k = 2; k <= vlen; k++) {
          CDF_max += c_x[k - 1];
        }
      }

      PDF[ns] = CDF_max;
    }
    break;
  }
}

//
// Arguments    : const coder::array<char, 2U> &name
//                const coder::array<char, 2U> &opt
//                coder::array<double, 2U> &val_temp
//                const coder::array<double, 2U> &add
// Return Type  : void
//
void ntf_ERADist::ntf_init(const coder::array<char, 2U> &name, const coder::
  array<char, 2U> &opt, coder::array<double, 2U> &val_temp, const coder::array<
  double, 2U> &add)
{
  int vlen;
  int i;
  double Mean;
  double Var;
  double Std;
  coder::array<char, 2U> switch_expression;
  int k;
  static const char b_cv[128] = { '\x00', '\x01', '\x02', '\x03', '\x04', '\x05',
    '\x06', '\x07', '\x08', '	', '\x0a', '\x0b', '\x0c', '\x0d', '\x0e', '\x0f',
    '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18',
    '\x19', '\x1a', '\x1b', '\x1c', '\x1d', '\x1e', '\x1f', ' ', '!', '\"', '#',
    '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2',
    '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A',
    'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
    '`', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '{', '|', '}',
    '~', '\x7f' };

  coder::array<double, 1U> val;
  double b_val[4];
  static const char t7_f1[6] = { 'n', 'o', 'r', 'm', 'a', 'l' };

  coder::array<double, 1U> F;
  static const char t7_f2[8] = { 'g', 'a', 'u', 's', 's', 'i', 'a', 'n' };

  coder::array<double, 2U> pval;
  double lam0;
  double mu0;
  coder::array<double, 2U> y;
  coder::array<boolean_T, 1U> c_val;
  double b_init[2];
  ntf_coder_internal_anonymous_fu b_this;
  double lambs[1000];
  coder::array<int, 1U> r1;
  ntf_ERADist Obj_tmp;
  ntf_b_coder_internal_anonymous_ c_this;
  ntf_c_coder_internal_anonymous_ fun;
  double xx[5000];
  double b_xx[1000];
  double b_y1[1000];
  double lam1;
  coder::array<double, 1U> r2;
  double y2[1000];
  double mean1;
  double c_y1[5000];
  double b_y2[5000];
  double b[3];

  //  Generation of distribution objects
  //    construct distribution object with Obj = ERADist(name,opt,val) with
  //    opt = "PAR", if you want to specify the distibution by its parameters:
  //    Binomial:                   Obj = ERADist('binomial','PAR',[n,p])
  //    Geometric:                  Obj = ERADist('geometric','PAR',[p])
  //    Negative binomial:          Obj = ERADist('negativebinomial','PAR',[k,p]) 
  //    Poisson:                    Obj = ERADist('poisson','PAR',[lambda,t])
  //    Uniform:                    Obj = ERADist('uniform','PAR',[lower,upper]) 
  //    Normal:                     Obj = ERADist('normal','PAR',[mean,std])
  //    Standard normal:            Obj = ERADist('standardnormal','PAR',[])
  //    Log-normal:                 Obj = ERADist('lognormal','PAR',[mu_lnx,sig_lnx]) 
  //    Exponential:                Obj = ERADist('exponential','PAR',[lambda])
  //    Gamma:                      Obj = ERADist('gamma','PAR',[lambda,k])
  //    Beta:                       Obj = ERADist('beta','PAR',[r,s,lower,upper]) 
  //    Gumbel (to model minima):   Obj = ERADist('gumbelMin','PAR',[a_n,b_n])
  //    Gumbel (to model maxima):   Obj = ERADist('gumbel','PAR',[a_n,b_n])
  //    Frechet:                    Obj = ERADist('frechet','PAR',[a_n,k])
  //    Weibull:                    Obj = ERADist('weibull','PAR',[a_n,k])
  //    GEV (to model maxima):      Obj = ERADist('GEV','PAR',[beta,alpha,epsilon]) 
  //    GEV (to model minima):      Obj = ERADist('GEVMin','PAR',[beta,alpha,epsilon]) 
  //    Pareto:                     Obj = ERADist('pareto','PAR',[x_m,alpha])
  //    Rayleigh:                   Obj = ERADist('rayleigh','PAR',[alpha])
  //    Chi-squared:                Obj = ERADist('chisquare','PAR',[k])
  //
  //
  //    Discrete:                   Obj = ERADist('discrete','PAR',[value and weight pairs]) 
  //
  //
  //    opt = "MOM", if you want to specify the distibution by its moments:
  //    Binomial:                   Obj = ERADist('binomial','MOM',[mean,std])
  //    Geometric:                  Obj = ERADist('geometric','MOM',[mean])
  //    Negative binomial:          Obj = ERADist('negativebinomial','MOM',[mean,std]) 
  //    Poisson:                    Obj = ERADist('poisson','MOM',[mean])
  //    Uniform:                    Obj = ERADist('uniform','MOM',[mean,std])
  //    Normal:                     Obj = ERADist('normal','MOM',[mean,std])
  //    Standard normal:            Obj = ERADist('standardnormal','MOM',[])
  //    Log-normal:                 Obj = ERADist('lognormal','MOM',[mean,std])
  //    Exponential:                Obj = ERADist('exponential','MOM',[mean])
  //    Gamma:                      Obj = ERADist('gamma','MOM',[mean,std])
  //    Beta:                       Obj = ERADist('beta','MOM',[mean,std,lower,upper]) 
  //    Gumbel (to model minima):   Obj = ERADist('gumbel','MOM',[mean,std])
  //    Gumbel (to model maxima):   Obj = ERADist('gumbelMax','MOM',[mean,std])
  //    (removed)Frechet:           Obj = ERADist('frechet','MOM',[mean,std])
  //
  //    Weibull:                    Obj = ERADist('weibull','MOM',[mean,std])
  //    GEV (to model minima):      Obj = ERADist('GEVMin','MOM',[mean,std,epsilon]) 
  //    GEV (to model maxima):      Obj = ERADist('GEV','MOM',[mean,std,epsilon]) 
  //    Pareto:                     Obj = ERADist('pareto','MOM',[mean,std])
  //    Rayleigh:                   Obj = ERADist('rayleigh','MOM',[mean])
  //    Chi-squared:                Obj = ERADist('chisquare','MOM',[mean])
  // {
  // --------------------------------------------------------------------------- 
  // Developed by:
  // Sebastian Geyer (s.geyer@tum.de),
  // Felipe Uribe
  // Iason Papaioannou
  // Daniel Straub
  //
  // Assistant Developers:
  // Alexander von Ramm
  // Matthias Willer
  // Peter Kaplan
  //
  // Engineering Risk Analysis Group
  // Technische Universitat Munchen
  // www.era.bgu.tum.de
  // --------------------------------------------------------------------------- 
  // New Version 2019-01:
  // * Fixing of bugs in the exponential distribution
  // * Matlab reference page with all available distributions: type "help
  //   ERADist" to view available distributions and how to define them
  // Version 2017-12:
  // * Fixing of bugs in the gumbel,gumbelmin and gamma distribution
  // --------------------------------------------------------------------------- 
  // This software generates distribution objects according to the parameters
  // and definitions used in the distribution table of the ERA Group of TUM.
  // They can be defined either by their parameters, the first and second
  // moment or by data, given as a vector.
  // --------------------------------------------------------------------------- 
  // }
  //  MATLAB class: definition of the 'properties' block
  //  Name of the distribution
  //  Parameters of the distribution
  //  matlab distribution object of the marginal distribution
  //  returns mean
  //  returns standard deviaton
  //  MATLAB class: definition of the 'methods' block
  // {
  // Definition of all member functions of the ERADist class. Those are:
  // - ERADist    (Constructor)
  // - mean       returns mean
  // - std        returns standard deviaton
  // - cdf        returns value of CDF
  // - icdf       returns value of inverse CDF
  // - pdf        returns value of pdf
  // - random     generates random numbers according to the distribution of the object 
  // }
  this->Name.set_size(1, name.size(1));
  vlen = name.size(0) * name.size(1);
  for (i = 0; i < vlen; i++) {
    this->Name[i] = name[i];
  }

  this->Par[0] = 0.0;
  this->Par[1] = 0.0;
  this->Par[2] = 0.0;
  this->Par[3] = 0.0;
  this->Multinomial.set_size(1, val_temp.size(1));
  vlen = val_temp.size(0) * val_temp.size(1);
  for (i = 0; i < vlen; i++) {
    this->Multinomial[i] = val_temp[i];
  }

  Mean = 0.0;
  Var = 0.0;
  Std = 0.0;
  switch_expression.set_size(opt.size(0), opt.size(1));
  i = opt.size(1);
  for (k = 0; k < i; k++) {
    switch_expression[k] = b_cv[static_cast<unsigned char>(opt[k]) & 127];
  }

  if (ntf_strcmp(switch_expression)) {
    vlen = 0;
  } else if (ntf_b_strcmp(switch_expression)) {
    vlen = 1;
  } else if (ntf_c_strcmp(switch_expression)) {
    vlen = 2;
  } else {
    vlen = -1;
  }

  switch (vlen) {
   case 0:
    {
      // -----------------------------------------------------------------
      this->Multinomial.set_size(1, val_temp.size(1));
      vlen = val_temp.size(0) * val_temp.size(1);
      for (i = 0; i < vlen; i++) {
        this->Multinomial[i] = val_temp[i];
      }

      b_val[0] = 0.0;
      b_val[1] = 0.0;
      b_val[2] = 0.0;
      b_val[3] = 0.0;
      if (4 < val_temp.size(1)) {
        i = 3;
      } else {
        i = val_temp.size(1) - 1;
      }

      for (vlen = 0; vlen <= i; vlen++) {
        b_val[vlen] = val_temp[vlen];
      }

      this->Par[0] = b_val[0];
      this->Par[1] = b_val[1];
      this->Par[2] = b_val[2];
      this->Par[3] = b_val[3];
      if (ntf_d_strcmp(name) || ntf_e_strcmp(name)) {
        b_val[0] = 0.0;
        b_val[1] = 1.0;
      }

      switch_expression.set_size(name.size(0), name.size(1));
      i = name.size(1);
      for (k = 0; k < i; k++) {
        switch_expression[k] = ntf_cv[static_cast<unsigned char>(name[k]) & 127];
      }

      if (ntf_f_strcmp(switch_expression)) {
        vlen = 0;
      } else if (ntf_g_strcmp(switch_expression)) {
        vlen = 1;
      } else if (ntf_h_strcmp(switch_expression)) {
        vlen = 2;
      } else if (ntf_i_strcmp(switch_expression)) {
        vlen = 3;
      } else if (ntf_j_strcmp(switch_expression)) {
        vlen = 4;
      } else if (ntf_k_strcmp(switch_expression)) {
        vlen = 5;
      } else if (ntf_l_strcmp(switch_expression)) {
        vlen = 6;
      } else if (ntf_m_strcmp(switch_expression)) {
        vlen = 7;
      } else if (ntf_n_strcmp(switch_expression)) {
        vlen = 8;
      } else if (ntf_o_strcmp(switch_expression)) {
        vlen = 9;
      } else if (ntf_p_strcmp(switch_expression)) {
        vlen = 10;
      } else if (ntf_q_strcmp(switch_expression)) {
        vlen = 11;
      } else if (ntf_r_strcmp(switch_expression)) {
        vlen = 12;
      } else if (ntf_s_strcmp(switch_expression, ntf_cv1)) {
        vlen = 13;
      } else if (ntf_t_strcmp(switch_expression, ntf_cv2)) {
        vlen = 13;
      } else if (ntf_u_strcmp(switch_expression, t7_f1)) {
        vlen = 14;
      } else if (ntf_v_strcmp(switch_expression, t7_f2)) {
        vlen = 14;
      } else if (ntf_w_strcmp(switch_expression)) {
        vlen = 15;
      } else if (ntf_x_strcmp(switch_expression)) {
        vlen = 16;
      } else if (ntf_y_strcmp(switch_expression)) {
        vlen = 17;
      } else {
        vlen = -1;
      }

      switch (vlen) {
       case 0:
        if ((0.0 <= b_val[1]) && (b_val[1] <= 1.0) && (b_val[0] > 0.0) &&
            (ntf_mod(b_val[0]) == 0.0)) {
          ntf_binostat(b_val[0], b_val[1], &Mean, &Var);

          //  Obj.Dist = mymakedist(name,'N',val(1),'p',val(2));
          //  CDF = cdf(name,x,val(1),val(2));
        }
        break;

       case 1:
        //  special case of negative binomial distribution
        if ((0.0 < b_val[0]) && (b_val[0] <= 1.0)) {
          Mean = (1.0 - b_val[0]) / b_val[0];
          Var = Mean / b_val[0];
          Mean++;

          //  Obj.Dist = mymakedist('negativebinomial','r',1,'p',val);
          //  CDF = cdf('negativebinomial',x,1,val);
        }
        break;

       case 2:
        if ((0.0 < b_val[1]) && (b_val[1] <= 1.0) && (b_val[0] > 0.0) &&
            (ntf_mod(b_val[0]) == 0.0)) {
          ntf_nbinstat(b_val[0], b_val[1], &Mean, &Var);
          Mean += b_val[0];

          //  Obj.Dist = mymakedist(name,'r',val(1),'p',val(2));
          //  CDF  = cdf(name,x,val(1),val(2));
        }
        break;

       case 3:
        if (b_val[1] == 0.0) {
          if (b_val[0] > 0.0) {
            //  Obj.Dist = mymakedist(name,'lambda',val);
            //  CDF  = cdf(name,x,val);
            Mean = b_val[0];
            Var = b_val[0];
          }
        } else {
          if ((b_val[0] > 0.0) && (b_val[1] > 0.0)) {
            //  Obj.Dist = mymakedist(name,'lambda',val(1)*val(2));
            //  CDF  = cdf(name,x,val(1)*val(2));
            Mean = b_val[0] * b_val[1];
            if (Mean > 0.0) {
              Var = Mean;
            } else {
              Mean = rtNaN;
              Var = rtNaN;
            }
          }
        }
        break;

       case 4:
        if (b_val[0] > 0.0) {
          //  Obj.Dist = mymakedist(name,'mu',1/val);
          //  CDF  = cdf(name,x,1/val);
          Mean = 1.0 / b_val[0];
          if (Mean > 0.0) {
            Var = Mean * Mean;
          } else {
            Mean = rtNaN;
            Var = rtNaN;
          }
        }
        break;

       case 5:
        if ((b_val[0] > 0.0) && (b_val[1] > 0.0)) {
          //  Obj.Dist = mymakedist(name,'a',val(2),'b',1/val(1));
          //  CDF  = cdf(name,x,val(2),1/val(1));
          Var = 1.0 / b_val[0];
          if (Var > 0.0) {
            Mean = b_val[1] * Var;
            Var *= Mean;
          } else {
            Mean = rtNaN;
            Var = rtNaN;
          }
        }
        break;

       case 6:
        if ((b_val[0] > 0.0) && (b_val[1] > 0.0) && (b_val[2] < b_val[3])) {
          //  Obj.Dist = mymakedist(name,'a',val(1),'b',val(2));
          //  CDF  = cdf(name,x,val(1),val(2));
          Var = b_val[0] + b_val[1];
          Mean = (b_val[1] * b_val[2] + b_val[0] * b_val[3]) / Var;

          // Var  =Var*(val(4)-val(3));
          // Var  =(val(1)*val(2)*(val(4)-val(3))/(val(1)+val(2))^2/(val(1)+val(2)+1)); 
          lam0 = b_val[3] - b_val[2];
          Var = b_val[0] / Var * b_val[1] / (Var * (Var + 1.0)) * (lam0 * lam0);
        }

        //                case 'gumbelmin'  % this distribution can be used to model minima 
        //                    if val(1) > 0
        //                        % sigma is the scale parameter
        //                        % mu is the location parameter
        //                       % Obj.Dist = mymakedist('GeneralizedExtremeValue','k',0,'sigma',val(1),'mu',-val(2)); 
        //                       % CDF  = cdf('GeneralizedExtremeValue',x,0,val(1),-val(2)); 
        //
        //                       [Mean ,Var] = evstat(val(2),val(1));
        //                    else
        //                       error('The Gumbel (min) distribution is not defined for your parameters'); 
        //                    end
        break;

       case 7:
        //  mirror image of this distribution can be used to model maxima
        if (b_val[0] > 0.0) {
          //  sigma is the scale parameter
          //  mu is the location parameter
          //  Obj.Dist = mymakedist('GeneralizedExtremeValue','k',0,'sigma',val(1),'mu',val(2));  
          //  CDF  = cdf('GeneralizedExtremeValue',x,0,val(1),val(2));
          if (!rtIsNaN(b_val[1])) {
            Mean = b_val[1] + 0.57721566490153231 * b_val[0];
            Var = 1.6449340668482264 * (b_val[0] * b_val[0]);
          } else {
            Mean = rtNaN;
            Var = rtNaN;
          }
        }

        //                case 'frechet'
        //                   if (val(1) > 0) && (val(2) > 0)
        //                     % Obj.Dist = mymakedist('GeneralizedExtremeValue','k',1/val(2),'sigma',val(1)/val(2),'mu',val(1)); 
        //                      % CDF  = cdf('GeneralizedExtremeValue',x,1/val(2),val(1)/val(2),val(1)); 
        //                      [Mean ,Var] = gevstat(1/val(2),val(1)/val(2),val(1)); 
        //                   else
        //                      error('The Frechet distribution is not defined for your parameters'); 
        //                   end
        break;

       case 8:
        if ((b_val[0] > 0.0) && (b_val[1] > 0.0)) {
          //  Obj.Dist = mymakedist(name,'a',val(1),'b',val(2));
          //  CDF  = cdf(name,x,val(1),val(2));
          ntf_wblstat(b_val[0], b_val[1], &Mean, &Var);
        }
        break;

       case 9:
        if (b_val[1] > 0.0) {
          //  Obj.Dist = mymakedist('GeneralizedExtremeValue','k',val(1),'sigma',val(2),'mu',val(3)); 
          //  CDF  = cdf('GeneralizedExtremeValue',x,val(1),val(2),val(3));
          ntf_gevstat(b_val[0], b_val[1], b_val[2], &Mean, &Var);
        }

        //                 case 'gevmin'
        //                    if val(2) > 0
        //                       % Obj.Dist = mymakedist('GeneralizedExtremeValue','k',val(1),'sigma',val(2),'mu',-val(3)); 
        //                       % CDF = cdf('GeneralizedExtremeValue',x,val(1),val(2),-val(3)); 
        //                        [Mean ,Var] = gevstat(val(1),val(2),-val(3));
        //                        Mean=-Mean;
        //                    else
        //                       error('The Generalized Extreme Value distribution is not defined for your parameters'); 
        //                    end
        //                 case 'pareto'
        //                    if (val(1) > 0) && (val(2) > 0)
        //                       % Obj.Dist = mymakedist('Generalizedpareto','k',1/val(2),'sigma',val(1)/val(2),'theta',val(1)); 
        //                       % CDF = cdf('Generalizedpareto',x,1/val(2),val(1)/val(2),val(1)); 
        //                        [Mean ,Var] = gpstat(1/val(2),val(1)/val(2),val(1)); 
        //                    else
        //                       error('The Pareto distribution is not defined for your parameters'); 
        //                    end
        break;

       case 10:
        if (b_val[0] > 0.0) {
          //  Obj.Dist = mymakedist(name,'b',val);
          //  CDF = cdf(name,x,val);
          Mean = b_val[0] * 1.2533141373155001;
          Var = 0.42920367320510344 * (b_val[0] * b_val[0]);
        }
        break;

       case 11:
        //  special case of gamma distribution
        if ((b_val[0] > 0.0) && (ntf_mod(b_val[0]) == 0.0)) {
          //   Obj.Dist = mymakedist('gamma','a',val/2,'b',2);
          //   CDF = cdf('gamma',x,val/2,2);
          lam0 = b_val[0] / 2.0;
          if (lam0 > 0.0) {
            Mean = lam0 * 2.0;
            Var = Mean * 2.0;
          } else {
            Mean = rtNaN;
            Var = rtNaN;
          }
        }
        break;

       case 12:
        //  Obj.Dist = mymakedist(name,'lower',val(1),'upper',val(2));
        //  CDF = cdf(name,x,val(1),val(2));
        if (b_val[0] <= b_val[1]) {
          Mean = (b_val[0] + b_val[1]) / 2.0;
          Var = b_val[1] - b_val[0];
          Var = Var * Var / 12.0;
        } else {
          Mean = rtNaN;
          Var = rtNaN;
        }
        break;

       case 13:
        //  special case of normal distribution
        //  Obj.Dist = mymakedist('normal');
        //  CDF = cdf('normal',x,0,1);
        Var = 1.0;
        break;

       case 14:
        if (b_val[1] > 0.0) {
          //  Obj.Dist = mymakedist(name,'mu',val(1),'sigma',val(2));
          //  CDF = cdf(name,x,val(1),val(2));
          Mean = b_val[0];
          Var = b_val[1] * b_val[1];
        }
        break;

       case 15:
        if (b_val[1] > 0.0) {
          //  Obj.Dist = mymakedist(name,'mu',val(1),'sigma',val(2));
          //  CDF = cdf(name,x,val(1),val(2));
          ntf_lognstat(b_val[0], b_val[1], &Mean, &Var);
        }
        break;

       case 16:
        ntf_linspace(this->Par[1], b_val[2], b_xx);
        this->ntf_fb_pdf(b_xx, b_y1);
        for (k = 0; k < 1000; k++) {
          b_y1[k] *= b_xx[k];
          y2[k] = ntf_rt_powd_snf(b_xx[k], 2.0);
        }

        this->ntf_fb_pdf(b_xx, lambs);
        for (i = 0; i < 1000; i++) {
          y2[i] *= lambs[i];
        }

        Mean = ntf_trapz(b_xx, b_y1);
        Var = ntf_trapz(b_xx, y2) - Mean * Mean;
        break;

       case 17:
        {
          int b_i;
          int i1;
          int i2;
          int i3;
          int i4;
          int i5;
          int vlen_tmp;
          if (2 > val_temp.size(1)) {
            i = 0;
            i1 = 1;
            i2 = -1;
          } else {
            i = 1;
            i1 = 2;
            i2 = val_temp.size(1) - 1;
          }

          if (2 > val_temp.size(1)) {
            i3 = 0;
            b_i = 1;
            vlen = -1;
          } else {
            i3 = 1;
            b_i = 2;
            vlen = val_temp.size(1) - 1;
          }

          if (2 > val_temp.size(1)) {
            i4 = 0;
            i5 = 1;
          } else {
            i4 = 1;
            i5 = 2;
          }

          vlen_tmp = ntf_div_s32_floor(vlen - i3, b_i);
          vlen = vlen_tmp + 1;
          if (vlen == 0) {
            mu0 = 0.0;
          } else {
            mu0 = val_temp[i3];
            for (k = 2; k <= vlen_tmp + 1; k++) {
              mu0 += val_temp[i3 + b_i * (k - 1)];
            }
          }

          vlen = ntf_div_s32_floor(i2 - i, i1);
          pval.set_size(1, (vlen + 1));
          for (i2 = 0; i2 <= vlen; i2++) {
            pval[i2] = val_temp[i + i1 * i2] / mu0;
          }

          vlen = pval.size(1);
          for (i = 0; i < vlen; i++) {
            val_temp[i4 + i5 * i] = pval[i];
          }

          this->Multinomial.set_size(1, val_temp.size(1));
          vlen = val_temp.size(0) * val_temp.size(1);
          for (i = 0; i < vlen; i++) {
            this->Multinomial[i] = val_temp[i];
          }

          // vals=[3,0.2,5,0.3,9,0.1,6,0.2,12,0.2];
          if (2 > val_temp.size(1)) {
            i = 0;
            i1 = 1;
            i2 = -1;
          } else {
            i = 1;
            i1 = 2;
            i2 = val_temp.size(1) - 1;
          }

          if (1 > val_temp.size(1)) {
            i3 = 1;
          } else {
            i3 = 2;
          }

          vlen = ntf_div_s32_floor(i2 - i, i1);
          pval.set_size(1, (vlen + 1));
          for (i2 = 0; i2 <= vlen; i2++) {
            pval[i2] = val_temp[i + i1 * i2] * val_temp[i3 * i2];
          }

          vlen = pval.size(1);
          if (pval.size(1) != 0) {
            Mean = pval[0];
            for (k = 2; k <= vlen; k++) {
              Mean += pval[k - 1];
            }
          }

          if (2 > val_temp.size(1)) {
            i = 0;
            i1 = 1;
            i2 = -1;
          } else {
            i = 1;
            i1 = 2;
            i2 = val_temp.size(1) - 1;
          }

          if (1 > val_temp.size(1)) {
            i3 = 1;
            b_i = 0;
          } else {
            i3 = 2;
            b_i = val_temp.size(1);
          }

          b_i = ntf_div_s32_floor(b_i - 1, i3) + 1;
          y.set_size(1, b_i);
          for (k = 0; k < b_i; k++) {
            y[k] = ntf_rt_powd_snf(val_temp[i3 * k], 2.0);
          }

          vlen = ntf_div_s32_floor(i2 - i, i1);
          pval.set_size(1, (vlen + 1));
          for (i2 = 0; i2 <= vlen; i2++) {
            pval[i2] = val_temp[i + i1 * i2] * y[i2];
          }

          vlen = pval.size(1);
          if (pval.size(1) == 0) {
            mu0 = 0.0;
          } else {
            mu0 = pval[0];
            for (k = 2; k <= vlen; k++) {
              mu0 += pval[k - 1];
            }
          }

          Var = mu0 - Mean * Mean;
        }
        break;
      }

      Std = std::sqrt(Var);

      // -----------------------------------------------------------------
    }
    break;

   case 1:
    {
      this->Multinomial.set_size(1, val_temp.size(1));
      vlen = val_temp.size(0) * val_temp.size(1);
      for (i = 0; i < vlen; i++) {
        this->Multinomial[i] = val_temp[i];
      }

      b_val[0] = 0.0;
      b_val[1] = 0.0;
      b_val[2] = 0.0;
      b_val[3] = 0.0;
      vlen = val_temp.size(1);
      for (i = 0; i < vlen; i++) {
        b_val[i] = val_temp[i];
      }

      Mean = b_val[0];
      if ((!(b_val[1] < 0.0)) && (b_val[1] > 0.0)) {
        Std = b_val[1];
      }

      switch_expression.set_size(name.size(0), name.size(1));
      i = name.size(1);
      for (k = 0; k < i; k++) {
        switch_expression[k] = ntf_cv[static_cast<unsigned char>(name[k]) & 127];
      }

      if (ntf_f_strcmp(switch_expression)) {
        vlen = 0;
      } else if (ntf_g_strcmp(switch_expression)) {
        vlen = 1;
      } else if (ntf_h_strcmp(switch_expression)) {
        vlen = 2;
      } else if (ntf_i_strcmp(switch_expression)) {
        vlen = 3;
      } else if (ntf_j_strcmp(switch_expression)) {
        vlen = 4;
      } else if (ntf_k_strcmp(switch_expression)) {
        vlen = 5;
      } else if (ntf_l_strcmp(switch_expression)) {
        vlen = 6;
      } else if (ntf_m_strcmp(switch_expression)) {
        vlen = 7;
      } else if (ntf_n_strcmp(switch_expression)) {
        vlen = 8;
      } else if (ntf_o_strcmp(switch_expression)) {
        vlen = 9;
      } else if (ntf_p_strcmp(switch_expression)) {
        vlen = 10;
      } else if (ntf_q_strcmp(switch_expression)) {
        vlen = 11;
      } else if (ntf_r_strcmp(switch_expression)) {
        vlen = 12;
      } else if (ntf_s_strcmp(switch_expression, ntf_cv1)) {
        vlen = 13;
      } else if (ntf_t_strcmp(switch_expression, ntf_cv2)) {
        vlen = 13;
      } else if (ntf_u_strcmp(switch_expression, t7_f1)) {
        vlen = 14;
      } else if (ntf_v_strcmp(switch_expression, t7_f2)) {
        vlen = 14;
      } else if (ntf_w_strcmp(switch_expression)) {
        vlen = 15;
      } else if (ntf_x_strcmp(switch_expression)) {
        vlen = 16;
      } else {
        vlen = -1;
      }

      switch (vlen) {
       case 0:
        //  Solve System of two equations for the parameters of the distribution 
        this->Par[1] = 1.0 - b_val[1] * b_val[1] / b_val[0];
        this->Par[0] = b_val[0] / this->Par[1];

        //  Evaluate if distribution can be defined on the parameters
        if (ntf_mod(this->Par[0]) <= 0.0001) {
          this->Par[0] = ntf_rt_roundd_snf(this->Par[0]);
        }
        break;

       case 1:
        //  Solve Equation for the parameter of the distribution based on the first moment 
        this->Par[0] = 1.0 / b_val[0];

        //  Evaluate if distribution can be defined on the paramater and if the moments are well defined 
        Std = std::sqrt((b_val[0] - 1.0) * ((b_val[0] - 1.0) + 1.0));
        break;

       case 2:
        //  Solve System of two equations for the parameters of the distribution 
        this->Par[1] = b_val[0] / (b_val[0] + b_val[1] * b_val[1]);
        this->Par[0] = this->Par[1] * b_val[0];

        //  Evaluate if distribution can be defined on the parameters
        if (ntf_mod(this->Par[0]) <= 0.0001) {
          this->Par[0] = ntf_rt_roundd_snf(this->Par[0]);
        }

        //  Define distribution
        //  Obj.Dist = mymakedist(name,'r',Obj.Par(1),'p',Obj.Par(2));
        break;

       case 3:
        this->Par[0] = b_val[0];

        //  Evaluate if moments match
        Std = std::sqrt(b_val[0]);
        break;

       case 4:
        //  Solve Equation for the parameter of the distribution based on the first moment 
        this->Par[0] = 1.0 / b_val[0];

        //  Evaluate if distribution can be defined on the paramater and if the moments are well defined 
        Std = b_val[0];
        break;

       case 5:
        //  Solve System of two equations for the parameters of the distribution 
        //                       syms a b;
        //                       sol        = solve(a/b==val(1),a/b^2==val(2)^2); 
        //                       Obj.Par(1) = double(sol.a);
        //                       Obj.Par(2) = double(sol.b);
        mu0 = b_val[1] * b_val[1];
        this->Par[1] = b_val[0] * b_val[0] / mu0;
        this->Par[0] = b_val[0] / mu0;

        //  Evaluate if distribution can be defined on the parameters
        break;

       case 6:
        //  Solve System of two equations for the parameters of the distribution 
        mu0 = b_val[0] - b_val[2];
        Var = b_val[3] - b_val[0];
        this->Par[0] = (Var * mu0 / (b_val[1] * b_val[1]) - 1.0) * mu0 / (b_val
          [3] - b_val[2]);
        this->Par[1] = this->Par[0] * Var / mu0;
        this->Par[2] = b_val[2];
        this->Par[3] = b_val[3];

        //  Evaluate if distribution can be defined on the parameters
        Mean = (this->Par[1] * b_val[2] + this->Par[0] * b_val[3]) / (this->Par
          [0] + this->Par[1]);

        // Std  =  Std*(Obj.Par(4)-Obj.Par(3));
        //                    case 'gumbelmin'   % mirror image of gumbel can be used to model minima 
        //                       ne = 0.57721566490153;   % euler constant
        //                       % Solve two equations for the parameters of the distribution 
        //                       Obj.Par(1) = val(2)*sqrt(6)/pi;       % scale parameter 
        //                       Obj.Par(2) = val(1) + ne*Obj.Par(1);  % location parameter 
        break;

       case 7:
        //  gumbel can be used to model maxima
        //  euler constant
        //  Solve two equations for the parameters of the distribution
        this->Par[0] = b_val[1] * 2.4494897427831779 / 3.1415926535897931;

        //  scale parameter
        this->Par[1] = b_val[0] - 0.57721566490153 * this->Par[0];

        //  location parameter
        //  Define distribution
        //  Obj.Dist = mymakedist('GeneralizedExtremeValue','k',0,'sigma',Obj.Par(1),'mu',Obj.Par(2));  
        //                   case 'frechet'
        //                      % Solve equation for the parameters of the distribution 
        //                      options = optimset('Display','off');
        //                      par0    = [2.001,1.0e3];
        //                      fun     = @(par) sqrt(gamma(1-2/par)-(gamma(1-1/par)).^2)./... 
        //                                       gamma(1-1/par)-val(2)/val(1);
        //                      [xs,~,exitflag] = fzero(fun,par0,options);
        //                      if exitflag > 0
        //                         Obj.Par(2) = xs;
        //                         Obj.Par(1) = val(1)/gamma(1-1/Obj.Par(2));
        //                      else
        //                         error('fzero could not converge to a solution for determining the parameters of the frechet distribution'); 
        //                     end
        //  Evaluate if distribution can be defined on the parameters
        //                      if (Obj.Par(1) > 0) && (Obj.Par(2) > 0)
        //  Obj.Dist = mymakedist('GeneralizedExtremeValue','k',1/Obj.Par(2),'sigma',Obj.Par(1)/Obj.Par(2),'mu',Obj.Par(1)); 
        //                      else
        //                         error('Please select other moments');
        //                      end
        break;

       case 8:
        //  Solve equation for the parameters of the distribution
        fun.tunableEnvironment[0].f1[0] = b_val[0];
        fun.tunableEnvironment[0].f1[1] = b_val[1];
        fun.tunableEnvironment[0].f1[2] = b_val[2];
        fun.tunableEnvironment[0].f1[3] = b_val[3];
        ntf_fzero(fun, &lam0, &Var, &mu0);
        if (mu0 > 0.0) {
          this->Par[1] = lam0;
          mu0 = 1.0 / lam0 + 1.0;
          ntf_gamma(&mu0);
          this->Par[0] = b_val[0] / mu0;
        }

        //  Evaluate if distribution can be defined on the parameters
        break;

       case 9:
        //  Solve System of two equations for the parameters of the distribution 
        if (b_val[0] == b_val[2]) {
          this->Par[0] = -1.0;
          this->Par[1] = b_val[1];
          this->Par[2] = b_val[2];
        } else {
          fun.tunableEnvironment[0].f1[0] = b_val[0];
          fun.tunableEnvironment[0].f1[1] = b_val[1];
          fun.tunableEnvironment[0].f1[2] = b_val[2];
          fun.tunableEnvironment[0].f1[3] = b_val[3];
          if (b_val[0] > b_val[2]) {
            lam1 = 0.3;
          } else {
            lam1 = -1.5;
          }

          ntf_b_fzero(fun, lam1, &lam0, &Var, &mu0);
          if (mu0 > 0.0) {
            this->Par[0] = lam0;
            mu0 = 1.0 - lam0;
            ntf_gamma(&mu0);
            this->Par[1] = (b_val[0] - b_val[2]) * lam0 / (mu0 - 1.0);
            this->Par[2] = b_val[2];
          }
        }

        //  Evaluate if distribution can be defined on the parameters
        //                    case 'gevmin' % mirror image of gumbel can be used to model maxima 
        //                       % Solve System of two equations for the parameters of the distribution 
        //                       if val(1) == val(3)
        //                          Obj.Par(1) = -1;
        //                          Obj.Par(2) = val(2);
        //                          Obj.Par(3) = val(3);
        //                       else
        //                          options = optimset('Display','off');
        //                          if val(1) < val(3)
        //                             par0 = 0.3;
        //                          else
        //                             par0 = -1.5;
        //                          end
        //                          fun = @(par) (gamma(1-2*par)-gamma(1-par).^2)./(gamma(1-par)-1).^2-... 
        //                                       (val(2)/(-val(1)+val(3)))^2;
        //                          [xs,~,exitflag] = fzero(fun,par0,options);
        //                          if exitflag > 0
        //                             Obj.Par(1) = xs;
        //                             Obj.Par(2) = -(val(1)-val(3))*Obj.Par(1)/(gamma(1-Obj.Par(1))-1); 
        //                             Obj.Par(3) = val(3);
        //                          else
        //                             error('fzero could not converge to a solution for determining the parameters of the GEV distribution') 
        //                          end
        //                       end
        //                       % Evaluate if distribution can be defined on the parameters 
        //                       if Obj.Par(2) > 0
        //                          % Obj.Dist = mymakedist('GeneralizedExtremeValue','k',Obj.Par(1),'sigma',Obj.Par(2),'mu',-Obj.Par(3)); 
        //                       else
        //                          error('Please select other moments');
        //                       end
        //                    case 'pareto'
        //                       % Solve System of two equations for the parameters of the distribution 
        //                       Obj.Par(2) = 1 + sqrt(1+(val(1)/val(2))^2);
        //                       Obj.Par(1) = val(1)*(Obj.Par(2)-1)/Obj.Par(2);
        //                       % Evaluate if distribution can be defined on the parameters 
        //                       if (Obj.Par(1) > 0) && (Obj.Par(2 )> 0)
        //                          % Obj.Dist = mymakedist('Generalizedpareto','k',1/Obj.Par(2),'sigma',Obj.Par(1)/Obj.Par(2),'theta',Obj.Par(1)); 
        //                       else
        //                          error('Please select other moments');
        //                       end
        break;

       case 10:
        //  Solve Equation for the parameter of the distribution based on the first moment 
        this->Par[0] = b_val[0] / 1.2533141373155001;

        //  Evaluate if distribution can be defined on the paramater and if the moments are well defined 
        Std = 0.65513637756203358 * this->Par[0];
        break;

       case 11:
        //  Solve Equation for the parameter of the distribution based on the first moment 
        this->Par[0] = b_val[0];

        //  Evaluate if distribution can be defined on the paramater and if the moments are well defined 
        if (ntf_mod(b_val[0]) <= 0.0001) {
          this->Par[0] = ntf_rt_roundd_snf(b_val[0]);
        }

        Std = std::sqrt(2.0 * b_val[0]);
        break;

       case 12:
        //  compute parameters
        mu0 = 3.4641016151377544 * b_val[1] / 2.0;
        this->Par[0] = b_val[0] - mu0;
        this->Par[1] = b_val[0] + mu0;

        //  Define distribution
        //  Obj.Dist = mymakedist(name,'lower',Obj.Par(1),'upper',Obj.Par(2));
        break;

       case 13:
        //  special case of normal distribution
        this->Par[0] = 0.0;
        this->Par[1] = 1.0;

        //  Obj.Dist = mymakedist('normal');
        break;

       case 14:
        this->Par[0] = b_val[0];
        this->Par[1] = b_val[1];

        //  Obj.Dist = mymakedist(name,'mu',val(1),'sigma',val(2));
        break;

       case 15:
        //  Solve two equations for the parameters of the distribution
        Var = b_val[1] / b_val[0];
        mu0 = Var * Var + 1.0;
        this->Par[0] = std::log(b_val[0]) - std::log(std::sqrt(mu0));

        //  mean normal
        this->Par[1] = std::sqrt(std::log(mu0));

        //  sigma normal
        //  Obj.Dist   = mymakedist(name,'mu',Obj.Par(1),'sigma',Obj.Par(2));
        break;

       case 16:
        {
          int b_i;
          boolean_T exitg1;

          // %%
          this->Par[1] = b_val[1];
          this->Par[2] = b_val[2];
          ntf_linspace(0.0, 1.0 / (b_val[0] - b_val[1]), lambs);
          Obj_tmp = *this;
          Var = 0.0;
          lam0 = 0.0;
          vlen = 0;
          ntf_linspace(b_val[1], b_val[2], b_xx);
          b_i = 0;
          exitg1 = false;
          while ((!exitg1) && (b_i < 1000)) {
            lam1 = lambs[b_i];
            Obj_tmp.Par[0] = lambs[b_i];
            Obj_tmp.ntf_fb_pdf(b_xx, b_y1);
            for (i = 0; i < 1000; i++) {
              b_y1[i] *= b_xx[i];
            }

            mean1 = ntf_trapz(b_xx, b_y1);
            if (mean1 - b_val[0] < 0.0) {
              vlen = 1;
              exitg1 = true;
            } else {
              Var = mean1;
              lam0 = lambs[b_i];
              b_i++;
            }
          }

          if (vlen == 0) {
            ntf_linspace(b_val[1], lambs[1], y2);
            b_i = 0;
            exitg1 = false;
            while ((!exitg1) && (b_i < 1000)) {
              lam1 = y2[b_i];
              Obj_tmp.Par[0] = y2[b_i];
              Obj_tmp.ntf_fb_pdf(b_xx, b_y1);
              for (i = 0; i < 1000; i++) {
                b_y1[i] *= b_xx[i];
              }

              mean1 = ntf_trapz(b_xx, b_y1);
              if (mean1 - b_val[0] < 0.0) {
                exitg1 = true;
              } else {
                Var = mean1;
                lam0 = y2[b_i];
                b_i++;
              }
            }
          }

          this->Par[0] = lam0 + (b_val[0] - Var) * (lam1 - lam0) / (mean1 - Var);
          for (k = 0; k < 1000; k++) {
            y2[k] = ntf_rt_powd_snf(b_xx[k], 2.0);
          }

          this->ntf_fb_pdf(b_xx, lambs);
          for (i = 0; i < 1000; i++) {
            y2[i] *= lambs[i];
          }

          Std = std::sqrt(ntf_trapz(b_xx, y2) - b_val[0] * b_val[0]);
        }
        break;
      }

      // -----------------------------------------------------------------
    }
    break;

   case 2:
    {
      val.set_size(val_temp.size(1));
      vlen = val_temp.size(1);
      for (i = 0; i < vlen; i++) {
        val[i] = val_temp[i];
      }

      switch_expression.set_size(name.size(0), name.size(1));
      i = name.size(1);
      for (k = 0; k < i; k++) {
        switch_expression[k] = ntf_cv[static_cast<unsigned char>(name[k]) & 127];
      }

      if (ntf_f_strcmp(switch_expression)) {
        vlen = 0;
      } else if (ntf_g_strcmp(switch_expression)) {
        vlen = 1;
      } else if (ntf_h_strcmp(switch_expression)) {
        vlen = 2;
      } else if (ntf_i_strcmp(switch_expression)) {
        vlen = 3;
      } else if (ntf_u_strcmp(switch_expression, t7_f1)) {
        vlen = 4;
      } else if (ntf_v_strcmp(switch_expression, t7_f2)) {
        vlen = 4;
      } else if (ntf_w_strcmp(switch_expression)) {
        vlen = 5;
      } else if (ntf_j_strcmp(switch_expression)) {
        vlen = 6;
      } else if (ntf_k_strcmp(switch_expression)) {
        vlen = 7;
      } else if (ntf_l_strcmp(switch_expression)) {
        vlen = 8;
      } else if (ntf_r_strcmp(switch_expression)) {
        vlen = 9;
      } else if (ntf_m_strcmp(switch_expression)) {
        vlen = 10;
      } else if (ntf_n_strcmp(switch_expression)) {
        vlen = 11;
      } else if (ntf_o_strcmp(switch_expression)) {
        vlen = 12;
      } else if (ntf_p_strcmp(switch_expression)) {
        vlen = 13;
      } else if (ntf_q_strcmp(switch_expression)) {
        vlen = 14;
      } else if (ntf_y_strcmp(switch_expression)) {
        vlen = 15;
      } else if (ntf_x_strcmp(switch_expression)) {
        vlen = 16;
      } else {
        vlen = -1;
      }

      switch (vlen) {
       case 0:
        //  Error occurs by using fitdist
        // =============Additionally needs N ==============
        this->Par[0] = add[0];
        vlen = val.size(0);
        if (val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += val[k - 1];
          }
        }

        this->Par[1] = mu0 / add[0] / static_cast<double>(val.size(0));
        ntf_binostat(add[0], this->Par[1], &Mean, &Var);
        break;

       case 1:
        //  see negativebinomial
        //  Fit based on moment
        vlen = val.size(0);
        if (val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += val[k - 1];
          }
        }

        Mean = mu0 / static_cast<double>(val.size(0));
        Var = ntf_var(val);
        this->Par[0] = 1.0 / Mean;
        break;

       case 2:
        //  Error occurs by using fitdist
        //  Method of moment
        lam0 = ntf_std(val);
        vlen = val.size(0);
        if (val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += val[k - 1];
          }
        }

        mu0 /= static_cast<double>(val.size(0));
        vlen = val.size(0);
        if (val.size(0) == 0) {
          Var = 0.0;
        } else {
          Var = val[0];
          for (k = 2; k <= vlen; k++) {
            Var += val[k - 1];
          }
        }

        Var /= static_cast<double>(val.size(0));
        this->Par[1] = mu0 / (Var + lam0 * lam0);
        vlen = val.size(0);
        if (val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += val[k - 1];
          }
        }

        mu0 /= static_cast<double>(val.size(0));
        this->Par[0] = this->Par[1] * mu0;
        ntf_b_mod(val, F);
        vlen = F.size(0);
        if (F.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = F[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += F[k - 1];
          }
        }

        if (mu0 < 0.01) {
          vlen = val.size(0);
          if (val.size(0) == 0) {
            mu0 = 0.0;
          } else {
            mu0 = val[0];
            for (k = 2; k <= vlen; k++) {
              mu0 += val[k - 1];
            }
          }

          mu0 /= static_cast<double>(val.size(0));
          this->Par[0] = ntf_rt_roundd_snf(this->Par[1] * mu0);
        }

        ntf_nbinstat(this->Par[0], this->Par[1], &Mean, &Var);
        Mean += this->Par[0];
        break;

       case 3:
        vlen = val.size(0);
        if (val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += val[k - 1];
          }
        }

        Mean = mu0 / static_cast<double>(val.size(0));
        Var = Mean;
        this->Par[0] = Mean;
        break;

       case 4:
        {
          ntf_prob_coder_NormalDistributi Dist;
          Dist = ntf_prob_coder_NormalDistributi::ntf_fit((val));
          this->Par[0] = Dist.ParameterValues[0];
          this->Par[1] = Dist.ParameterValues[1];
          Mean = Dist.ParameterValues[0];
          Var = Dist.ParameterValues[1] * Dist.ParameterValues[1];
        }
        break;

       case 5:
        {
          ntf_prob_coder_LognormalDistrib b_Dist;
          b_Dist = ntf_prob_coder_LognormalDistrib::ntf_fit((val));
          this->Par[0] = b_Dist.ParameterValues[0];
          this->Par[1] = b_Dist.ParameterValues[1];
          ntf_lognstat(b_Dist.ParameterValues[0], b_Dist.ParameterValues[1],
                       &Mean, &Var);
        }
        break;

       case 6:
        {
          ntf_prob_coder_ExponentialDistr r;
          r = ntf_prob_coder_ExponentialDistr::ntf_fit((val));
          this->Par[0] = 1.0 / r.ParameterValues;
          Mean = 1.0 / this->Par[0];
          if (Mean > 0.0) {
            Var = Mean * Mean;
          } else {
            Mean = rtNaN;
            Var = rtNaN;
          }
        }
        break;

       case 7:
        //  Method of moment
        vlen = val.size(0);
        if (val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += val[k - 1];
          }
        }

        Var = mu0 / static_cast<double>(val.size(0));
        mu0 = ntf_b_var(val);
        b_init[0] = Var * Var / mu0;
        b_init[1] = 1.0 / (Var / mu0);

        //  maximum likelihood
        c_this.tunableEnvironment[0].f1.set_size(val.size(0));
        vlen = val.size(0);
        for (i = 0; i < vlen; i++) {
          c_this.tunableEnvironment[0].f1[i] = val[i];
        }

        ntf_b_fminsearch(&c_this, b_init);
        this->Par[1] = b_init[0];
        this->Par[0] = 1.0 / b_init[1];
        Var = 1.0 / this->Par[0];
        if ((b_init[0] > 0.0) && (Var > 0.0)) {
          Mean = b_init[0] * Var;
          Var *= Mean;
        } else {
          Mean = rtNaN;
          Var = rtNaN;
        }
        break;

       case 8:
        {
          ntf_prob_coder_BetaDistribution e_Dist;

          //  Upper and lower bound have to be implemented
          Var = add[0];
          mu0 = add[1] - add[0];
          vlen = val.size(0);
          for (i = 0; i < vlen; i++) {
            val[i] = (val[i] - Var) / mu0;
          }

          e_Dist = ntf_prob_coder_BetaDistribution::ntf_fit((val));
          this->Par[0] = e_Dist.ParameterValues[0];
          this->Par[1] = e_Dist.ParameterValues[1];
          this->Par[2] = add[0];
          this->Par[3] = add[1];
          if ((e_Dist.ParameterValues[0] > 0.0) && (e_Dist.ParameterValues[1] >
               0.0)) {
            Var = e_Dist.ParameterValues[0] + e_Dist.ParameterValues[1];
            Var = e_Dist.ParameterValues[0] / Var * e_Dist.ParameterValues[1] /
              (Var * (Var + 1.0));
          } else {
            Var = rtNaN;
          }

          Mean = (e_Dist.ParameterValues[1] * add[0] + e_Dist.ParameterValues[0]
                  * add[1]) / (e_Dist.ParameterValues[0] +
                               e_Dist.ParameterValues[1]);
          Var *= mu0 * mu0;
        }
        break;

       case 9:
        //  to model the minimum value
        Var = ntf_minimum(val);
        lam0 = ntf_maximum(val);
        this->Par[1] = Var + (static_cast<double>(val.size(0)) + 1.0) * (lam0 -
          Var) / static_cast<double>(val.size(0));
        this->Par[0] = lam0 + (static_cast<double>(val.size(0)) + 1.0) * (Var -
          lam0) / static_cast<double>(val.size(0));

        //  Quasi-unbiased estimator
        if (this->Par[0] <= this->Par[1]) {
          Mean = (this->Par[0] + this->Par[1]) / 2.0;
          Var = this->Par[1] - this->Par[0];
          Var = Var * Var / 12.0;
        } else {
          Mean = rtNaN;
          Var = rtNaN;
        }

        //                 case 'gumbelmin'   % to model the minimum value
        //                    Dist = fitdist(val,'extremevalue');
        //                    Obj.Par(2) = Dist.ParameterValues(1);
        //                    Obj.Par(1) = Dist.ParameterValues(2);
        //
        //                    [Mean ,Var] = evstat(Obj.Par(2),Obj.Par(1));
        break;

       case 10:
        {
          ntf_prob_coder_ExtremeValueDist d_Dist;

          //  to model the maximum value, use the negative of the original values 
          vlen = val.size(0);
          for (i = 0; i < vlen; i++) {
            val[i] = -val[i];
          }

          d_Dist = ntf_prob_coder_ExtremeValueDist::ntf_fit((val));
          this->Par[0] = d_Dist.ParameterValues[1];
          this->Par[1] = -d_Dist.ParameterValues[0];
          if ((d_Dist.ParameterValues[1] > 0.0) && (!rtIsNaN
               (-d_Dist.ParameterValues[0]))) {
            Mean = -d_Dist.ParameterValues[0] + 0.57721566490153231 *
              d_Dist.ParameterValues[1];
            Var = 1.6449340668482264 * (d_Dist.ParameterValues[1] *
              d_Dist.ParameterValues[1]);
          } else {
            Mean = rtNaN;
            Var = rtNaN;
          }

          //                case 'frechet'
          //
          //                   % Obj.Dist=fitdist(val,'Generalized ExtremeValue');                  
          //                   Dist=fitdist(1./val,'Weibull');
          //                   Obj.Par(1) = 1/Dist.ParameterValues(1);                       
          //                   Obj.Par(2) = Dist.ParameterValues(2);
          //                   [Mean ,Var] = gevstat(1/Obj.Par(2),Obj.Par(1)/Obj.Par(2),Obj.Par(1)); 
        }
        break;

       case 11:
        {
          ntf_prob_coder_WeibullDistribut c_Dist;
          c_Dist = ntf_prob_coder_WeibullDistribut::ntf_fit((val));
          this->Par[0] = c_Dist.ParameterValues[0];
          this->Par[1] = c_Dist.ParameterValues[1];
          ntf_wblstat(c_Dist.ParameterValues[0], c_Dist.ParameterValues[1],
                      &Mean, &Var);
        }
        break;

       case 12:
        ntf_sort(val);
        if (static_cast<double>(val.size(0)) - 0.5 < 0.5) {
          y.set_size(1, 0);
        } else {
          ntf_eml_float_colon(static_cast<double>(val.size(0)) - 0.5, y);
        }

        F.set_size(y.size(1));
        vlen = y.size(1);
        for (i = 0; i < vlen; i++) {
          F[i] = y[i] / static_cast<double>(val.size(0));
        }

        b_this.tunableEnvironment[0].f1.set_size(val.size(0));
        vlen = val.size(0);
        for (i = 0; i < vlen; i++) {
          b_this.tunableEnvironment[0].f1[i] = val[i];
        }

        b_this.tunableEnvironment[1].f1.set_size(F.size(0));
        vlen = F.size(0);
        for (i = 0; i < vlen; i++) {
          b_this.tunableEnvironment[1].f1[i] = F[i];
        }

        Var = ntf_fminsearch(&b_this);
        ntf_gevinv(F, Var, r2);
        ntf_polyfit(r2, val, b_init);
        lam0 = b_init[0];
        mu0 = b_init[1];
        if (((Var < 0.0) && (ntf_maximum(val) > -b_init[0] / Var + b_init[1])) ||
            ((Var > 0.0) && (ntf_minimum(val) < -b_init[0] / Var + b_init[1])))
        {
          //  The initial value calculation failed -- the data are not even in the 
          //  support of the parameter guesses.  Fall back to an EV, whose support is 
          //  unbounded.
          Var = 0.0;
          ntf_evfit(val, b_init);
          lam0 = b_init[1];
          mu0 = b_init[0];
        }

        //  maximum likelihood
        c_this.tunableEnvironment[0].f1.set_size(val.size(0));
        vlen = val.size(0);
        for (i = 0; i < vlen; i++) {
          c_this.tunableEnvironment[0].f1[i] = val[i];
        }

        b[0] = Var;
        b[1] = std::log(lam0);
        b[2] = mu0;
        ntf_d_fminsearch(&c_this, b);
        this->Par[0] = b[0];
        this->Par[1] = std::exp(b[1]);
        this->Par[2] = b[2];
        ntf_gevstat(b[0], this->Par[1], b[2], &Mean, &Var);

        //                  case 'gevmin'
        //                      val=sort(-val);
        //                      F = (.5:1:(length(val)-.5))' ./ length(val);
        //                      %k0 = fminsearch(@(k) 1-corr(val,gevinv(F,k,1,0)), 0); 
        //                      k0 = fminsearch(@(k) 1-[1 0]*corrcoef(val,gevinv(F,k,1,0))*[0; 1], 0); 
        //                      bt = polyfit(gevinv(F,k0,1,0),val,1);
        //                      sigma0 = bt(1);
        //                      mu0 = bt(2);
        //                      if (k0 < 0 && (max(val) > -sigma0/k0+mu0)) || (k0 > 0 && (min(val) < -sigma0/k0+mu0)) 
        //                          % The initial value calculation failed -- the data are not even in the 
        //                          % support of the parameter guesses.  Fall back to an EV, whose support is 
        //                          % unbounded.
        //                          k0 = 0;
        //                          evparms = evfit(val);
        //                          sigma0 = evparms(2);
        //                          mu0 = evparms(1);
        //                      end
        //                      init = [k0 log(sigma0) mu0];
        //
        //                    % maximum likelihood
        //                    b=fminsearch(@(b) nllGEV(b,val),init);
        //                    Obj.Par(1) = b(1);
        //                    Obj.Par(2) = exp(b(2));
        //                    Obj.Par(3) = -b(3);
        //                    [Mean ,Var] = gevstat(Obj.Par(1),Obj.Par(2),-Obj.Par(3));                   
        //                    Mean=-Mean;
        //                 case 'pareto'
        //                    %error('The pareto distribution is not supported in DATA'); 
        //                    % Method of Moment
        //                   Obj.Par(2) = 1 + sqrt(1+(mean(val)/std(val))^2);
        //                   Obj.Par(1) =mean(val)*(Obj.Par(2)-1)/Obj.Par(2);
        //                   Mean=mean(val);
        //                   Var=var(val);
        break;

       case 13:
        // Dist = fitdist(val,'rayleigh');
        // Obj.Par(1) = Dist.ParameterValues;
        F.set_size(val.size(0));
        vlen = val.size(0);
        for (k = 0; k < vlen; k++) {
          F[k] = ntf_rt_powd_snf(val[k], 2.0);
        }

        vlen = F.size(0);
        if (F.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = F[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += F[k - 1];
          }
        }

        mu0 /= static_cast<double>(F.size(0));
        this->Par[0] = std::sqrt(0.5 * mu0);
        if (this->Par[0] > 0.0) {
          Mean = this->Par[0] * 1.2533141373155001;
          Var = 0.42920367320510344 * (this->Par[0] * this->Par[0]);
        } else {
          Mean = rtNaN;
          Var = rtNaN;
        }
        break;

       case 14:
        // error('The chi-square distribution is not supported in DATA');
        vlen = val.size(0);
        if (val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += val[k - 1];
          }
        }

        Mean = mu0 / static_cast<double>(val.size(0));
        this->Par[0] = Mean;

        //  Evaluate if distribution can be defined on the paramater and if the moments are well defined 
        if (ntf_mod(Mean) <= 0.0001) {
          this->Par[0] = ntf_rt_roundd_snf(Mean);
        }

        Var = 2.0 * Mean;
        break;

       case 15:
        {
          int i1;
          ntf_unique_vector(val, F);
          pval.set_size(1, F.size(0));
          i = F.size(0);
          for (int b_i = 0; b_i < i; b_i++) {
            vlen = val.size(0);
            c_val.set_size(val.size(0));
            for (i1 = 0; i1 < vlen; i1++) {
              c_val[i1] = (val[i1] == F[b_i]);
            }

            ntf_eml_find(c_val, r1);
            pval[b_i] = static_cast<double>(r1.size(0)) / static_cast<double>
              (val.size(0));
          }

          this->Multinomial.set_size(1, (F.size(0) * 2));
          vlen = F.size(0) * 2;
          for (i = 0; i < vlen; i++) {
            this->Multinomial[i] = 0.0;
          }

          if (1 > (F.size(0) << 1)) {
            i = 1;
            i1 = 0;
          } else {
            i = 2;
            i1 = F.size(0) << 1;
          }

          vlen = ntf_div_s32_floor(i1 - 1, i) + 1;
          for (i1 = 0; i1 < vlen; i1++) {
            this->Multinomial[i * i1] = F[i1];
          }

          if (2 > this->Multinomial.size(1)) {
            i = 0;
            i1 = 1;
          } else {
            i = 1;
            i1 = 2;
          }

          vlen = pval.size(1);
          for (int i2 = 0; i2 < vlen; i2++) {
            this->Multinomial[i + i1 * i2] = pval[i2];
          }

          vlen = val.size(0);
          if (val.size(0) == 0) {
            mu0 = 0.0;
          } else {
            mu0 = val[0];
            for (k = 2; k <= vlen; k++) {
              mu0 += val[k - 1];
            }
          }

          Mean = mu0 / static_cast<double>(val.size(0));
          Var = ntf_b_var(val);
        }
        break;

       case 16:
        {
          int b_i;
          boolean_T exitg1;

          //                     %% approximated METHOD OF MOMENTS
          vlen = val.size(0);
          if (val.size(0) == 0) {
            mu0 = 0.0;
          } else {
            mu0 = val[0];
            for (k = 2; k <= vlen; k++) {
              mu0 += val[k - 1];
            }
          }

          Mean = mu0 / static_cast<double>(val.size(0));
          this->Par[1] = add[0];
          this->Par[2] = add[1];
          ntf_linspace(0.0, 1.0 / (Mean - add[0]), lambs);
          Obj_tmp = *this;
          Var = 0.0;
          lam0 = 0.0;
          vlen = 0;
          ntf_b_linspace(add[0], add[1], xx);
          b_i = 0;
          exitg1 = false;
          while ((!exitg1) && (b_i < 1000)) {
            lam1 = lambs[b_i];
            Obj_tmp.Par[0] = lambs[b_i];
            Obj_tmp.ntf_gb_pdf(xx, c_y1);
            for (i = 0; i < 5000; i++) {
              c_y1[i] *= xx[i];
            }

            mean1 = ntf_b_trapz(xx, c_y1);
            if (mean1 - Mean < 0.0) {
              vlen = 1;
              exitg1 = true;
            } else {
              Var = mean1;
              lam0 = lambs[b_i];
              b_i++;
            }
          }

          if (vlen == 0) {
            ntf_linspace(add[0], lambs[1], y2);
            b_i = 0;
            exitg1 = false;
            while ((!exitg1) && (b_i < 1000)) {
              lam1 = y2[b_i];
              Obj_tmp.Par[0] = y2[b_i];
              Obj_tmp.ntf_gb_pdf(xx, c_y1);
              for (i = 0; i < 5000; i++) {
                c_y1[i] *= xx[i];
              }

              mean1 = ntf_b_trapz(xx, c_y1);
              if (mean1 - Mean < 0.0) {
                exitg1 = true;
              } else {
                Var = mean1;
                lam0 = y2[b_i];
                b_i++;
              }
            }
          }

          this->Par[0] = lam0 + (Mean - Var) * (lam1 - lam0) / (mean1 - Var);
          for (k = 0; k < 5000; k++) {
            b_y2[k] = ntf_rt_powd_snf(xx[k], 2.0);
          }

          this->ntf_gb_pdf(xx, c_y1);
          for (i = 0; i < 5000; i++) {
            b_y2[i] *= c_y1[i];
          }

          Var = ntf_b_trapz(xx, b_y2) - Mean * Mean;

          // Std2=std(val);
        }
        break;
      }

      // }
      Std = std::sqrt(Var);
    }
    break;
  }

  this->mean = Mean;
  this->std = Std;
}

//
// Arguments    : const coder::array<double, 1U> &x
//                coder::array<double, 1U> &CDF
// Return Type  : void
//
void ntf_ERADist::ntf_o_cdf(const coder::array<double, 1U> &x, coder::array<
  double, 1U> &CDF) const
{
  int vlen;
  int i;
  coder::array<char, 2U> switch_expression;
  int k;
  boolean_T b_bool;
  int exitg1;
  static const char b_cv[8] = { 'b', 'i', 'n', 'o', 'm', 'i', 'a', 'l' };

  double CDF_max;
  coder::array<double, 1U> b_x;
  int i1;
  int i2;
  coder::array<double, 2U> c_x;
  int loop_ub;
  int i3;
  int i4;
  static const char b_cv1[7] = { 'p', 'o', 'i', 's', 's', 'o', 'n' };

  static const char b_cv2[4] = { 'b', 'e', 't', 'a' };

  static const char b_cv3[3] = { 'g', 'e', 'v' };

  static const char t11_f1[6] = { 'n', 'o', 'r', 'm', 'a', 'l' };

  static const char t11_f2[8] = { 'g', 'a', 'u', 's', 's', 'i', 'a', 'n' };

  // -----------------------------------------------------------------------
  //     function Mean = mean(Obj)
  //        switch lower(Obj.Name)
  //           case 'geometric'
  //              Mean = Obj.Dist.mean+1;
  //           case 'negativebinomial'
  //              Mean = Obj.Dist.mean+Obj.Dist.R;
  //           case 'beta'
  //              Mean = (Obj.Par(2)*Obj.Par(3)+Obj.Par(1)*Obj.Par(4))/(Obj.Par(1)+Obj.Par(2));    
  //           case 'gevmin'
  //              Mean = -Obj.Dist.mean;
  //           case 'frechet'
  //              Mean = Obj.Par(1)*gamma(1-1/Obj.Par(2));
  //           otherwise
  //              Mean = Obj.Dist.mean;
  //        end
  //     end
  //
  // -----------------------------------------------------------------------
  //     function Standarddeviation = std(Obj)
  //        switch lower(Obj.Name)
  //           case 'beta'
  //              Standarddeviation = Obj.Dist.std*(Obj.Par(4)-Obj.Par(3));
  //           otherwise
  //              Standarddeviation = Obj.Dist.std;
  //        end
  //     end
  // -----------------------------------------------------------------------
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
  CDF.set_size(x.size(0));
  vlen = x.size(0);
  for (i = 0; i < vlen; i++) {
    CDF[i] = 0.0;
  }

  switch_expression.set_size(this->Name.size(0), this->Name.size(1));
  i = this->Name.size(1);
  for (k = 0; k < i; k++) {
    switch_expression[k] = ntf_cv[static_cast<unsigned char>(this->Name[k]) &
      127];
  }

  b_bool = false;
  if (switch_expression.size(1) == 8) {
    vlen = 0;
    do {
      exitg1 = 0;
      if (vlen < 8) {
        if (switch_expression[vlen] != b_cv[vlen]) {
          exitg1 = 1;
        } else {
          vlen++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  if (b_bool) {
    vlen = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      vlen = 0;
      do {
        exitg1 = 0;
        if (vlen < 9) {
          if (switch_expression[vlen] != ntf_cv3[vlen]) {
            exitg1 = 1;
          } else {
            vlen++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }

    if (b_bool) {
      vlen = 1;
    } else {
      b_bool = false;
      if (switch_expression.size(1) == 16) {
        vlen = 0;
        do {
          exitg1 = 0;
          if (vlen < 16) {
            if (switch_expression[vlen] != ntf_cv4[vlen]) {
              exitg1 = 1;
            } else {
              vlen++;
            }
          } else {
            b_bool = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }

      if (b_bool) {
        vlen = 2;
      } else {
        b_bool = false;
        if (switch_expression.size(1) == 7) {
          vlen = 0;
          do {
            exitg1 = 0;
            if (vlen < 7) {
              if (switch_expression[vlen] != b_cv1[vlen]) {
                exitg1 = 1;
              } else {
                vlen++;
              }
            } else {
              b_bool = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (b_bool) {
          vlen = 3;
        } else if (ntf_j_strcmp(switch_expression)) {
          vlen = 4;
        } else if (ntf_k_strcmp(switch_expression)) {
          vlen = 5;
        } else {
          b_bool = false;
          if (switch_expression.size(1) == 4) {
            vlen = 0;
            do {
              exitg1 = 0;
              if (vlen < 4) {
                if (switch_expression[vlen] != b_cv2[vlen]) {
                  exitg1 = 1;
                } else {
                  vlen++;
                }
              } else {
                b_bool = true;
                exitg1 = 1;
              }
            } while (exitg1 == 0);
          }

          if (b_bool) {
            vlen = 6;
          } else if (ntf_m_strcmp(switch_expression)) {
            vlen = 7;
          } else if (ntf_n_strcmp(switch_expression)) {
            vlen = 8;
          } else {
            b_bool = false;
            if (switch_expression.size(1) == 3) {
              vlen = 0;
              do {
                exitg1 = 0;
                if (vlen < 3) {
                  if (switch_expression[vlen] != b_cv3[vlen]) {
                    exitg1 = 1;
                  } else {
                    vlen++;
                  }
                } else {
                  b_bool = true;
                  exitg1 = 1;
                }
              } while (exitg1 == 0);
            }

            if (b_bool) {
              vlen = 9;
            } else if (ntf_p_strcmp(switch_expression)) {
              vlen = 10;
            } else if (ntf_q_strcmp(switch_expression)) {
              vlen = 11;
            } else if (ntf_r_strcmp(switch_expression)) {
              vlen = 12;
            } else {
              b_bool = false;
              if (switch_expression.size(1) == 14) {
                vlen = 0;
                do {
                  exitg1 = 0;
                  if (vlen < 14) {
                    if (switch_expression[vlen] != ntf_cv1[vlen]) {
                      exitg1 = 1;
                    } else {
                      vlen++;
                    }
                  } else {
                    b_bool = true;
                    exitg1 = 1;
                  }
                } while (exitg1 == 0);
              }

              if (b_bool) {
                vlen = 13;
              } else {
                b_bool = false;
                if (switch_expression.size(1) == 16) {
                  vlen = 0;
                  do {
                    exitg1 = 0;
                    if (vlen < 16) {
                      if (switch_expression[vlen] != ntf_cv2[vlen]) {
                        exitg1 = 1;
                      } else {
                        vlen++;
                      }
                    } else {
                      b_bool = true;
                      exitg1 = 1;
                    }
                  } while (exitg1 == 0);
                }

                if (b_bool) {
                  vlen = 13;
                } else {
                  b_bool = false;
                  if (switch_expression.size(1) == 6) {
                    vlen = 0;
                    do {
                      exitg1 = 0;
                      if (vlen < 6) {
                        if (switch_expression[vlen] != t11_f1[vlen]) {
                          exitg1 = 1;
                        } else {
                          vlen++;
                        }
                      } else {
                        b_bool = true;
                        exitg1 = 1;
                      }
                    } while (exitg1 == 0);
                  }

                  if (b_bool) {
                    vlen = 14;
                  } else {
                    b_bool = false;
                    if (switch_expression.size(1) == 8) {
                      vlen = 0;
                      do {
                        exitg1 = 0;
                        if (vlen < 8) {
                          if (switch_expression[vlen] != t11_f2[vlen]) {
                            exitg1 = 1;
                          } else {
                            vlen++;
                          }
                        } else {
                          b_bool = true;
                          exitg1 = 1;
                        }
                      } while (exitg1 == 0);
                    }

                    if (b_bool) {
                      vlen = 14;
                    } else if (ntf_w_strcmp(switch_expression)) {
                      vlen = 15;
                    } else if (ntf_x_strcmp(switch_expression)) {
                      vlen = 16;
                    } else if (ntf_y_strcmp(switch_expression)) {
                      vlen = 17;
                    } else {
                      vlen = -1;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  switch (vlen) {
   case 0:
    ntf_cdf(x, this->Par[0], this->Par[1], CDF);
    break;

   case 1:
    // CDF = Obj.Dist.cdf(x-1);
    // CDF = cdf('negativebinomial',x,1,Obj.Par);
    b_x.set_size(x.size(0));
    vlen = x.size(0);
    for (i = 0; i < vlen; i++) {
      b_x[i] = x[i] - 1.0;
    }

    ntf_b_cdf(b_x, this->Par[0], CDF);
    break;

   case 2:
    // CDF = Obj.Dist.cdf(x-Obj.Par(1));
    // CDF  = cdf(name,x,Obj.Par(1),Obj.Par(2));
    b_x.set_size(x.size(0));
    vlen = x.size(0);
    for (i = 0; i < vlen; i++) {
      b_x[i] = x[i] - this->Par[0];
    }

    ntf_c_cdf(b_x, this->Par[0], this->Par[1], CDF);
    break;

   case 3:
    if (this->Par[1] == 0.0) {
      ntf_d_cdf(x, this->Par[0], CDF);
    } else {
      ntf_d_cdf(x, this->Par[0] * this->Par[1], CDF);
    }
    break;

   case 4:
    ntf_e_cdf(x, 1.0 / this->Par[0], CDF);
    break;

   case 5:
    ntf_f_cdf(x, this->Par[1], 1.0 / this->Par[0], CDF);
    break;

   case 6:
    // CDF = Obj.Dist.cdf();
    // CDF  = cdf(name,x,Obj.Par(1),Obj.Par(2));
    CDF_max = this->Par[3] - this->Par[2];
    b_x.set_size(x.size(0));
    vlen = x.size(0);
    for (i = 0; i < vlen; i++) {
      b_x[i] = (x[i] - this->Par[2]) / CDF_max;
    }

    ntf_g_cdf(b_x, this->Par[0], this->Par[1], CDF);

    //              case 'gumbelmin'  % this distribution can be used to model minima 
    //                  CDF  = cdf('Extreme Value',x,Obj.Par(2),Obj.Par(1));
    break;

   case 7:
    //  mirror image of this distribution can be used to model maxima
    CDF_max = this->Par[0];
    CDF.set_size(x.size(0));
    i = x.size(0);
    for (vlen = 0; vlen < i; vlen++) {
      if (CDF_max > 0.0) {
        CDF[vlen] = std::exp(-std::exp(-((x[vlen] - this->Par[1]) / CDF_max)));
      } else {
        CDF[vlen] = rtNaN;
      }
    }

    //             case 'frechet'
    //                 CDF  = cdf('Generalized Extreme Value',x,1/Obj.Par(2),Obj.Par(1)/Obj.Par(2),Obj.Par(1)); 
    break;

   case 8:
    ntf_h_cdf(x, this->Par[0], this->Par[1], CDF);
    break;

   case 9:
    ntf_i_cdf(x, this->Par[0], this->Par[1], this->Par[2], CDF);

    //              case 'gevmin'
    //                  CDF = cdf('Generalized Extreme Value',-x,Obj.Par(1),Obj.Par(2),-Obj.Par(3)); 
    break;

   case 10:
    ntf_j_cdf(x, this->Par[0], CDF);
    break;

   case 11:
    ntf_k_cdf(x, this->Par[0] / 2.0, CDF);
    break;

   case 12:
    ntf_l_cdf(x, this->Par[0], this->Par[1], CDF);
    break;

   case 13:
    CDF.set_size(x.size(0));
    i = x.size(0);
    for (k = 0; k < i; k++) {
      CDF_max = ntf_eml_erfcore(-x[k] / 1.4142135623730951);
      CDF[k] = 0.5 * CDF_max;
    }
    break;

   case 14:
    ntf_m_cdf(x, this->Par[0], this->Par[1], CDF);
    break;

   case 15:
    ntf_n_cdf(x, this->Par[0], this->Par[1], CDF);
    break;

   case 16:
    {
      double xk;
      double CDF_min;
      ntf_e_cdf(x, 1.0 / this->Par[0], CDF);
      CDF_max = 1.0 / this->Par[0];
      xk = this->Par[1];
      if ((CDF_max > 0.0) && (!rtIsNaN(this->Par[1]))) {
        if (this->Par[1] < 0.0) {
          xk = 0.0;
        }

        CDF_max = -(xk / CDF_max);
        ntf_expm1(&CDF_max);
        CDF_min = -CDF_max;
      } else {
        CDF_min = rtNaN;
      }

      CDF_max = 1.0 / this->Par[0];
      xk = this->Par[2];
      if ((CDF_max > 0.0) && (!rtIsNaN(this->Par[2]))) {
        if (this->Par[2] < 0.0) {
          xk = 0.0;
        }

        CDF_max = -(xk / CDF_max);
        ntf_expm1(&CDF_max);
        CDF_max = -CDF_max;
      } else {
        CDF_max = rtNaN;
      }

      CDF_max -= CDF_min;
      vlen = CDF.size(0);
      for (i = 0; i < vlen; i++) {
        CDF[i] = (CDF[i] - CDF_min) / CDF_max;
      }
    }
    break;

   case 17:
    i = x.size(0);
    if (0 <= x.size(0) - 1) {
      if (1 > this->Multinomial.size(1)) {
        i1 = 1;
        i2 = -1;
      } else {
        i1 = 2;
        i2 = this->Multinomial.size(1) - 1;
      }

      if (2 > this->Multinomial.size(1)) {
        i3 = 0;
        i4 = 1;
      } else {
        i3 = 1;
        i4 = 2;
      }

      loop_ub = ntf_div_s32_floor(i2, i1);
    }

    for (int ns = 0; ns < i; ns++) {
      c_x.set_size(1, (ntf_div_s32_floor(i2, i1) + 1));
      for (vlen = 0; vlen <= loop_ub; vlen++) {
        c_x[vlen] = static_cast<double>(x[ns] - this->Multinomial[i1 * vlen] >=
          0.0) * this->Multinomial[i3 + i4 * vlen];
      }

      vlen = c_x.size(1);
      if (c_x.size(1) == 0) {
        CDF_max = 0.0;
      } else {
        CDF_max = c_x[0];
        for (k = 2; k <= vlen; k++) {
          CDF_max += c_x[k - 1];
        }
      }

      CDF[ns] = CDF_max;
    }
    break;
  }
}

//
// File trailer for ntf_ERADist.cpp
//
// [EOF]
//
