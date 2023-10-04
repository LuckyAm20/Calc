#include "evaluator.h"


Evaluator::Evaluator() 
{
    operators = calc_inf.set_operators();
    unary_op = calc_inf.set_un_op();
    operator_priority = calc_inf.set_op_priority();
    functions = calc_inf.set_functions();
}

double Evaluator::apply_op(char op, double operand1, double operand2) {
    if (operators.find(op) != operators.end()) {
        return operators[op](operand1, operand2);
    }
    cerr << "Ошибка: неизвестный оператор " << op << endl;
    exit(1);
}

double Evaluator::apply_op(char op, double operand1) {
    if (unary_op.find(op) != unary_op.end())
    {
        return unary_op[op](operand1);
    }
    cerr << "Ошибка: неизвестный оператор " << op << endl;
    exit(1);
}
double Evaluator::apply_op(string op, double operand1) {
     
    return functions[op](operand1);
    
}
double Evaluator::evaluate(const vector<string>& rpn) {
    stack<double> operands;

    for (string token : rpn) {
        if (isdigit(token[0])) {
            setlocale(LC_NUMERIC, "C");
            operands.push(stod(token));
            setlocale(LC_NUMERIC, "");
        }
        else if (operator_priority.find(token[0]) != operator_priority.end()) {
            if (unary_op.find(token[0]) != unary_op.end())
            {
                double operand = operands.top();
                operands.pop();
                double result = apply_op(token[0], operand);
                operands.push(result);
            }
            else if (operators.find(token[0]) != operators.end())
            {
                double operand2 = operands.top();
                operands.pop();
                double operand1 = operands.top();
                operands.pop();
                double result = apply_op(token[0], operand1, operand2);
                operands.push(result);
            }
        }
        else if (functions.find(token) != functions.end())
        {
            double operand = operands.top();
            operands.pop();
            double result = apply_op(token, operand);
            operands.push(result);
        }
        
    }

    return operands.top();
}