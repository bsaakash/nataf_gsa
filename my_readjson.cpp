
#include "lib_json\json.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using json = nlohmann::json;


void Getpnames(std::string distname, std::string optname, std::vector<std::string>& par_char);

void readjson(int &nmc, int& nrv, int &rseed, std::string& UQ_method, std::vector<std::string>& get_distnames, std::vector<std::vector<double>>& get_pars,
					std::vector<std::string>& get_opts, std::vector<double>& get_corr)
{
	// === IMPORTANT* need to additionally import correlation matrix & "input option" to GUI
	get_corr = { 1.0, 0.2, 0.2, 1.0 }; // {{row1}, {row2},...}
	get_opts = { "MOM","MOM" }; // either "MOM" or "PAR" (later, extend to "DATA")
	//get_corr = { 1.0, 0.2, 0.0, 0.2, 1.0, 0.2, 0.0, 0.2, 1.0}; 
	//get_opts = { "MOM","MOM","MOM" }; 

	// === read json
	std::ifstream myfile("dakota.json");
	json UQjson = json::parse(myfile);

	// === get variables
	nmc = UQjson["UQ_Method"]["samplingMethodData"]["samples"];
	rseed = UQjson["UQ_Method"]["samplingMethodData"]["seed"];
	UQ_method  = UQjson["UQ_Method"]["samplingMethodData"]["method"];

	// === Manually specify parameters in each distributions.
	nrv = 0;
	for (auto& elem : UQjson["randomVariables"])
	{
		get_distnames.push_back(elem["distribution"]);		

		std::vector<std::string> pnames;
		Getpnames(get_distnames[nrv], get_opts[nrv], pnames); // get parameter names from dist name

		std::vector<double> pars_temp;
		for (auto& pn : pnames)
		{
			pars_temp.push_back(elem[pn]); // get parameter value from dist & parameter name
		}
		get_pars.push_back(pars_temp);
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
			par_char.push_back("std");
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
		else
		{
			// disabled
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
	else
	{
	// disabled
	}

}