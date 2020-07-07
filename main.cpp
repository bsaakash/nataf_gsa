

#include <iostream>
#include <random>

// (1) Read json, (2) do (inverse) Nataf, (3) do Global sensitivity analysis
#include "my_functions.h"

int main()
{
	// (1) Read JSON file 
	int nmc, nrv, rseed;
	std::string UQ_method;
	std::vector<double> get_corr;	
	std::vector<std::string> get_distnames, get_opts;	
	std::vector<std::vector<double>> get_pars;
	readjson(nmc, nrv, rseed, UQ_method, get_distnames, get_pars, get_opts, get_corr); 

	// Random sampler: standard gaussian -> Later change into LHS
	coder::array<double, 2U> u_temp;
	std::default_random_engine generator(rseed);
	std::normal_distribution<double> distribution(0.0, 1.0);
	u_temp.set_size(nmc, nrv);
	for (int i = 0; i < nmc; ++i) {
		for (int j = 0; j < nrv; ++j) {
			u_temp[i + j * nmc] = distribution(generator);
		}
	}
	
	// (2) Nataf transform + FEM simulation <- *********** need to be connected to other FEM softwares
	std::vector<double> px, g; // will be modified for multiple outputs
	std::vector<std::vector<double>> x; 
	nataf_transf(nrv, nmc, get_distnames, get_opts, get_pars, get_corr, u_temp, x, px, g); // NEED ERROR CHECK
	
	// WRITE
	std::cout << "Monte Carlo done.. running Global Sensitivity Analysis..." << std::endl;
	
	//  (3) GSA
	coder::array<gsa_cell_wrap_0, 2U> combs;
	int Kos = 50; // number of GM compontents - fixed
	int ncomb = nrv;
	std::vector<double> Si, St;
	combs.set_size(1, ncomb);
	for (int i = 0; i < ncomb; i++) {
		combs[i].f1 = { (double)i + 1.0 }; // Fixed to be 1st order only. Later we could get this as user input.
	}			
	gsa_analysis(nrv, nmc, ncomb, x, g, combs, Kos, Si, St); // NEED ERROR CHECK, will be modified for multiple outputs

	// WRITE
	for (int i = 0; i < nrv; i++) {
		std::cout << "S" << i << ": " << Si[i] << ",   " << St[i] << "   " << std::endl;
	}
	std::cout << "#MCS=" << nmc << std::endl;

	return 0;
}
