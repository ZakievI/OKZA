#include <iostream>

#include "lib\\unit4\\include\\unit_4.hpp"
#include "lib\\unit1_2\\include\\unit_1_2.hpp"
#include "lib\\unit6\\include\\HilbertIntegral.hpp"
#include "lib\\unit_3_5\\include\\unit_3_5.hpp"
#include "lib\\unit_7_8\\include\\unit_7_8.hpp"
#include <map>
#include <stdexcept>
#define PI 2 * asin(1)

static std::map<std::string, double> constant{
	{"s_a", 0.992308},
	{"bet", 0.15482},
	{"gamma", 0.476448},
	{"gamma_a", 3.451234},
	{"C1", 0.747573},
	{"u0", 0.245876},
	{"ia", 99},
	{"fi0", 0.756995},
	{"fi1", 1.233443},
	{"ja", 197},
	{"mu1", -0.134882},
	{"mu2", 0.126386},
	{"mu3", 0.102002},
	{"b", 0.785091},
	{"alf", 0.163446},
	{"Cx", 0.000000},
	{"Cy", 1.213739},
	{"Cx1", 0.000000},
	{"Cy1", 1.213729},

};
void checking_parameters(double const betta_, double const G_, double const C1_, double const u0_, double const sa_, double const gamma_a_)
{
	double eps = 1e-4;
	if (
		abs(betta_ - constant["bet"]) < eps ||
		abs(G_ - constant["gamma"]) < eps ||
		abs(C1_ - constant["C1"]) < eps ||
		abs(u0_ - constant["u0"]) < eps ||
		abs(sa_ - constant["s_a"]) < eps ||
		abs(gamma_a_ - constant["gamma_a"]) < eps)
		throw std::invalid_argument("Ошибка в параметрах");
}
int main()
{
	LoadSplineDLL();

	///////////////////////unit 1-2///////////////////////
	std::cout << "start unit 1-2" << std::endl;
	std::string FileName = "resourse/s.dat";

	std::vector<double> S;
	std::vector<double> V;
	std::vector<double> Fi;
	std::vector<double> S1;
	std::vector<double> gamma_arr_;
	std::vector<double> S_gamma_arr;

	double fi0_ = 0.0;
	double fi1_ = 0.0;
	double sa_ = 0.0;
	double G_ = 0.0;
	double betta_ = 0;
	double C1_ = 0;
	double u0_ = 0;
	double gamma_a_ = 0;

	svWriter(FileName, S, V);

	SaCompute(S, V, sa_);

	FiCompute(sa_, S, V, Fi, fi0_, fi1_);

	GCompute(fi0_, fi1_, G_);

	size_t n = S.size() - 1;

	// std::cout << "s_a = " << sa_ << " " << std::endl;

	// std::cout << "G = " << G_ << " " << "fi0 = " << fi0_ << " " << "fi1 = " << fi1_ << std::endl;

	std::cout << "finish unit 1-2" << std::endl;
	//////////////////////////////////////////////////////
	////////////////////////unit 3////////////////////////
	std::cout << "start unit 3" << std::endl;
	unit3(G_, fi1_, betta_, C1_, u0_, gamma_a_);
	std::cout << "finish unit 3" << std::endl;
	//////////////////////////////////////////////////////
	////////////////////////unit 4////////////////////////
	// checking_parameters(betta_, G_, C1_, u0_, sa_, gamma_a_);
	std::cout << "start unit 4" << std::endl;
	size_t N = 361;
	gamma_arr_.resize(N);
	for (size_t i = 0; i < N; ++i)
	{
		gamma_arr_[i] = 2 * PI * i / (N - 1);
	}

	S_gamma_arr = calculate_s(S, Fi, gamma_arr_, betta_, G_, C1_, u0_, sa_, gamma_a_);
	std::cout << "finish unit 4" << std::endl;

	//////////////////////////////////////////////////////
	////////////////////////unit 5////////////////////////
	std::cout << "start unit 5" << std::endl;
	unit5(S, V, gamma_a_, gamma_arr_, S_gamma_arr, S1);
	std::cout << "finish unit 5" << std::endl;

	//////////////////////////////////////////////////////
	////////////////////////unit 6////////////////////////
	std::cout << "start unit 6\n";
	std::vector<double> S2;

	hilbert_integral(gamma_arr_, S1, S2);
	std::cout << "end unit 6\n";

	//////////////////////////////////////////////////////
	////////////////////////unit 7-8////////////////////////
	std::cout << "start unit 7\n";
	double db = 0.001;

	std::vector<double> x_out;
	std::vector<double> y_out;
	std::vector<double> s_out;
	double b_out;
	double alpha_out;
	double relative_thickness_out;

	unit_7_8(u0_, betta_, db, gamma_arr_, S_gamma_arr, S2, x_out, y_out, s_out, b_out, alpha_out, relative_thickness_out);
	std::cout << "end unit 7-8\n";

	FreeSplineDLL();
}