#include "inf_for_calc.h"

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
    operators['/'] = [](double a, double b) { if (b == 0) { throw std::exception("Деление на ноль!"); } return a / b; };
    unary_op['u'] = [](double a) { return -a; };
    setlocale(LC_ALL, "ru");
    try
    {
        load_lib(); 
    }
    catch (const std::exception& e)
    {
        
        std::cerr << "Ошибка: " << e.what() << std::endl;
        exit(1);
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
        throw std::exception("Не найдено dll для подгрузки");

    const wchar_t* file_name;
    HINSTANCE load;

    for (const auto& name : files)
    {
        file_name = name.c_str();
        load = LoadLibraryW(file_name);

        if (load)
        {
            std::function<std::string()> type = (std::string(*)())GetProcAddress(load, "name_type");

            if (type() == "op")
            {
                char* name_op = (char*)GetProcAddress(load, "name");
                int* priority = (int*)GetProcAddress(load, "op_priority");
                priority_op[*name_op] = *priority;
                std::function<double(double, double)> func = (double (*) (double, double))GetProcAddress(load, "function");
                operators[*name_op] = func;
            }
            else if (type() == "func")
            {
                std::function<std::string()> name_func = (std::string(*)())GetProcAddress(load, "name");
                functions_name.push_back(name_func());
                std::function<double(double)> func = (double (*) (double))GetProcAddress(load, "function");
                functions[name_func()] = func;
            }
        }
        else
            throw std::exception("Проблема с открытием dll");
    }
}