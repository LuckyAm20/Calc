#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <functional>
#include <sstream>
#include <vector>
#include "inf_for_calc.h"

class Parser {
public:
    Parser(Calc_Inf& calc_inf_) { operator_priority = calc_inf_.set_op_priority(); };
    std::vector<std::string> parse(const std::string& expression);
    void push_pop(std::vector<std::string>& rpn, std::stack<std::string>& operators);
    void parse_func(const std::string& expression, int& i, std::stack<std::string>& operators);
    void parse_digit(const std::string& expression, int& i, std::vector<std::string>& rpn);

private:
    std::map<char, int> operator_priority;
};
