#include "validator.h"


Validator::Validator(Calc_Inf& calc_inf_) 
{
    operator_priority = calc_inf_.set_op_priority();
    func = calc_inf_.set_func_names();
}

void Validator::check_end_str(const std::stack<unsigned char>& brackets, char last_c)
{
    if (!brackets.empty())
        throw std::runtime_error("Unbalanced brackets");

    if (last_c != '\0' && last_c != ')')
        throw std::runtime_error("Insufficient data");

}

void Validator::process_fract(const std::string& expression, int& i, char last_c)
{

    if (last_c == '\0')
    {
        i++;
        last_c = '.';
        while (isdigit(expression[i]) && i < expression.length())
        {
            last_c = '\0';
            i++;
        }
        if (i != expression.length() && expression[i] == '.' || last_c == '.')
            throw std::runtime_error("Incomplete fractional number ");
        i--;
    }
    else
        throw std::runtime_error("Incorrect number entry ");
}


void Validator::process_func(const std::string& expression, int& i)
{
    std::string func_name = "";
    while (isalpha(expression[i]))
    {
        func_name += expression[i];
        i++;
    }

    if (!isalpha(expression[i]) && std::find(func.begin(), func.end(), func_name) == func.end())
        throw std::runtime_error("Invalid function");
    else if (!isalpha(expression[i]) && std::find(func.begin(), func.end(), func_name) != func.end())
        if (expression[i] != '(')
            throw std::runtime_error("Lack (");
    i--;
}

void Validator::process_brackets(std::stack<unsigned char>& brackets, char last_c, char symbol)
{
    if (symbol == '(')
    {
        if (last_c == '\0' || last_c == ')')
            throw std::runtime_error("Invalid expression: " + std::string(1, last_c) + symbol);
        brackets.push(symbol);
    }
    else
    {
        if (brackets.empty() || brackets.top() != '(')
            throw std::runtime_error("Unbalanced brackets");
        else if (last_c == '(')
            throw std::runtime_error("Insufficient data");

        brackets.pop();
    }
    last_c = symbol;
}


void Validator::validate(const std::string& expression)
{
    std::stack<unsigned char> brackets;
    char last_c = ' ';

    for (int i = 0; i < expression.length(); i++)
    {    
        if (isdigit(expression[i]))
            last_c = '\0';

        else if (isalpha(expression[i]) && (operator_priority.find(last_c) != operator_priority.end() && expression[i] != 'u' || last_c == '(' || last_c == ' '))
            process_func(expression, i);

        else if (expression[i] == '.')
            process_fract(expression, i, last_c);

        else if (expression[i] == '(' || expression[i] == ')')
        {
            process_brackets(brackets, last_c, expression[i]);
        }
        else if (operator_priority.find(expression[i]) != operator_priority.end())
        {
            if (last_c == expression[i] && expression[i] != '-')
                throw std::runtime_error("Invalid expression: " + std::string(1, expression[i]) + expression[i]);
            else if ((last_c == '(' || last_c != '\0') && expression[i] != '-' && last_c != ')')
                throw std::runtime_error("Invalid expression: " + std::string(1, last_c) + expression[i]);

            last_c = expression[i];
        }
        else 
            throw std::runtime_error("Invalid character: " + std::string(1, expression[i]));
    }
    check_end_str(brackets, last_c);
}