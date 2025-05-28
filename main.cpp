#include <iostream>
#include "test_unit9.hpp"
#include <fstream>
#include <utility>

int main()
{
	if (LoadSplineDLL() < 0) {
		std::cout << "Load spline error" << std::endl;
		return 0;
	}

	std::ifstream in;
	in.open("../../../resourse/gam1.dat");
	if (!in.is_open()) {
		std::cerr << "Не удалось открыть файл!" << std::endl;
		return 1;
	}

	std::vector<double> v = read_vector(in, 8);
	in.close();
	in.open("../../../resourse/gam1.dat");
	std::vector<double> theta_p = read_vector(in, 7);
	in.close();
	in.open("../../../resourse/gam1.dat");
	std::vector<double> x = read_vector(in, 9);
	in.close();
	in.open("../../../resourse/gam1.dat");
	std::vector<double> y = read_vector(in, 10);
	in.close();

	vec s(x.size(), 0.0);
	vec v_s(x.size(), 0.0);
	vec theta_p_s(x.size(), 0.0);
	double sa = 0.992308;
	double b = 0.987986;
	try {
		auto cxcy = compute_cxcy(b, v, theta_p, theta_p_s, x, y, s, v_s);
		std::cout << cxcy.first << " " << cxcy.second << std::endl;
		vec delta1 = compute_delta(s, v_s, sa);
		draw_graph(delta1, theta_p_s, x, y);
	}
	catch (std::exception& e) { std::cout << e.what() << std::endl; }
	std::cout << "Hello World!" << std::endl;
	
	FreeSplineDLL();

}