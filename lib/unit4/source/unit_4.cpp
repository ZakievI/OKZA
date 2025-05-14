#include "../include/unit_4.hpp"

#include <algorithm>
#include <iostream>
#include <cmath>
#include <stdexcept>
#define PI 2 * asin(1)

struct p
{
    double param;
    double u0;
    double beta;
    double Gamma;
    double c1;
    double fi;
};

double newton(
    std::function<double(double, struct p)> f,  // Функция f(x, args...)
    std::function<double(double, struct p)> df, // Производная f'(x, args...)
    double initial_guess,                       // Начальное приближение
    double epsilon,                             // Точность
    size_t max_iterations,                      // Макс. число итераций
    struct p params                             // Доп. параметры функции
)
{
    double x = initial_guess;
    double error = f(x, params);
    size_t iter = 0;

    while (std::abs(error) > epsilon && iter < max_iterations)
    {
        double derivative = df(x, params);
        if (std::abs(derivative) < 1e-10)
            throw std::invalid_argument("Ошибка newton! Derivative is too small, Newton's method fails"); // Защита от деления на 0
        x -= f(x, params) / derivative;
        error = f(x, params);
        if (std::abs(error) > pow(10, 7))
            throw std::invalid_argument("Ошибка newton! Error is too big");
        iter++;
        if (iter == max_iterations)
            throw std::invalid_argument("Ошибка newton! Error is iter! Дошли до максимальной итерации");
    }
    return x;
}

double func(double gam, struct p params)
{
    return 2.0 * params.u0 * cos(gam - params.beta) - params.Gamma * gam / 2.0 / acos(-1.0) + params.c1 - params.fi;
}

double dfunc(double gam, struct p params)
{
    return -2.0 * params.u0 * sin(gam - params.beta) - params.Gamma / 2.0 / acos(-1.0);
}

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
                                double U0, double const s_a, double const gamma_a)
{
    if (s.size() != fi_s.size())
        throw std::invalid_argument("Ошибка calculate_s! size(s)!=size(fi_s)");
    int N_fi_s = fi_s.size();

    bool check_zerro = false;

    // проверка на присутствия 0 в fi 
    auto it = std::find(fi_s.begin(), fi_s.end(), 0.0);
    if (it != fi_s.end())
    {
        N_fi_s++;
        fi_s.push_back(0);
        s.push_back(s_a);
    }
    
    std::vector<double> gamma_(N_fi_s, 1.0);
    std::vector<double> gamma_s_(N_fi_s, 0.0);
    std::vector<double> s_gamma(g.size(), 0);
    double accurate = 1;
    struct p params;
    params.beta = betta;
    params.Gamma = G;
    params.c1 = C1;
    params.u0 = U0;

    for (size_t i = 0; i < N_fi_s; ++i)
    {
        gamma_[i] = 2 * PI * (i) / (N_fi_s - 1);
    }

    double zero;
    for (size_t i = 1; i < N_fi_s - 1; i++)
    {
        params.fi = fi_s[i];
        if (s[i] < s_a)
            zero = PI + gamma_a / 2.0;
        else
            zero = gamma_a / 2.0;
        gamma_s_[i] = newton(
            std::function<double(double, struct p)>(
                [](double gam, struct p p)
                { return func(gam, p); }),
            std::function<double(double, struct p)>(
                [](double gam, struct p p)
                { return dfunc(gam, p); }),
            zero, 1e-12, 20, params);
    }
    gamma_s_[0] = 2.0 * PI;
    gamma_s_[N_fi_s - 1] = 0.0;

    // if (LoadSplineDLL() != 0)
    // {
    //     throw std::invalid_argument("Ошибка загрузки DLL!");
    // }
    double bb[N_fi_s], cc[4 * N_fi_s];
    if (fc_spline(&N_fi_s, &gamma_s_[0], &s[0], bb, cc))
    {
        throw std::invalid_argument("Ошибка построения сплайна!");
    }
    for (size_t i = 0; i < s_gamma.size(); i++)
    {
        s_gamma[i] = fc_spline_val(&N_fi_s, &g[i], bb, cc);
        std::cout << g[i] << " " << s_gamma[i] << std::endl;
    }
    return s_gamma;
};
