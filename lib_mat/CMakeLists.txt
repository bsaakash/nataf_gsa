include_directories(${CMAKE_CURRENT_LIST_DIR})

add_library(libmat 
gsa_bsxfun.cpp
gsa_eml_rand_mt19937ar_stateful.cpp
gsa_eml_setop.cpp
gsa_heapsort.cpp
gsa_insertionsort.cpp
gsa_introsort.cpp
gsa_mixGaussEm.cpp
gsa_mrdivide_helper.cpp
gsa_mycholcov.cpp
gsa_mymvnpdf.cpp
gsa_qrsolve.cpp
gsa_rand.cpp
gsa_runGSA.cpp
gsa_runGSA_data.cpp
gsa_runGSA_initialize.cpp
gsa_sparse.cpp
gsa_stack1.cpp
gsa_sum.cpp
gsa_unique.cpp
gsa_vvarstd.cpp
gsa_xgeqp3.cpp
gsa_xgetrf.cpp
gsa_xnrm2.cpp
gsa_xzgeqp3.cpp
ntf_BetaDistribution.cpp
ntf_ERADist.cpp
ntf_ERANataf.cpp
ntf_ExponentialDistribution.cpp
ntf_ExtremeValueDistribution.cpp
ntf_LognormalDistribution.cpp
ntf_NormalDistribution.cpp
ntf_WeibullDistribution.cpp
ntf_betafit.cpp
ntf_betainc.cpp
ntf_betaincinv.cpp
ntf_binodeviance.cpp
ntf_binopdf.cpp
ntf_binostat.cpp
ntf_cdf.cpp
ntf_colon.cpp
ntf_corrcoef.cpp
ntf_cospiAndSinpi.cpp
ntf_eml_rand_mt19937ar_stateful.cpp
ntf_erfcinv.cpp
ntf_evfit.cpp
ntf_expm1.cpp
ntf_find.cpp
ntf_fminsearch.cpp
ntf_fzero.cpp
ntf_gamma.cpp
ntf_gammainc.cpp
ntf_gammaincinv.cpp
ntf_gammaln.cpp
ntf_gampdf.cpp
ntf_gevinv.cpp
ntf_gevstat.cpp
ntf_icdf.cpp
ntf_inataf.cpp
ntf_inataf_data.cpp
ntf_inataf_initialize.cpp
ntf_inataf_rtwutil.cpp
ntf_linspace.cpp
ntf_lognstat.cpp
ntf_minOrMax.cpp
ntf_mod.cpp
ntf_mod1.cpp
ntf_mrdivide_helper.cpp
ntf_mycholcov.cpp
ntf_nbinpdf.cpp
ntf_nbinstat.cpp
ntf_normfit.cpp
ntf_pdf.cpp
ntf_polyfit.cpp
ntf_rand.cpp
ntf_sort.cpp
ntf_sortIdx.cpp
ntf_std.cpp
ntf_stirlerr.cpp
ntf_strcmp.cpp
ntf_svd.cpp
ntf_trapz.cpp
ntf_unique.cpp
ntf_var.cpp
ntf_wblstat.cpp
ntf_xaxpy.cpp
ntf_xnrm2.cpp
ntf_xrotg.cpp
ntf_xzgeqp3.cpp
rtGetInf.cpp
rtGetNaN.cpp
rt_nonfinite.cpp)
