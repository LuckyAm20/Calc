#pragma once
#include <string>
#include <map>
#include <functional>
#include <vector>
using std::map, std::string, std::vector, std::function;
class Calc_Inf {
public:
    Calc_Inf() {
        
        priority_op['+'] = 1;
        priority_op['-'] = 1;
        priority_op['*'] = 2;
        priority_op['/'] = 2;
        priority_op['u'] = 3;
        functions_name.push_back("sin");
        functions_name.push_back("sqrt");
        functions["sin"] = [](double a) { return sin(a); };
        operators['+'] = [](double a, double b) { return a + b; };
        operators['-'] = [](double a, double b) { return a - b; };
        operators['*'] = [](double a, double b) { return a * b; };
        operators['/'] = [](double a, double b) { return a / b; };
        unary_op['u'] = [](double a) { return -a; };
        functions["sqrt"] = [](double a) { return sqrt(a); };
      
    }

   
    map<char, int> set_op_priority() {
        return priority_op;
    }
    vector<string> set_func_names() {
        return functions_name;
    }
    map<char, function<double(double, double)>> set_operators() {
        return operators;
    }
    map<string, function<double(double)>> set_functions() {
        return functions;
    }
    map<char, function<double(double)>> set_un_op() {
        return unary_op;
    }
    
    

private:
    map<char, int> priority_op;
    map<char, function<double(double, double)>> operators;
    map<string, function<double(double)>> functions;
    map<char, function<double(double)>> unary_op;
    vector<string> functions_name;
};