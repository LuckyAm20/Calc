#include "calculator.h"

double Calculator::calculate(const string& expression) {
    vector<string> rpn = parser.parse(expression);
    double result = evaluator.evaluate(rpn);
    return result;
}