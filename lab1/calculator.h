#pragma once
#include "evaluator.h"
#include "parser.h"
#include "validator.h"

class Calculator 
{
public:
    Calculator(Calc_Inf& calc_inf) : parser(calc_inf), evaluator(calc_inf), validator(calc_inf) {}
    double calculate(const std::string& expression);
    std::string del_spaces(const std::string& expression);
private:
    Parser parser;
    Evaluator evaluator;
    Validator validator;
};