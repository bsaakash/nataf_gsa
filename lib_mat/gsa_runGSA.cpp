//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gsa_runGSA.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 23-Jul-2020 01:50:34
//

// Include Files
#include "gsa_runGSA.h"
#include "gsa_eml_setop.h"
#include "gsa_mixGaussEm.h"
#include "gsa_mrdivide_helper.h"
#include "gsa_mymvnpdf.h"
#include "gsa_sum.h"
#include "gsa_vvarstd.h"
#include "rt_nonfinite.h"
#include <cmath>

// Type Definitions
struct gsa_b_struct_T
{
  coder::array<double, 2U> mu;
  coder::array<double, 3U> Sigma;
  coder::array<double, 2U> w;
};

// Function Declarations
static double gsa_rt_roundd_snf(double u);

// Function Definitions

//
// Arguments    : double u
// Return Type  : double
//
static double gsa_rt_roundd_snf(double u)
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
  coder::array<double, 2U> xall;
  coder::array<double, 1U> z1;
  gsa_b_struct_T models[5];
  double llh_data[999];
  int llh_size[2];
  double pdfval;
  double llhs[5];
  coder::array<double, 3U> SiginvSig;
  coder::array<unsigned int, 2U> id1;
  coder::array<double, 2U> pik_tempi;
  coder::array<double, 2U> b_models;
  coder::array<double, 2U> piki;
  coder::array<double, 1U> b_xi;
  coder::array<double, 2U> c_models;

  //      x=(x-mean(x))./std(x);
  //      gval=(gval-mean(gval))./std(gval);
  if (opts == 'T') {
    combs.set_size(1, combs_temp.size(1));
    i = combs_temp.size(1);
    if (0 <= combs_temp.size(1) - 1) {
      if (x.size(1) < 1) {
        xi.set_size(1, 0);
      } else {
        xi.set_size(1, (static_cast<int>(static_cast<double>(x.size(1)) - 1.0) +
                        1));
        loop_ub = static_cast<int>(static_cast<double>(x.size(1)) - 1.0);
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

  V = gsa_rt_roundd_snf(gsa_vvarstd(gval, gval.size(0)) * 1.0E+10) * 1.0E-10;
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
    int k;
    int iindx;
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

    xall.set_size(result, (loop_ub + i3));
    for (i1 = 0; i1 < loop_ub; i1++) {
      for (i2 = 0; i2 < result; i2++) {
        xall[i2 + xall.size(0) * i1] = xsec[i2 + result * i1];
      }
    }

    b_loop_ub = i3;
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      for (i2 = 0; i2 < result; i2++) {
        xall[i2 + xall.size(0) * loop_ub] = gval[i2];
      }
    }

    //  [x, y]
    // == GM fitting
    //          options = statset('MaxIter',5000);
    //          %GMM=fitgmdist(xall,Ko,'Options',options);
    //          GMM=fitgmdist(xall,Ko,'Options',options,'regularization',0.000001); 
    //          mu=GMM.mu';
    //          Sig=GMM.Sigma;
    //          pi=GMM.ComponentProportion;
    //              xall_norm=(xall-mean(xall))./std(xall);
    gsa_mixGaussEm(xall, Kos, z1, models[0].mu, models[0].Sigma, models[0].w,
                   llh_data, llh_size);

    //  Kos is upper limit of the mixture components
    pdfval = llh_data[llh_size[1] - 1];
    llhs[0] = llh_data[llh_size[1] - 1];

    //              xall_norm=(xall-mean(xall))./std(xall);
    gsa_mixGaussEm(xall, Kos, z1, models[1].mu, models[1].Sigma, models[1].w,
                   llh_data, llh_size);

    //  Kos is upper limit of the mixture components
    llhs[1] = llh_data[llh_size[1] - 1];

    //              xall_norm=(xall-mean(xall))./std(xall);
    gsa_mixGaussEm(xall, Kos, z1, models[2].mu, models[2].Sigma, models[2].w,
                   llh_data, llh_size);

    //  Kos is upper limit of the mixture components
    llhs[2] = llh_data[llh_size[1] - 1];

    //              xall_norm=(xall-mean(xall))./std(xall);
    gsa_mixGaussEm(xall, Kos, z1, models[3].mu, models[3].Sigma, models[3].w,
                   llh_data, llh_size);

    //  Kos is upper limit of the mixture components
    llhs[3] = llh_data[llh_size[1] - 1];

    //              xall_norm=(xall-mean(xall))./std(xall);
    gsa_mixGaussEm(xall, Kos, z1, models[4].mu, models[4].Sigma, models[4].w,
                   llh_data, llh_size);

    //  Kos is upper limit of the mixture components
    llhs[4] = llh_data[llh_size[1] - 1];
    if (!rtIsNaN(pdfval)) {
      result = 1;
    } else {
      boolean_T exitg1;
      result = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k < 6)) {
        if (!rtIsNaN(llhs[k - 1])) {
          result = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (result == 0) {
      iindx = 0;
    } else {
      pdfval = llhs[result - 1];
      iindx = result - 1;
      i1 = result + 1;
      for (k = i1; k < 6; k++) {
        double d;
        d = llhs[k - 1];
        if (pdfval < d) {
          pdfval = d;
          iindx = k - 1;
        }
      }
    }

    //          Ko=size(models{maxid}.mu,2);
    //          mu=models{maxid}.mu.*repmat(std(xall)',1,Ko)+mean(xall)';
    //          Sig=models{maxid}.Sigma;
    //          for k=1:Ko
    //              Sig(:,:,k)=(std(xall)'*std(xall)).*Sig(:,:,k);
    //          end
    // Ko=size(mu,2);
    //  == Used to calculate conditional mean and covariance
    SiginvSig.set_size(1, combs[combs.size(0) * nc].f1.size(1), models[iindx].
                       mu.size(1));
    loop_ub = combs[nc].f1.size(1) * models[iindx].mu.size(1);
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

    i1 = models[iindx].mu.size(1);
    for (k = 0; k < i1; k++) {
      loop_ub = id1.size(1);
      z1.set_size(id1.size(1));
      for (i2 = 0; i2 < loop_ub; i2++) {
        z1[i2] = id1[i2];
      }

      xi.set_size(1, z1.size(0));
      loop_ub = z1.size(0);
      for (i2 = 0; i2 < loop_ub; i2++) {
        xi[i2] = models[iindx].Sigma[(combs[nc].f1.size(1) + models[iindx].
          Sigma.size(0) * (static_cast<int>(z1[i2]) - 1)) + models[iindx].
          Sigma.size(0) * models[iindx].Sigma.size(1) * k];
      }

      b_models.set_size(z1.size(0), z1.size(0));
      loop_ub = z1.size(0);
      for (i2 = 0; i2 < loop_ub; i2++) {
        b_loop_ub = z1.size(0);
        for (result = 0; result < b_loop_ub; result++) {
          b_models[result + b_models.size(0) * i2] = models[iindx].Sigma[((
            static_cast<int>(z1[result]) + models[iindx].Sigma.size(0) * (
            static_cast<int>(z1[i2]) - 1)) + models[iindx].Sigma.size(0) *
            models[iindx].Sigma.size(1) * k) - 1];
        }
      }

      gsa_mrdiv(xi, b_models);
      loop_ub = xi.size(1);
      for (i2 = 0; i2 < loop_ub; i2++) {
        SiginvSig[i2 + SiginvSig.size(1) * k] = xi[i2];
      }
    }

    //  == Conditional component means, covariances, weights
    xall.set_size(nsamp, models[iindx].mu.size(1));
    loop_ub = nsamp * models[iindx].mu.size(1);
    for (i1 = 0; i1 < loop_ub; i1++) {
      xall[i1] = 0.0;
    }

    pik_tempi.set_size(nsamp, models[iindx].mu.size(1));
    loop_ub = nsamp * models[iindx].mu.size(1);
    for (i1 = 0; i1 < loop_ub; i1++) {
      pik_tempi[i1] = 0.0;
    }

    piki.set_size(nsamp, models[iindx].mu.size(1));
    loop_ub = nsamp * models[iindx].mu.size(1);
    for (i1 = 0; i1 < loop_ub; i1++) {
      piki[i1] = 0.0;
    }

    for (int b_i = 0; b_i < nsamp; b_i++) {
      loop_ub = combs[nc].f1.size(1);
      xi.set_size(1, combs[combs.size(0) * nc].f1.size(1));
      for (i1 = 0; i1 < loop_ub; i1++) {
        xi[i1] = xsec[b_i + xsec.size(0) * i1];
      }

      i1 = models[iindx].mu.size(1);
      for (k = 0; k < i1; k++) {
        loop_ub = id1.size(1);
        z1.set_size(id1.size(1));
        for (i2 = 0; i2 < loop_ub; i2++) {
          z1[i2] = models[iindx].mu[(static_cast<int>(id1[i2]) + models[iindx].
            mu.size(0) * k) - 1];
        }

        loop_ub = SiginvSig.size(1);
        pdfval = 0.0;
        for (i2 = 0; i2 < loop_ub; i2++) {
          pdfval += SiginvSig[i2 + SiginvSig.size(1) * k] * (xi[i2] - z1[i2]);
        }

        xall[b_i + xall.size(0) * k] = models[iindx].mu[combs[nc].f1.size(1) +
          models[iindx].mu.size(0) * k] + pdfval;
        loop_ub = id1.size(1);
        c_models.set_size(1, id1.size(1));
        for (i2 = 0; i2 < loop_ub; i2++) {
          c_models[i2] = models[iindx].mu[(static_cast<int>(id1[i2]) +
            models[iindx].mu.size(0) * k) - 1];
        }

        loop_ub = id1.size(1);
        b_models.set_size(id1.size(1), id1.size(1));
        for (i2 = 0; i2 < loop_ub; i2++) {
          b_loop_ub = id1.size(1);
          for (result = 0; result < b_loop_ub; result++) {
            b_models[result + b_models.size(0) * i2] = models[iindx].Sigma[((
              static_cast<int>(id1[result]) + models[iindx].Sigma.size(0) * (
              static_cast<int>(id1[i2]) - 1)) + models[iindx].Sigma.size(0) *
              models[iindx].Sigma.size(1) * k) - 1];
          }
        }

        pdfval = gsa_mymvnpdf(xi, c_models, b_models);
        pik_tempi[b_i + pik_tempi.size(0) * k] = models[iindx].w[k] * pdfval;
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
        for (k = 2; k <= i1; k++) {
          pdfval += xi[k - 1];
        }
      }

      loop_ub = pik_tempi.size(1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        piki[b_i + piki.size(0) * i1] = pik_tempi[b_i + pik_tempi.size(0) * i1] /
          pdfval;
      }
    }

    //  == Vi=Var(E(p(y|x)))
    xsec.set_size(piki.size(1), piki.size(0));
    loop_ub = piki.size(0);
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_loop_ub = piki.size(1);
      for (i2 = 0; i2 < b_loop_ub; i2++) {
        xsec[i2 + xsec.size(0) * i1] = piki[i1 + piki.size(0) * i2] * xall[i1 +
          xall.size(0) * i2];
      }
    }

    gsa_sum(xsec, xi);
    result = xi.size(1);
    b_xi = xi.reshape(result);
    Si[nc] = gsa_rt_roundd_snf(gsa_vvarstd(b_xi, xi.size(1)) * 1.0E+15) *
      1.0E-15 / V;

    //  Above two lines are different from the original paper (simplified)
  }

  //     %%
  if (opts == 'T') {
    loop_ub = Si.size(0);
    for (i = 0; i < loop_ub; i++) {
      Si[i] = 1.0 - Si[i];
    }
  }

  //    %{
  //      idsamp=(mnrnd(1,pi,1.e3)*[1:Ko]');
  //      for ns=1:length(idsamp)
  //         ss(ns,:)=mvnrnd(mu(:,idsamp(ns))',Sig(:,:,idsamp(ns)));
  //     end
  //     figure; scatter(ss(:,1),ss(:,2));
  //         hold on; scatter(xall(:,1),xall(:,2))
  //
  //     cov(xall)
  //     cov([ss(:,1),ss(:,2)])
  //
  //     %}
}

//
// File trailer for gsa_runGSA.cpp
//
// [EOF]
//
