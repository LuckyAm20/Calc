#pragma once
#include "Wrapper.h"
#include <unordered_set>

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

    int execute(const std::string& command, const std::unordered_multimap<std::string, int>& parameters) {
        if (hasDuplicateKeys(parameters)) {
            std::cerr << "Error: Duplicate keys Code: ";
            return -1;
        }

        std::unordered_map<std::string, int> procParameters(parameters.begin(), parameters.end());
        
        auto it = commands.find(command);
        if (it != commands.end()) {
            return it->second(procParameters);
        }
        else {
            std::cerr << "Error: The command was not found. Code: ";
            return -1;
        }
    }

private:
    bool hasDuplicateKeys(const std::unordered_multimap<std::string, int>& parameters) const {
        std::unordered_set<std::string> uniqueKeys;

        for (const auto& pair : parameters) {

            if (!uniqueKeys.insert(pair.first).second) {
                return true;
            }
        }

        return false;
    }

    std::unordered_map<std::string, std::function<int(const std::unordered_map<std::string, int>&)>> commands;
};