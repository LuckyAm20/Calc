#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <functional>
#include <sstream>
#include <vector>
using std::map, std::vector, std::string, std::stack, std::stringstream;

class Parser {
public:
    Parser();
    vector<string> parse(const string& expression);

private:
    map<string, int> operator_priority;
};
