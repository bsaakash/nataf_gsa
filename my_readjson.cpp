

#include "lib_json/json.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <regex>

using json = nlohmann::json;

extern std::ofstream theErrorFile;
void Getpnames(std::string distname, std::string optname, std::vector<std::string>& par_char);

void readjson(std::string workdir, int &nmc, int& nrv, int&nco, int& nqoi, int &rseed, std::string& UQ_method, std::vector<std::string>& get_distnames, std::vector<std::vector<double>>& get_vals, std::vector<double> & get_const,
				std::vector<std::string>& get_opts, std::vector<std::string>& get_rvnames, std::vector<std::string>& get_qoinames, std::vector<double>& get_corr, std::vector<std::vector<double>>& get_add,
				std::vector<std::vector<double>>& get_groups)
{

	//
	// read json
	//

	std::ifstream myfile(workdir+"/templatedir/dakota.json");
	//std::ifstream myfile(inpargv[1]);
	if (!myfile.is_open()) {
		theErrorFile << "Error reading json: Unable to open dakota.json";
		theErrorFile.close();
		exit(1);
	}


	json UQjson = json::parse(myfile);

	// 
	// Get variables
	// 

	nmc = UQjson["UQ_Method"]["samplingMethodData"]["samples"];
	rseed = UQjson["UQ_Method"]["samplingMethodData"]["seed"];
	UQ_method  = UQjson["UQ_Method"]["samplingMethodData"]["method"];

	//
	// Specify parameters in each distributions.
	//

	std::vector<int> corrIdx;
	int corrCount=0;
	nrv = 0;
	for (auto& elem : UQjson["randomVariables"])
	{
		corrCount++;

		// *name of distribution
		std::string distname = elem["distribution"];
		std::transform(distname.begin(), distname.end(), distname.begin(), ::tolower); // make lower case
		distname.erase(remove_if(distname.begin(), distname.end(), isspace), distname.end()); // remove space

		// *type of inputs ("PAR","MOM","DAT")
		std::string inpType = elem["inputType"];
		std::string inpTypeSub = inpType.substr(0, 3);
		for (int i = 0; i < 3; i++) {
			inpTypeSub[i] = toupper(inpTypeSub[i]);
		}

		// get parameter names for each dist
		std::vector<std::string> pnames;
		Getpnames(distname, inpTypeSub, pnames); 


		if (distname.compare("constant") == 0) {
			continue;
		}
		if ((distname.compare("discrete") == 0) && (inpTypeSub.compare("PAR"))==0) {
			if (elem[pnames[0]].size()==1) {
				// discrete distribution with only one quantity = constant
				continue;
			}
		}


		// *name of random variable
		get_rvnames.push_back(elem["name"]);
		get_distnames.push_back(distname);
		get_opts.push_back(inpTypeSub);


		

		std::vector<double> addDefault{ 0.0, 0.0 };

		// IF "DAT"
		if (get_opts[nrv].compare("DAT") == 0) {

			std::string directory = elem["dataDir"];
			std::ifstream data_table(directory);
			if (!data_table.is_open()) {
				//*ERROR*
				theErrorFile << "Error reading json: cannot open data file at " << directory << std::endl;
				theErrorFile.close();
				exit(1);
			}

			std::vector<double> vals_temp;
			double samps = 0.0;
			while (data_table >> samps) {
				vals_temp.push_back(samps);
			}
			get_vals.push_back(vals_temp);
			if (get_vals.size() < 5) {
				//*ERROR*
				theErrorFile << "Error reading json: data file of ";
				theErrorFile << get_rvnames[nrv];
				theErrorFile << " has less then five samples."  << std::endl;
				theErrorFile.close();
				exit(1);
			}

			if (vals_temp.size()==0) {
				//*ERROR*
				theErrorFile << "Error reading json: cannot find data at " << directory << std::endl;
				theErrorFile.close();
				exit(1);
			}
			data_table.close();

			if (get_distnames[nrv].compare("binomial") == 0) {
				get_add.push_back({ elem["n"],0.0 });
			}
			else if (get_distnames[nrv].compare("beta") == 0) {
				get_add.push_back({ elem["lowerbound"],elem["upperbound"] });
			}
			else if (get_distnames[nrv].compare("truncatedexponential") == 0) {
				get_add.push_back({ elem["a"],elem["b"] });
			}
			else
			{
				get_add.push_back(addDefault);
			}
		}
		else
		{ 
			if (get_distnames[nrv].compare("discrete") == 0) {
				std::vector<double> vals_temp;
				int numdisc = elem[pnames[0]].size();
				for (int i=0 ; i< numdisc ;i++)
				{
					vals_temp.push_back(elem[pnames[0]][i]);
					vals_temp.push_back(elem[pnames[1]][i]);
				}
				get_vals.push_back(vals_temp);
			}
			else
			{
				std::vector<double> vals_temp;
				for (auto& pn : pnames)
				{
					vals_temp.push_back(elem[pn]); // get parameter value from dist & parameter name
				}
				get_vals.push_back(vals_temp);	
			}
				
			get_add.push_back(addDefault);
		}
		corrIdx.push_back(corrCount-1);
		nrv++;
	}

	//
	// get constants
	//

	nco = 0;
	for (auto& elem : UQjson["randomVariables"])
	{
		// *name of distribution
		std::string distname = elem["distribution"];
		std::transform(distname.begin(), distname.end(), distname.begin(), ::tolower); // make lower case
		
		// *input type
		std::string inpType = elem["inputType"];
		std::string inpTypeSub = inpType.substr(0, 3);
		std::transform(inpTypeSub.begin(), inpTypeSub.end(), inpTypeSub.begin(), ::toupper); // make upper case


		// *parameter name
		std::vector<std::string> pnames;
		Getpnames(distname, inpTypeSub, pnames);

		// If constant
		if (distname.compare("constant") == 0) {

			// *name of random variable
			get_rvnames.push_back(elem["name"]);
			get_const.push_back(elem[pnames[0]]);
			nco++;
		}	


		// If constant (discrete)
		if ((distname.compare("discrete") == 0) && (inpTypeSub.compare("PAR"))==0) {
			if (elem[pnames[0]].size()==1) {
				// discrete distribution with only one quantity = constant

				get_rvnames.push_back(elem["name"]);
				get_const.push_back(elem[pnames[0]][0]);
				nco++;
			}
		}


	}


	//
	// get edp names
	//

	nqoi = 0;
	for (auto& elem : UQjson["EDP"]) {
		// *name of distribution
		get_qoinames.push_back(elem["name"]);
		nqoi++;
	}

	//
	// get correlation matrix
	//

	if (UQjson.find("correlationMatrix") != UQjson.end()) {
		// if key "correlationMatrix" exists
		for (int i = 0; i < nrv; i++) {
			for (int j = 0; j < nrv; j++) {
				get_corr.push_back(UQjson["correlationMatrix"][corrIdx[i]+corrIdx[j]*(nrv+nco)]);
			}
		}
	} 
	else
	{
		for (int i = 0; i < nrv * nrv; i++) {
			get_corr.push_back(0);
		}
		for (int i = 0; i < nrv; i++) {
			get_corr[i * nrv + i] = 1;
		}
	}

	//
	// get group index matrix
	//

	if (UQjson["UQ_Method"].find("sensitivityGroups") != UQjson["UQ_Method"].end()) {
		// if key "sensitivityGroups" exists

		std::string groupTxt = UQjson["UQ_Method"]["sensitivityGroups"];
		std::regex re(R"(\{([^}]+)\})"); // will get string inside {}
		std::sregex_token_iterator it(groupTxt.begin(), groupTxt.end(), re, 1);
		std::sregex_token_iterator end;
		while (it != end) {
			std::stringstream ss(*it++);
			std::vector<double> aGroup; // use double for future use (gsa function)
			while (ss.good()) {
				std::string substr;
				getline(ss, substr, ',');  // incase we have multiple strings inside {}
				std::vector<std::string>::iterator itr = std::find(get_rvnames.begin(), get_rvnames.end(), substr);
				if (itr != get_rvnames.cend()) { // from names (a,b,{a,b}) to idx's (1,2,{1,2})		
					int index_rvn = std::distance(get_rvnames.begin(), itr) + 1.0;
					aGroup.push_back(index_rvn );

					if (index_rvn>nrv) {
						// If it is constant variable
						theErrorFile << "Error reading json: RV group (for Sobol) cannot contain constant variable: ";
						theErrorFile << get_rvnames[index_rvn - 1] << std::endl;
						theErrorFile.close();
						exit(1);
					}
				}
				else {
					// *ERROR*
					theErrorFile << "Error reading json: element <"<< substr << "> inside the sensitivity groups not found." << std::endl;
					theErrorFile.close();
					exit(1);
				}
			}
			get_groups.push_back(aGroup);
		}
		}
	else {
		for (int i = 0; i < nrv; i++) {
			get_groups.push_back({ i + 1.0 });
		}
	}

}


