#include <iostream>

#include <fstream>
// #include "resourse\\fcalc.h"
#include "lib\\unit4\\include\\unit_4.hpp"
#include <sstream>
#include <vector>
#include <stdexcept>
#define s_a 0.992308
#define bet 0.15482
#define gam 0.476448
#define C1 0.747573
#define gam_a 3.451234
#define u0 0.245876

int main()
{
    std::ifstream file_s_fi("resourse\\s.dat");
    if (!file_s_fi.is_open())
    {
        throw std::invalid_argument("Неправильный путь");
    }
    std::ifstream file_s_g("resourse\\gam.dat");
    if (!file_s_g.is_open())
    {
        throw std::invalid_argument("Неправильный путь");
    }
    std::vector<double> data_s;
    std::vector<double> data_fi_s;
    std::vector<double> data_g;
    std::vector<double> data_fi_g;
    std::string line;
    int len_fi;
    file_s_fi >> len_fi;
    std::getline(file_s_fi, line);
    std::getline(file_s_fi, line);
    data_fi_s.resize(len_fi + 1);
    data_s.resize(len_fi + 1);

    int len_g;
    file_s_g >> len_g;
    std::getline(file_s_g, line);
    std::getline(file_s_g, line);
    data_g.resize(len_g + 1);
    data_fi_g.resize(len_g + 1);

    for (int i = 0; i < len_fi + 1; i++)
    {   
        std::getline(file_s_fi, line); // Читаем файл построчно
        std::vector<double> row;
        std::istringstream iss(line);
        double value;

        while (iss >> value)
        { // Читаем значения из строки
            row.push_back(value);
        }

        data_s[i] = row[0]; // Добавляем строку в вектор
        data_fi_s[i] = row[2]; // Добавляем строку в вектор
    }
    for (int i = 0; i < len_g + 1; i++)
    {   
        std::getline(file_s_g, line); // Читаем файл построчно
        std::vector<double> row;
        std::istringstream iss(line);
        double value;

        while (iss >> value)
        { // Читаем значения из строки
            row.push_back(value);
        }

        data_g[i] = row[0]; // Добавляем строку в вектор
        data_fi_g[i] = row[1];
    }
    file_s_fi.close(); // Закрываем файл
    file_s_g.close(); // Закрываем файл
    // if (LoadSplineDLL() != 0)
    // {
    //     throw std::invalid_argument("Ошибка загрузки DLL!");
    // }
    calculate_s(data_s, data_fi_s, data_g, bet, gam, C1, u0, s_a, gam_a);
}