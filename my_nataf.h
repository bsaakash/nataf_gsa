

#ifndef MY_NATAF_H
#define MY_NATAF_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "lib_mat\rtwtypes.h"
#include "lib_mat\ntf_inataf_types.h"

// Function Declarations

extern void nataf_transf(int nrv, int nmc, std::vector<std::string>& get_distnames, std::vector<std::string>& get_opts,
	std::vector<std::vector<double>>& get_pars, std::vector<double>& get_corr, coder::array<double, 2U>& u_temp,
	std::vector<double>& x_val, std::vector<double>& px_val, std::vector<double>& g_val);

extern void GetdistID(std::string distname, std::string optname, int& distID, int& optID, int& npar, int& nmom);

#endif