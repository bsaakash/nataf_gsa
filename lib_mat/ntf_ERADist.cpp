//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_ERADist.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Jul-2020 21:26:42
//

// Include Files
#include "ntf_ERADist.h"
#include "ntf_BetaDistribution.h"
#include "ntf_ERANataf.h"
#include "ntf_ExponentialDistribution.h"
#include "ntf_ExtremeValueDistribution.h"
#include "ntf_LognormalDistribution.h"
#include "ntf_NormalDistribution.h"
#include "ntf_WeibullDistribution.h"
#include "ntf_binostat.h"
#include "ntf_cdf.h"
#include "ntf_colon.h"
#include "ntf_evfit.h"
#include "ntf_fminsearch.h"
#include "ntf_fzero.h"
#include "ntf_gamma.h"
#include "ntf_gampdf.h"
#include "ntf_gevinv.h"
#include "ntf_gevstat.h"
#include "ntf_gpstat.h"
#include "ntf_icdf.h"
#include "ntf_inataf.h"
#include "ntf_inataf_data.h"
#include "ntf_lognstat.h"
#include "ntf_minOrMax.h"
#include "ntf_mod.h"
#include "ntf_mod1.h"
#include "ntf_nbinstat.h"
#include "ntf_pdf.h"
#include "ntf_polyfit.h"
#include "ntf_sort.h"
#include "ntf_std.h"
#include "ntf_strcmp.h"
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
static double ntf_rt_roundd_snf(double u);

