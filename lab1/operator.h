#pragma once
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