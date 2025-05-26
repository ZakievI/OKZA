#include <iostream>

#include "lib\\unit4\\include\\unit_4.hpp"
#include "lib\\unit1_2\\include\\unit_1_2.hpp"
#include "lib\\unit6\\include\\HilbertIntegral.hpp"
#include "lib\\unit_3,5\\include\\unit_3,5.hpp"


int main()
{
	LoadSplineDLL();

	std::string FileName = "resourse/s.dat";

	std::vector<double> S;
	std::vector<double> V;
	std::vector<double> Fi;
	std :: vector<double> S1;

	double fi0 = 0.0;
	double fi1 = 0.0;
	double sa = 0.0;
	double G = 0.0;
	double betta=0;
	double C1 =0;
	double u0 = 0;
	double gammaa = 0;
	


	svWriter(FileName, S, V);

	SaCompute(S, V, sa);

	FiCompute(sa, S, V, Fi, fi0, fi1);

	GCompute(fi0, fi1, G);

	size_t n = S.size() - 1;

	std::cout << "s_a = " << sa << " " << std::endl;

	std::cout << "G = " << G << " " << "fi0 = " << fi0 << " " << "fi1 = " << fi1 << std::endl;
	unit3(G, fi1, betta, C1, u0, gammaa);
	
	//unit5(S, V, gammaa, gamma, sj, S1);


	FreeSplineDLL();
}