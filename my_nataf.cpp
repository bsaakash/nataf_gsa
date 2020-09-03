
#include "lib_mat/ntf_ERADist.h"
#include "lib_mat/ntf_ERANataf.h"
#include "lib_mat/ntf_inataf.h"
#include "lib_mat/ntf_inataf_initialize.h"
#include "lib_mat/ntf_strcmp.h"
#include "lib_mat/rt_nonfinite.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem>

extern std::ofstream theErrorFile;

using std::vector;
using std::string;

vector<vector<double> > runApps(int nmc,
				int nrv,
				int nqoi,
				vector<vector<double> > x,
				vector<std::string> get_rvnames,
				std::string workdir);

void nataf_transf(int nmc,
		  int nrv,
		  int nco,
		  int nqoi,
		  vector<string> &get_distnames,
		  vector<string> &get_opts,
		  vector<vector<double> > &
		  get_vals,
		  vector<double>& get_const,
		  vector<string>& get_rvnames,
		  vector<double> &get_corr,
		  vector<vector<double> > &get_add,
		  string & workdir,
		  coder::array<double, 2U> &u_temp,
		  vector<vector<double> > &x_val,
		  vector<double> &px_val,
		  vector<vector<double> > &g_val)
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
			for (int k = 0; k < nco; k++)
			{
				x_temp.push_back(get_const[k]);
			}
		}
		x_val.push_back(x_temp);
	}

	// Run FEM and other simulations
	g_val = runApps(nmc, nrv+nco, nqoi, x_val, get_rvnames, workdir );
	
}


vector<vector<double> > runApps(int nmc, int nrvs, int nqoi, vector<vector<double> > x, vector<std::string> get_rvnames, std::string workdir)
{
	vector<vector<double> > g_val;
	

	for (int i = 0; i < nmc; i++)
	{

		//
		// (1) create "workdir.i " folder :need C++17 to use the files system namespace 
		//
		
		string workDir = workdir + "/tmp.SimCenter/workdir." + std::to_string(i+1);
		//std::filesystem::remove(workDir);
		std::filesystem::create_directory(workDir);
		std::filesystem::current_path(workDir);

		//
		// (2) copy files from templatedir to workdir.i
		//

		//TEMPORARY:: REPLACE THIS PART
		const auto copyOptions = std::filesystem::copy_options::overwrite_existing;

		//std::filesystem::copy("C:/Users/yisan/Desktop/Development/nataf_gsa/additional_files/insideTemplatedir/workflow_driver.bat",workdir + "/tmp.SimCenter/templateDir/workflow_driver.bat", copyOptions);
		std::filesystem::copy(workdir + "/tmp.SimCenter/templateDir", workDir, copyOptions);

		//
		// (3) write param.in file
		//

		string params = workDir + "/params.in";
		std::ofstream writeFile(params.data());
		if (writeFile.is_open()) {
			writeFile << std::to_string(nrvs)+ "\n";
			for (int j = 0; j < nrvs; j++) {
				writeFile << get_rvnames[j] + " ";
				writeFile << std::to_string(x[i][j]) + "\n";
			}
			writeFile.close();
		}

		//
		// (4) run workflow_driver.bat(e.g. It will make "SimCenterInput.tcl" and run OpenSees)
		//

		string workflowDriver_string = workDir + "/workflow_driver.bat";
		const char* workflowDriver_char = workflowDriver_string.c_str();
		system(workflowDriver_char);

		//
		// (5) get the values in "results.out"
		//

		string results = workDir + "/results.out";
		std::ifstream readFile(results.data());

		if (!readFile.is_open()) {
			//*ERROR*
			theErrorFile << "Error reading FEM results: check your working directory: " << workDir << std::endl;
			theErrorFile.close();
			exit(1);
		}



		vector<double> g_tmp(nqoi);
		if (readFile.is_open()) {
			int j = 0;
			double g;
			while (readFile >> g) {
				g_tmp[j] = g;
				j++;
			}
			readFile.close();
		}

		g_val.push_back(g_tmp);

	}
	
	return g_val;





	//double sum = 0;
	//for (double x_elem : x)
	//{
	//	sum += (abs(x_elem));
	//}

	//vector<double> response;
	//response.push_back(sum);

}
