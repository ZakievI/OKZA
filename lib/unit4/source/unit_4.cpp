#include "../include/unit_4.hpp"
#include "../../../resourse/fcalc.h"

#include <iostream>
#include <cmath>
#include <stdexcept>
#define PI 2 * asin(1)

    /**
     *  @brief 
     *  Нахождени функции s(gamma)
     *
     *
     *  @tparam fi_s  Двумерный вектор, размера (N)*(2) {N - число разбиений s}, содержащий значения s_i и fi(s_i) .
     *  @tparam fi_g  Двумерный вектор, размера (N)*(2) {N - число разбиений gamma}, содержащий значения gamma_i и fi(gamma_i).
     * @tparam s_a  Параметр, считываеться из файла param.dat.
     *  @return ...
     */
std::vector<std::vector<double>> calculate_s(std::vector<std::vector<double>> fi_s, std::vector<std::vector<double>> fi_g, double const s_a){
 
    double* gamma_ = new double[fi_g.size()];
    double* s_ = new double[fi_g.size()];
    double* fi_s_ = new double[fi_g.size()];
    double* fi_g_ = new double[fi_g.size()];
    size_t N;


    bool check_zerro = false;
    // проверка на присутствия 0 в fi (необходимо оптимизировать)
    for (size_t i = 0; i < fi_s.size(); i++) {
        s_[i] = fi_s[i][0];
        fi_s_[i] = fi_s[i][1];
        

        if (fi_s[i][1] == 0.0) {
            check_zerro = true;
        }
    }
    for (size_t i = 0; i < fi_g.size(); i++) {
        gamma_[i] = fi_g[i][0];
        fi_g_[i] = fi_g[i][1];
    }
    if (check_zerro) {
        double* s_new = new double[fi_g.size() + 1];
        double* fi_s_new = new double[fi_g.size() + 1];
        for (size_t i=0; i<fi_s.size() + 1; ++i){
            s_new[i] = s_[i];
            fi_s_new[i] = fi_s_[i];
        }
        s_new[fi_s.size()] = s_a;
        fi_s_new[fi_s.size()] = 0.0;
        delete[] s_;
        delete[] fi_s_;
        s_ = s_new;
        fi_s_ = fi_s_new;
        delete[] s_new;
        delete[] fi_s_new;
    }

    /////
    // N = fi_s.size();
    // for (size_t i = 0; i < N; ++i) {
    //     gamma_[i] = 2 * PI * (i)/ (N - 1);
    // }
    /////
    
    if (LoadSplineDLL() != 0){
        throw std::invalid_argument("Ошибка загрузки DLL!");
    }


    // double bb[5], cc[5];
    // if (fc_spline(&n, s_, fi_s_, bb, cc) {
    //     std::cerr << "Ошибка построения сплайна!" << std::endl;
    //     FreeSplineDLL();
    //     return 1;
    // }

    delete[] s_;
    delete[] fi_s_;
    return fi_s;
};