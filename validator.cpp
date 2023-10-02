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
    bool is_fract = false;

    for (char c : expression) {
        if (is_fract) {
            if (is_fract && (!isdigit(c) && last_c == '.'))
                throw User_Exept("Незавершенное дробное число ");
            if (!isdigit(c) && last_c == '\0' && c != '.') {
                is_fract = false;
            }
            else if (c == '.')
            {
                throw User_Exept("Некорректная запись числа ");
            }
        }
        if (isdigit(c)) {
            last_c = '\0';
        }
        else if (c == '.')
        {
            if (!is_fract && c == '.' && last_c == '\0')
            {
                last_c = '.';
                is_fract = true;
            }
            else
                throw User_Exept("Некорректная запись числа ");
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
            if (last_c == c && c != '-') {
                throw User_Exept("Недопустимое выражение: " + string(1, c) + c);
            }
            else if ((last_c == '(' || last_c != '\0') && c != '-' && last_c != ')') {
                throw User_Exept("Недопустимое выражение: " + string(1, last_c) + c);
            }
            is_fract = false;
            last_c = c;
            
        }
        else {
            throw User_Exept("Недопустимый символ: " + string(1, c));
        }
    }

    if (!brackets.empty())
        throw User_Exept("Несбалансированные скобки");

    if (last_c != '\0' && last_c != ')')
        throw User_Exept("Недостаточно данных");

    if (is_fract && last_c != '\0')
        throw User_Exept("Незавершенное дробное число");
    
}