#include <iostream>


#include <fstream>
#include "lib\\unit4\\include\\unit_4.hpp"
#include <sstream>
#include <vector>
#include <stdexcept>
#define s_a 0.992308

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
    std::vector<std::vector<double>> data_s_g;
    std::vector<std::vector<double>> data_s_fi;
    std::string line;
    int len_fi;
    file_s_fi >> len_fi;
    std::getline(file_s_fi, line);
    std::getline(file_s_fi, line);
    data_s_fi.resize(len_fi + 1);

    int len_g;
    file_s_g >> len_g;
    std::getline(file_s_g, line);
    std::getline(file_s_g, line);
    data_s_g.resize(len_g + 1);

    for (int i = 0; i < len_fi + 1; i++)
    {   
        data_s_fi[i].resize(2);
        std::getline(file_s_fi, line); // Читаем файл построчно
        std::vector<double> row;
        std::istringstream iss(line);
        double value;

        while (iss >> value)
        { // Читаем значения из строки
            row.push_back(value);
        }

        data_s_fi[i][0] = row[0]; // Добавляем строку в вектор
        data_s_fi[i][1] = row[2]; // Добавляем строку в вектор
    }
    for (int i = 0; i < len_g + 1; i++)
    {   
        data_s_g[i].resize(2);
        std::getline(file_s_g, line); // Читаем файл построчно
        std::vector<double> row;
        std::istringstream iss(line);
        double value;

        while (iss >> value)
        { // Читаем значения из строки
            row.push_back(value);
        }

        data_s_g[i][0] = row[0]; // Добавляем строку в вектор
        data_s_g[i][1] = row[1];
    }
    file_s_fi.close(); // Закрываем файл
    file_s_g.close(); // Закрываем файл
    calculate_s(data_s_fi, data_s_g, s_a);
}