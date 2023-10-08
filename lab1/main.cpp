#include <iostream>
#include "calculator.h"


int main() 
{
    system("chcp 1251");
    Calc_Inf calc_inf;
    Calculator calculator(calc_inf);
    std::string expression;
    setlocale(LC_ALL, "ru");
    std::cout << "Введите выражение: ";
    std::getline(std::cin, expression);

    double result = calculator.calculate(expression);

    std::cout << "Результат вычислений: " << result << std::endl;

    return 0;
}
