


#include "lib_mat/gsa_runGSA.h"
#include "lib_mat/gsa_runGSA_initialize.h"
#include "lib_mat/gsa_vvarstd.h"
#include "lib_mat/rt_nonfinite.h"
#include <iostream>
#include <random>

using std::vector;

void gsa_analysis(int& nmc, int &nrv, int& ng, int& ncombs, vector<vector<double>>& x_val, vector<vector<double>>& g_val,
	coder::array<gsa_cell_wrap_0, 2U>& combs_temp, int & Kos, vector<vector<double>>& Si_val, vector<vector<double>>& St_val)
{
	
	coder::array<double, 2U> x_temp;
	coder::array<double, 1U> g_temp;

	x_temp.set_size(nmc, nrv);
	g_temp.set_size(nmc);

	for (int i = 0; i < nmc; i++) {
		for (int j = 0; j < nrv; j++) {
			x_temp[i + j * nmc] = x_val[i][j];
		}
	}

	const coder::array<double, 2U> x = x_temp;
	const coder::array<gsa_cell_wrap_0, 2U> combs = combs_temp;
	
	for (int j = 0; j < ng; j++) {
		
		coder::array<double, 1U> Si, St;
		
		for (int i = 0; i < nmc; i++) {
				g_temp[i] = g_val[i][j];
		}
		
		const coder::array<double, 1U> g = g_temp;

		runGSA_initialize();
		runGSA(x, g, combs, Kos, 'T', St); // 1st order total sobol indecies
		runGSA_initialize();
		runGSA(x, g, combs, Kos, 'M', Si); // 1st order sobol indecies




		vector<double> Si_temp, St_temp;

		for (int i = 0; i < ncombs; i++)
		{
			Si_temp.push_back(Si[i]);
			St_temp.push_back(St[i]);
		}

		Si_val.push_back(Si_temp);
		St_val.push_back(St_temp);

	}


	
}