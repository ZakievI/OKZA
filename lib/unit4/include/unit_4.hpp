#ifndef _UNIT4_HPP
#define UNIT4_HPP
#include <vector>
#include <cmath>
#include <functional>
#include <iostream>
#include "../../../resourse/fcalc.h"


/**
 *  @brief 
 *  Нахождени функции s(gamma)
 *
 *
 *  @tparam s  Вектор размера N, содержащий значения s_i.
 *  @tparam fi_s  Вектор размера N, содержащий значения fi(s_i) .
 *  @tparam g Вектор размера M, в значениях которго необходимо найти s
 *  @tparam ... константы
 *  @return Вектор размера M
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

#endif