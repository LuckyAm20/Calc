#pragma once
#include "Wrapper.h"

class Engine {
public:
    template <typename T, typename... Args>
    void register_command(Wrapper<T, Args...>* wrapper, const std::string& command) {
        commands[command] = [wrapper](const std::unordered_map<std::string, int>& parameters) {
            try {
                return wrapper->invoke(parameters);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << " Code: ";
                return -1;
            }
            };
    }

    int execute(const std::string& command, const std::unordered_map<std::string, int>& parameters) {
        auto it = commands.find(command);
        if (it != commands.end()) {
            return it->second(parameters);
        }
        else {
            std::cerr << "Error: The command was not found. Code: ";
            return -1;
        }
    }

private:
    std::unordered_map<std::string, std::function<int(const std::unordered_map<std::string, int>&)>> commands;
};