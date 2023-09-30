#include "evaluator.h"


Evaluator::Evaluator() 
{
    operators['+'] = [](double a, double b) { return a + b; };
    operators['-'] = [](double a, double b) { return a - b; };
    operators['*'] = [](double a, double b) { return a * b; };
    operators['/'] = [](double a, double b) { return a / b; };
    operator_priority['+'] = 1;
    operator_priority['-'] = 1;
    operator_priority['*'] = 2;
    operator_priority['/'] = 2;
}

double Evaluator::apply_op(char op, double operand1, double operand2) {
    if (operators.find(op) != operators.end()) {
        return operators[op](operand1, operand2);
    }
    cerr << "Ошибка: неизвестный оператор " << op << endl;
    exit(1);
}

double Evaluator::evaluate(const vector<string>& rpn) {
    stack<double> operands;

    for (string token : rpn) {
        if (isdigit(token[0])) {
            operands.push(stod(token));
        }
        else if (operator_priority.find(token[0]) != operator_priority.end()) {
            double operand2 = operands.top();
            operands.pop();
            double operand1 = operands.top();
            operands.pop();
            double result = apply_op(token[0], operand1, operand2);
            operands.push(result);
        }
    }

    return operands.top();
}