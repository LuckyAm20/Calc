#include <iostream>
#include "calculator.h"

using namespace std;

int main() {
    Calculator calculator;
    string expression;
    setlocale(LC_ALL, "ru");
    cout << "Введите выражение: ";
    getline(cin, expression);

    double result = calculator.calculate(expression);

    cout << "Результат вычислений: " << result << endl;

    return 0;
}
