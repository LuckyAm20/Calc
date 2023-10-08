#include <iostream>
#include "calculator.h"


int main() 
{
    Calc_Inf calc_inf;
    Calculator calculator(calc_inf);
    std::string expression;
    std::cout << "Input expression: ";
    std::getline(std::cin, expression);

    double result = calculator.calculate(expression);

    std::cout << "Result: " << result << std::endl;

    return 0;
}