// Function Definitions

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
void ntf_ERADist::ntf_gb_icdf(const coder::array<double, 2U> &p, coder::array<
  double, 2U> &InverseCDF) const
{
  unsigned int unnamed_idx_1;
  int loop_ub;
  int i;
  coder::array<char, 2U> switch_expression;
  boolean_T b_bool;
  int exitg1;
  static const char b_cv[8] = { 'b', 'i', 'n', 'o', 'm', 'i', 'a', 'l' };

  static const char b_cv1[7] = { 'p', 'o', 'i', 's', 's', 'o', 'n' };

  static const char b_cv2[5] = { 'g', 'a', 'm', 'm', 'a' };

  static const char b_cv3[4] = { 'b', 'e', 't', 'a' };

  static const char b_cv4[6] = { 'g', 'u', 'm', 'b', 'e', 'l' };

  static const char b_cv5[7] = { 'f', 'r', 'e', 'c', 'h', 'e', 't' };

  static const char b_cv6[3] = { 'g', 'e', 'v' };

  static const char b_cv7[6] = { 'g', 'e', 'v', 'm', 'i', 'n' };

  static const char t9_f1[6] = { 'n', 'o', 'r', 'm', 'a', 'l' };

  static const char t9_f2[8] = { 'g', 'a', 'u', 's', 's', 'i', 'a', 'n' };

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
            } else {
              b_bool = false;
              if (switch_expression.size(1) == 4) {
                loop_ub = 0;
                do {
                  exitg1 = 0;
                  if (loop_ub < 4) {
                    if (switch_expression[loop_ub] != b_cv3[loop_ub]) {
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
                loop_ub = 6;
              } else {
                b_bool = false;
                if (switch_expression.size(1) == 9) {
                  loop_ub = 0;
                  do {
                    exitg1 = 0;
                    if (loop_ub < 9) {
                      if (switch_expression[loop_ub] != ntf_cv6[loop_ub]) {
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
                  loop_ub = 7;
                } else {
                  b_bool = false;
                  if (switch_expression.size(1) == 6) {
                    loop_ub = 0;
                    do {
                      exitg1 = 0;
                      if (loop_ub < 6) {
                        if (switch_expression[loop_ub] != b_cv4[loop_ub]) {
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
                    loop_ub = 8;
                  } else {
                    b_bool = false;
                    if (switch_expression.size(1) == 7) {
                      loop_ub = 0;
                      do {
                        exitg1 = 0;
                        if (loop_ub < 7) {
                          if (switch_expression[loop_ub] != b_cv5[loop_ub]) {
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
                      loop_ub = 9;
                    } else if (ntf_p_strcmp(switch_expression)) {
                      loop_ub = 10;
                    } else {
                      b_bool = false;
                      if (switch_expression.size(1) == 3) {
                        loop_ub = 0;
                        do {
                          exitg1 = 0;
                          if (loop_ub < 3) {
                            if (switch_expression[loop_ub] != b_cv6[loop_ub]) {
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
                        loop_ub = 11;
                      } else {
                        b_bool = false;
                        if (switch_expression.size(1) == 6) {
                          loop_ub = 0;
                          do {
                            exitg1 = 0;
                            if (loop_ub < 6) {
                              if (switch_expression[loop_ub] != b_cv7[loop_ub])
                              {
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
                          loop_ub = 12;
                        } else if (ntf_s_strcmp(switch_expression)) {
                          loop_ub = 13;
                        } else if (ntf_t_strcmp(switch_expression)) {
                          loop_ub = 14;
                        } else if (ntf_u_strcmp(switch_expression)) {
                          loop_ub = 15;
                        } else if (ntf_v_strcmp(switch_expression)) {
                          loop_ub = 16;
                        } else {
                          b_bool = false;
                          if (switch_expression.size(1) == 14) {
                            loop_ub = 0;
                            do {
                              exitg1 = 0;
                              if (loop_ub < 14) {
                                if (switch_expression[loop_ub] !=
                                    ntf_cv1[loop_ub]) {
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
                            loop_ub = 17;
                          } else {
                            b_bool = false;
                            if (switch_expression.size(1) == 16) {
                              loop_ub = 0;
                              do {
                                exitg1 = 0;
                                if (loop_ub < 16) {
                                  if (switch_expression[loop_ub] !=
                                      ntf_cv2[loop_ub]) {
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
                              loop_ub = 17;
                            } else {
                              b_bool = false;
                              if (switch_expression.size(1) == 6) {
                                loop_ub = 0;
                                do {
                                  exitg1 = 0;
                                  if (loop_ub < 6) {
                                    if (switch_expression[loop_ub] !=
                                        t9_f1[loop_ub]) {
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
                                loop_ub = 18;
                              } else {
                                b_bool = false;
                                if (switch_expression.size(1) == 8) {
                                  loop_ub = 0;
                                  do {
                                    exitg1 = 0;
                                    if (loop_ub < 8) {
                                      if (switch_expression[loop_ub] !=
                                          t9_f2[loop_ub]) {
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
                                  loop_ub = 18;
                                } else if (ntf_bb_strcmp(switch_expression)) {
                                  loop_ub = 19;
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
              }
            }
          }
        }
      }
    }
  }

  switch (loop_ub) {
   case 0:
    ntf_n_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 1:
    ntf_o_icdf(p, this->Par[0], InverseCDF);
    i = InverseCDF.size(0) * InverseCDF.size(1);
    InverseCDF.set_size(1, InverseCDF.size(1));
    loop_ub = i - 1;
    for (i = 0; i <= loop_ub; i++) {
      InverseCDF[i] = InverseCDF[i] + 1.0;
    }
    break;

   case 2:
    ntf_p_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    i = InverseCDF.size(0) * InverseCDF.size(1);
    InverseCDF.set_size(1, InverseCDF.size(1));
    loop_ub = i - 1;
    for (i = 0; i <= loop_ub; i++) {
      InverseCDF[i] = InverseCDF[i] + this->Par[0];
    }
    break;

   case 3:
    if (this->Par[1] == 0.0) {
      ntf_q_icdf(p, this->Par[0], InverseCDF);
    } else {
      ntf_q_icdf(p, this->Par[0] * this->Par[1], InverseCDF);
    }
    break;

   case 4:
    ntf_r_icdf(p, 1.0 / this->Par[0], InverseCDF);
    break;

   case 5:
    ntf_s_icdf(p, this->Par[1], 1.0 / this->Par[0], InverseCDF);
    break;

   case 6:
    {
      double b;
      ntf_t_icdf(p, this->Par[0], this->Par[1], InverseCDF);
      b = this->Par[3] - this->Par[2];
      i = InverseCDF.size(0) * InverseCDF.size(1);
      InverseCDF.set_size(1, InverseCDF.size(1));
      loop_ub = i - 1;
      for (i = 0; i <= loop_ub; i++) {
        InverseCDF[i] = InverseCDF[i] * b + this->Par[2];
      }
    }
    break;

   case 7:
    //  this distribution can be used to model minima
    // InverseCDF  = -icdf('Generalized Extreme Value',p,0,Obj.Par(1),-Obj.Par(2)); 
    // InverseCDF  = -icdf('Generalized Extreme Value',p,0,Obj.Par(1),-Obj.Par(2)); 
    ntf_u_icdf(p, this->Par[1], this->Par[0], InverseCDF);
    break;

   case 8:
    //  mirror image of this distribution can be used to model maxima
    ntf_v_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 9:
    ntf_w_icdf(p, 1.0 / this->Par[1], this->Par[0] / this->Par[1], this->Par[0],
               InverseCDF);
    break;

   case 10:
    ntf_x_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 11:
    ntf_w_icdf(p, this->Par[0], this->Par[1], this->Par[2], InverseCDF);
    break;

   case 12:
    ntf_w_icdf(p, this->Par[0], this->Par[1], -this->Par[2], InverseCDF);
    i = InverseCDF.size(0) * InverseCDF.size(1);
    InverseCDF.set_size(1, InverseCDF.size(1));
    loop_ub = i - 1;
    for (i = 0; i <= loop_ub; i++) {
      InverseCDF[i] = -InverseCDF[i];
    }
    break;

   case 13:
    ntf_y_icdf(p, 1.0 / this->Par[1], this->Par[0] / this->Par[1], this->Par[0],
               InverseCDF);
    break;

   case 14:
    ntf_ab_icdf(p, this->Par[0], InverseCDF);
    break;

   case 15:
    ntf_bb_icdf(p, this->Par[0] / 2.0, InverseCDF);
    break;

   case 16:
    ntf_cb_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 17:
    ntf_db_icdf(p, InverseCDF);
    break;

   case 18:
    ntf_eb_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 19:
    ntf_fb_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;
  }

  //     function InverseCDF = icdf(Obj,y)
  //        switch lower(Obj.Name)
  //           case 'geometric'
  //              InverseCDF = Obj.Dist.icdf(y)+1;
  //           case 'negativebinomial'
  //              InverseCDF = Obj.Dist.icdf(y)+Obj.Par(1);
  //           case 'beta'
  //              InverseCDF = Obj.Dist.icdf(y)*(Obj.Par(4)-Obj.Par(3))+Obj.Par(3); 
  //           case 'gumbelmin'
  //              InverseCDF = -Obj.Dist.icdf(y);
  //           case 'gevmin'
  //              InverseCDF = -Obj.Dist.icdf(y);
  //           otherwise
  //              InverseCDF = Obj.Dist.icdf(y);
  //        end
  //     end
  // -----------------------------------------------------------------------
  //     function Random = random(Obj,m,n)
  //        if nargin == 2
  //           switch lower(Obj.Name)
  //              case 'geometric'
  //                 Random = random(Obj.Dist,m)+1;
  //              case 'negativebinomial'
  //                 Random = random(Obj.Dist,m)+Obj.Par(1);
  //              case 'beta'
  //                 Random = random(Obj.Dist,m)*(Obj.Par(4)-Obj.Par(3))+Obj.Par(3); 
  //              case 'gumbelmin'
  //                 Random = -random(Obj.Dist,m);
  //              case 'gevmin'
  //                 Random = -random(Obj.Dist,m);
  //              otherwise
  //                 Random = random(Obj.Dist,m);
  //           end
  //        elseif nargin == 3
  //           switch lower(Obj.Name)
  //              case 'geometric'
  //                 Random = random(Obj.Dist,m,n)+1;
  //              case 'negativebinomial'
  //                 Random = random(Obj.Dist,m,n)+Obj.Par(1);
  //              case 'beta'
  //                 Random = random(Obj.Dist,m,n)*(Obj.Par(4)-Obj.Par(3))+Obj.Par(3); 
  //              case 'gumbelmin'
  //                 Random = -random(Obj.Dist,m,n);
  //              case 'gevmin'
  //                 Random = -random(Obj.Dist,m,n);
  //               otherwise
  //                 Random = random(Obj.Dist,m,n);
  //           end
  //        else
  //           error('Wrong Input in Method random');
  //        end
  //     end
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
void ntf_ERADist::ntf_gb_icdf(const double p[1048576], double InverseCDF[1048576])
  const
{
  coder::array<char, 2U> switch_expression;
  int kstr;
  int k;
  boolean_T b_bool;
  int exitg1;
  static const char b_cv[8] = { 'b', 'i', 'n', 'o', 'm', 'i', 'a', 'l' };

  static const char b_cv1[7] = { 'p', 'o', 'i', 's', 's', 'o', 'n' };

  static const char b_cv2[5] = { 'g', 'a', 'm', 'm', 'a' };

  static const char b_cv3[4] = { 'b', 'e', 't', 'a' };

  static const char b_cv4[6] = { 'g', 'u', 'm', 'b', 'e', 'l' };

  static const char b_cv5[7] = { 'f', 'r', 'e', 'c', 'h', 'e', 't' };

  static const char b_cv6[7] = { 'w', 'e', 'i', 'b', 'u', 'l', 'l' };

  static const char b_cv7[3] = { 'g', 'e', 'v' };

  static const char cv8[6] = { 'g', 'e', 'v', 'm', 'i', 'n' };

  static const char cv9[6] = { 'p', 'a', 'r', 'e', 't', 'o' };

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
  kstr = this->Name.size(1);
  for (k = 0; k < kstr; k++) {
    switch_expression[k] = ntf_cv[static_cast<unsigned char>(this->Name[k]) &
      127];
  }

  b_bool = false;
  if (switch_expression.size(1) == 8) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 8) {
        if (switch_expression[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  if (b_bool) {
    kstr = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      kstr = 0;
      do {
        exitg1 = 0;
        if (kstr < 9) {
          if (switch_expression[kstr] != ntf_cv3[kstr]) {
            exitg1 = 1;
          } else {
            kstr++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }

    if (b_bool) {
      kstr = 1;
    } else {
      b_bool = false;
      if (switch_expression.size(1) == 16) {
        kstr = 0;
        do {
          exitg1 = 0;
          if (kstr < 16) {
            if (switch_expression[kstr] != ntf_cv4[kstr]) {
              exitg1 = 1;
            } else {
              kstr++;
            }
          } else {
            b_bool = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }

      if (b_bool) {
        kstr = 2;
      } else {
        b_bool = false;
        if (switch_expression.size(1) == 7) {
          kstr = 0;
          do {
            exitg1 = 0;
            if (kstr < 7) {
              if (switch_expression[kstr] != b_cv1[kstr]) {
                exitg1 = 1;
              } else {
                kstr++;
              }
            } else {
              b_bool = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (b_bool) {
          kstr = 3;
        } else {
          b_bool = false;
          if (switch_expression.size(1) == 11) {
            kstr = 0;
            do {
              exitg1 = 0;
              if (kstr < 11) {
                if (switch_expression[kstr] != ntf_cv5[kstr]) {
                  exitg1 = 1;
                } else {
                  kstr++;
                }
              } else {
                b_bool = true;
                exitg1 = 1;
              }
            } while (exitg1 == 0);
          }

          if (b_bool) {
            kstr = 4;
          } else {
            b_bool = false;
            if (switch_expression.size(1) == 5) {
              kstr = 0;
              do {
                exitg1 = 0;
                if (kstr < 5) {
                  if (switch_expression[kstr] != b_cv2[kstr]) {
                    exitg1 = 1;
                  } else {
                    kstr++;
                  }
                } else {
                  b_bool = true;
                  exitg1 = 1;
                }
              } while (exitg1 == 0);
            }

            if (b_bool) {
              kstr = 5;
            } else {
              b_bool = false;
              if (switch_expression.size(1) == 4) {
                kstr = 0;
                do {
                  exitg1 = 0;
                  if (kstr < 4) {
                    if (switch_expression[kstr] != b_cv3[kstr]) {
                      exitg1 = 1;
                    } else {
                      kstr++;
                    }
                  } else {
                    b_bool = true;
                    exitg1 = 1;
                  }
                } while (exitg1 == 0);
              }

              if (b_bool) {
                kstr = 6;
              } else {
                b_bool = false;
                if (switch_expression.size(1) == 9) {
                  kstr = 0;
                  do {
                    exitg1 = 0;
                    if (kstr < 9) {
                      if (switch_expression[kstr] != ntf_cv6[kstr]) {
                        exitg1 = 1;
                      } else {
                        kstr++;
                      }
                    } else {
                      b_bool = true;
                      exitg1 = 1;
                    }
                  } while (exitg1 == 0);
                }

                if (b_bool) {
                  kstr = 7;
                } else {
                  b_bool = false;
                  if (switch_expression.size(1) == 6) {
                    kstr = 0;
                    do {
                      exitg1 = 0;
                      if (kstr < 6) {
                        if (switch_expression[kstr] != b_cv4[kstr]) {
                          exitg1 = 1;
                        } else {
                          kstr++;
                        }
                      } else {
                        b_bool = true;
                        exitg1 = 1;
                      }
                    } while (exitg1 == 0);
                  }

                  if (b_bool) {
                    kstr = 8;
                  } else {
                    b_bool = false;
                    if (switch_expression.size(1) == 7) {
                      kstr = 0;
                      do {
                        exitg1 = 0;
                        if (kstr < 7) {
                          if (switch_expression[kstr] != b_cv5[kstr]) {
                            exitg1 = 1;
                          } else {
                            kstr++;
                          }
                        } else {
                          b_bool = true;
                          exitg1 = 1;
                        }
                      } while (exitg1 == 0);
                    }

                    if (b_bool) {
                      kstr = 9;
                    } else {
                      b_bool = false;
                      if (switch_expression.size(1) == 7) {
                        kstr = 0;
                        do {
                          exitg1 = 0;
                          if (kstr < 7) {
                            if (switch_expression[kstr] != b_cv6[kstr]) {
                              exitg1 = 1;
                            } else {
                              kstr++;
                            }
                          } else {
                            b_bool = true;
                            exitg1 = 1;
                          }
                        } while (exitg1 == 0);
                      }

                      if (b_bool) {
                        kstr = 10;
                      } else {
                        b_bool = false;
                        if (switch_expression.size(1) == 3) {
                          kstr = 0;
                          do {
                            exitg1 = 0;
                            if (kstr < 3) {
                              if (switch_expression[kstr] != b_cv7[kstr]) {
                                exitg1 = 1;
                              } else {
                                kstr++;
                              }
                            } else {
                              b_bool = true;
                              exitg1 = 1;
                            }
                          } while (exitg1 == 0);
                        }

                        if (b_bool) {
                          kstr = 11;
                        } else {
                          b_bool = false;
                          if (switch_expression.size(1) == 6) {
                            kstr = 0;
                            do {
                              exitg1 = 0;
                              if (kstr < 6) {
                                if (switch_expression[kstr] != cv8[kstr]) {
                                  exitg1 = 1;
                                } else {
                                  kstr++;
                                }
                              } else {
                                b_bool = true;
                                exitg1 = 1;
                              }
                            } while (exitg1 == 0);
                          }

                          if (b_bool) {
                            kstr = 12;
                          } else {
                            b_bool = false;
                            if (switch_expression.size(1) == 6) {
                              kstr = 0;
                              do {
                                exitg1 = 0;
                                if (kstr < 6) {
                                  if (switch_expression[kstr] != cv9[kstr]) {
                                    exitg1 = 1;
                                  } else {
                                    kstr++;
                                  }
                                } else {
                                  b_bool = true;
                                  exitg1 = 1;
                                }
                              } while (exitg1 == 0);
                            }

                            if (b_bool) {
                              kstr = 13;
                            } else if (ntf_t_strcmp(switch_expression)) {
                              kstr = 14;
                            } else if (ntf_u_strcmp(switch_expression)) {
                              kstr = 15;
                            } else if (ntf_v_strcmp(switch_expression)) {
                              kstr = 16;
                            } else {
                              b_bool = false;
                              if (switch_expression.size(1) == 14) {
                                kstr = 0;
                                do {
                                  exitg1 = 0;
                                  if (kstr < 14) {
                                    if (switch_expression[kstr] != ntf_cv1[kstr])
                                    {
                                      exitg1 = 1;
                                    } else {
                                      kstr++;
                                    }
                                  } else {
                                    b_bool = true;
                                    exitg1 = 1;
                                  }
                                } while (exitg1 == 0);
                              }

                              if (b_bool) {
                                kstr = 17;
                              } else {
                                b_bool = false;
                                if (switch_expression.size(1) == 16) {
                                  kstr = 0;
                                  do {
                                    exitg1 = 0;
                                    if (kstr < 16) {
                                      if (switch_expression[kstr] !=
                                          ntf_cv2[kstr]) {
                                        exitg1 = 1;
                                      } else {
                                        kstr++;
                                      }
                                    } else {
                                      b_bool = true;
                                      exitg1 = 1;
                                    }
                                  } while (exitg1 == 0);
                                }

                                if (b_bool) {
                                  kstr = 17;
                                } else {
                                  b_bool = false;
                                  if (switch_expression.size(1) == 6) {
                                    kstr = 0;
                                    do {
                                      exitg1 = 0;
                                      if (kstr < 6) {
                                        if (switch_expression[kstr] !=
                                            t1_f1[kstr]) {
                                          exitg1 = 1;
                                        } else {
                                          kstr++;
                                        }
                                      } else {
                                        b_bool = true;
                                        exitg1 = 1;
                                      }
                                    } while (exitg1 == 0);
                                  }

                                  if (b_bool) {
                                    kstr = 18;
                                  } else {
                                    b_bool = false;
                                    if (switch_expression.size(1) == 8) {
                                      kstr = 0;
                                      do {
                                        exitg1 = 0;
                                        if (kstr < 8) {
                                          if (switch_expression[kstr] !=
                                              t1_f2[kstr]) {
                                            exitg1 = 1;
                                          } else {
                                            kstr++;
                                          }
                                        } else {
                                          b_bool = true;
                                          exitg1 = 1;
                                        }
                                      } while (exitg1 == 0);
                                    }

                                    if (b_bool) {
                                      kstr = 18;
                                    } else if (ntf_bb_strcmp(switch_expression))
                                    {
                                      kstr = 19;
                                    } else {
                                      kstr = -1;
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
              }
            }
          }
        }
      }
    }
  }

  switch (kstr) {
   case 0:
    ntf_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 1:
    ntf_b_icdf(p, 1.0, this->Par[0], InverseCDF);
    for (kstr = 0; kstr < 1048576; kstr++) {
      InverseCDF[kstr]++;
    }
    break;

   case 2:
    ntf_b_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    for (kstr = 0; kstr < 1048576; kstr++) {
      InverseCDF[kstr] += this->Par[0];
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
      double b;
      b = this->Par[3] - this->Par[2];
      ntf_f_icdf(p, this->Par[0], this->Par[1], InverseCDF);
      for (kstr = 0; kstr < 1048576; kstr++) {
        InverseCDF[kstr] = InverseCDF[kstr] * b + this->Par[2];
      }
    }
    break;

   case 7:
    //  this distribution can be used to model minima
    // InverseCDF  = -icdf('Generalized Extreme Value',p,0,Obj.Par(1),-Obj.Par(2)); 
    // InverseCDF  = -icdf('Generalized Extreme Value',p,0,Obj.Par(1),-Obj.Par(2)); 
    ntf_g_icdf(p, this->Par[1], this->Par[0], InverseCDF);
    break;

   case 8:
    //  mirror image of this distribution can be used to model maxima
    ntf_h_icdf(p, 0.0, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 9:
    ntf_h_icdf(p, 1.0 / this->Par[1], this->Par[0] / this->Par[1], this->Par[0],
               InverseCDF);
    break;

   case 10:
    ntf_i_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 11:
    ntf_h_icdf(p, this->Par[0], this->Par[1], this->Par[2], InverseCDF);
    break;

   case 12:
    ntf_h_icdf(p, this->Par[0], this->Par[1], -this->Par[2], InverseCDF);
    for (kstr = 0; kstr < 1048576; kstr++) {
      InverseCDF[kstr] = -InverseCDF[kstr];
    }
    break;

   case 13:
    ntf_j_icdf(p, 1.0 / this->Par[1], this->Par[0] / this->Par[1], this->Par[0],
               InverseCDF);
    break;

   case 14:
    ntf_k_icdf(p, this->Par[0], InverseCDF);
    break;

   case 15:
    ntf_e_icdf(p, this->Par[0] / 2.0, 2.0, InverseCDF);
    break;

   case 16:
    {
      double b;
      double a;
      a = this->Par[0];
      b = this->Par[1];
      for (k = 0; k < 1048576; k++) {
        if ((a < b) && (0.0 <= p[k]) && (p[k] <= 1.0)) {
          InverseCDF[k] = a + p[k] * (b - a);
        } else {
          InverseCDF[k] = rtNaN;
        }
      }
    }
    break;

   case 17:
    ntf_l_icdf(p, 0.0, 1.0, InverseCDF);
    break;

   case 18:
    ntf_l_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;

   case 19:
    ntf_m_icdf(p, this->Par[0], this->Par[1], InverseCDF);
    break;
  }

  //     function InverseCDF = icdf(Obj,y)
  //        switch lower(Obj.Name)
  //           case 'geometric'
  //              InverseCDF = Obj.Dist.icdf(y)+1;
  //           case 'negativebinomial'
  //              InverseCDF = Obj.Dist.icdf(y)+Obj.Par(1);
  //           case 'beta'
  //              InverseCDF = Obj.Dist.icdf(y)*(Obj.Par(4)-Obj.Par(3))+Obj.Par(3); 
  //           case 'gumbelmin'
  //              InverseCDF = -Obj.Dist.icdf(y);
  //           case 'gevmin'
  //              InverseCDF = -Obj.Dist.icdf(y);
  //           otherwise
  //              InverseCDF = Obj.Dist.icdf(y);
  //        end
  //     end
  // -----------------------------------------------------------------------
  //     function Random = random(Obj,m,n)
  //        if nargin == 2
  //           switch lower(Obj.Name)
  //              case 'geometric'
  //                 Random = random(Obj.Dist,m)+1;
  //              case 'negativebinomial'
  //                 Random = random(Obj.Dist,m)+Obj.Par(1);
  //              case 'beta'
  //                 Random = random(Obj.Dist,m)*(Obj.Par(4)-Obj.Par(3))+Obj.Par(3); 
  //              case 'gumbelmin'
  //                 Random = -random(Obj.Dist,m);
  //              case 'gevmin'
  //                 Random = -random(Obj.Dist,m);
  //              otherwise
  //                 Random = random(Obj.Dist,m);
  //           end
  //        elseif nargin == 3
  //           switch lower(Obj.Name)
  //              case 'geometric'
  //                 Random = random(Obj.Dist,m,n)+1;
  //              case 'negativebinomial'
  //                 Random = random(Obj.Dist,m,n)+Obj.Par(1);
  //              case 'beta'
  //                 Random = random(Obj.Dist,m,n)*(Obj.Par(4)-Obj.Par(3))+Obj.Par(3); 
  //              case 'gumbelmin'
  //                 Random = -random(Obj.Dist,m,n);
  //              case 'gevmin'
  //                 Random = -random(Obj.Dist,m,n);
  //               otherwise
  //                 Random = random(Obj.Dist,m,n);
  //           end
  //        else
  //           error('Wrong Input in Method random');
  //        end
  //     end
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
// Arguments    : const coder::array<char, 2U> &name
//                const coder::array<char, 2U> &opt
//                const coder::array<double, 2U> &val_temp
//                const coder::array<double, 2U> &add
// Return Type  : void
//
void ntf_ERADist::ntf_init(const coder::array<char, 2U> &name, const coder::
  array<char, 2U> &opt, const coder::array<double, 2U> &val_temp, const coder::
  array<double, 2U> &add)
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

  double val[4];
  coder::array<double, 1U> b_val;
  static const char t3_f1[6] = { 'n', 'o', 'r', 'm', 'a', 'l' };

  static const char t3_f2[8] = { 'g', 'a', 'u', 's', 's', 'i', 'a', 'n' };

  double sigma0;
  double mu0;
  coder::array<double, 2U> y;
  coder::array<double, 1U> F;
  double c_val;
  ntf_coder_internal_anonymous_fu fun;
  double b_init[2];
  ntf_b_coder_internal_anonymous_ b_this;
  ntf_c_coder_internal_anonymous_ c_this;
  coder::array<double, 1U> r1;
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
  //    Frechet:                    Obj = ERADist('frechet','MOM',[mean,std])
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
    // -----------------------------------------------------------------
    val[0] = 0.0;
    val[1] = 0.0;
    val[2] = 0.0;
    val[3] = 0.0;
    vlen = val_temp.size(1);
    for (i = 0; i < vlen; i++) {
      val[i] = val_temp[i];
    }

    this->Par[0] = val[0];
    this->Par[1] = val[1];
    this->Par[2] = val[2];
    this->Par[3] = val[3];
    if (ntf_d_strcmp(name) || ntf_e_strcmp(name)) {
      val[0] = 0.0;
      val[1] = 1.0;
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
    } else if (ntf_s_strcmp(switch_expression)) {
      vlen = 13;
    } else if (ntf_t_strcmp(switch_expression)) {
      vlen = 14;
    } else if (ntf_u_strcmp(switch_expression)) {
      vlen = 15;
    } else if (ntf_v_strcmp(switch_expression)) {
      vlen = 16;
    } else if (ntf_w_strcmp(switch_expression, ntf_cv1)) {
      vlen = 17;
    } else if (ntf_x_strcmp(switch_expression, ntf_cv2)) {
      vlen = 17;
    } else if (ntf_y_strcmp(switch_expression, t3_f1)) {
      vlen = 18;
    } else if (ntf_ab_strcmp(switch_expression, t3_f2)) {
      vlen = 18;
    } else if (ntf_bb_strcmp(switch_expression)) {
      vlen = 19;
    } else {
      vlen = -1;
    }

    switch (vlen) {
     case 0:
      if ((0.0 <= val[1]) && (val[1] <= 1.0) && (val[0] > 0.0) && (ntf_mod(val[0])
           == 0.0)) {
        ntf_binostat(val[0], val[1], &Mean, &Var);

        //  Obj.Dist = mymakedist(name,'N',val(1),'p',val(2));
        //  CDF = cdf(name,x,val(1),val(2));
      }
      break;

     case 1:
      //  special case of negative binomial distribution
      if ((0.0 < val[0]) && (val[0] <= 1.0)) {
        Mean = (1.0 - val[0]) / val[0];
        Var = Mean / val[0];
        Mean++;

        //  Obj.Dist = mymakedist('negativebinomial','r',1,'p',val);
        //  CDF = cdf('negativebinomial',x,1,val);
      }
      break;

     case 2:
      if ((0.0 < val[1]) && (val[1] <= 1.0) && (val[0] > 0.0) && (ntf_mod(val[0])
           == 0.0)) {
        ntf_nbinstat(val[0], val[1], &Mean, &Var);
        Mean += val[0];

        //  Obj.Dist = mymakedist(name,'r',val(1),'p',val(2));
        //  CDF  = cdf(name,x,val(1),val(2));
      }
      break;

     case 3:
      if (val[1] == 0.0) {
        if (val[0] > 0.0) {
          //  Obj.Dist = mymakedist(name,'lambda',val);
          //  CDF  = cdf(name,x,val);
          Mean = val[0];
          Var = val[0];
        }
      } else {
        if ((val[0] > 0.0) && (val[1] > 0.0)) {
          //  Obj.Dist = mymakedist(name,'lambda',val(1)*val(2));
          //  CDF  = cdf(name,x,val(1)*val(2));
          Mean = val[0] * val[1];
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
      if (val[0] > 0.0) {
        //  Obj.Dist = mymakedist(name,'mu',1/val);
        //  CDF  = cdf(name,x,1/val);
        Mean = 1.0 / val[0];
        if (Mean > 0.0) {
          Var = Mean * Mean;
        } else {
          Mean = rtNaN;
          Var = rtNaN;
        }
      }
      break;

     case 5:
      if ((val[0] > 0.0) && (val[1] > 0.0)) {
        //  Obj.Dist = mymakedist(name,'a',val(2),'b',1/val(1));
        //  CDF  = cdf(name,x,val(2),1/val(1));
        Var = 1.0 / val[0];
        if (Var > 0.0) {
          Mean = val[1] * Var;
          Var *= Mean;
        } else {
          Mean = rtNaN;
          Var = rtNaN;
        }
      }
      break;

     case 6:
      if ((val[0] > 0.0) && (val[1] > 0.0) && (val[2] < val[3])) {
        //  Obj.Dist = mymakedist(name,'a',val(1),'b',val(2));
        //  CDF  = cdf(name,x,val(1),val(2));
        Var = val[0] + val[1];
        Mean = (val[1] * val[2] + val[0] * val[3]) / Var;

        // Var  =Var*(val(4)-val(3));
        // Var  =(val(1)*val(2)*(val(4)-val(3))/(val(1)+val(2))^2/(val(1)+val(2)+1)); 
        sigma0 = val[3] - val[2];
        Var = val[0] / Var * val[1] / (Var * (Var + 1.0)) * (sigma0 * sigma0);
      }
      break;

     case 7:
      //  this distribution can be used to model minima
      if (val[0] > 0.0) {
        //  sigma is the scale parameter
        //  mu is the location parameter
        //  Obj.Dist = mymakedist('GeneralizedExtremeValue','k',0,'sigma',val(1),'mu',-val(2)); 
        //  CDF  = cdf('GeneralizedExtremeValue',x,0,val(1),-val(2));
        Mean = val[1] + -0.57721566490153231 * val[0];
        Var = val[0] * 3.1415926535897931;
        Var = Var * Var / 6.0;
      }
      break;

     case 8:
      //  mirror image of this distribution can be used to model maxima
      if (val[0] > 0.0) {
        //  sigma is the scale parameter
        //  mu is the location parameter
        //  Obj.Dist = mymakedist('GeneralizedExtremeValue','k',0,'sigma',val(1),'mu',val(2));  
        //  CDF  = cdf('GeneralizedExtremeValue',x,0,val(1),val(2));
        if (!rtIsNaN(val[1])) {
          Mean = val[1] + 0.57721566490153231 * val[0];
          Var = 1.6449340668482264 * (val[0] * val[0]);
        } else {
          Mean = rtNaN;
          Var = rtNaN;
        }
      }
      break;

     case 9:
      if ((val[0] > 0.0) && (val[1] > 0.0)) {
        //  Obj.Dist = mymakedist('GeneralizedExtremeValue','k',1/val(2),'sigma',val(1)/val(2),'mu',val(1)); 
        //  CDF  = cdf('GeneralizedExtremeValue',x,1/val(2),val(1)/val(2),val(1)); 
        ntf_gevstat(1.0 / val[1], val[0] / val[1], val[0], &Mean, &Var);
      }
      break;

     case 10:
      if ((val[0] > 0.0) && (val[1] > 0.0)) {
        //  Obj.Dist = mymakedist(name,'a',val(1),'b',val(2));
        //  CDF  = cdf(name,x,val(1),val(2));
        ntf_wblstat(val[0], val[1], &Mean, &Var);
      }
      break;

     case 11:
      if (val[1] > 0.0) {
        //  Obj.Dist = mymakedist('GeneralizedExtremeValue','k',val(1),'sigma',val(2),'mu',val(3)); 
        //  CDF  = cdf('GeneralizedExtremeValue',x,val(1),val(2),val(3));
        ntf_gevstat(val[0], val[1], val[2], &Mean, &Var);
      }
      break;

     case 12:
      if (val[1] > 0.0) {
        //  Obj.Dist = mymakedist('GeneralizedExtremeValue','k',val(1),'sigma',val(2),'mu',-val(3)); 
        //  CDF = cdf('GeneralizedExtremeValue',x,val(1),val(2),-val(3));
        ntf_gevstat(val[0], val[1], -val[2], &Mean, &Var);
        Mean = -Mean;
      }
      break;

     case 13:
      if ((val[0] > 0.0) && (val[1] > 0.0)) {
        //  Obj.Dist = mymakedist('Generalizedpareto','k',1/val(2),'sigma',val(1)/val(2),'theta',val(1)); 
        //  CDF = cdf('Generalizedpareto',x,1/val(2),val(1)/val(2),val(1));
        ntf_gpstat(1.0 / val[1], val[0] / val[1], val[0], &Mean, &Var);
      }
      break;

     case 14:
      if (val[0] > 0.0) {
        //  Obj.Dist = mymakedist(name,'b',val);
        //  CDF = cdf(name,x,val);
        Mean = val[0] * 1.2533141373155001;
        Var = 0.42920367320510344 * (val[0] * val[0]);
      }
      break;

     case 15:
      //  special case of gamma distribution
      if ((val[0] > 0.0) && (ntf_mod(val[0]) == 0.0)) {
        //   Obj.Dist = mymakedist('gamma','a',val/2,'b',2);
        //   CDF = cdf('gamma',x,val/2,2);
        sigma0 = val[0] / 2.0;
        if (sigma0 > 0.0) {
          Mean = sigma0 * 2.0;
          Var = Mean * 2.0;
        } else {
          Mean = rtNaN;
          Var = rtNaN;
        }
      }
      break;

     case 16:
      //  Obj.Dist = mymakedist(name,'lower',val(1),'upper',val(2));
      //  CDF = cdf(name,x,val(1),val(2));
      if (val[0] <= val[1]) {
        Mean = (val[0] + val[1]) / 2.0;
        Var = val[1] - val[0];
        Var = Var * Var / 12.0;
      } else {
        Mean = rtNaN;
        Var = rtNaN;
      }
      break;

     case 17:
      //  special case of normal distribution
      //  Obj.Dist = mymakedist('normal');
      //  CDF = cdf('normal',x,0,1);
      Var = 1.0;
      break;

     case 18:
      if (val[1] > 0.0) {
        //  Obj.Dist = mymakedist(name,'mu',val(1),'sigma',val(2));
        //  CDF = cdf(name,x,val(1),val(2));
        Mean = val[0];
        Var = val[1] * val[1];
      }
      break;

     case 19:
      if (val[1] > 0.0) {
        //  Obj.Dist = mymakedist(name,'mu',val(1),'sigma',val(2));
        //  CDF = cdf(name,x,val(1),val(2));
        ntf_lognstat(val[0], val[1], &Mean, &Var);
      }
      break;
    }

    Std = std::sqrt(Var);

    // -----------------------------------------------------------------
    break;

   case 1:
    val[0] = 0.0;
    val[1] = 0.0;
    val[2] = 0.0;
    val[3] = 0.0;
    vlen = val_temp.size(1);
    for (i = 0; i < vlen; i++) {
      val[i] = val_temp[i];
    }

    Mean = val[0];
    if ((!(val[1] < 0.0)) && (val[1] > 0.0)) {
      Std = val[1];
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
    } else if (ntf_s_strcmp(switch_expression)) {
      vlen = 13;
    } else if (ntf_t_strcmp(switch_expression)) {
      vlen = 14;
    } else if (ntf_u_strcmp(switch_expression)) {
      vlen = 15;
    } else if (ntf_v_strcmp(switch_expression)) {
      vlen = 16;
    } else if (ntf_w_strcmp(switch_expression, ntf_cv1)) {
      vlen = 17;
    } else if (ntf_x_strcmp(switch_expression, ntf_cv2)) {
      vlen = 17;
    } else if (ntf_y_strcmp(switch_expression, t3_f1)) {
      vlen = 18;
    } else if (ntf_ab_strcmp(switch_expression, t3_f2)) {
      vlen = 18;
    } else if (ntf_bb_strcmp(switch_expression)) {
      vlen = 19;
    } else {
      vlen = -1;
    }

    switch (vlen) {
     case 0:
      //  Solve System of two equations for the parameters of the distribution
      this->Par[1] = 1.0 - val[1] * val[1] / val[0];
      this->Par[0] = val[0] / this->Par[1];

      //  Evaluate if distribution can be defined on the parameters
      if (ntf_mod(this->Par[0]) <= 0.0001) {
        this->Par[0] = ntf_rt_roundd_snf(this->Par[0]);
      }
      break;

     case 1:
      //  Solve Equation for the parameter of the distribution based on the first moment 
      this->Par[0] = 1.0 / val[0];

      //  Evaluate if distribution can be defined on the paramater and if the moments are well defined 
      Std = std::sqrt((val[0] - 1.0) * ((val[0] - 1.0) + 1.0));
      break;

     case 2:
      //  Solve System of two equations for the parameters of the distribution
      this->Par[1] = val[0] / (val[0] + val[1] * val[1]);
      this->Par[0] = this->Par[1] * val[0];

      //  Evaluate if distribution can be defined on the parameters
      if (ntf_mod(this->Par[0]) <= 0.0001) {
        this->Par[0] = ntf_rt_roundd_snf(this->Par[0]);
      }

      //  Define distribution
      //  Obj.Dist = mymakedist(name,'r',Obj.Par(1),'p',Obj.Par(2));
      break;

     case 3:
      this->Par[0] = val[0];

      //  Evaluate if moments match
      Std = std::sqrt(val[0]);
      break;

     case 4:
      //  Solve Equation for the parameter of the distribution based on the first moment 
      this->Par[0] = 1.0 / val[0];

      //  Evaluate if distribution can be defined on the paramater and if the moments are well defined 
      Std = val[0];
      break;

     case 5:
      //  Solve System of two equations for the parameters of the distribution
      //                       syms a b;
      //                       sol        = solve(a/b==val(1),a/b^2==val(2)^2);
      //                       Obj.Par(1) = double(sol.a);
      //                       Obj.Par(2) = double(sol.b);
      c_val = val[1] * val[1];
      this->Par[1] = val[0] * val[0] / c_val;
      this->Par[0] = val[0] / c_val;

      //  Evaluate if distribution can be defined on the parameters
      break;

     case 6:
      //  Solve System of two equations for the parameters of the distribution
      c_val = val[0] - val[2];
      Var = val[3] - val[0];
      this->Par[0] = (Var * c_val / (val[1] * val[1]) - 1.0) * c_val / (val[3] -
        val[2]);
      this->Par[1] = this->Par[0] * Var / c_val;
      this->Par[2] = val[2];
      this->Par[3] = val[3];

      //  Evaluate if distribution can be defined on the parameters
      Mean = (this->Par[1] * val[2] + this->Par[0] * val[3]) / (this->Par[0] +
        this->Par[1]);

      // Std  =  Std*(Obj.Par(4)-Obj.Par(3));
      break;

     case 7:
      //  mirror image of gumbel can be used to model minima
      //  euler constant
      //  Solve two equations for the parameters of the distribution
      this->Par[0] = val[1] * 2.4494897427831779 / 3.1415926535897931;

      //  scale parameter
      // Obj.Par(2) = -val(1) + ne*Obj.Par(1);  % location parameter
      this->Par[1] = val[0] + 0.57721566490153 * this->Par[0];

      //  location parameter
      //  Define distribution
      //  Obj.Dist = mymakedist('extremevalue','mu',Obj.Par(1),'sigma',Obj.Par(2));   
      break;

     case 8:
      //  gumbel can be used to model maxima
      //  euler constant
      //  Solve two equations for the parameters of the distribution
      this->Par[0] = val[1] * 2.4494897427831779 / 3.1415926535897931;

      //  scale parameter
      this->Par[1] = val[0] - 0.57721566490153 * this->Par[0];

      //  location parameter
      //  Define distribution
      //  Obj.Dist = mymakedist('GeneralizedExtremeValue','k',0,'sigma',Obj.Par(1),'mu',Obj.Par(2));  
      break;

     case 9:
      //  Solve equation for the parameters of the distribution
      fun.tunableEnvironment[0].f1[0] = val[0];
      fun.tunableEnvironment[0].f1[1] = val[1];
      fun.tunableEnvironment[0].f1[2] = val[2];
      fun.tunableEnvironment[0].f1[3] = val[3];
      ntf_fzero(fun, &Var, &sigma0, &mu0);
      if (mu0 > 0.0) {
        this->Par[1] = Var;
        c_val = 1.0 - 1.0 / Var;
        ntf_gamma(&c_val);
        this->Par[0] = val[0] / c_val;
      }

      //  Evaluate if distribution can be defined on the parameters
      break;

     case 10:
      //  Solve equation for the parameters of the distribution
      fun.tunableEnvironment[0].f1[0] = val[0];
      fun.tunableEnvironment[0].f1[1] = val[1];
      fun.tunableEnvironment[0].f1[2] = val[2];
      fun.tunableEnvironment[0].f1[3] = val[3];
      ntf_b_fzero(fun, &Var, &sigma0, &mu0);
      if (mu0 > 0.0) {
        this->Par[1] = Var;
        c_val = 1.0 / Var + 1.0;
        ntf_gamma(&c_val);
        this->Par[0] = val[0] / c_val;
      }

      //  Evaluate if distribution can be defined on the parameters
      break;

     case 11:
      //  Solve System of two equations for the parameters of the distribution
      if (val[0] == val[2]) {
        this->Par[0] = -1.0;
        this->Par[1] = val[1];
        this->Par[2] = val[2];
      } else {
        fun.tunableEnvironment[0].f1[0] = val[0];
        fun.tunableEnvironment[0].f1[1] = val[1];
        fun.tunableEnvironment[0].f1[2] = val[2];
        fun.tunableEnvironment[0].f1[3] = val[3];
        if (val[0] > val[2]) {
          c_val = 0.3;
        } else {
          c_val = -1.5;
        }

        ntf_c_fzero(fun, c_val, &Var, &sigma0, &mu0);
        if (mu0 > 0.0) {
          this->Par[0] = Var;
          c_val = 1.0 - Var;
          ntf_gamma(&c_val);
          this->Par[1] = (val[0] - val[2]) * Var / (c_val - 1.0);
          this->Par[2] = val[2];
        }
      }

      //  Evaluate if distribution can be defined on the parameters
      break;

     case 12:
      //  mirror image of gumbel can be used to model maxima
      //  Solve System of two equations for the parameters of the distribution
      if (val[0] == val[2]) {
        this->Par[0] = -1.0;
        this->Par[1] = val[1];
        this->Par[2] = val[2];
      } else {
        fun.tunableEnvironment[0].f1[0] = val[0];
        fun.tunableEnvironment[0].f1[1] = val[1];
        fun.tunableEnvironment[0].f1[2] = val[2];
        fun.tunableEnvironment[0].f1[3] = val[3];
        if (val[0] < val[2]) {
          c_val = 0.3;
        } else {
          c_val = -1.5;
        }

        ntf_d_fzero(fun, c_val, &Var, &sigma0, &mu0);
        if (mu0 > 0.0) {
          this->Par[0] = Var;
          c_val = 1.0 - Var;
          ntf_gamma(&c_val);
          this->Par[1] = -(val[0] - val[2]) * Var / (c_val - 1.0);
          this->Par[2] = val[2];
        }
      }

      //  Evaluate if distribution can be defined on the parameters
      break;

     case 13:
      //  Solve System of two equations for the parameters of the distribution
      sigma0 = val[0] / val[1];
      sigma0 = std::sqrt(sigma0 * sigma0 + 1.0);
      this->Par[1] = sigma0 + 1.0;
      this->Par[0] = val[0] * ((sigma0 + 1.0) - 1.0) / (sigma0 + 1.0);

      //  Evaluate if distribution can be defined on the parameters
      break;

     case 14:
      //  Solve Equation for the parameter of the distribution based on the first moment 
      this->Par[0] = val[0] / 1.2533141373155001;

      //  Evaluate if distribution can be defined on the paramater and if the moments are well defined 
      Std = 0.65513637756203358 * this->Par[0];
      break;

     case 15:
      //  Solve Equation for the parameter of the distribution based on the first moment 
      this->Par[0] = val[0];

      //  Evaluate if distribution can be defined on the paramater and if the moments are well defined 
      if (ntf_mod(val[0]) <= 0.0001) {
        this->Par[0] = ntf_rt_roundd_snf(val[0]);
      }

      Std = std::sqrt(2.0 * val[0]);
      break;

     case 16:
      //  compute parameters
      c_val = 3.4641016151377544 * val[1] / 2.0;
      this->Par[0] = val[0] - c_val;
      this->Par[1] = val[0] + c_val;

      //  Define distribution
      //  Obj.Dist = mymakedist(name,'lower',Obj.Par(1),'upper',Obj.Par(2));
      break;

     case 17:
      //  special case of normal distribution
      this->Par[0] = 0.0;
      this->Par[1] = 1.0;

      //  Obj.Dist = mymakedist('normal');
      break;

     case 18:
      this->Par[0] = val[0];
      this->Par[1] = val[1];

      //  Obj.Dist = mymakedist(name,'mu',val(1),'sigma',val(2));
      break;

     case 19:
      //  Solve two equations for the parameters of the distribution
      Var = val[1] / val[0];
      c_val = Var * Var + 1.0;
      this->Par[0] = std::log(val[0]) - std::log(std::sqrt(c_val));

      //  mean normal
      this->Par[1] = std::sqrt(std::log(c_val));

      //  sigma normal
      //  Obj.Dist   = mymakedist(name,'mu',Obj.Par(1),'sigma',Obj.Par(2));
      break;
    }

    // -----------------------------------------------------------------
    break;

   case 2:
    {
      b_val.set_size(val_temp.size(1));
      vlen = val_temp.size(1);
      for (i = 0; i < vlen; i++) {
        b_val[i] = val_temp[i];
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
      } else if (ntf_y_strcmp(switch_expression, t3_f1)) {
        vlen = 4;
      } else if (ntf_ab_strcmp(switch_expression, t3_f2)) {
        vlen = 4;
      } else if (ntf_bb_strcmp(switch_expression)) {
        vlen = 5;
      } else if (ntf_j_strcmp(switch_expression)) {
        vlen = 6;
      } else if (ntf_k_strcmp(switch_expression)) {
        vlen = 7;
      } else if (ntf_l_strcmp(switch_expression)) {
        vlen = 8;
      } else if (ntf_v_strcmp(switch_expression)) {
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
      } else if (ntf_r_strcmp(switch_expression)) {
        vlen = 15;
      } else if (ntf_s_strcmp(switch_expression)) {
        vlen = 16;
      } else if (ntf_t_strcmp(switch_expression)) {
        vlen = 17;
      } else if (ntf_u_strcmp(switch_expression)) {
        vlen = 18;
      } else {
        vlen = -1;
      }

      switch (vlen) {
       case 0:
        //  Error occurs by using fitdist
        // =============Additionally needs N ==============
        this->Par[0] = add[0];
        vlen = b_val.size(0);
        if (b_val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = b_val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += b_val[k - 1];
          }
        }

        this->Par[1] = mu0 / add[0] / static_cast<double>(b_val.size(0));
        ntf_binostat(add[0], this->Par[1], &Mean, &Var);
        break;

       case 1:
        //  see negativebinomial
        //  Fit based on moment
        vlen = b_val.size(0);
        if (b_val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = b_val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += b_val[k - 1];
          }
        }

        Mean = mu0 / static_cast<double>(b_val.size(0));
        Var = ntf_var(b_val);
        this->Par[0] = 1.0 / Mean;
        break;

       case 2:
        //  Error occurs by using fitdist
        //  Method of moment
        sigma0 = ntf_std(b_val);
        vlen = b_val.size(0);
        if (b_val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = b_val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += b_val[k - 1];
          }
        }

        mu0 /= static_cast<double>(b_val.size(0));
        vlen = b_val.size(0);
        if (b_val.size(0) == 0) {
          Var = 0.0;
        } else {
          Var = b_val[0];
          for (k = 2; k <= vlen; k++) {
            Var += b_val[k - 1];
          }
        }

        Var /= static_cast<double>(b_val.size(0));
        this->Par[1] = mu0 / (Var + sigma0 * sigma0);
        vlen = b_val.size(0);
        if (b_val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = b_val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += b_val[k - 1];
          }
        }

        mu0 /= static_cast<double>(b_val.size(0));
        this->Par[0] = this->Par[1] * mu0;
        ntf_b_mod(b_val, F);
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
          vlen = b_val.size(0);
          if (b_val.size(0) == 0) {
            mu0 = 0.0;
          } else {
            mu0 = b_val[0];
            for (k = 2; k <= vlen; k++) {
              mu0 += b_val[k - 1];
            }
          }

          mu0 /= static_cast<double>(b_val.size(0));
          this->Par[0] = ntf_rt_roundd_snf(this->Par[1] * mu0);
        }

        ntf_nbinstat(this->Par[0], this->Par[1], &Mean, &Var);
        Mean += this->Par[0];
        break;

       case 3:
        vlen = b_val.size(0);
        if (b_val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = b_val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += b_val[k - 1];
          }
        }

        Mean = mu0 / static_cast<double>(b_val.size(0));
        Var = Mean;
        this->Par[0] = Mean;
        break;

       case 4:
        {
          ntf_prob_coder_NormalDistributi Dist;
          Dist = ntf_prob_coder_NormalDistributi::ntf_fit((b_val));
          this->Par[0] = Dist.ParameterValues[0];
          this->Par[1] = Dist.ParameterValues[1];
          Mean = Dist.ParameterValues[0];
          Var = Dist.ParameterValues[1] * Dist.ParameterValues[1];
        }
        break;

       case 5:
        {
          ntf_prob_coder_LognormalDistrib b_Dist;
          b_Dist = ntf_prob_coder_LognormalDistrib::ntf_fit((b_val));
          this->Par[0] = b_Dist.ParameterValues[0];
          this->Par[1] = b_Dist.ParameterValues[1];
          ntf_lognstat(b_Dist.ParameterValues[0], b_Dist.ParameterValues[1],
                       &Mean, &Var);
        }
        break;

       case 6:
        {
          ntf_prob_coder_ExponentialDistr r;
          r = ntf_prob_coder_ExponentialDistr::ntf_fit((b_val));
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
        vlen = b_val.size(0);
        if (b_val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = b_val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += b_val[k - 1];
          }
        }

        sigma0 = mu0 / static_cast<double>(b_val.size(0));
        c_val = ntf_b_var(b_val);
        b_init[0] = sigma0 * sigma0 / c_val;
        vlen = b_val.size(0);
        if (b_val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = b_val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += b_val[k - 1];
          }
        }

        mu0 /= static_cast<double>(b_val.size(0));
        b_init[1] = 1.0 / (mu0 / c_val);

        //  maximum likelihood
        c_this.tunableEnvironment[0].f1.set_size(b_val.size(0));
        vlen = b_val.size(0);
        for (i = 0; i < vlen; i++) {
          c_this.tunableEnvironment[0].f1[i] = b_val[i];
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
          sigma0 = add[1] - add[0];
          vlen = b_val.size(0);
          for (i = 0; i < vlen; i++) {
            b_val[i] = (b_val[i] - Var) / sigma0;
          }

          e_Dist = ntf_prob_coder_BetaDistribution::ntf_fit((b_val));
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
          Var *= sigma0 * sigma0;
        }
        break;

       case 9:
        //  to model the minimum value
        Var = ntf_maximum(b_val);
        sigma0 = ntf_minimum(b_val);
        this->Par[1] = sigma0 + (static_cast<double>(b_val.size(0)) + 1.0) *
          (Var - sigma0) / static_cast<double>(b_val.size(0));
        this->Par[0] = Var + (static_cast<double>(b_val.size(0)) + 1.0) *
          (sigma0 - Var) / static_cast<double>(b_val.size(0));

        //  Quasi-unbiased estimator
        if (this->Par[0] <= this->Par[1]) {
          Mean = (this->Par[0] + this->Par[1]) / 2.0;
          Var = this->Par[1] - this->Par[0];
          Var = Var * Var / 12.0;
        } else {
          Mean = rtNaN;
          Var = rtNaN;
        }
        break;

       case 10:
        {
          ntf_prob_coder_ExtremeValueDist d_Dist;

          //  to model the minimum value
          d_Dist = ntf_prob_coder_ExtremeValueDist::ntf_fit((b_val));
          this->Par[1] = d_Dist.ParameterValues[0];
          this->Par[0] = d_Dist.ParameterValues[1];
          if (d_Dist.ParameterValues[1] > 0.0) {
            Mean = d_Dist.ParameterValues[0] + -0.57721566490153231 *
              d_Dist.ParameterValues[1];
            Var = d_Dist.ParameterValues[1] * 3.1415926535897931;
            Var = Var * Var / 6.0;
          } else {
            Mean = rtNaN;
            Var = rtNaN;
          }
        }
        break;

       case 11:
        {
          ntf_prob_coder_ExtremeValueDist d_Dist;

          //  to model the maximum value, use the negative of the original values 
          vlen = b_val.size(0);
          for (i = 0; i < vlen; i++) {
            b_val[i] = -b_val[i];
          }

          d_Dist = ntf_prob_coder_ExtremeValueDist::ntf_fit((b_val));
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
        }
        break;

       case 12:
        {
          //  Obj.Dist=fitdist(val,'Generalized ExtremeValue');                  
          vlen = b_val.size(0);
          for (i = 0; i < vlen; i++) {
            b_val[i] = 1.0 / b_val[i];
          }

          ntf_prob_coder_WeibullDistribut c_Dist;
          c_Dist = ntf_prob_coder_WeibullDistribut::ntf_fit((b_val));
          this->Par[0] = 1.0 / c_Dist.ParameterValues[0];
          this->Par[1] = c_Dist.ParameterValues[1];
          ntf_gevstat(1.0 / c_Dist.ParameterValues[1], this->Par[0] /
                      c_Dist.ParameterValues[1], this->Par[0], &Mean, &Var);
        }
        break;

       case 13:
        {
          ntf_prob_coder_WeibullDistribut c_Dist;
          c_Dist = ntf_prob_coder_WeibullDistribut::ntf_fit((b_val));
          this->Par[0] = c_Dist.ParameterValues[0];
          this->Par[1] = c_Dist.ParameterValues[1];
          ntf_wblstat(c_Dist.ParameterValues[0], c_Dist.ParameterValues[1],
                      &Mean, &Var);
        }
        break;

       case 14:
        ntf_sort(b_val);
        if (static_cast<double>(b_val.size(0)) - 0.5 < 0.5) {
          y.set_size(1, 0);
        } else {
          ntf_eml_float_colon(static_cast<double>(b_val.size(0)) - 0.5, y);
        }

        F.set_size(y.size(1));
        vlen = y.size(1);
        for (i = 0; i < vlen; i++) {
          F[i] = y[i] / static_cast<double>(b_val.size(0));
        }

        b_this.tunableEnvironment[0].f1.set_size(b_val.size(0));
        vlen = b_val.size(0);
        for (i = 0; i < vlen; i++) {
          b_this.tunableEnvironment[0].f1[i] = b_val[i];
        }

        b_this.tunableEnvironment[1].f1.set_size(F.size(0));
        vlen = F.size(0);
        for (i = 0; i < vlen; i++) {
          b_this.tunableEnvironment[1].f1[i] = F[i];
        }

        Var = ntf_fminsearch(&b_this);
        ntf_gevinv(F, Var, r1);
        ntf_polyfit(r1, b_val, b_init);
        sigma0 = b_init[0];
        mu0 = b_init[1];
        if (((Var < 0.0) && (ntf_maximum(b_val) > -b_init[0] / Var + b_init[1]))
            || ((Var > 0.0) && (ntf_minimum(b_val) < -b_init[0] / Var + b_init[1])))
        {
          //  The initial value calculation failed -- the data are not even in the 
          //  support of the parameter guesses.  Fall back to an EV, whose support is 
          //  unbounded.
          Var = 0.0;
          ntf_evfit(b_val, b_init);
          sigma0 = b_init[1];
          mu0 = b_init[0];
        }

        //  maximum likelihood
        c_this.tunableEnvironment[0].f1.set_size(b_val.size(0));
        vlen = b_val.size(0);
        for (i = 0; i < vlen; i++) {
          c_this.tunableEnvironment[0].f1[i] = b_val[i];
        }

        b[0] = Var;
        b[1] = std::log(sigma0);
        b[2] = mu0;
        ntf_d_fminsearch(&c_this, b);
        this->Par[0] = b[0];
        this->Par[1] = std::exp(b[1]);
        this->Par[2] = b[2];
        ntf_gevstat(b[0], this->Par[1], b[2], &Mean, &Var);
        break;

       case 15:
        vlen = b_val.size(0);
        for (i = 0; i < vlen; i++) {
          b_val[i] = -b_val[i];
        }

        ntf_sort(b_val);
        if (static_cast<double>(b_val.size(0)) - 0.5 < 0.5) {
          y.set_size(1, 0);
        } else {
          ntf_eml_float_colon(static_cast<double>(b_val.size(0)) - 0.5, y);
        }

        F.set_size(y.size(1));
        vlen = y.size(1);
        for (i = 0; i < vlen; i++) {
          F[i] = y[i] / static_cast<double>(b_val.size(0));
        }

        // k0 = fminsearch(@(k) 1-corr(val,gevinv(F,k,1,0)), 0);
        b_this.tunableEnvironment[0].f1.set_size(b_val.size(0));
        vlen = b_val.size(0);
        for (i = 0; i < vlen; i++) {
          b_this.tunableEnvironment[0].f1[i] = b_val[i];
        }

        b_this.tunableEnvironment[1].f1.set_size(F.size(0));
        vlen = F.size(0);
        for (i = 0; i < vlen; i++) {
          b_this.tunableEnvironment[1].f1[i] = F[i];
        }

        Var = ntf_fminsearch(&b_this);
        ntf_gevinv(F, Var, r1);
        ntf_polyfit(r1, b_val, b_init);
        sigma0 = b_init[0];
        mu0 = b_init[1];
        if (((Var < 0.0) && (ntf_maximum(b_val) > -b_init[0] / Var + b_init[1]))
            || ((Var > 0.0) && (ntf_minimum(b_val) < -b_init[0] / Var + b_init[1])))
        {
          //  The initial value calculation failed -- the data are not even in the 
          //  support of the parameter guesses.  Fall back to an EV, whose support is 
          //  unbounded.
          Var = 0.0;
          ntf_evfit(b_val, b_init);
          sigma0 = b_init[1];
          mu0 = b_init[0];
        }

        //  maximum likelihood
        c_this.tunableEnvironment[0].f1.set_size(b_val.size(0));
        vlen = b_val.size(0);
        for (i = 0; i < vlen; i++) {
          c_this.tunableEnvironment[0].f1[i] = b_val[i];
        }

        b[0] = Var;
        b[1] = std::log(sigma0);
        b[2] = mu0;
        ntf_d_fminsearch(&c_this, b);
        this->Par[0] = b[0];
        this->Par[1] = std::exp(b[1]);
        this->Par[2] = -b[2];
        ntf_gevstat(b[0], this->Par[1], b[2], &Mean, &Var);
        Mean = -Mean;
        break;

       case 16:
        // error('The pareto distribution is not supported in DATA');
        //  Method of Moment
        vlen = b_val.size(0);
        if (b_val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = b_val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += b_val[k - 1];
          }
        }

        mu0 /= static_cast<double>(b_val.size(0));
        sigma0 = mu0 / ntf_std(b_val);
        sigma0 = std::sqrt(sigma0 * sigma0 + 1.0);
        this->Par[1] = sigma0 + 1.0;
        vlen = b_val.size(0);
        if (b_val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = b_val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += b_val[k - 1];
          }
        }

        mu0 /= static_cast<double>(b_val.size(0));
        this->Par[0] = mu0 * ((sigma0 + 1.0) - 1.0) / (sigma0 + 1.0);
        vlen = b_val.size(0);
        if (b_val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = b_val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += b_val[k - 1];
          }
        }

        Mean = mu0 / static_cast<double>(b_val.size(0));
        Var = ntf_b_var(b_val);
        break;

       case 17:
        // Dist = fitdist(val,'rayleigh');
        // Obj.Par(1) = Dist.ParameterValues;
        F.set_size(b_val.size(0));
        vlen = b_val.size(0);
        for (k = 0; k < vlen; k++) {
          F[k] = b_val[k] * b_val[k];
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

       case 18:
        // error('The chi-square distribution is not supported in DATA');
        vlen = b_val.size(0);
        if (b_val.size(0) == 0) {
          mu0 = 0.0;
        } else {
          mu0 = b_val[0];
          for (k = 2; k <= vlen; k++) {
            mu0 += b_val[k - 1];
          }
        }

        Mean = mu0 / static_cast<double>(b_val.size(0));
        this->Par[0] = Mean;

        //  Evaluate if distribution can be defined on the paramater and if the moments are well defined 
        if (ntf_mod(Mean) <= 0.0001) {
          this->Par[0] = ntf_rt_roundd_snf(Mean);
        }

        Var = 2.0 * Mean;
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
void ntf_ERADist::ntf_q_cdf(const coder::array<double, 1U> &x, coder::array<
  double, 1U> &CDF) const
{
  int loop_ub;
  int i;
  coder::array<char, 2U> switch_expression;
  boolean_T b_bool;
  int exitg1;
  static const char b_cv[8] = { 'b', 'i', 'n', 'o', 'm', 'i', 'a', 'l' };

  coder::array<double, 1U> b_x;
  static const char b_cv1[7] = { 'p', 'o', 'i', 's', 's', 'o', 'n' };

  static const char b_cv2[5] = { 'g', 'a', 'm', 'm', 'a' };

  static const char b_cv3[4] = { 'b', 'e', 't', 'a' };

  static const char b_cv4[6] = { 'g', 'u', 'm', 'b', 'e', 'l' };

  static const char b_cv5[7] = { 'f', 'r', 'e', 'c', 'h', 'e', 't' };

  static const char b_cv6[3] = { 'g', 'e', 'v' };

  static const char b_cv7[6] = { 'g', 'e', 'v', 'm', 'i', 'n' };

  static const char t7_f1[6] = { 'n', 'o', 'r', 'm', 'a', 'l' };

  static const char t7_f2[8] = { 'g', 'a', 'u', 's', 's', 'i', 'a', 'n' };

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
  loop_ub = x.size(0);
  for (i = 0; i < loop_ub; i++) {
    CDF[i] = 0.0;
  }

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
            } else {
              b_bool = false;
              if (switch_expression.size(1) == 4) {
                loop_ub = 0;
                do {
                  exitg1 = 0;
                  if (loop_ub < 4) {
                    if (switch_expression[loop_ub] != b_cv3[loop_ub]) {
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
                loop_ub = 6;
              } else {
                b_bool = false;
                if (switch_expression.size(1) == 9) {
                  loop_ub = 0;
                  do {
                    exitg1 = 0;
                    if (loop_ub < 9) {
                      if (switch_expression[loop_ub] != ntf_cv6[loop_ub]) {
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
                  loop_ub = 7;
                } else {
                  b_bool = false;
                  if (switch_expression.size(1) == 6) {
                    loop_ub = 0;
                    do {
                      exitg1 = 0;
                      if (loop_ub < 6) {
                        if (switch_expression[loop_ub] != b_cv4[loop_ub]) {
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
                    loop_ub = 8;
                  } else {
                    b_bool = false;
                    if (switch_expression.size(1) == 7) {
                      loop_ub = 0;
                      do {
                        exitg1 = 0;
                        if (loop_ub < 7) {
                          if (switch_expression[loop_ub] != b_cv5[loop_ub]) {
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
                      loop_ub = 9;
                    } else if (ntf_p_strcmp(switch_expression)) {
                      loop_ub = 10;
                    } else {
                      b_bool = false;
                      if (switch_expression.size(1) == 3) {
                        loop_ub = 0;
                        do {
                          exitg1 = 0;
                          if (loop_ub < 3) {
                            if (switch_expression[loop_ub] != b_cv6[loop_ub]) {
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
                        loop_ub = 11;
                      } else {
                        b_bool = false;
                        if (switch_expression.size(1) == 6) {
                          loop_ub = 0;
                          do {
                            exitg1 = 0;
                            if (loop_ub < 6) {
                              if (switch_expression[loop_ub] != b_cv7[loop_ub])
                              {
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
                          loop_ub = 12;
                        } else if (ntf_s_strcmp(switch_expression)) {
                          loop_ub = 13;
                        } else if (ntf_t_strcmp(switch_expression)) {
                          loop_ub = 14;
                        } else if (ntf_u_strcmp(switch_expression)) {
                          loop_ub = 15;
                        } else if (ntf_v_strcmp(switch_expression)) {
                          loop_ub = 16;
                        } else {
                          b_bool = false;
                          if (switch_expression.size(1) == 14) {
                            loop_ub = 0;
                            do {
                              exitg1 = 0;
                              if (loop_ub < 14) {
                                if (switch_expression[loop_ub] !=
                                    ntf_cv1[loop_ub]) {
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
                            loop_ub = 17;
                          } else {
                            b_bool = false;
                            if (switch_expression.size(1) == 16) {
                              loop_ub = 0;
                              do {
                                exitg1 = 0;
                                if (loop_ub < 16) {
                                  if (switch_expression[loop_ub] !=
                                      ntf_cv2[loop_ub]) {
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
                              loop_ub = 17;
                            } else {
                              b_bool = false;
                              if (switch_expression.size(1) == 6) {
                                loop_ub = 0;
                                do {
                                  exitg1 = 0;
                                  if (loop_ub < 6) {
                                    if (switch_expression[loop_ub] !=
                                        t7_f1[loop_ub]) {
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
                                loop_ub = 18;
                              } else {
                                b_bool = false;
                                if (switch_expression.size(1) == 8) {
                                  loop_ub = 0;
                                  do {
                                    exitg1 = 0;
                                    if (loop_ub < 8) {
                                      if (switch_expression[loop_ub] !=
                                          t7_f2[loop_ub]) {
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
                                  loop_ub = 18;
                                } else if (ntf_bb_strcmp(switch_expression)) {
                                  loop_ub = 19;
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
              }
            }
          }
        }
      }
    }
  }

  switch (loop_ub) {
   case 0:
    ntf_cdf(x, this->Par[0], this->Par[1], CDF);
    break;

   case 1:
    // CDF = Obj.Dist.cdf(x-1);
    // CDF = cdf('negativebinomial',x,1,Obj.Par);
    b_x.set_size(x.size(0));
    loop_ub = x.size(0);
    for (i = 0; i < loop_ub; i++) {
      b_x[i] = x[i] - 1.0;
    }

    ntf_b_cdf(b_x, this->Par[0], CDF);
    break;

   case 2:
    // CDF = Obj.Dist.cdf(x-Obj.Par(1));
    // CDF  = cdf(name,x,Obj.Par(1),Obj.Par(2));
    b_x.set_size(x.size(0));
    loop_ub = x.size(0);
    for (i = 0; i < loop_ub; i++) {
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
    {
      double Obj;

      // CDF = Obj.Dist.cdf();
      // CDF  = cdf(name,x,Obj.Par(1),Obj.Par(2));
      Obj = this->Par[3] - this->Par[2];
      b_x.set_size(x.size(0));
      loop_ub = x.size(0);
      for (i = 0; i < loop_ub; i++) {
        b_x[i] = (x[i] - this->Par[2]) / Obj;
      }

      ntf_g_cdf(b_x, this->Par[0], this->Par[1], CDF);
    }
    break;

   case 7:
    //  this distribution can be used to model minima
    // CDF = Obj.Dist.cdf(-x);
    // CDF  = cdf('GeneralizedExtremeValue',x,0,Obj.Par(1),-Obj.Par(2));
    // CDF  = cdf('Generalized Extreme Value',-x,0,Obj.Par(1),-Obj.Par(2));
    ntf_h_cdf(x, this->Par[1], this->Par[0], CDF);
    break;

   case 8:
    {
      double Obj;

      //  mirror image of this distribution can be used to model maxima
      Obj = this->Par[0];
      CDF.set_size(x.size(0));
      i = x.size(0);
      for (loop_ub = 0; loop_ub < i; loop_ub++) {
        if (Obj > 0.0) {
          CDF[loop_ub] = std::exp(-std::exp(-((x[loop_ub] - this->Par[1]) / Obj)));
        } else {
          CDF[loop_ub] = rtNaN;
        }
      }
    }
    break;

   case 9:
    ntf_i_cdf(x, 1.0 / this->Par[1], this->Par[0] / this->Par[1], this->Par[0],
              CDF);
    break;

   case 10:
    ntf_j_cdf(x, this->Par[0], this->Par[1], CDF);
    break;

   case 11:
    ntf_i_cdf(x, this->Par[0], this->Par[1], this->Par[2], CDF);
    break;

   case 12:
    // CDF = Obj.Dist.cdf(-x);
    // CDF = cdf('GeneralizedExtremeValue',x,Obj.Par(1),Obj.Par(2),-Obj.Par(3)); 
    b_x.set_size(x.size(0));
    loop_ub = x.size(0);
    for (i = 0; i < loop_ub; i++) {
      b_x[i] = -x[i];
    }

    ntf_i_cdf(b_x, this->Par[0], this->Par[1], -this->Par[2], CDF);
    break;

   case 13:
    ntf_k_cdf(x, 1.0 / this->Par[1], this->Par[0] / this->Par[1], this->Par[0],
              CDF);
    break;

   case 14:
    ntf_l_cdf(x, this->Par[0], CDF);
    break;

   case 15:
    ntf_m_cdf(x, this->Par[0] / 2.0, CDF);
    break;

   case 16:
    ntf_n_cdf(x, this->Par[0], this->Par[1], CDF);
    break;

   case 17:
    {
      CDF.set_size(x.size(0));
      i = x.size(0);
      for (loop_ub = 0; loop_ub < i; loop_ub++) {
        double Obj;
        Obj = ntf_eml_erfcore(-x[loop_ub] / 1.4142135623730951);
        CDF[loop_ub] = 0.5 * Obj;
      }
    }
    break;

   case 18:
    ntf_o_cdf(x, this->Par[0], this->Par[1], CDF);
    break;

   case 19:
    ntf_p_cdf(x, this->Par[0], this->Par[1], CDF);
    break;
  }
}

//
// Arguments    : const coder::array<double, 1U> &x
//                coder::array<double, 1U> &PDF
// Return Type  : void
//
void ntf_ERADist::ntf_q_pdf(const coder::array<double, 1U> &x, coder::array<
  double, 1U> &PDF) const
{
  int loop_ub;
  int i;
  coder::array<char, 2U> switch_expression;
  boolean_T b_bool;
  int exitg1;
  static const char b_cv[8] = { 'b', 'i', 'n', 'o', 'm', 'i', 'a', 'l' };

  coder::array<double, 1U> b_x;
  static const char b_cv1[7] = { 'p', 'o', 'i', 's', 's', 'o', 'n' };

  static const char b_cv2[5] = { 'g', 'a', 'm', 'm', 'a' };

  static const char b_cv3[4] = { 'b', 'e', 't', 'a' };

  static const char b_cv4[6] = { 'g', 'u', 'm', 'b', 'e', 'l' };

  static const char b_cv5[7] = { 'f', 'r', 'e', 'c', 'h', 'e', 't' };

  static const char b_cv6[3] = { 'g', 'e', 'v' };

  static const char b_cv7[6] = { 'g', 'e', 'v', 'm', 'i', 'n' };

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
  PDF.set_size(x.size(0));
  loop_ub = x.size(0);
  for (i = 0; i < loop_ub; i++) {
    PDF[i] = 0.0;
  }

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
            } else {
              b_bool = false;
              if (switch_expression.size(1) == 4) {
                loop_ub = 0;
                do {
                  exitg1 = 0;
                  if (loop_ub < 4) {
                    if (switch_expression[loop_ub] != b_cv3[loop_ub]) {
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
                loop_ub = 6;
              } else {
                b_bool = false;
                if (switch_expression.size(1) == 9) {
                  loop_ub = 0;
                  do {
                    exitg1 = 0;
                    if (loop_ub < 9) {
                      if (switch_expression[loop_ub] != ntf_cv6[loop_ub]) {
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
                  loop_ub = 7;
                } else {
                  b_bool = false;
                  if (switch_expression.size(1) == 6) {
                    loop_ub = 0;
                    do {
                      exitg1 = 0;
                      if (loop_ub < 6) {
                        if (switch_expression[loop_ub] != b_cv4[loop_ub]) {
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
                    loop_ub = 8;
                  } else {
                    b_bool = false;
                    if (switch_expression.size(1) == 7) {
                      loop_ub = 0;
                      do {
                        exitg1 = 0;
                        if (loop_ub < 7) {
                          if (switch_expression[loop_ub] != b_cv5[loop_ub]) {
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
                      loop_ub = 9;
                    } else if (ntf_p_strcmp(switch_expression)) {
                      loop_ub = 10;
                    } else {
                      b_bool = false;
                      if (switch_expression.size(1) == 3) {
                        loop_ub = 0;
                        do {
                          exitg1 = 0;
                          if (loop_ub < 3) {
                            if (switch_expression[loop_ub] != b_cv6[loop_ub]) {
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
                        loop_ub = 11;
                      } else {
                        b_bool = false;
                        if (switch_expression.size(1) == 6) {
                          loop_ub = 0;
                          do {
                            exitg1 = 0;
                            if (loop_ub < 6) {
                              if (switch_expression[loop_ub] != b_cv7[loop_ub])
                              {
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
                          loop_ub = 12;
                        } else if (ntf_s_strcmp(switch_expression)) {
                          loop_ub = 13;
                        } else if (ntf_t_strcmp(switch_expression)) {
                          loop_ub = 14;
                        } else if (ntf_u_strcmp(switch_expression)) {
                          loop_ub = 15;
                        } else if (ntf_v_strcmp(switch_expression)) {
                          loop_ub = 16;
                        } else {
                          b_bool = false;
                          if (switch_expression.size(1) == 14) {
                            loop_ub = 0;
                            do {
                              exitg1 = 0;
                              if (loop_ub < 14) {
                                if (switch_expression[loop_ub] !=
                                    ntf_cv1[loop_ub]) {
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
                            loop_ub = 17;
                          } else {
                            b_bool = false;
                            if (switch_expression.size(1) == 16) {
                              loop_ub = 0;
                              do {
                                exitg1 = 0;
                                if (loop_ub < 16) {
                                  if (switch_expression[loop_ub] !=
                                      ntf_cv2[loop_ub]) {
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
                              loop_ub = 17;
                            } else {
                              b_bool = false;
                              if (switch_expression.size(1) == 6) {
                                loop_ub = 0;
                                do {
                                  exitg1 = 0;
                                  if (loop_ub < 6) {
                                    if (switch_expression[loop_ub] !=
                                        t5_f1[loop_ub]) {
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
                                loop_ub = 18;
                              } else {
                                b_bool = false;
                                if (switch_expression.size(1) == 8) {
                                  loop_ub = 0;
                                  do {
                                    exitg1 = 0;
                                    if (loop_ub < 8) {
                                      if (switch_expression[loop_ub] !=
                                          t5_f2[loop_ub]) {
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
                                  loop_ub = 18;
                                } else if (ntf_bb_strcmp(switch_expression)) {
                                  loop_ub = 19;
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
              }
            }
          }
        }
      }
    }
  }

  switch (loop_ub) {
   case 0:
    ntf_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 1:
    b_x.set_size(x.size(0));
    loop_ub = x.size(0);
    for (i = 0; i < loop_ub; i++) {
      b_x[i] = x[i] - 1.0;
    }

    ntf_b_pdf(b_x, this->Par[0], PDF);
    break;

   case 2:
    b_x.set_size(x.size(0));
    loop_ub = x.size(0);
    for (i = 0; i < loop_ub; i++) {
      b_x[i] = x[i] - this->Par[0];
    }

    ntf_c_pdf(b_x, this->Par[0], this->Par[1], PDF);
    break;

   case 3:
    if (this->Par[1] == 0.0) {
      ntf_d_pdf(x, this->Par[0], PDF);
    } else {
      ntf_d_pdf(x, this->Par[0] * this->Par[1], PDF);
    }
    break;

   case 4:
    ntf_e_pdf(x, 1.0 / this->Par[0], PDF);
    break;

   case 5:
    ntf_gampdf(x, this->Par[1], 1.0 / this->Par[0], PDF);
    break;

   case 6:
    {
      double Obj_tmp;

      //                  PDF  = pdf('beta',(x-Obj.Par(3))/(Obj.Par(4)-Obj.Par(3)),Obj.Par(1),Obj.Par(2))./(Obj.Par(4)-Obj.Par(3)); 
      Obj_tmp = this->Par[3] - this->Par[2];
      b_x.set_size(x.size(0));
      loop_ub = x.size(0);
      for (i = 0; i < loop_ub; i++) {
        b_x[i] = (x[i] - this->Par[2]) / Obj_tmp;
      }

      ntf_f_pdf(b_x, this->Par[0], this->Par[1], PDF);
      loop_ub = PDF.size(0);
      for (i = 0; i < loop_ub; i++) {
        PDF[i] = PDF[i] / Obj_tmp;
      }
    }
    break;

   case 7:
    //  this distribution can be used to model minima
    ntf_g_pdf(x, this->Par[1], this->Par[0], PDF);
    break;

   case 8:
    //  mirror image of this distribution can be used to model maxima
    ntf_h_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 9:
    ntf_i_pdf(x, 1.0 / this->Par[1], this->Par[0] / this->Par[1], this->Par[0],
              PDF);
    break;

   case 10:
    ntf_j_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 11:
    ntf_i_pdf(x, this->Par[0], this->Par[1], this->Par[2], PDF);
    break;

   case 12:
    b_x.set_size(x.size(0));
    loop_ub = x.size(0);
    for (i = 0; i < loop_ub; i++) {
      b_x[i] = -x[i];
    }

    ntf_i_pdf(b_x, this->Par[0], this->Par[1], -this->Par[2], PDF);
    break;

   case 13:
    ntf_k_pdf(x, 1.0 / this->Par[1], this->Par[0] / this->Par[1], this->Par[0],
              PDF);
    break;

   case 14:
    ntf_l_pdf(x, this->Par[0], PDF);
    break;

   case 15:
    ntf_m_pdf(x, this->Par[0] / 2.0, PDF);
    break;

   case 16:
    ntf_n_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 17:
    PDF.set_size(x.size(0));
    i = x.size(0);
    for (loop_ub = 0; loop_ub < i; loop_ub++) {
      PDF[loop_ub] = std::exp(-0.5 * x[loop_ub] * x[loop_ub]) /
        2.5066282746310002;
    }
    break;

   case 18:
    ntf_o_pdf(x, this->Par[0], this->Par[1], PDF);
    break;

   case 19:
    ntf_p_pdf(x, this->Par[0], this->Par[1], PDF);
    break;
  }
}

//
// File trailer for ntf_ERADist.cpp
//
// [EOF]
//
