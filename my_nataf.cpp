
#include "lib_mat/ntf_ERADist.h"
#include "lib_mat/ntf_ERANataf.h"
#include "lib_mat/ntf_inataf.h"
#include "lib_mat/ntf_inataf_initialize.h"
#include "lib_mat/ntf_strcmp.h"
#include "lib_mat/rt_nonfinite.h"
#include <iostream>
#include <cmath>

using std::vector;


vector<double> FEM_analysis(int nrv, vector<double> x);

void nataf_transf(int nmc, int nrv, vector<std::string> &get_distnames, vector<std::string> &get_opts,
					vector<vector<double>> &get_vals, vector<double> &get_corr, vector<vector<double>> &get_add, coder::array<double, 2U> &u_temp,
					vector<vector<double>> &x_val, vector<double> &px_val, vector<vector<double>> &g_val)
{


	coder::array<double, 2U> corrs_temp;
	coder::array<ntf_cell_wrap_0, 2U> distnames_temp;
	coder::array<ntf_cell_wrap_0, 2U> opts_temp;
	coder::array<ntf_cell_wrap_1, 2U> vals_temp;
	coder::array<ntf_cell_wrap_1, 2U> add_temp;

	distnames_temp.set_size(1, nrv);
	opts_temp.set_size(1, nrv);
	vals_temp.set_size(1, nrv);
	corrs_temp.set_size(nrv, nrv);
	add_temp.set_size(1, nrv);


	for (int i = 0; i < nrv; i++) {
		distnames_temp[i] = { get_distnames[i] };
		opts_temp[i] = { get_opts[i] };
		vals_temp[i].f1 = get_vals[i];
		add_temp[i].f1 = get_add[i];

		for (int j = 0; j < nrv; j++) {
			corrs_temp[i + j * nrv] = get_corr[i + j * nrv];
		}

	}
	
	//coder::array<double, 2U> u = u_temp;
	//coder::array<ntf_cell_wrap_0, 2U> distnames = distnames_temp;
	//coder::array<ntf_cell_wrap_0, 2U> opts = opts_temp;
	//coder::array<ntf_cell_wrap_1, 2U> vals = vals_temp;
	//coder::array<double, 2U> corrs = corrs_temp;
	//coder::array<ntf_cell_wrap_1, 2U> add = add_temp;

	coder::array<double, 2U> x;
	coder::array<double, 1U> px;
	
	inataf_initialize();
	//inataf(u, distnames, opts, vals, corrs, add, x, px);
	inataf(u_temp, distnames_temp, opts_temp, vals_temp, corrs_temp, add_temp, x, px);


	coder::array<double, 1U> g;
	
	for (int i = 0; i < nmc; i++) 
	{
		vector<double> x_temp ;
		px_val.push_back(px[i]);
		for (int j = 0; j < nrv; j++)
		{
			x_temp.push_back(x[i + j * nmc]);
		}
		x_val.push_back(x_temp);
	}

	// Run FEM simulations

	vector<double> FEM_val;
	for (int i = 0; i < nmc; i++)
	{
		FEM_val = FEM_analysis(nrv, x_val[i]);
		g_val.push_back(FEM_val); 
	}
}


vector<double>  FEM_analysis(int nrv, vector<double> x)
{
	
	double sum = 0;
	for (double x_elem : x)
	{
		sum += (abs(x_elem));
	}

	//double sum2 = 0;
	//for (double x_elem : x)
	//{
	//	sum2 += (sqrt(abs(x_elem)));
	//}

	//double sum3 = 0;
	//for (double x_elem : x)
	//{
	//	sum3 += sqrt(sqrt(abs(x_elem)));
	//}
	vector<double> response;
	response.push_back(sum);
	//response.push_back(sum2);
	//response.push_back(sum3);

	return response;
}