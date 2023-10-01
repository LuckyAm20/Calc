#include "validator.h"


Validator::Validator() {
    operator_priority['+'] = 1;
    operator_priority['-'] = 1;
    operator_priority['*'] = 2;
    operator_priority['/'] = 2;

}
void Validator::validate(const string& expression) {
    stack<char> brackets;
    char last_c = ' ';

    for (char c : expression) {
        if (isdigit(c)) {
            last_c = '\0';
        }
        else if (c == '(') {
            if (last_c == '\0' || last_c == ')') {
                throw User_Exept("Недопустимое выражение: " + string(1, last_c) + c);
            }
            brackets.push(c);
            last_c = c;
        }
        else if (c == ')') {
            if (brackets.empty() || brackets.top() != '(') {
                throw User_Exept("Несбалансированные скобки");
            }
            else if (last_c == '(')
            {
                throw User_Exept("Недостаточно данных");
            }
            brackets.pop();
            last_c = c;
        }
        else if (operator_priority.find(c) != operator_priority.end()) {
            if (last_c == c && c != '-' || c == '-' && last_c == 'm') {
                throw User_Exept("Недопустимое выражение: " + string(1, c) + c);
            }
            else if ((last_c == '(' || last_c != '\0') && c != '-') {
                throw User_Exept("Недопустимое выражение: " + string(1, last_c) + c);
            }
            if (c == '-' && (last_c == '(' || operator_priority.find(last_c) != operator_priority.end() || last_c == ' ')) {
                last_c = 'm';
            }
            else {
                last_c = c;
            }
        }
        else {
            throw User_Exept("Недопустимый символ: " + string(1, c));
        }
    }

    if (!brackets.empty())
        throw User_Exept("Несбалансированные скобки");

    if (last_c != '\0' && last_c != ')')
        throw User_Exept("Недостаточно данных");
    
}