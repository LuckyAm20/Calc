#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <functional>
#include <sstream>
#include <vector>
using std::map, std::vector, std::string, std::stack, std::function, std::cerr, std::endl;

class Evaluator {
public:
    Evaluator();
    double evaluate(const vector<string>& rpn);

private:
    map<char, function<double(double, double)>> operators;
    map<char, function<double(double)>> unary_op;
    map<char, int> operator_priority;
    double apply_op(char op, double operand1, double operand2);
    double apply_op(char op, double operand1);
};
