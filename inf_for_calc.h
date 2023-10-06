#pragma once
#include <string>
#include <map>
#include <functional>
#include <filesystem>
#include <Windows.h>
#include <iostream>
#include <vector>

using std::map, std::string, std::vector, std::function, std::filesystem::directory_iterator, std::filesystem::path;

class Calc_Inf 
{
public:
    Calc_Inf(); 
    ~Calc_Inf(){ for (const auto& lib : libs) { FreeLibrary(lib); } }
    map<char, int> set_op_priority() { return priority_op; }
    vector<string> set_func_names() { return functions_name; }
    map<char, function<double(double, double)>> set_operators() { return operators; }    
    map<string, function<double(double)>> set_functions() { return functions; }   
    map<char, function<double(double)>> set_un_op() { return unary_op; }
    void load_lib();
    
private:
    map<char, int> priority_op;
    map<char, function<double(double, double)>> operators;
    map<string, function<double(double)>> functions;
    map<char, function<double(double)>> unary_op;
    vector<string> functions_name;
    vector<HINSTANCE> libs;
};