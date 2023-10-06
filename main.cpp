#include <iostream>
#include "calculator.h"

using std::cout, std::getline, std::cin, std::endl;

int main() 
{
    Calc_Inf calc_inf;
    Calculator calculator(calc_inf);
    string expression;
    setlocale(LC_ALL, "ru");
    cout << "Введите выражение: ";
    getline(cin, expression);

    double result = calculator.calculate(expression);

    cout << "Результат вычислений: " << result << endl;

    return 0;
}
