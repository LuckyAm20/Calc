#include "parser.h"

Parser::Parser() {
    operator_priority["+"] = 1;
    operator_priority["-"] = 1;
    operator_priority["*"] = 2;
    operator_priority["/"] = 2;
    operator_priority["u"] = 3;
}

vector<string> Parser::parse(const string& expression) {
    vector<string> rpn;
    stack<string> operators;

    for (int i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i]) || expression[i] == '.') {
            stringstream ss;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                ss << expression[i];
                i++;
            }
            rpn.push_back(ss.str());
            i--;
        }
        else if (expression[i] == '(') {
            operators.push("(");
        }
        else if (expression[i] == ')') {
            while (operators.top() != "(")
            {
                rpn.push_back(operators.top());
                operators.pop();
            }
            operators.pop();
            if (isalpha(operators.top()[0]))
            {
                rpn.push_back(operators.top());
                operators.pop();
            }
        }
        else if (operator_priority.find(string(1, expression[i])) != operator_priority.end()) {
            if (expression[i] == '-' && (i == 0 || expression[i - 1] == '(' || operator_priority.find(string(1, expression[i-1])) != operator_priority.end())) {
                operators.push("u");
            }
            else {
                while (!operators.empty() && operator_priority[operators.top()] >= operator_priority[string(1, expression[i])]) {
                    rpn.push_back(operators.top());
                    operators.pop();
                }
                operators.push(string(1, expression[i]));
            }
        }
        else if (isalpha(expression[i])) {
            stringstream ss;
            while (i < expression.length() && isalpha(expression[i])) {
                ss << expression[i];
                i++;
            }
            string function_name = ss.str();
            operators.push(function_name);
            i--;
            
        }
    }

    while (!operators.empty()) {
        rpn.push_back(operators.top());
        operators.pop();
    }

    return rpn;
}