void Getpnames(std::string distname, std::string optname, std::vector<std::string>& par_char)
{
	if (optname.compare("PAR") == 0) { // Get parameters

		if (distname.compare("binomial") == 0) {  // Not used
			par_char.push_back("n");
			par_char.push_back("p");
		}
		else if (distname.compare("geometric") == 0) {  // Not used
			par_char.push_back("p");
		}
		else if (distname.compare("negativebinomial") == 0) {  // Not used
			par_char.push_back("k");
			par_char.push_back("p");
		}
		else if (distname.compare("poisson") == 0) {
			par_char.push_back("lambda");
			par_char.push_back("t");
		}
		else if (distname.compare("uniform") == 0) {
			par_char.push_back("lowerbound");
			par_char.push_back("upperbound");
		}
		else if (distname.compare("normal") == 0) {
			par_char.push_back("mean");
			par_char.push_back("stdDev");
		}
		else if (distname.compare("lognormal") == 0) {
			par_char.push_back("lambda");
			par_char.push_back("zeta");
		}
		else if (distname.compare("exponential") == 0) {
			par_char.push_back("lambda");
		}
		else if (distname.compare("gamma") == 0) {
			par_char.push_back("lambda");
			par_char.push_back("k");
		}
		else if (distname.compare("beta") == 0) {
			par_char.push_back("alphas");
			par_char.push_back("betas");
			par_char.push_back("lowerbound");
			par_char.push_back("upperbound");
		}
		else if (distname.compare("gumbelMin") == 0) {  // Not used
			par_char.push_back("an");
			par_char.push_back("bn");
		}
		else if (distname.compare("gumbel") == 0) {
			par_char.push_back("alphaparam");
			par_char.push_back("betaparam");
		}
		else if (distname.compare("frechet") == 0) {  // Not used
			par_char.push_back("an");
			par_char.push_back("k");
		}
		else if (distname.compare("weibull") == 0) {
			par_char.push_back("scaleparam"); //an
			par_char.push_back("shapeparam"); //k
		}
		else if (distname.compare("gev") == 0) {  
			par_char.push_back("beta");
			par_char.push_back("alpha");
			par_char.push_back("epsilon");
		}
		else if (distname.compare("gevmin") == 0) {  // Not used
			par_char.push_back("beta");
			par_char.push_back("alpha");
			par_char.push_back("epsilon");
		}
		else if (distname.compare("pareto") == 0) {  // Not used
			par_char.push_back("x_m");
			par_char.push_back("alpha");
		}
		else if (distname.compare("rayleigh") == 0) {  // Not used
			par_char.push_back("alpha");
		}
		else if (distname.compare("chisquare") == 0) {
			par_char.push_back("k");
		}
		else if (distname.compare("discrete") == 0) {
			par_char.push_back("Values");
			par_char.push_back("Weights");
		}
		else if (distname.compare("truncatedexponential") == 0) {
			par_char.push_back("lambda");
			par_char.push_back("a");
			par_char.push_back("b");
		}
		else if (distname.compare("constant") == 0) {
			par_char.push_back("value");
		}
		else {
			theErrorFile << "Error reading json: cannot interpret distribution name: " << distname;
			theErrorFile.close();
			exit(1);
			// NA
		}
	} 
	else if (optname.compare("MOM") == 0) { // Get Moments
		if (distname.compare("normal") == 0) {  // Not used
			par_char.push_back("mean");
			par_char.push_back("stdDev");  // 
		}
		else if (distname.compare("lognormal") == 0) {  // Not used
			par_char.push_back("mean");
			par_char.push_back("stdDev");  // 
		}
		else if (distname.compare("geometric") == 0) {  // Not used
			par_char.push_back("mean");
		}
		else if (distname.compare("poisson") == 0) {
			par_char.push_back("mean");
		}
		else if (distname.compare("exponential") == 0) {
			par_char.push_back("mean");
		}
		else if (distname.compare("beta") == 0) {
			par_char.push_back("mean");
			par_char.push_back("standardDev");
			par_char.push_back("lowerbound");
			par_char.push_back("upperbound");
		}
		else if (distname.compare("gev") == 0) {
			par_char.push_back("mean");
			par_char.push_back("standardDev");
			par_char.push_back("epsilon");
		}
		else if (distname.compare("gevmin") == 0) {  // Not used
			par_char.push_back("mean");
			par_char.push_back("standardDev");
			par_char.push_back("epsilon");
		}
		else if (distname.compare("rayleigh") == 0) {  // Not used
			par_char.push_back("mean");
		}
		else if (distname.compare("chisquare") == 0) {
			par_char.push_back("mean");
		}
		else if (distname.compare("constant") == 0) {
			par_char.push_back("value");
		}
		else if (distname.compare("truncatedexponential") == 0) {
			par_char.push_back("mean");
			par_char.push_back("a");
			par_char.push_back("b");
		}
		else
		{
			par_char.push_back("mean");
			par_char.push_back("standardDev");
		}
	}
	else if (optname.compare("DAT") == 0) { // Get DATA	
		if (distname.compare("binomial") == 0) {
			par_char.push_back("n");
		}
		else if (distname.compare("beta") == 0) {
			par_char.push_back("lowerbound");
			par_char.push_back("upperbound");
		}
		else if (distname.compare("truncatedexponential") == 0) {
			par_char.push_back("a");
			par_char.push_back("b");
		}
		else if (distname.compare("constant") == 0) {
			par_char.push_back("value");
		}
	}
	else {
		theErrorFile << "Error reading json: input type should be one of PAR/MOM/DAT";
		theErrorFile.close();
		exit(1);
	}
}
