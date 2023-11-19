#include <iostream>
#include <string>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <functional>

class Subject {
public:
    void f3(int arg1, int arg2) {
        std::cout << "f3 called with arg1: " << arg1 << ", arg2: " << arg2 << std::endl;
    }
};

template <typename T, typename... Args>
class Wrapper {
public:
    Wrapper(T* obj, void (T::* func)(Args...), const std::unordered_map<std::string, int>& args)
        : obj(obj), func(func), originalArgs(args) {}

    void invoke(const std::unordered_map<std::string, int>& parameters) const {
        auto updatedArgs = updateArguments(originalArgs, parameters);
        auto argumentsTuple = getArgumentsTuple(updatedArgs, std::make_index_sequence<sizeof...(Args)>());

        std::apply([this](auto&&... args) {
            (obj->*func)(std::forward<decltype(args)>(args)...);
            }, argumentsTuple);
    }

private:
    template <std::size_t... Indices>
    auto getArgumentsTuple(const std::unordered_map<std::string, int>& args, std::index_sequence<Indices...>) const {
        std::vector<int> argValues;
        for (const auto& arg : args) {
            argValues.push_back(arg.second);
        }

        return std::make_tuple(argValues[Indices]...);
    }

    std::unordered_map<std::string, int> updateArguments(const std::unordered_map<std::string, int>& originalArgs,
        const std::unordered_map<std::string, int>& newArgs) const {
        std::unordered_map<std::string, int> updatedArgs = originalArgs;

        for (const auto& newArg : newArgs) {
            auto it = updatedArgs.find(newArg.first);
            if (it != updatedArgs.end()) {
                it->second = newArg.second;
            }
        }

        return updatedArgs;
    }

    T* obj;
    void (T::* func)(Args...);
    std::unordered_map<std::string, int> originalArgs;
};




class Engine {
public:
    template <typename T, typename... Args>
    void register_command(Wrapper<T, Args...>* wrapper, const std::string& command) {
        commands[command] = [wrapper](const std::unordered_map<std::string, int>& parameters) {
            wrapper->invoke(parameters);
            };
    }

    int execute(const std::string& command, const std::unordered_map<std::string, int>& parameters) {
        auto it = commands.find(command);
        if (it != commands.end()) {
            it->second(parameters);
            return 0;
        }
        else {
            std::cerr << "Ошибка: Команда не найдена." << std::endl;
            return -1;
        }
    }

private:
    std::unordered_map<std::string, std::function<void(const std::unordered_map<std::string, int>&)>> commands;
};

int main() {
    Subject subj;
    Wrapper wrapper(&subj, &Subject::f3, { {"arg1", 0}, {"arg2", 0} });

    Engine engine;
    engine.register_command(&wrapper, "command1");

    std::cout << engine.execute("command1", { {"arg2", 4} }) << std::endl;
    std::cout << engine.execute("command1", { {"arg1", 867}, {"arg2", 9} }) << std::endl;

}












