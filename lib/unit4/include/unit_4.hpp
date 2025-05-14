#ifndef UNIT4_HPP
#define UNIT4_HPP
#include <vector>
#include <cmath>
#include <functional>
#include <iostream>


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
std::vector<double> calculate_s(std::vector<double> s,
     std::vector<double> fi_s, std::vector<double> g,
    double const betta, double const G, double const C1,
     double U0, double const s_a, double const gamma_a);

struct p;

double func(double gam, struct p params);

double dfunc(double gam, struct p params);

double newton(
    std::function<double(double, struct p)> f,      // Функция f(x, args...)
    std::function<double(double, struct p)> df,     // Производная f'(x, args...)
    double initial_guess,                          // Начальное приближение
    double epsilon,                               // Точность
    size_t max_iterations,                         // Макс. число итераций
    struct p params                                  // Доп. параметры функции
);

#endif UNIT4_HPP