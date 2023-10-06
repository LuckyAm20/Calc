#include "inf_for_calc.h"

Calc_Inf::Calc_Inf() 
{

    priority_op['+'] = 1;
    priority_op['-'] = 1;
    priority_op['*'] = 2;
    priority_op['/'] = 2;
    priority_op['u'] = 3; // ������������� ��� ���������� �������� ������ � evaluate �� ������������ �������� � �� �������� �������� �� ������������ � validate
    operators['+'] = [](double a, double b) { return a + b; };
    operators['-'] = [](double a, double b) { return a - b; };
    operators['*'] = [](double a, double b) { return a * b; };
    operators['/'] = [](double a, double b) { if (b == 0) { throw std::exception("������� �� ����!"); } return a / b; };
    unary_op['u'] = [](double a) { return -a; };
    try
    {
        load_lib(); // �������� ������� �� dll
    }
    catch (const std::exception& e)
    {
        setlocale(LC_ALL, "ru");
        std::cerr << "������: " << e.what() << std::endl;
        exit(1);
    }

}

void Calc_Inf::load_lib()
{
    vector<path> files;

    for (const auto& name : directory_iterator("./plugins"))
    {
        if (name.path().extension() == ".dll")
            files.push_back(name.path().c_str());
    }

    if (files.empty())
        throw std::exception("�� ������� dll ��� ���������");

    const wchar_t* file_name;
    HINSTANCE load;

    for (const auto& name : files)
    {
        file_name = name.c_str();
        load = LoadLibraryW(file_name);

        if (load)
        {
            function<string()> type = (string(*)())GetProcAddress(load, "name_type");

            if (type() == "op")
            {
                char* name_op = (char*)GetProcAddress(load, "name");
                int* priority = (int*)GetProcAddress(load, "op_priority");
                priority_op[*name_op] = *priority;
                function<double(double, double)> func = (double (*) (double, double))GetProcAddress(load, "function");
                operators[*name_op] = func;
            }
            else if (type() == "func")
            {
                function<string()> name_func = (string(*)())GetProcAddress(load, "name");
                functions_name.push_back(name_func());
                function<double(double)> func = (double (*) (double))GetProcAddress(load, "function");
                functions[name_func()] = func;
            }
        }
        else
            throw std::exception("�������� � ��������� dll");
    }
}