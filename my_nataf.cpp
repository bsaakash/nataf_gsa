
#include "lib_mat\ntf_ERADist.h"
#include "lib_mat\ntf_ERANataf.h"
#include "lib_mat\ntf_inataf.h"
#include "lib_mat\ntf_inataf_initialize.h"
#include "lib_mat\ntf_strcmp.h"
#include "lib_mat\rt_nonfinite.h"

#include <iostream>
#include <cmath>

double FEM_analysis(int nrv, std::vector<double> x);

void nataf_transf(int nrv, int nmc, std::vector<std::string> &get_distnames, std::vector<std::string> &get_opts,
					std::vector<std::vector<double>> &get_pars, std::vector<double> &get_corr, coder::array<double, 2U> &u_temp,
					std::vector<std::vector<double>> &x_val, std::vector<double> &px_val, std::vector<double> &g_val)
{


	coder::array<double, 2U> corrs_temp;
	coder::array<ntf_cell_wrap_0, 2U> distnames_temp;
	coder::array<ntf_cell_wrap_0, 2U> opts_temp;
	coder::array<ntf_cell_wrap_1, 2U> pars_temp;

	distnames_temp.set_size(1, nrv);
	opts_temp.set_size(1, nrv);
	pars_temp.set_size(1, nrv);
	corrs_temp.set_size(nrv, nrv);


	for (int i = 0; i < nrv; i++) {
		distnames_temp[i] = { get_distnames[i] };
		opts_temp[i] = { get_opts[i] };
		pars_temp[i].f1 = get_pars[i];

		for (int j = 0; j < nrv; j++) {
			corrs_temp[i + j * nrv] = get_corr[i + j * nrv];
		}

	}
	
	coder::array<double, 2U> u = u_temp;
	coder::array<ntf_cell_wrap_0, 2U> distnames = distnames_temp;
	coder::array<ntf_cell_wrap_0, 2U> opts = opts_temp;
	coder::array<ntf_cell_wrap_1, 2U> pars = pars_temp;
	coder::array<double, 2U> corrs = corrs_temp;

	coder::array<double, 2U> x;
	coder::array<double, 1U> px;
	coder::array<double, 1U> g;
	inataf_initialize();
	inataf(u, distnames, opts, pars, corrs, x, px);


	for (int i = 0; i < nmc; i++) 
	{
		std::vector<double> x_temp ;
		px_val.push_back(px[i]);
		for (int j = 0; j < nrv; j++)
		{
			x_temp.push_back(x[i + j * nmc]);
		}
		x_val.push_back(x_temp);
	}

	// Run FEM simulations

	double FEM_val;
	for (int i = 0; i < nmc; i++)
	{
		FEM_val = FEM_analysis(nrv, x_val[i]);
		g_val.push_back(FEM_val); // Later Replaced by OPENSEES
	}
}


double FEM_analysis(int nrv, std::vector<double> x)
{
	
	double sum = 0;
	for (double x_elem : x)
	{
		sum += sqrt(abs(x_elem));
	}

	return sum;
}