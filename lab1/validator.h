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
    void process_fract(const std::string& expression, int& i, char last_c);
    void check_end_str(const std::stack<unsigned char>& brackets, char last_c);
    void process_func(const std::string& expression, int& i);
    void process_brackets(std::stack<unsigned char>& brackets, char last_c, char symbol);
private:
    std::map<char, int> operator_priority;
    std::vector<std::string> unary_op;
    std::vector<std::string> func;
};