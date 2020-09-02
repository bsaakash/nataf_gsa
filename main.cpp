#include <iostream>
#include <fstream>
#include <random>

// (1) Read json, (2) do (inverse) Nataf, (3) do Global sensitivity analysis
#include "my_functions.h"

using std::vector;
std::ofstream theErrorFile;

int main(int argc, char **argv)
//int main()
{
	std::string workdir = argv[1];
	//theErrorFile.open(workdir + "/tmp.SimCenter/dakota.err");
	//my_MakeErrorFile theErrorFile = my_MakeErrorFile(workdir);
	theErrorFile.open(workdir + "/tmp.SimCenter/dakota.err");

	// (1) Read JSON file 
	int nmc, nrv, nco, nqoi, rseed;
	std::string UQ_method;
	vector<double> get_corr, get_const;	
	vector<std::string> get_distnames, get_opts, get_rvnames, get_qoinames;
	vector<vector<double>> get_pars, get_add;
	vector<vector<double>> get_groups; // use double for GSA from matlab
	readjson(workdir, nmc, nrv, nco, nqoi, rseed, UQ_method, get_distnames, get_pars, get_const, get_opts,
		     get_rvnames, get_qoinames, get_corr, get_add, get_groups);
	//readjson(nmc, nrv, ng, rseed, UQ_method, get_distnames, get_pars, get_opts,
	//	     get_rvnames, get_corr, get_add, get_groups, get_workdir);

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
	
	nataf_transf(nmc, nrv, nco, nqoi, get_distnames, get_opts, get_pars, get_const, get_rvnames, get_corr, get_add, workdir, u_temp, x, px, g); // NEED ERROR CHECK

	// WRITE
	std::cout << "Monte Carlo done.. running Global Sensitivity Analysis..." << std::endl;
	
	//  (3) GSA
	int Kos = 3; // number of GM compontents - fixed
	int ncomb = get_groups.size();;
	vector<vector<double>> Si, St;
	gsa_analysis(nmc, nrv, nqoi, ncomb, x, g, get_groups, Kos, Si, St); // NEED ERROR CHECK, will be modified for multiple outputs

	// (4) WRITE /dakota.out
	std::string writingloc = workdir + "/tmp.SimCenter/dakota.out";
	std::ofstream outfile(writingloc);

	
	outfile.setf(std::ios::fixed, std::ios::floatfield); // set fixed floating format
	outfile.precision(4); // for fixed format, two decimal places

	
	outfile << "* number of input combinations" << std::endl;
	outfile << ncomb << std::endl;

	outfile << "* input names" << std::endl;
	for (int i = 0; i < ncomb; i++) {
		for (int j = 0; j < get_groups[i].size()-1; j++) {
			outfile << get_rvnames[get_groups[i][j]-1] << ",";
		}
		outfile << get_rvnames[get_groups[i][get_groups[i].size()-1]-1] << std::endl;
	}

	outfile << "* number of outputs" << std::endl;
	outfile << nqoi << std::endl;

	outfile << "* output names" << std::endl;
	for (int i = 0; i < nqoi; i++) {
		outfile << get_qoinames[i] << std::endl;
	}

	outfile <<"* ";
	for (int j = 0; j < ncomb; j++) {
		outfile << "Sm(" << std::to_string(j+1) << ")  ";
	}
	for (int j = 0; j < ncomb; j++) {
		outfile << "St(" << std::to_string(j + 1) << ")  ";
	}	
	outfile << std::endl;

	for (int i = 0; i < nqoi; i++) {

		for (int j = 0; j< ncomb; j++) {
			outfile << Si[i][j] << " " ;
		}
		for (int j = 0; j < ncomb; j++) {
			outfile << St[i][j] << " ";
		}
		outfile << std::endl;
	}

	outfile << "* number of samples" << std::endl;
	outfile << nmc << std::endl;

	outfile.close();

	// (4) WRITE dakotaTab.out
	std::string writingloc1 = workdir + "/tmp.SimCenter/dakotaTab.out";
	std::ofstream Taboutfile(writingloc1);

	Taboutfile.setf(std::ios::fixed, std::ios::floatfield); // set fixed floating format
	Taboutfile.precision(10); // for fixed format, two decimal places

		Taboutfile << "idx         ";
		for (int j = 0; j < nrv+nco; j++) {
			Taboutfile << get_rvnames[j] << "           ";
		}
		for (int j = 0; j < nqoi; j++) {
			Taboutfile << get_qoinames[j] << "            ";
		}
		Taboutfile << std::endl;


	for (int i = 0; i < nmc; i++) {
		Taboutfile << std::to_string(i+1) << "    ";
		for (int j = 0; j < nrv+nco; j++) {
			Taboutfile << std::to_string(x[i][j]) << "    ";
		}
		for (int j = 0; j < nqoi; j++) {
			Taboutfile << std::to_string(g[i][j]) << "    ";
		}
		Taboutfile << std::endl;
	}

	theErrorFile.close();

	return 0;
}
