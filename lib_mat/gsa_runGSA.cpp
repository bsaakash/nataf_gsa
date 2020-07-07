//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_runGSA.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 06-Jul-2020 21:48:16
//

// Include Files
#include "gsa_runGSA.h"
#include "gsa_combineVectorElements.h"
#include "gsa_eml_setop.h"
#include "gsa_mixGaussEm.h"
#include "gsa_mrdivide_helper.h"
#include "gsa_mymvnpdf.h"
#include "gsa_vvarstd.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// x: input of size  [nsamp x dim]
//  g: otuput of size [nsamp x 1]
//  combs: combination of dimensions of x as a cell e.g. {1,2,[1,2],..}
//  Si_first:  = Vi/V. First-order sobol index.
//               In order to get higher order Sobol index,
//               user needs to substract the interaction term
// Arguments    : const coder::array<double, 2U> *x
//                const coder::array<double, 1U> *gval
//                const coder::array<gsa_cell_wrap_0, 2U> *combs_temp
//                double Kos
//                char opts
//                coder::array<double, 1U> *Si
// Return Type  : void
//
void runGSA(const coder::array<double, 2U> &x, const coder::array<double, 1U>
            &gval, const coder::array<gsa_cell_wrap_0, 2U> &combs_temp, double
            Kos, char opts, coder::array<double, 1U> &Si)
{
  coder::array<gsa_cell_wrap_0, 2U> combs;
  int loop_ub;
  int i;
  int nc;
  coder::array<double, 2U> xi;
  double V;
  int nsamp;
  coder::array<int, 1U> ia;
  int ib_size[1];
  int i1;
  coder::array<double, 2U> xsec;
  coder::array<double, 2U> b_xsec;
  coder::array<double, 1U> z1;
  coder::array<double, 2U> model_mu;
  coder::array<double, 3U> model_Sigma;
  coder::array<double, 2U> model_w;
  double llh_data[999];
  int llh_size[2];
  coder::array<double, 3U> SiginvSig;
  coder::array<unsigned int, 2U> id1;
  coder::array<double, 2U> muki;
  coder::array<double, 2U> pik_tempi;
  coder::array<double, 2U> piki;
  coder::array<double, 1U> b_xi;
  double pdfval;
  coder::array<double, 2U> b_model_mu;
  if (opts == 'T') {
    combs.set_size(1, combs_temp.size(1));
    i = combs_temp.size(1);
    if (0 <= combs_temp.size(1) - 1) {
      if (x.size(1) < 1) {
        xi.set_size(1, 0);
      } else {
        xi.set_size(1, x.size(1));
        loop_ub = x.size(1) - 1;
        for (i1 = 0; i1 <= loop_ub; i1++) {
          xi[i1] = static_cast<double>(i1) + 1.0;
        }
      }
    }

    for (nc = 0; nc < i; nc++) {
      gsa_do_vectors(xi, combs_temp[nc].f1, combs[nc].f1, ia, ib_size);

      // combs{nc}= nc;
    }
  } else {
    combs.set_size(1, combs_temp.size(1));
    loop_ub = combs_temp.size(0) * combs_temp.size(1);
    for (i = 0; i < loop_ub; i++) {
      combs[i] = combs_temp[i];
    }
  }

  V = gsa_vvarstd(gval, gval.size(0));
  nsamp = x.size(0);
  Si.set_size(combs.size(1));
  loop_ub = combs.size(1);
  for (i = 0; i < loop_ub; i++) {
    Si[i] = 0.0;
  }

  i = combs.size(1);
  for (nc = 0; nc < i; nc++) {
    int b_loop_ub;
    int i2;
    int result;
    boolean_T empty_non_axis_sizes;
    signed char i3;
    int u1;
    loop_ub = x.size(0);
    b_loop_ub = combs[nc].f1.size(1);
    xsec.set_size(x.size(0), combs[combs.size(0) * nc].f1.size(1));
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      for (i2 = 0; i2 < loop_ub; i2++) {
        xsec[i2 + xsec.size(0) * i1] = x[i2 + x.size(0) * (static_cast<int>
          (combs[nc].f1[i1]) - 1)];
      }
    }

    if ((x.size(0) != 0) && (combs[nc].f1.size(1) != 0)) {
      result = x.size(0);
    } else if (gval.size(0) != 0) {
      result = gval.size(0);
    } else if (x.size(0) > 0) {
      result = x.size(0);
    } else {
      result = 0;
    }

    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || ((x.size(0) != 0) && (combs[nc].f1.size(1) != 0)))
    {
      loop_ub = combs[nc].f1.size(1);
    } else {
      loop_ub = 0;
    }

    if (empty_non_axis_sizes || (gval.size(0) != 0)) {
      i3 = 1;
    } else {
      i3 = 0;
    }

    //  [x, y]
    // == GM fitting
    //          options = statset('MaxIter',5000);
    //          %GMM=fitgmdist(xall,Ko,'Options',options);
    //          GMM=fitgmdist(xall,Ko,'Options',options,'regularization',0.000001); 
    //          mu=GMM.mu';
    //          Sig=GMM.Sigma;
    //          pi=GMM.ComponentProportion;
    b_xsec.set_size(result, (loop_ub + i3));
    for (i1 = 0; i1 < loop_ub; i1++) {
      for (i2 = 0; i2 < result; i2++) {
        b_xsec[i2 + b_xsec.size(0) * i1] = xsec[i2 + result * i1];
      }
    }

    b_loop_ub = i3;
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      for (i2 = 0; i2 < result; i2++) {
        b_xsec[i2 + b_xsec.size(0) * loop_ub] = gval[i2];
      }
    }

    gsa_mixGaussEm(b_xsec, Kos, z1, model_mu, model_Sigma, model_w, llh_data,
                   llh_size);

    //  Kos is upper limit of the mixture components
    if ((model_mu.size(0) == 0) || (model_mu.size(1) == 0)) {
      u1 = 0;
    } else {
      result = model_mu.size(0);
      u1 = model_mu.size(1);
      if (result > u1) {
        u1 = result;
      }
    }

    //  == Used to calculate conditional mean and covariance
    SiginvSig.set_size(1, combs[combs.size(0) * nc].f1.size(1), u1);
    loop_ub = combs[nc].f1.size(1) * u1;
    for (i1 = 0; i1 < loop_ub; i1++) {
      SiginvSig[i1] = 0.0;
    }

    if (combs[nc].f1.size(1) < 1) {
      id1.set_size(1, 0);
    } else {
      id1.set_size(1, combs[combs.size(0) * nc].f1.size(1));
      loop_ub = combs[nc].f1.size(1) - 1;
      for (i1 = 0; i1 <= loop_ub; i1++) {
        id1[i1] = i1 + 1U;
      }
    }

    for (result = 0; result < u1; result++) {
      loop_ub = id1.size(1);
      z1.set_size(id1.size(1));
      for (i1 = 0; i1 < loop_ub; i1++) {
        z1[i1] = id1[i1];
      }

      xi.set_size(1, z1.size(0));
      loop_ub = z1.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        xi[i1] = model_Sigma[(combs[nc].f1.size(1) + model_Sigma.size(0) * (
          static_cast<int>(z1[i1]) - 1)) + model_Sigma.size(0) *
          model_Sigma.size(1) * result];
      }

      b_xsec.set_size(z1.size(0), z1.size(0));
      loop_ub = z1.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_loop_ub = z1.size(0);
        for (i2 = 0; i2 < b_loop_ub; i2++) {
          b_xsec[i2 + b_xsec.size(0) * i1] = model_Sigma[((static_cast<int>
            (z1[i2]) + model_Sigma.size(0) * (static_cast<int>(z1[i1]) - 1)) +
            model_Sigma.size(0) * model_Sigma.size(1) * result) - 1];
        }
      }

      gsa_mrdiv(xi, b_xsec);
      loop_ub = xi.size(1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        SiginvSig[i1 + SiginvSig.size(1) * result] = xi[i1];
      }
    }

    //  == Conditional component means, covariances, weights
    muki.set_size(nsamp, u1);
    result = nsamp * u1;
    for (i1 = 0; i1 < result; i1++) {
      muki[i1] = 0.0;
    }

    pik_tempi.set_size(nsamp, u1);
    for (i1 = 0; i1 < result; i1++) {
      pik_tempi[i1] = 0.0;
    }

    piki.set_size(nsamp, u1);
    for (i1 = 0; i1 < result; i1++) {
      piki[i1] = 0.0;
    }

    for (int b_i = 0; b_i < nsamp; b_i++) {
      loop_ub = combs[nc].f1.size(1);
      xi.set_size(1, combs[combs.size(0) * nc].f1.size(1));
      for (i1 = 0; i1 < loop_ub; i1++) {
        xi[i1] = xsec[b_i + xsec.size(0) * i1];
      }

      for (result = 0; result < u1; result++) {
        loop_ub = id1.size(1);
        z1.set_size(id1.size(1));
        for (i1 = 0; i1 < loop_ub; i1++) {
          z1[i1] = model_mu[(static_cast<int>(id1[i1]) + model_mu.size(0) *
                             result) - 1];
        }

        loop_ub = SiginvSig.size(1);
        pdfval = 0.0;
        for (i1 = 0; i1 < loop_ub; i1++) {
          pdfval += SiginvSig[i1 + SiginvSig.size(1) * result] * (xi[i1] - z1[i1]);
        }

        muki[b_i + muki.size(0) * result] = model_mu[combs[nc].f1.size(1) +
          model_mu.size(0) * result] + pdfval;
        loop_ub = id1.size(1);
        b_model_mu.set_size(1, id1.size(1));
        for (i1 = 0; i1 < loop_ub; i1++) {
          b_model_mu[i1] = model_mu[(static_cast<int>(id1[i1]) + model_mu.size(0)
            * result) - 1];
        }

        loop_ub = id1.size(1);
        b_xsec.set_size(id1.size(1), id1.size(1));
        for (i1 = 0; i1 < loop_ub; i1++) {
          b_loop_ub = id1.size(1);
          for (i2 = 0; i2 < b_loop_ub; i2++) {
            b_xsec[i2 + b_xsec.size(0) * i1] = model_Sigma[((static_cast<int>
              (id1[i2]) + model_Sigma.size(0) * (static_cast<int>(id1[i1]) - 1))
              + model_Sigma.size(0) * model_Sigma.size(1) * result) - 1];
          }
        }

        pdfval = gsa_mymvnpdf(xi, b_model_mu, b_xsec);
        pik_tempi[b_i + pik_tempi.size(0) * result] = model_w[result] * pdfval;
      }

      loop_ub = pik_tempi.size(1);
      xi.set_size(1, pik_tempi.size(1));
      for (i1 = 0; i1 < loop_ub; i1++) {
        xi[i1] = pik_tempi[b_i + pik_tempi.size(0) * i1];
      }

      i1 = pik_tempi.size(1);
      if (pik_tempi.size(1) == 0) {
        pdfval = 0.0;
      } else {
        pdfval = pik_tempi[b_i];
        for (result = 2; result <= i1; result++) {
          pdfval += xi[result - 1];
        }
      }

      loop_ub = pik_tempi.size(1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        piki[b_i + piki.size(0) * i1] = pik_tempi[b_i + pik_tempi.size(0) * i1] /
          pdfval;
      }
    }

    //  == Vi=Var(E(p(y|x)))
    b_xsec.set_size(piki.size(1), piki.size(0));
    loop_ub = piki.size(0);
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_loop_ub = piki.size(1);
      for (i2 = 0; i2 < b_loop_ub; i2++) {
        b_xsec[i2 + b_xsec.size(0) * i1] = piki[i1 + piki.size(0) * i2] *
          muki[i1 + muki.size(0) * i2];
      }
    }

    gsa_combineVectorElements(b_xsec, xi);
    result = xi.size(1);
    b_xi = xi.reshape(result);
    Si[nc] = gsa_vvarstd(b_xi, xi.size(1)) / V;

    //  Above two lines are different from the original paper (simplified)
  }

  //     %%
  if (opts == 'T') {
    loop_ub = Si.size(0);
    for (i = 0; i < loop_ub; i++) {
      Si[i] = 1.0 - Si[i];
    }
  }
}

//
// File trailer for gsa_runGSA.cpp
//
// [EOF]
//
