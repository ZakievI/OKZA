
#pragma once
#ifndef _UNIT4_HPP
#define UNIT4_HPP
#include <vector>
#include <cmath>
#include <functional>
#include <iostream>
#include "../../../resourse/fcalc.h"




double newton_method(double Pi, double G, double fi1, double initial); // initial приближение ньютона 
double unit3(double G, double fi1, double& betta, double& C1, double& u0, double& gammaa);
std::vector <double> unit5(std::vector<double> s, std::vector<double> V, double gammaa, std::vector <double>& gamma, std::vector <double>& sj, std::vector<double>& S1);

#endif