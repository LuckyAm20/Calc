#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <functional>
#include <sstream>
#include <vector>
#include "inf_for_calc.h"

class Validator 
{
public:
    Validator(Calc_Inf& calc_inf_);
    void validate(const std::string& expression);
private:
    std::map<char, int> operator_priority;
    std::vector<std::string> unary_op;
    std::vector<std::string> func;
};