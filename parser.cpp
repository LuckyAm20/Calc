#include "parser.h"

Parser::Parser() {
    operator_priority['+'] = 1;
    operator_priority['-'] = 1;
    operator_priority['*'] = 2;
    operator_priority['/'] = 2;
}

vector<string> Parser::parse(const string& expression) {
    vector<string> rpn;
    stack<char> operators;

    for (int i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i])) {
            stringstream ss;
            while (i < expression.length() && isdigit(expression[i])) {
                ss << expression[i];
                i++;
            }
            rpn.push_back(ss.str());
            i--;
        }
        else if (expression[i] == '(') {
            operators.push('(');
        }
        else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                rpn.push_back(string(1, operators.top()));
                operators.pop();
            }
            operators.pop();
        }
        else if (operator_priority.find(expression[i]) != operator_priority.end()) {
            while (!operators.empty() && operator_priority[operators.top()] >= operator_priority[expression[i]]) {
                rpn.push_back(string(1, operators.top()));
                operators.pop();
            }
            operators.push(expression[i]);
        }
    }

    while (!operators.empty()) {
        rpn.push_back(string(1, operators.top()));
        operators.pop();
    }

    return rpn;
}

