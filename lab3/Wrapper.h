#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <functional>
template <typename T, typename... Args>
class Wrapper {
public:
    Wrapper(T* obj, int (T::* func)(Args...), const std::unordered_map<std::string, int>& args)
        : obj(obj), func(func), initializationArgs(args) {}

    int invoke(const std::unordered_map<std::string, int>& parameters) const {
        if (!validateArguments(parameters)) {
            throw std::invalid_argument("Invalid arguments.");
        }

        auto argumentsTuple = getArgumentsTuple(parameters, std::make_index_sequence<sizeof...(Args)>());

        int result = 0;
        std::apply([&result, this](auto&&... args) {
            result = (obj->*func)(std::forward<decltype(args)>(args)...);
            }, argumentsTuple);

        return result;
    }

private:
    template <std::size_t... Ind>
    auto getArgumentsTuple(const std::unordered_map<std::string, int>& args, std::index_sequence<Ind...>) const {
        std::vector<std::pair<std::string, int>> argValues;
        for (const auto& arg : initializationArgs) {
            auto it = args.find(arg.first);
            if (it != args.end()) {
                argValues.emplace_back(arg.first, it->second);
            }
        }

        return std::make_tuple(argValues[Ind].second...);
    }

    bool validateArguments(const std::unordered_map<std::string, int>& parameters) const {
        if (parameters.size() != initializationArgs.size()) {
            return false;
        }

        for (const auto& arg : initializationArgs) {
            auto range = parameters.equal_range(arg.first);
            if (std::distance(range.first, range.second) == 0) {
                return false;
            }
        }

        return true;
    }

    T* obj;
    int (T::* func)(Args...);
    std::unordered_map<std::string, int> initializationArgs;
};