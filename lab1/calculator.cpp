#include "calculator.h"

double Calculator::calculate(const std::string& expression)
{
    try 
    {
        validator.validate(del_spaces(expression));
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }

    std::vector<std::string> rpn = parser.parse(del_spaces(expression));

    try
    {
        double result = evaluator.evaluate(rpn);
        return result;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }
}

std::string Calculator::del_spaces(const std::string& expression)
{
    std::string s = "";
    for (int i = 0; i < expression.length(); i++)
        if (expression[i] != ' ')
            s += expression[i];

    return s;
}