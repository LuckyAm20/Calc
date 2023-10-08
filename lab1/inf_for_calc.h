#pragma once
#include <string>
#include <map>
#include <functional>
#include <filesystem>
#include <Windows.h>
#include <iostream>
#include <vector>


class Calc_Inf 
{
public:
    Calc_Inf(); 
    ~Calc_Inf(){ for (const auto& lib : libs) { FreeLibrary(lib); } }
    std::map<char, int> set_op_priority() { return priority_op; }
    std::vector<std::string> set_func_names() { return functions_name; }
    std::map<char, std::function<double(double, double)>> set_operators() { return operators; }
    std::map<std::string, std::function<double(double)>> set_functions() { return functions; }
    std::map<char, std::function<double(double)>> set_un_op() { return unary_op; }
    void load_lib();
    
private:
    std::map<char, int> priority_op;
    std::map<char, std::function<double(double, double)>> operators;
    std::map<std::string, std::function<double(double)>> functions;
    std::map<char, std::function<double(double)>> unary_op;
    std::vector<std::string> functions_name;
    std::vector<HINSTANCE> libs;
};