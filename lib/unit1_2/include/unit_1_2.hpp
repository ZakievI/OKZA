#ifndef unit_1_2_H
#define unit_1_2_H

#include<iostream>
#include<vector>
#include<fstream>
#include<string> 
#include<cmath> 
#include<sstream>
#include"../../../resourse/fcalc.h"

void svWriter(std::string Sout, std::vector<double>& S, std::vector<double>& V);

void SaCompute(std::vector<double> S, std::vector<double> V, double& sa);

void FiCompute(double sa, std::vector<double> S, std::vector<double> V, std::vector<double>& Fi, double& fi0, double& fi1);

void GCompute(double fi0, double fi1, double& G);

void svWriterGCRS(std::string Sout, std::vector<double>& S, std::vector<double>& V);

#endif
