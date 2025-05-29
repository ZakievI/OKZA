#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <complex>

#include "../../../resourse/fcalc.h"

using namespace std;

pair<vector<double>, vector<double>> splineAkim(int n, vector<double> x, vector<double>y);

complex<double> f1g(double gamma_arg, double u0, double beta, vector<double>svv1_bb, vector<double>svv1_cc, vector<double>tetav_bb, vector<double>tetav_cc);

complex<double> h1v(complex<double> dzeta_arg, vector<double>svv1_bb, vector<double>svv1_cc, vector<double>tetav_bb, vector<double>tetav_cc);

double specialInt(int n, double a, double b, pair<vector<double>, vector<double>> data);

pair<vector<double>, vector<double>> splineAkimSpecific(int n, int start, vector<double> x, vector<double> y);

void unit_7_8(double &u0_in, double &beta_in, double &db, vector<double>& gamma_in, vector<double>& sg_in, vector<double>& tetav_in, vector<double>&x_out, vector<double>&y_out, vector<double> &s_out, double &b, double &alpha, double &relative_thickness);