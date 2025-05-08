#pragma once

#include <vector>
#ifndef UNIT4_HPP
#define UNIT4_HPP
/**
 *  @brief 
 *  Нахождени функции s(gamma)
 *
 *
 *  @tparam fi_s  Двумерный вектор, размера (N)*(2) {N - число разбиений s}, содержащий значения s_i и fi(s_i) .
 *  @tparam fi_g  Двумерный вектор, размера (N)*(2) {N - число разбиений gamma}, содержащий значения gamma_i и fi(gamma_i).
 *  @tparam s_a  Параметр, считываеться из файла param.dat.
 *  @return ...
 */
std::vector<std::vector<double>> calculate_s(std::vector<std::vector<double>> fi_s, std::vector<std::vector<double>> fi_g, double const s_a);
#endif 