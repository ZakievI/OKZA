#ifndef TEST_UNIT9_HPP
#define TEST_UNIT9_HPP

#include "fcalc.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <complex>
#include <algorithm>

const double M_PI = 3.14159265358979323846;
using vec = std::vector<double>;

vec read_vector(std::ifstream& in, int col);

std::pair<double, double> compute_cxcy(double b, vec v, vec theta_p, vec& theta_p_s, vec x, vec y, vec& s, vec& vs);

vec compute_delta(vec& s, vec& v_s, double sa = 0.992308);

void draw_graph(vec delta1, vec& teta_p, vec x, vec y);

#endif