#include "../include/unit_4.hpp"
// #include "../../../resourse/fcalc.h"

#include <iostream>
#include <cmath>
#include <stdexcept>
#define PI 2 * asin(1)

struct p{
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
        { // Защита от деления на 0
            std::cerr << "Derivative is too small, Newton's method fails.\n";
            break;
        }
        x -= f(x, params) / derivative;
        error = f(x, params);
        if (std::abs(error) > pow(10, 7))
        {
            std::cerr << "Error is too big.\n";
            break;
        }
        iter++;
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
 *  @tparam fi_s  Вектор, размера (N) {N - число разбиений s}, содержащий значения fi(s_i) .
 *  @tparam g  Вектор, размера (N) {N - число разбиений gamma}, содержащий значения gamma_i.
 * @tparam s_a  Параметр, считываеться из файла param.dat.
 *  @return ...
 */
void calculate_s(std::vector<double> s,
                 std::vector<double> fi_s, std::vector<double> g,
                 double const betta, double const G, double const C1,
                 double U0, double const s_a, double const gamma_a)
{

    int N_fi_s = fi_s.size();

    bool check_zerro = false;
    // проверка на присутствия 0 в fi (необходимо оптимизировать)
    for (size_t i = 0; i < fi_s.size(); i++)
    {
        if (fi_s[i] == 0.0)
        {
            check_zerro = true;
            break;
        }
    }
    if (check_zerro)
    {
        N_fi_s++;
        fi_s.push_back(0);
        s.push_back(s_a);
    }
    std::vector<double> gamma_(N_fi_s, 1.0);
    std::vector<double> gamma_s_(N_fi_s, 0.0);
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

    /////
    // N = fi_s.size();
    // for (size_t i = 0; i < N; ++i) {
    //     gamma_[i] = 2 * PI * (i)/ (N - 1);
    // }
    /////

    // if (LoadSplineDLL() != 0)
    // {
    //     throw std::invalid_argument("Ошибка загрузки DLL!");
    // }

    // double bb[N_fi_s], cc[N_fi_s];
    // if (fc_spline(&N, s_, fi_s_, bb, cc))
    // {
    //     throw std::invalid_argument("Ошибка построения сплайна!");
    //     FreeSplineDLL();
    // }
    // double a = 2.5;
    // double val = fc_spline_val(&N, &a, bb, cc);

    // return fi_s;
};
