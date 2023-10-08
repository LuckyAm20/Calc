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

private:
    std::map<char, int> operator_priority;
};
