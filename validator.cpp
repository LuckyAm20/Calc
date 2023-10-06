#include "validator.h"


Validator::Validator(Calc_Inf& calc_inf_) 
{
    operator_priority = calc_inf_.set_op_priority();
    func = calc_inf_.set_func_names();
}
void Validator::validate(const string& expression) 
{
    stack<char> brackets;
    char last_c = ' ';
    bool is_func = false;
    bool is_fract = false;
    string func_name = "";

    for (char c : expression) 
    {
        if (is_fract) 
        {
            if (is_fract && (!isdigit(c) && last_c == '.'))
                throw runtime_error("Незавершенное дробное число ");

            if (!isdigit(c) && last_c == '\0' && c != '.') 
                is_fract = false;
            else if (c == '.')
                throw runtime_error("Некорректная запись числа ");
        }

        if (is_func) 
        {
            if (isalpha(c))
            {
                func_name += c;
                continue;
            }
            
            if (!isalpha(c) && std::find(func.begin(), func.end(), func_name) == func.end())
                throw runtime_error("Некорректная функция");
            else if (!isalpha(c) && std::find(func.begin(), func.end(), func_name) != func.end())
            {
                func_name = "";
                is_func = false;
                if (c != '(')
                    throw runtime_error("Не хватает (");
            }
        }

        if (isdigit(c)) 
            last_c = '\0';
        else if (isalpha(c) && (operator_priority.find(last_c) != operator_priority.end() && c != 'u' || last_c == '(' || last_c == ' '))
        {
            is_func = true;
            func_name += c;
        }
        else if (c == '.')
        {
            if (!is_fract && c == '.' && last_c == '\0')
            {
                last_c = '.';
                is_fract = true;
            }
            else
                throw runtime_error("Некорректная запись числа ");
        }
        else if (c == '(') 
        {
            if (last_c == '\0' || last_c == ')') 
                throw runtime_error("Недопустимое выражение: " + string(1, last_c) + c);
            brackets.push(c);
            last_c = c;
        }
        else if (c == ')') 
        {
            if (brackets.empty() || brackets.top() != '(') 
                throw runtime_error("Несбалансированные скобки");
            else if (last_c == '(')
                throw runtime_error("Недостаточно данных");

            brackets.pop();
            last_c = c;
        }
        else if (operator_priority.find(c) != operator_priority.end()) 
        {
            if (last_c == c && c != '-') 
                throw runtime_error("Недопустимое выражение: " + string(1, c) + c);
            else if ((last_c == '(' || last_c != '\0') && c != '-' && last_c != ')') 
                throw runtime_error("Недопустимое выражение: " + string(1, last_c) + c);

            is_fract = false;
            last_c = c;  
        }
        else 
            throw runtime_error("Недопустимый символ: " + string(1, c));
    }

    if (!brackets.empty())
        throw runtime_error("Несбалансированные скобки");

    if (last_c != '\0' && last_c != ')')
        throw runtime_error("Недостаточно данных");

    if (is_fract && last_c != '\0')
        throw runtime_error("Незавершенное дробное число");  
}