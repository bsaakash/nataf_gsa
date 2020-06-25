


#include "lib_mat\gsa_combineVectorElements.h"
#include "lib_mat\gsa_runGSA.h"
#include "lib_mat\gsa_runGSA_initialize.h"
#include "lib_mat\gsa_sum.h"
#include "lib_mat\gsa_vvarstd.h"
#include "lib_mat\rt_nonfinite.h"
#include <iostream>
#include <random>

void gsa_analysis(int &nrv, int& nmc, int& ncombs, std::vector<std::vector<double>>& x_val, std::vector<double>& g_val,
	coder::array<gsa_cell_wrap_0, 2U>& combs_temp, int & Kos, std::vector<double>& Si_val)
{
	
	
	coder::array<double, 2U> x_temp;
	coder::array<double, 1U> g_temp;

	x_temp.set_size(nmc, nrv);
	g_temp.set_size(nmc);

	for (int i = 0; i < nmc; ++i) {
		g_temp[i] = g_val[i];
		for (int j = 0; j < nrv; ++j) {
			x_temp[i + j * nmc] = x_val[i][j];
		}
	}

	const coder::array<double, 2U> x = x_temp;
	const coder::array<double, 1U> g = g_temp;
	const coder::array<gsa_cell_wrap_0, 2U> combs = combs_temp;

	coder::array<double, 1U> Si;

	runGSA_initialize();
	runGSA(x, g, combs, Kos, Si); // 1st order sobol indecies

	// runGSA(x, g, combs, (double)Kos, Si);

	for (int i = 0; i < ncombs; i++)
	{
		Si_val.push_back(Si[i]);
	}
	
}