//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_runGSA.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 24-Jun-2020 22:12:52
//

// Include Files
#include "gsa_runGSA.h"
#include "gsa_combineVectorElements.h"
#include "gsa_mixGaussEm.h"
#include "gsa_mrdivide_helper.h"
#include "gsa_mymvnpdf.h"
#include "gsa_sum.h"
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
//                const coder::array<gsa_cell_wrap_0, 2U> *combs
//                double Kos
//                coder::array<double, 1U> *Si_first
// Return Type  : void
//
void runGSA(const coder::array<double, 2U> &x, const coder::array<double, 1U>
            &gval, const coder::array<gsa_cell_wrap_0, 2U> &combs, double Kos,
            coder::array<double, 1U> &Si_first)
{
  double V;
  int nsamp;
  int loop_ub;
  int i;
  coder::array<double, 2U> xsec;
  coder::array<double, 2U> SiginvSig;
  coder::array<double, 1U> xi;
  coder::array<double, 2U> model_mu;
  coder::array<double, 3U> model_Sigma;
  coder::array<double, 2U> model_w;
  double llh_data[999];
  int llh_size[2];
  coder::array<double, 2U> muki;
  coder::array<double, 2U> pik_tempi;
  coder::array<double, 2U> piki;
  coder::array<double, 2U> b_x;
  coder::array<double, 2U> b_model_Sigma;
  coder::array<double, 1U> b_model_mu;
  double b_SiginvSig;
  coder::array<double, 1U> pdfval;
  V = gsa_vvarstd(gval, gval.size(0));
  nsamp = x.size(0);
  Si_first.set_size(combs.size(1));
  loop_ub = combs.size(1);
  for (i = 0; i < loop_ub; i++) {
    Si_first[i] = 0.0;
  }

  i = combs.size(1);
  for (int nc = 0; nc < i; nc++) {
    int b_loop_ub;
    int i1;
    int i2;
    int result;
    boolean_T empty_non_axis_sizes;
    signed char i3;
    int u1;
    int k;
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
    SiginvSig.set_size(result, (loop_ub + i3));
    for (i1 = 0; i1 < loop_ub; i1++) {
      for (i2 = 0; i2 < result; i2++) {
        SiginvSig[i2 + SiginvSig.size(0) * i1] = xsec[i2 + result * i1];
      }
    }

    b_loop_ub = i3;
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      for (i2 = 0; i2 < result; i2++) {
        SiginvSig[i2 + SiginvSig.size(0) * loop_ub] = gval[i2];
      }
    }

    gsa_mixGaussEm(SiginvSig, Kos, xi, model_mu, model_Sigma, model_w, llh_data,
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
    SiginvSig.set_size(combs[combs.size(0) * nc].f1.size(1), u1);
    loop_ub = combs[nc].f1.size(1) * u1;
    for (i1 = 0; i1 < loop_ub; i1++) {
      SiginvSig[i1] = 0.0;
    }

    for (k = 0; k < u1; k++) {
      if (1 > model_Sigma.size(1) - 1) {
        loop_ub = 0;
      } else {
        loop_ub = model_Sigma.size(1) - 1;
      }

      if (1 > model_Sigma.size(0) - 1) {
        b_loop_ub = 0;
      } else {
        b_loop_ub = model_Sigma.size(0) - 1;
      }

      if (1 > model_Sigma.size(1) - 1) {
        result = 0;
      } else {
        result = model_Sigma.size(1) - 1;
      }

      b_x.set_size(1, loop_ub);
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_x[i1] = model_Sigma[((model_Sigma.size(0) + model_Sigma.size(0) * i1)
          + model_Sigma.size(0) * model_Sigma.size(1) * k) - 1];
      }

      b_model_Sigma.set_size(b_loop_ub, result);
      for (i1 = 0; i1 < result; i1++) {
        for (i2 = 0; i2 < b_loop_ub; i2++) {
          b_model_Sigma[i2 + b_model_Sigma.size(0) * i1] = model_Sigma[(i2 +
            model_Sigma.size(0) * i1) + model_Sigma.size(0) * model_Sigma.size(1)
            * k];
        }
      }

      gsa_mrdiv(b_x, b_model_Sigma);
      loop_ub = SiginvSig.size(0);
      for (i1 = 0; i1 < loop_ub; i1++) {
        SiginvSig[i1 + SiginvSig.size(0) * k] = b_x[i1];
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
      xi.set_size(combs[combs.size(0) * nc].f1.size(1));
      for (i1 = 0; i1 < loop_ub; i1++) {
        xi[i1] = xsec[b_i + xsec.size(0) * i1];
      }

      for (k = 0; k < u1; k++) {
        loop_ub = SiginvSig.size(0);
        b_SiginvSig = 0.0;
        for (i1 = 0; i1 < loop_ub; i1++) {
          b_SiginvSig += SiginvSig[i1 + SiginvSig.size(0) * k] * (xi[i1] -
            model_mu[i1 + model_mu.size(0) * k]);
        }

        muki[b_i + muki.size(0) * k] = model_mu[(model_mu.size(0) +
          model_mu.size(0) * k) - 1] + b_SiginvSig;
        if (1 > model_mu.size(0) - 1) {
          loop_ub = 0;
        } else {
          loop_ub = model_mu.size(0) - 1;
        }

        if (1 > model_Sigma.size(0) - 1) {
          b_loop_ub = 0;
        } else {
          b_loop_ub = model_Sigma.size(0) - 1;
        }

        if (1 > model_Sigma.size(1) - 1) {
          result = 0;
        } else {
          result = model_Sigma.size(1) - 1;
        }

        b_model_mu.set_size(loop_ub);
        for (i1 = 0; i1 < loop_ub; i1++) {
          b_model_mu[i1] = model_mu[i1 + model_mu.size(0) * k];
        }

        b_model_Sigma.set_size(b_loop_ub, result);
        for (i1 = 0; i1 < result; i1++) {
          for (i2 = 0; i2 < b_loop_ub; i2++) {
            b_model_Sigma[i2 + b_model_Sigma.size(0) * i1] = model_Sigma[(i2 +
              model_Sigma.size(0) * i1) + model_Sigma.size(0) * model_Sigma.size
              (1) * k];
          }
        }

        gsa_mymvnpdf(xi, b_model_mu, b_model_Sigma, pdfval);
        pik_tempi[b_i + pik_tempi.size(0) * k] = model_w[k] * pdfval[0];
      }

      loop_ub = pik_tempi.size(1);
      b_x.set_size(1, pik_tempi.size(1));
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_x[i1] = pik_tempi[b_i + pik_tempi.size(0) * i1];
      }

      i1 = pik_tempi.size(1);
      if (pik_tempi.size(1) == 0) {
        b_SiginvSig = 0.0;
      } else {
        b_SiginvSig = pik_tempi[b_i];
        for (k = 2; k <= i1; k++) {
          b_SiginvSig += b_x[k - 1];
        }
      }

      loop_ub = pik_tempi.size(1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        piki[b_i + piki.size(0) * i1] = pik_tempi[b_i + pik_tempi.size(0) * i1] /
          b_SiginvSig;
      }
    }

    //  == Vi=Var(E(p(y|x)))
    SiginvSig.set_size(piki.size(1), piki.size(0));
    loop_ub = piki.size(0);
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_loop_ub = piki.size(1);
      for (i2 = 0; i2 < b_loop_ub; i2++) {
        SiginvSig[i2 + SiginvSig.size(0) * i1] = piki[i1 + piki.size(0) * i2] *
          muki[i1 + muki.size(0) * i2];
      }
    }

    gsa_combineVectorElements(SiginvSig, b_x);
    result = b_x.size(1);
    b_model_mu = b_x.reshape(result);
    Si_first[nc] = gsa_vvarstd(b_model_mu, b_x.size(1)) / V;

    //  Above two lines are different from the original paper (simplified)
    //          disp(['GSA i=' sprintf(nc) ', Si=' num2str(Si_first(nc)) ', K=' num2str(Ko)]); 
    //          sprintf('GSA i=%f, Si=%f, K=%f', nc, Si_first(nc),Ko)
  }

  //     %%
}

//
// File trailer for gsa_runGSA.cpp
//
// [EOF]
//
