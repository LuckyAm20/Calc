#include "calculator.h"

double Calculator::calculate(const string& expression) 
{
    try 
    {
        validator.validate(del_spaces(expression));
    }
    catch (const runtime_error& e)
    {
        cerr << "Îøèáêà: " << e.what() << endl;
        exit(1);
    }

    vector<string> rpn = parser.parse(del_spaces(expression));

    try
    {
        double result = evaluator.evaluate(rpn);
        return result;
    }
    catch (const std::exception& e)
    {
        cerr << "Îøèáêà: " << e.what() << endl;
        exit(1);
    }
    
}

string Calculator::del_spaces(const string& expression)
{
    string s = "";
    for (int i = 0; i < expression.length(); i++)
        if (expression[i] != ' ')
            s += expression[i];

    return s;
}