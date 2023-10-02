#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <functional>
#include <sstream>
#include <vector>
using std::map, std::vector, std::string, std::runtime_error, std::stack;

class Validator {
public:
    Validator();
    void validate(const string& expression);
private:
    map<char, int> operator_priority;
    vector<string> unary_op;
};

class User_Exept : public runtime_error {
public:
    User_Exept(const string& message) : runtime_error(message) {}
};