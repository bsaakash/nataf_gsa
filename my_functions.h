

#ifndef MY_GSA_H
#define MY_GSA_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "lib_mat/rtwtypes.h"
#include "lib_mat/gsa_runGSA_types.h"

// Function Declarations


using std::vector;

extern std::ofstream theErrorFile;

extern void gsa_analysis(int& nmc, int& nrv, int& ng, int& ncombs, vector<vector<double>>& x_val, vector<vector<double>>& g_val,
	vector<vector<double>>& combs_temp, int& Kos, vector<vector<double>>& Si_val, vector<vector<double>>& St_val);


extern void nataf_transf(int nmc,
			 int nrv,
			 int nco,
			 int nqoi,
			 vector<std::string>& get_distnames,
			 vector<std::string>& get_opts,
			 vector<vector<double>>& get_vals,
			 vector<double>& get_const,
			 vector<std::string>& get_rvnames,
			 vector<double>& get_corr,
			 vector<vector<double>>& get_add,
			 std::string& workdir,
			 std::string& osType,
			 std::string& runType,			 
			 coder::array<double, 2U>& u_temp,
			 vector<vector<double>>& x_val,
			 vector<double>& px_val,
			 vector<vector<double>>& g_val);

//extern void GetdistID(std::string distname, std::string optname, int& distID, int& optID, int& npar, int& nmom);

extern void readjson(std:: string workdir, int& nmc, int& nrv, int&nco, int& nquoi, int& rseed, std::string& UQ_method, std::vector<std::string>& get_distnames, std::vector<std::vector<double>>& get_vals, std::vector<double> &get_const,
	std::vector<std::string>& get_opts, std::vector<std::string>& get_rvnames, std::vector<std::string>& get_qoinames, std::vector<double>& get_corr, std::vector<std::vector<double>>& get_add,
	std::vector<std::vector<double>>& get_groups);

#endif

