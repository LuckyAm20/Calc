#pragma once
#include "evaluator.h"
#include "parser.h"
#include "validator.h"

using namespace std;
class Calculator {
public:
    double calculate(const string& expression);
    string del_spaces(const string& expression);
private:
    Parser parser;
    Evaluator evaluator;
    Validator validator;
};