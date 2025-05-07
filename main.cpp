#include <iostream>
#include <fstream>
#include "src\\unit_4.hpp"
#include <sstream>
#include <vector>
#include <filesystem>
#include <stdexcept>
#include <unistd.h>

int main()
{
    std::ifstream file("resourse\\s.dat");
    if (!file.is_open())
    {
        throw std::invalid_argument("Неправильный путь");
    }
    std::vector<double> data_fi_s;
    std::vector<double> data_s;
    std::vector<double> data_vs;
    std::string line;
    int len;
    file >> len;
    std::getline(file, line);
    std::getline(file, line);
    data_fi_s.resize(len + 1);
    data_s.resize(len + 1);

    for (int i = 0; i < len + 1; i++)
    {
        std::getline(file, line); // Читаем файл построчно
        std::vector<double> row;
        std::istringstream iss(line);
        double value;

        while (iss >> value)
        { // Читаем значения из строки
            row.push_back(value);
        }

        data_s[i] = row[0]; // Добавляем строку в вектор
        data_fi_s[i] = row[2];
    }
    file.close(); // Закрываем файл
    calculate_s(data_s, data_fi_s);
}