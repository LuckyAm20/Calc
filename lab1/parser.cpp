#include "parser.h"


void Parser::push_pop(std::vector<std::string>& rpn, std::stack<std::string>& operators)
{
    rpn.push_back(operators.top());
    operators.pop();
}

void Parser::parse_func(const std::string& expression, int& i, std::stack<std::string>& operators)
{
    std::stringstream ss;
    while (i < expression.length() && isalpha(expression[i]))
    {
        ss << expression[i];
        i++;
    }
    std::string function_name = ss.str();
    operators.push(function_name);
    i--;
}

void Parser::parse_digit(const std::string& expression, int& i, std::vector<std::string>& rpn)
{
    std::stringstream ss;
    while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.'))
    {
        ss << expression[i];
        i++;
    }
    rpn.push_back(ss.str());
    i--;
}

std::vector<std::string> Parser::parse(const std::string& expression)
{
    std::vector<std::string> rpn;
    std::stack<std::string> operators;

    for (int i = 0; i < expression.length(); i++)
    {
        if (isdigit(expression[i]) || expression[i] == '.')
        {
            parse_digit(expression, i, rpn);
        }
        else if (expression[i] == '(')
            operators.push("(");
        else if (expression[i] == ')')
        {
            while (operators.top() != "(")
                push_pop(rpn, operators);
            operators.pop();
            if (!operators.empty() && isalpha(operators.top()[0]))
                push_pop(rpn, operators);

        }
        else if (operator_priority.find(expression[i]) != operator_priority.end())
        {
            if (expression[i] == '-' && (i == 0 || expression[i - 1] == '(' || operator_priority.find(expression[i - 1]) != operator_priority.end()))
                operators.push("u");
            else
            {
                while (!operators.empty() && operator_priority[operators.top()[0]] >= operator_priority[expression[i]])
                    push_pop(rpn, operators);
                operators.push(std::string(1, expression[i]));
            }
        }
        else if (isalpha(expression[i]))
            parse_func(expression, i, operators);
        
    }

    while (!operators.empty())
        push_pop(rpn, operators);
    
    return rpn;
}

