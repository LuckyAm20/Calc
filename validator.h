#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <functional>
#include <sstream>
#include <vector>
#include "inf_for_calc.h"
using std::map, std::vector, std::string, std::runtime_error, std::stack;

class Validator 
{
public:
    Validator(Calc_Inf& calc_inf_);
    void validate(const string& expression);
private:
    map<char, int> operator_priority;
    vector<string> unary_op;
    vector<string> func;
};