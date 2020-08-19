

#include <iostream>
#include <fstream>
#include <random>

// (1) Read json, (2) do (inverse) Nataf, (3) do Global sensitivity analysis
#include "my_functions.h"

using std::vector;

int main()
{
	// (1) Read JSON file 
	int nmc, nrv, ng, rseed;
	std::string UQ_method, get_workdir;
	vector<double> get_corr;	
	vector<std::string> get_distnames, get_opts, get_rvnames;	
	vector<vector<double>> get_pars, get_add;
	vector<vector<double>> get_groups; // use double for GSA from matlab
	readjson(nmc, nrv, ng, rseed, UQ_method, get_distnames, get_pars, get_opts, get_rvnames, get_corr, get_add, get_groups, get_workdir);


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
	vector<double> px;
	vector<vector<double>> x, g;
	
	nataf_transf(nmc, nrv, ng, get_distnames, get_opts, get_pars, get_rvnames, get_corr, get_add, get_workdir, u_temp, x, px, g); // NEED ERROR CHECK



	// WRITE
	std::cout << "Monte Carlo done.. running Global Sensitivity Analysis..." << std::endl;
	//  (3) GSA
	int Kos = 50; // number of GM compontents - fixed
	int ncomb = get_groups.size();;
	vector<vector<double>> Si, St;
	gsa_analysis(nmc, nrv, ng, ncomb, x, g, get_groups, Kos, Si, St); // NEED ERROR CHECK, will be modified for multiple outputs

	// WRITE
	std::string writingloc = get_workdir + "/gsa.txt";
	std::ofstream outfile(writingloc);


	// header
	
	outfile.setf(std::ios::fixed, std::ios::floatfield); // set fixed floating format
	outfile.precision(4); // for fixed format, two decimal places

	outfile << "#MCS=" << nmc << std::endl;
	outfile <<"    ";
	for (int j = 0; j < ncomb; j++) {
		//outfile << "Sm" << std::to_string(j) << ",      ";
		outfile << "Sm(" << std::to_string(j) << "),    ";
	}
	for (int j = 0; j < ncomb-1; j++) {
		outfile << "St(" << std::to_string(j) << "),    ";
	}	
	outfile << "St(" << std::to_string(ncomb - 1) << "), " << std::endl;

	//rseults
	for (int i = 0; i < ng; i++) {
		outfile << "g" << i << ": ";

		for (int j = 0; j< ncomb; j++) {
			outfile << Si[i][j] << ",   " ;
		}
		for (int j = 0; j < ncomb-1; j++) {
			outfile << St[i][j] << ",   ";
		}
		outfile << St[i][ncomb - 1] << std::endl;
	}
	
	outfile.close();

	return 0;
}
