

#ifndef MY_GSA_H
#define MY_GSA_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "lib_mat\rtwtypes.h"
#include "lib_mat\gsa_runGSA_types.h"

// Function Declarations

extern void gsa_analysis(int& nrv, int& nmc, int& ncombs, std::vector<std::vector<double>>& x, std::vector<double>& g_val,
	coder::array<gsa_cell_wrap_0, 2U>& combs_temp, int& Kos, std::vector<double>& Si, std::vector<double>& St);
	
extern void nataf_transf(int nrv, int nmc, std::vector<std::string>& get_distnames, std::vector<std::string>& get_opts,
	std::vector<std::vector<double>>& get_pars, std::vector<double>& get_corr, coder::array<double, 2U>& u_temp,
	std::vector<std::vector<double>>& x_val, std::vector<double>& px_val, std::vector<double>& g_val);

extern void GetdistID(std::string distname, std::string optname, int& distID, int& optID, int& npar, int& nmom);

extern void readjson(int &nmc, int& nrv, int &rseed, std::string& UQ_method, std::vector<std::string>& get_distnames, 
	std::vector<std::vector<double>>& get_pars, std::vector<std::string>& get_opts, std::vector<double>& get_corr);

#endif

