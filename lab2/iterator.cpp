#include "iterator.h"

Iterator& Iterator::operator++() {
    if (current == nullptr) {
        if (!stack.empty()) {
            current = stack.back();
            stack.pop_back();
            ++(*this);
        }
    }
    else {
        if (!current->nodes.empty()) {
            for (int i = static_cast<int>(current->nodes.size()) - 1; i >= 0; --i) {
                stack.push_back(current->nodes[i].get());
            }
        }
        if (!stack.empty()) {
            current = stack.back();
            stack.pop_back();
        }
        else {
            current = nullptr;
        }
    }
    return *this;
}

Iterator Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}