#include <iostream>
#include "../include/unit_3,5.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

//#include "C:\Users\Tagir\Desktop\�����\Project1\Project1\fcalc.h"

using namespace std;

double newton_method( double G, double fi1, double initial) {
	double beta = initial;
	int maxit = 500;
	double tolerance = 1e-7;
	double beta_prev;
	int i = 0;
	double Pi = acos(-1);

	double a = Pi / G * fi1 - Pi / 2;
	do {
		beta_prev = beta;
		double fval = 1.0 / tan(beta) - a + beta;
		double dfval = -1.0 / (sin(beta) * sin(beta)) + 1;
		beta = beta - fval / dfval;
		i++;
	} while (abs(beta - beta_prev) > tolerance && i < maxit);

	if (i >= maxit) {
		cout << "did not converge after " << maxit << " iterations " << endl;
	}
	return beta;
}
double unit3(double G, double fi1, double& betta, double& C1, double& u0, double& gammaa) {
	double Pi = acos(-1);
	double initial = 0.001;
	cout << "		unit 3 start " << endl;
	double a = Pi / G * fi1 - Pi / 2;
	if (G > 0) {
		betta = newton_method( G, fi1, initial);
		gammaa = Pi + 2 * betta;
		u0 = G / (4 * Pi * sin(betta));
		C1 = fi1 - (G / (2 * Pi)) * (1 / tan(betta));
	}
	else if (G < 0) {
		cout << "G negative" << endl;
		betta = newton_method( G, fi1, -initial);
		gammaa = Pi + 2 * betta;
		u0 = G / (4 * Pi * sin(betta));
		C1 = fi1 - (G / (2 * Pi)) * (1 / tan(betta));
	}
	else if (G == 0) {
		cout << "G is zero" << endl;
		betta = 0;
		C1 = fi1 / 2;
		u0 = fi1 / 4;
		gammaa = Pi;
	}
	if (!isnan(betta)) {
		cout << "Find betta: " << setprecision(10) << betta << endl;
		cout << "Find C1: " << setprecision(10) << C1 << endl;
		cout << "Find u0: " << setprecision(10) << u0 << endl;
		cout << "Find gammaa: " << setprecision(10) << gammaa << endl;
		if (betta != 0) {
			cout << "residual:  " << 1.0 / tan(betta) - a + betta << endl;
		}
	}
	cout << "		unit 3 end" << endl;
	return  0;
}
vector<double> unit5(vector<double> s, vector<double> V, double gammaa, vector <double>& gamma, vector <double>& sj, vector<double>& S1) {
	cout << "		unit 5 start" << endl;
	double Pi = acos(-1);



	int splinesize = s.size();
	vector<double> bb, cc;
	bb.resize(splinesize);
	cc.resize(4 * splinesize);
	fc_spline(&splinesize, &s[0], &V[0], &bb[0], &cc[0]);

	vector<double> vj;
	int sjsize = sj.size();
	vector<double> Sj;
	vector<double> Stildaj;
	vector<double> gammasovpal;

	for (int j = 0; j < sjsize;j++) {
		vj.push_back(fc_spline_val(&splinesize, &sj[j], &bb[0], &cc[0]));
		Sj.push_back(log(abs(vj[j])));

		if (gammaa != gamma[j]) {
			double S0j = log(abs(2 * sin((gamma[j] - gammaa) / 2)));
			Stildaj.push_back(Sj[j] - S0j);
		}
		else {
			Stildaj.push_back(0);
			gammasovpal.push_back(j);
		}
	}
	for (int j = 0; j < gammasovpal.size();j++) {
		Stildaj[gammasovpal[j]] = (Stildaj[gammasovpal[j] + 1] + Stildaj[gammasovpal[j] - 1]) / 2;
	}
	double Vinf = 0;
	cout << "enter value Vinf = ";
	cin >> Vinf;
	if (Vinf < 0) {
		cout << "Vinf negative" << endl;
		Vinf = abs(Vinf);
	}
	double A1 = 2 * Pi * log(Vinf);
	double A2 = -Pi;
	double A3 = 0;
	double nu1 = 0;
	double nu2 = 0;
	double nu3 = 0;
	double up = 2 * Pi;
	double down = 0;


	vector<double> bbb, ccc;
	bbb.resize(sjsize);
	ccc.resize(4 * sjsize);
	fc_spline(&sjsize, &gamma[0], &Stildaj[0], &bbb[0], &ccc[0]);
	nu1 = fc_spline_int(&sjsize, &down, &up, &bbb[0], &ccc[0]);
	cout << "nu1 = " << (fc_spline_int(&sjsize, &down, &up, &bbb[0], &ccc[0]) - A1) / (2 * Pi) << endl;

	vector<double> nu2S;
	for (int j = 0; j < sjsize;j++) {
		nu2S.push_back(Stildaj[j] * cos(gamma[j]));
	}
	vector<double> bbbb, cccc;
	bbbb.resize(sjsize);
	cccc.resize(4 * sjsize);
	fc_spline(&sjsize, &gamma[0], &nu2S[0], &bbbb[0], &cccc[0]);
	nu2 = fc_spline_int(&sjsize, &down, &up, &bbbb[0], &cccc[0]);
	cout << "nu2 = " << (fc_spline_int(&sjsize, &down, &up, &bbbb[0], &cccc[0]) - A2) / (Pi) << endl;

	vector<double> nu3S;
	for (int j = 0; j < sjsize;j++) {
		nu3S.push_back(Stildaj[j] * sin(gamma[j]));
	}
	vector<double> bbbbb, ccccc;
	bbbbb.resize(sjsize);
	ccccc.resize(4 * sjsize);
	fc_spline(&sjsize, &gamma[0], &nu3S[0], &bbbbb[0], &ccccc[0]);
	nu3 = fc_spline_int(&sjsize, &down, &up, &bbbbb[0], &ccccc[0]);
	cout << "nu3 = " << (nu3 - A3) / Pi << endl;
	for (int j = 0; j < sjsize;j++) {
		S1.push_back(Stildaj[j] - (nu1 + nu2 * cos(gamma[j]) + nu3 * sin(gamma[j])));
	}
	cout << "		unit 5 end " << endl;
	return S1;
}
