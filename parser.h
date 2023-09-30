#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <functional>
#include <sstream>
#include <vector>
using namespace std;

class Parser {
public:
    Parser();
    vector<string> parse(const string& expression);

private:
    map<char, int> operator_priority;
};
