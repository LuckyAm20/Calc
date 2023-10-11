#include <cmath>
#include <string>
#include <functional>


enum class Type {
    op,
    func
};


class Operation {
public:
    virtual std::string name() = 0;
    virtual int priority() = 0;
    virtual double function(double a, double b) = 0;
    virtual double function(double a) = 0;
    virtual std::function<double(double)> get_pointer_un() = 0;
    virtual std::function<double(double, double)> get_pointer_bin() = 0;
    virtual Type type() = 0;
};


class MathOperator : public Operation {
public:
    std::string name() override { return "^"; }
    int priority() override { return 3; }
    double function(double a, double b) override { return pow(a, b); }
    double function(double a) override { return 0; }
    std::function<double(double, double)> get_pointer_bin() override { return [this](double a, double b) { return function(a, b); }; }
    std::function<double(double)> get_pointer_un() override { return [this](double a) { return function(a); }; }
    Type type() override { return Type::op; }
};

extern "C" {
    __declspec(dllexport) Operation* create_op() {
        return new MathOperator();
    }
}