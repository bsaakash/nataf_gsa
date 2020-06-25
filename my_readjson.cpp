
#include "lib_json\json.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using json = nlohmann::json;


void GetdistID(std::string distname, std::string optname, int& distID, int& optID, int& npar, int& nmom);

void readjson(int &nmc, int& nrv, int &rseed, std::string& UQ_method, std::vector<std::string>& get_distnames, std::vector<std::vector<double>>& get_pars,
					std::vector<std::string>& get_opts, std::vector<double>& get_corr)
{
	// === IMPORTANT* need to additionally import "correlation matrix" & "input option"
	get_corr = { 1.0, 0, 0, 1.0 }; // {{row1}, {row2},...}
	get_opts = { "MOM","MOM" }; // "MOM" or "PAR"

	// === read json
	std::ifstream myfile("dakota.json");
	json UQjson = json::parse(myfile);

	// === get variables
	nmc = UQjson["UQ_Method"]["samplingMethodData"]["samples"];
	rseed = UQjson["UQ_Method"]["samplingMethodData"]["seed"];
	UQ_method  = UQjson["UQ_Method"]["samplingMethodData"]["method"];

	// === Manually specify parameters in each distributions.
	// === IMPORTANT* TO BE FINISHED
	nrv = 0;
	int distID, optsID, npar, nmom;
	for (auto& elem : UQjson["randomVariables"])
	{
		get_distnames.push_back(elem["distribution"]);		

		GetdistID(get_distnames[nrv], get_opts[nrv], distID, optsID, npar, nmom);
		std::vector<double> pars_temp;
		switch (optsID)
		{
		case 1: // PAR
		{
			switch (distID)
			{
			case 1: {} // Binomial
			case 2: {} // geometric and so on..
			case 6: {  // Normal				
				pars_temp.push_back(elem["mean"]);
				pars_temp.push_back(elem["stdDev"]);
			}
			// and so on
			}
		}
		case 2: // MOM
			switch (distID)
			{
			case 2: { // geometric 
				pars_temp.push_back(elem["mean"]);
			}
			case 4: { // poisson 
				pars_temp.push_back(elem["mean"]);
			}
			case 8: { // exponential and so on..
				pars_temp.push_back(elem["mean"]);
			}
			case 10: { // exponential and so on..
				pars_temp.push_back(elem["mean"]);
				pars_temp.push_back(elem["mean"]);
				pars_temp.push_back(elem["lower"]);
				pars_temp.push_back(elem["upper"]);
			}
			// and so on..
			default: {  // Normal				
				pars_temp.push_back(elem["mean"]);
				pars_temp.push_back(elem["stdDev"]);
			}
			}
		}
		get_pars.push_back(pars_temp);
		nrv++;
	}
}


void GetdistID(std::string distname, std::string optname, int& distID, int& optID, int& npar, int& nmom)
{
	std::transform(distname.begin(), distname.end(), distname.begin(), ::tolower);
	if (distname.compare("binomial") == 0) {
		distID = 1; npar = 2; nmom = 2;
	}
	else if (distname.compare("geometric") == 0) {
		distID = 2; npar = 1; nmom = 1;
	}
	else if (distname.compare("negativebinomial") == 0) {
		distID = 3; npar = 2; nmom = 2;
	}
	else if (distname.compare("poisson") == 0) {
		distID = 4; npar = 2; nmom = 1;
	}
	else if (distname.compare("uniform") == 0) {
		distID = 5; npar = 2; nmom = 2;
	}
	else if (distname.compare("normal") == 0) {
		distID = 6; npar = 2; nmom = 2;
	}
	else if (distname.compare("lognormal") == 0) {
		distID = 7; npar = 2; nmom = 2;
	}
	else if (distname.compare("exponential") == 0) {
		distID = 8; npar = 1; nmom = 1;
	}
	else if (distname.compare("gamma") == 0) {
		distID = 9; npar = 2; nmom = 2;
	}
	else if (distname.compare("beta") == 0) {
		distID = 10; npar = 4; nmom = 4;
	}
	else if (distname.compare("gumbelMin") == 0) {
		distID = 11; npar = 2; nmom = 2;
	}
	else if (distname.compare("gumbel") == 0) {
		distID = 12; npar = 2; nmom = 2;
	}
	else if (distname.compare("frechet") == 0) {
		distID = 13; npar = 2; nmom = 2;
	}
	else if (distname.compare("weibull") == 0) {
		distID = 14; npar = 2; nmom = 2;
	}
	else if (distname.compare("GEV") == 0) {
		distID = 15; npar = 3; nmom = 3;
	}
	else if (distname.compare("GEVMin") == 0) {
		distID = 16; npar = 3; nmom = 3;
	}
	else if (distname.compare("pareto") == 0) {
		distID = 17; npar = 2; nmom = 2;
	}
	else if (distname.compare("rayleigh") == 0) {
		distID = 18; npar = 1; nmom = 1;
	}
	else if (distname.compare("chisquare") == 0) {
		distID = 19; npar = 1; nmom = 1;
	}
	else
	{
		distID = 0, npar = 0, nmom = 0;
	}

	if (optname.compare("PAR") == 0) {
		optID = 1;
	} 
	else if (optname.compare("MOM") == 0) {
		optID = 2;
	}
	else {
		optID = 0;
	}

}