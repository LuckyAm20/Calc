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
        return *current;
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