//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ntf_inataf_types.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 06-Jul-2020 21:30:41
//
#ifndef NTF_INATAF_TYPES_H
#define NTF_INATAF_TYPES_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#ifdef _MSC_VER

#pragma warning(push)
#pragma warning(disable : 4251)

#endif

// Type Definitions
struct ntf_cell_wrap_3
{
  double f1[4];
};

class ntf_ERADist
{
 public:
  void ntf_init(const coder::array<char, 2U> &name, const coder::array<char, 2U>
                &opt, const coder::array<double, 2U> &val_temp);
  void ntf_eb_icdf(const double p[1048576], double InverseCDF[1048576]) const;
  void ntf_eb_icdf(const coder::array<double, 2U> &p, coder::array<double, 2U>
                   &InverseCDF) const;
  void ntf_p_cdf(const coder::array<double, 1U> &x, coder::array<double, 1U>
                 &CDF) const;
  void ntf_q_pdf(const coder::array<double, 1U> &x, coder::array<double, 1U>
                 &PDF) const;
  coder::array<char, 2U> Name;
  double Par[4];
  double mean;
  double std;
};

class ntf_ERANataf
{
 public:
  void ntf_init(const coder::array<ntf_ERADist, 1U> &M, const coder::array<
                double, 2U> &Correlation);
  static double ntf___anon_fcn(const double coef[1048576], const double xi
    [1048576], const double eta[1048576], const ntf_ERANataf *Obj, double i,
    double j, double rho0);
  void ntf_U2X(const coder::array<double, 2U> &U, coder::array<double, 2U> &X)
    const;
  void ntf_q_pdf(const coder::array<double, 2U> &X, coder::array<double, 1U>
                 &jointpdf) const;
 private:
  static void ntf_quad_GL(double x[1024], double w[1024]);
 public:
  coder::array<double, 2U> Rho_X;
  coder::array<double, 2U> Rho_Z;
  coder::array<double, 2U> A;
  coder::array<ntf_ERADist, 1U> Marginals;
};

struct ntf_cell_11
{
  double f1[1048576];
  double f2[1048576];
  double f3[1048576];
  ntf_ERANataf f4;
  double f5;
  double f6;
};

class ntf_b_coder_internal_anonymous_
{
 public:
  ntf_cell_11 tunableEnvironment;
};

class ntf_coder_internal_anonymous_fu
{
 public:
  ntf_cell_wrap_3 tunableEnvironment[1];
};

struct ntf_cell_wrap_0
{
  coder::array<char, 2U> f1;
};

struct ntf_cell_wrap_1
{
  coder::array<double, 2U> f1;
};

#ifdef _MSC_VER

#pragma warning(pop)

#endif
#endif

//
// File trailer for ntf_inataf_types.h
//
// [EOF]
//
