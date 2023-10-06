#pragma once
#include "evaluator.h"
#include "parser.h"
#include "validator.h"

using std::vector, std::string, std::cerr, std::endl;
class Calculator 
{
public:
    Calculator(Calc_Inf& calc_inf) : parser(calc_inf), evaluator(calc_inf), validator(calc_inf) {}
    double calculate(const string& expression);
    string del_spaces(const string& expression);
private:
    Parser parser;
    Evaluator evaluator;
    Validator validator;
};