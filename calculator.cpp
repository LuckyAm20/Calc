#include "calculator.h"

double Calculator::calculate(const string& expression) {
    try {
        validator.validate(del_spaces(expression));
    }
    catch (const User_Exept& e) {
        cerr << "Îøèáêà: " << e.what() << endl;
        exit(1);
    }
    vector<string> rpn = parser.parse(del_spaces(expression));
    double result = evaluator.evaluate(rpn);
    return result;
}

string Calculator::del_spaces(const string& expression)
{
    string s = "";
    for (int i = 0; i < expression.length(); i++)
    {
        if (expression[i] != ' ')
            s += expression[i];
    }
    return s;
}