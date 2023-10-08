#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <functional>
#include <sstream>
#include <vector>
#include "inf_for_calc.h"

class Evaluator 
{
public:
    Evaluator(Calc_Inf& calc_inf_);
    double evaluate(const std::vector<std::string>& rpn);

private:
    std::map<char, std::function<double(double, double)>> operators;
    std::map<std::string, std::function<double(double)>> functions;
    std::map<char, std::function<double(double)>> unary_op;
    std::map<char, int> operator_priority;
    double apply_op(char op, double operand1, double operand2);
    double apply_op(char op, double operand1);
    double apply_op(std::string op, double operand1);
};
