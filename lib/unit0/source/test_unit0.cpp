#include <iostream>
#include "test_unit0.hpp"
#include "fcalc.h"

void test_unit0(){
    std::cout << "unit0" << std::endl;
}

void test_unit0_1(){
    if (LoadSplineDLL() != 0){
        std::cout << "Ошибка загрузки DLL!" << std::endl;
    }
}