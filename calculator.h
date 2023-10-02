#pragma once
#include "evaluator.h"
#include "parser.h"
#include "validator.h"

using std::vector, std::string, std::cerr, std::endl;
class Calculator {
public:
    double calculate(const string& expression);
    string del_spaces(const string& expression);
private:
    Parser parser;
    Evaluator evaluator;
    Validator validator;
};