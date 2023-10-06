#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <functional>
#include <sstream>
#include <vector>
#include "inf_for_calc.h"
using std::map, std::vector, std::string, std::stack, std::stringstream;

class Parser {
public:
    Parser(Calc_Inf& calc_inf_) { operator_priority = calc_inf_.set_op_priority(); };
    vector<string> parse(const string& expression);

private:
    map<char, int> operator_priority;
};
