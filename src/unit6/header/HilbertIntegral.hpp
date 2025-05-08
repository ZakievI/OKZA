#pragma once

#include <vector>
#include <cmath>

void hilbert_integral(const std::vector<double> &gammas, 
                      const std::vector<double> &real_function_values, 
                      std::vector<double> &imaginary_function_values);