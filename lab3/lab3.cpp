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
        if (!validateArguments(parameters)) {
            throw std::invalid_argument("Invalid arguments.");
        }

        auto argumentsTuple = getArgumentsTuple(parameters, std::make_index_sequence<sizeof...(Args)>());

        std::apply([this](auto&&... args) {
            (obj->*func)(std::forward<decltype(args)>(args)...);
            }, argumentsTuple);
    }

private:
    template <std::size_t... Indices>
    auto getArgumentsTuple(const std::unordered_map<std::string, int>& args, std::index_sequence<Indices...>) const {
        std::vector<std::pair<std::string, int>> argValues;
        for (const auto& arg : originalArgs) {
            auto it = args.find(arg.first);
            if (it != args.end()) {
                argValues.emplace_back(arg.first, it->second);
            }
        }

        return std::make_tuple(argValues[Indices].second...);
    }

    bool validateArguments(const std::unordered_map<std::string, int>& parameters) const {
        if (parameters.size() != originalArgs.size()) {
            return false;
        }

        for (const auto& arg : originalArgs) {
            auto range = parameters.equal_range(arg.first);
            if (std::distance(range.first, range.second) == 0) {
                return false;
            }
        }

        return true;
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
            try {
                wrapper->invoke(parameters);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
            };
    }

    int execute(const std::string& command, const std::unordered_map<std::string, int>& parameters) {
        auto it = commands.find(command);
        if (it != commands.end()) {
            it->second(parameters);
            return 0;
        }
        else {
            std::cerr << "Error: The command was not found." << std::endl;
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
    std::cout << engine.execute("command1", { {"arg2", 867}, {"arg1", 9} }) << std::endl;

}












