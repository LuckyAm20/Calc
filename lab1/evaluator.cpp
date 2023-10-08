#include "evaluator.h"


Evaluator::Evaluator(Calc_Inf& calc_inf_)
{
    operators = calc_inf_.set_operators();
    unary_op = calc_inf_.set_un_op();
    operator_priority = calc_inf_.set_op_priority();
    functions = calc_inf_.set_functions();
}

double Evaluator::apply_op(char op, double operand1, double operand2) 
{
    return operators[op](operand1, operand2);
}

double Evaluator::apply_op(char op, double operand1) 
{
    return unary_op[op](operand1);
}

double Evaluator::apply_op(std::string op, double operand1)
{ 
    return functions[op](operand1);  
}

double Evaluator::evaluate(const std::vector<std::string>& rpn)
{
    std::stack<double> operands;

    for (std::string token : rpn)
    {
        if (isdigit(token[0])) 
        {
            setlocale(LC_NUMERIC, "C");
            operands.push(stod(token));
            setlocale(LC_NUMERIC, "");
        }
        else if (operator_priority.find(token[0]) != operator_priority.end()) 
        {
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