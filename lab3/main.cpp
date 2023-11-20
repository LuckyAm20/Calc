#include "Engine.h"
#include "Subject.h"



int main() {
    Subject subj;
    Wrapper wrapper(&subj, &Subject::f3, { {"arg1", 0}, {"arg2", 0} });
    Wrapper wrapper1(&subj, &Subject::f4, { {"arg1", 0}});
    Wrapper wrapper2(&subj, &Subject::f5, { {"arg1", 0}, {"arg2", 0}, {"arg3", 0} , {"arg4", 0}});
    Wrapper wrapper3(&subj, &Subject::f4, { {"arg1", 0}, {"arg2", 0} });
    Engine engine;
    engine.register_command(&wrapper, "command1");
    engine.register_command(&wrapper1, "command2");
    engine.register_command(&wrapper2, "command3");
    engine.register_command(&wrapper3, "command4");

    std::cout << "Test1" << std::endl;
    std::cout << "Passing arguments in different order" << std::endl;
    std::cout << engine.execute("command1", { {"arg2", 867}, {"arg1", 9} }) << std::endl;
    std::cout << engine.execute("command1", { {"arg1", 9}, {"arg2", 867} }) << std::endl;
    std::cout << "That's right the order is preserved as during initialization" << std::endl << std::endl;


    std::cout << "Test2" << std::endl;
    std::cout << "A call for an unregistered command" << std::endl;
    std::cout << engine.execute("un_command", { {"arg2", 867}, {"arg1", 9} }) << std::endl;
    std::cout << "That's right, it brought out an error" << std::endl << std::endl;


    std::cout << "Test3" << std::endl;
    std::cout << "A call for an incorrect number of argumets" << std::endl;
    std::cout << engine.execute("command1", { {"arg2", 4} }) << std::endl;
    std::cout << engine.execute("command1", { {"arg2", 4}, {"arg3", 867}, {"arg1", 9} }) << std::endl;
    std::cout << "That's right, it brought out an error" << std::endl << std::endl;


    std::cout << "Test4" << std::endl;
    std::cout << "A call for an unknown argument" << std::endl;
    std::cout << engine.execute("command1", { {"arg1", 4}, {"arg3", 867}}) << std::endl;
    std::cout << "That's right, it brought out an error" << std::endl << std::endl;

    std::cout << "Test5" << std::endl;
    std::cout << "A call for functions taking a different number of arguments" << std::endl;
    std::cout << engine.execute("command2", { {"arg1", 4} }) << std::endl;
    std::cout << engine.execute("command3", { {"arg1", 43}, {"arg2", 5}, {"arg3", 1} , {"arg4", 8} }) << std::endl;
    std::cout << "That's right" << std::endl << std::endl;


    std::cout << "Test6" << std::endl;
    std::cout << "A call for a wrapper that is incorrectly initialized\n(the number of arguments passed does not correspond to the number of arguments accepted by the function)" << std::endl;
    std::cout << engine.execute("command4", { {"arg1", 4} }) << std::endl;
    std::cout << engine.execute("command4", { {"arg1", 43}, {"arg2", 5}}) << std::endl;
    std::cout << "That's right. an error is returned for any passed parameters" << std::endl;


}
