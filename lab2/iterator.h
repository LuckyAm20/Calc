#pragma once
#include "node.h"
class Iterator {
private:
    Node* current;
    std::vector<Node*> stack;

public:
    Iterator(Node* node) : current(node) {}
    Iterator() : current(nullptr) {}
    Node& operator*() const {
        if (current != nullptr)
            return *current;
        std::cerr << "Error";
    }

    Iterator& operator++();

    Iterator operator++(int);

    bool operator!=(const Iterator& other) const {
        return current != other.current;
    }

    bool operator==(const Iterator& other) const {
        return current == other.current;
    }
};