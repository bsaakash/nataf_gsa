
#include "lib_json/json.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using json = nlohmann::json;


void Getpnames(std::string distname, std::string optname, std::vector<std::string>& par_char);

void readjson(int &nmc, int& nrv, int& ng, int &rseed, std::string& UQ_method, std::vector<std::string>& get_distnames, std::vector<std::vector<double>>& get_vals,
					std::vector<std::string>& get_opts, std::vector<double>& get_corr, std::vector<std::vector<double>>& get_add)
{
	// === IMPORTANT* need to additionally import correlation matrix & "input option" to GUI
	get_corr = { 1.0, 0.2, 0.2, 1.0 }; // {{row1}, {row2},...}
	//get_opts = { "DATA","DATA" }; // either "MOM" or "PAR" (later, extend to "DATA")
	
	
	get_opts = { "PAR","PAR" }; // either "MOM" or "PAR" (later, extend to "DATA")
	ng = 1; // Number of outputs
	//get_corr = { 1.0, 0.2, 0.2, 0.2,   0.2, 1.0, 0.2, 0.2 ,  0.2, 0.2, 1.0, 0.2,   0.2, 0.2, 0.2, 1.0}; 
	//get_corr = { 1.0, 0.0, 0.0, 0.0,   0.0, 1.0, 0.0, 0.0 ,  0.0, 0.0, 1.0, 0.0,   0.0, 0.0, 0.0, 1.0 };
	//get_opts = { "MOM","MOM","MOM","MOM" };

	// === read json
	//std::ifstream myfile("dakotaDataExact.json");
	//std::ifstream myfile("dakotaData.json");
	std::ifstream myfile("dakotaDataDiscrete.json");
	json UQjson = json::parse(myfile);

	// === get variables
	nmc = UQjson["UQ_Method"]["samplingMethodData"]["samples"];
	rseed = UQjson["UQ_Method"]["samplingMethodData"]["seed"];
	UQ_method  = UQjson["UQ_Method"]["samplingMethodData"]["method"];

	// === Specify parameters in each distributions.
	nrv = 0;
	for (auto& elem : UQjson["randomVariables"])
	{
		get_distnames.push_back(elem["distribution"]);		

		std::vector<std::string> pnames;
		Getpnames(get_distnames[nrv], get_opts[nrv], pnames); // get parameter names from dist name
		std::vector<double> addDefault{ 0.0, 0.0 };
		// IF Data
		if (get_opts[nrv].compare("DATA") == 0) {

			std::string directory = elem["datafile"];
			std::ifstream data_table(directory);
			if (!data_table.is_open()) {
				//std::cerr << "There was a problem opening the input file!\n";
				//exit(1);//exit or do additional error checking
				// PRINT ERROR
			}

			std::vector<double> vals_temp;
			double samps = 0.0;
			while (data_table >> samps) {
				vals_temp.push_back(samps);
			}
			get_vals.push_back(vals_temp);
			data_table.close();
			//std::vector<double> add_temp;

			if (get_distnames[nrv].compare("binomial") == 0) {
				//add_temp.push_back(elem["n"]);
				//add_temp.push_back(0.0);
				//get_add.push_back(add_temp);
				get_add.push_back({ elem["n"],0.0 });
			}
			else if (get_distnames[nrv].compare("beta") == 0) {
				//add_temp.push_back(elem["lower"]);
				//add_temp.push_back(elem["upper"]);
				//get_add.push_back(add_temp);
				get_add.push_back({ elem["lower"],elem["upper"] });

			} 
			else
			{
				get_add.push_back(addDefault);
			}
		}
		else
		{ 

			
			if (get_distnames[nrv].compare("discrete") == 0) {
				get_vals.push_back(elem[pnames[0]]);
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
		nrv++;
	}

}


void Getpnames(std::string distname, std::string optname, std::vector<std::string>& par_char)
{
	std::transform(distname.begin(), distname.end(), distname.begin(), ::tolower);

	if (optname.compare("PAR") == 0) { // Get parameters

		if (distname.compare("binomial") == 0) {
			par_char.push_back("n");
			par_char.push_back("p");
		}
		else if (distname.compare("geometric") == 0) {
			par_char.push_back("p");
		}
		else if (distname.compare("negativebinomial") == 0) {
			par_char.push_back("k");
			par_char.push_back("p");
		}
		else if (distname.compare("poisson") == 0) {
			par_char.push_back("lambda");
			par_char.push_back("t");
		}
		else if (distname.compare("uniform") == 0) {
			par_char.push_back("lower");
			par_char.push_back("upper");
		}
		else if (distname.compare("normal") == 0) {
			par_char.push_back("mean");
			par_char.push_back("stdDev");
		}
		else if (distname.compare("lognormal") == 0) {
			par_char.push_back("logmean");
			par_char.push_back("logstd");
		}
		else if (distname.compare("exponential") == 0) {
			par_char.push_back("lambda");
		}
		else if (distname.compare("gamma") == 0) {
			par_char.push_back("lambda");
			par_char.push_back("k");
		}
		else if (distname.compare("beta") == 0) {
			par_char.push_back("r");
			par_char.push_back("s");
			par_char.push_back("lower");
			par_char.push_back("upper");
		}
		else if (distname.compare("gumbelMin") == 0) {
			par_char.push_back("an");
			par_char.push_back("bn");
		}
		else if (distname.compare("gumbel") == 0) {
			par_char.push_back("an");
			par_char.push_back("bn");
		}
		else if (distname.compare("frechet") == 0) {
			par_char.push_back("an");
			par_char.push_back("k");
		}
		else if (distname.compare("weibull") == 0) {
			par_char.push_back("an");
			par_char.push_back("k");
		}
		else if (distname.compare("GEV") == 0) {
			par_char.push_back("beta");
			par_char.push_back("alpha");
			par_char.push_back("epsilon");
		}
		else if (distname.compare("GEVMin") == 0) {
			par_char.push_back("beta");
			par_char.push_back("alpha");
			par_char.push_back("epsilon");
		}
		else if (distname.compare("pareto") == 0) {
			par_char.push_back("x_m");
			par_char.push_back("alpha");
		}
		else if (distname.compare("rayleigh") == 0) {
			par_char.push_back("alpha");
		}
		else if (distname.compare("chisquare") == 0) {
			par_char.push_back("k");
		}
		else if (distname.compare("discrete") == 0) {
			par_char.push_back("pmf");
		}
		else {
			// NA
		}
	} 
	else if (optname.compare("MOM") == 0) { // Get Moments
		if (distname.compare("geometric") == 0) {
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
			par_char.push_back("stdDev");
			par_char.push_back("lower");
			par_char.push_back("upper");
		}
		else if (distname.compare("GEV") == 0) {
			par_char.push_back("mean");
			par_char.push_back("stdDev");
			par_char.push_back("epsilon");
		}
		else if (distname.compare("GEVMin") == 0) {
			par_char.push_back("mean");
			par_char.push_back("stdDev");
			par_char.push_back("epsilon");
		}
		else if (distname.compare("rayleigh") == 0) {
			par_char.push_back("mean");
		}
		else if (distname.compare("chisquare") == 0) {
			par_char.push_back("mean");
		}
		else
		{
			par_char.push_back("mean");
			par_char.push_back("stdDev");
		}
	}
	else if (optname.compare("DATA") == 0) { // Get DATA	
		if (distname.compare("binomial") == 0) {
			par_char.push_back("n");
		}
		else if (distname.compare("beta") == 0) {
			par_char.push_back("lower");
			par_char.push_back("upper");
		}
	}
	else {
		//NA
	}
}