
#include "lib_mat/gsa_runGSA.h"
#include "lib_mat/gsa_runGSA_initialize.h"
#include "lib_mat/gsa_vvarstd.h"
#include "lib_mat/rt_nonfinite.h"
#include <iostream>
#include <fstream>
#include <random>
#include <math.h>


extern std::ofstream theErrorFile;

using std::vector;
void gsa_analysis(int& nmc, int &nrv, int& nqoi, int& ncombs, vector<vector<double>>& x_val, vector<vector<double>>& g_val,
	vector<vector<double>>& get_groups, int & Kos, vector<vector<double>>& Si_val, vector<vector<double>>& St_val)
{

	coder::array<gsa_cell_wrap_0, 2U> combs_temp;

	combs_temp.set_size(1, ncombs);
	for (int i = 0; i < ncombs; i++) {
		//combs[i].f1 = { (double)i + 1.0 }; // Fixed to be 1st order only. Later we could get this as user input.
		combs_temp[i].f1 = { get_groups[i] };


	}


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
	
	for (int j = 0; j < nqoi; j++) {
		
		coder::array<double, 1U> Si, St;
		
		for (int i = 0; i < nmc; i++) {
				g_temp[i] = g_val[i][j];
		}

		// check if the variance is zero
		double sum = 0, sqDiff = 0;
		for (int i = 0; i < nmc; i++) {
			sum += g_val[i][j];
		}
		double mean = sum / double(nmc);
		for (int i = 0; i < nmc; i++)
			sqDiff += (g_val[i][j] - mean) * (g_val[i][j] - mean);
		//double var = sqDiff / nmc;
		if (sqDiff <1.e-10) {
			theErrorFile << "Error running FEM: the variance of output is zero. Output value is " << mean;
			theErrorFile.close();
			exit(1);
		};


		
		const coder::array<double, 1U> g = g_temp;


		runGSA_initialize();
		//runGSA(x, g, combs, Kos, 'T', St); // 1st order total sobol indecies
		runGSA(x, g, combs, 3, 'T', St); // 1st order total sobol indecies
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