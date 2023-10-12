#include "inf_for_calc.h"
#include "operator.h"

Calc_Inf::Calc_Inf() 
{

    priority_op['+'] = 1;
    priority_op['-'] = 1;
    priority_op['*'] = 2;
    priority_op['/'] = 2;
    priority_op['u'] = 3; 
    operators['+'] = [](double a, double b) { return a + b; };
    operators['-'] = [](double a, double b) { return a - b; };
    operators['*'] = [](double a, double b) { return a * b; };
    operators['/'] = [](double a, double b) { if (b == 0) { throw std::exception("Division by zero!"); } return a / b; };
    unary_op['u'] = [](double a) { return -a; };
    try
    {
        load_lib(); 
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}

void Calc_Inf::load_lib()
{
    std::vector<std::filesystem::path> files;

    for (const auto& name : std::filesystem::directory_iterator("plugins"))
    {
        if (name.path().extension() == ".dll")
            files.push_back(name.path().c_str());
    }

    if (files.empty())
        throw std::exception("No dll found for uploading");

    const wchar_t* file_name;
    HINSTANCE load;

    for (const auto& name : files)
    {
        file_name = name.c_str();
        load = LoadLibraryW(file_name);

        if (load)
        {
            Operation* (*create)() = (Operation * (*)())GetProcAddress(load, "create_op");
            Operation* operation = create();
            
            if (operation->type() == Type::op)
            {
                char name = operation->name()[0];
                priority_op[name] = operation->priority();
                std::function<double(double, double)> func = operation->get_pointer_bin();
                operators[name] = func;
            }
            else if (operation->type() == Type::func)
            {
                std::string name_func = operation->name();
                functions_name.push_back(name_func);
                std::function<double(double)> func = operation->get_pointer_un();
                functions[name_func] = func;
            }
            ptrs.push_back(operation);
        }
        else
            std::cerr << "Problem with opening dll";
    }
}