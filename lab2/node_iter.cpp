#include "node_iter.h"

std::string Node::make_str(const int depth) const {
    const std::string indentation = std::string(depth * 2, ' ');
    std::string res = "";

    res += indentation + "<" + tag + ">" + content;
    if (!nodes.empty()) {
        res += "\n";
    }

    for (const auto& node : nodes) {
        res += node->make_str(depth + 1);
    }

    if (!nodes.empty()) {
        res += indentation;
    }

    res += "</" + tag + ">" + "\n";

    return res;
}

void Node::process(const std::function<void(const Node&)>& callback) const {
    callback(*this);
    for (const auto& node : nodes) {
        node->process(callback);
    }
}

bool Node::erase(Iterator pos) {
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if (it->get() == &(*pos)) {
            nodes.erase(it);
            return true;
        }

        if (erase_recurs((*it)->nodes, pos)) {
            return true;
        }
    }
    return false;
}

bool Node::erase_recurs(std::vector<std::unique_ptr<Node>>& nodes, Iterator pos) {
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if (it->get() == &(*pos)) {
            nodes.erase(it);
            return true;
        }

        if (erase_recurs((*it)->nodes, pos)) {
            return true;
        }
    }
    return false;
}

Iterator& Iterator::operator++() {
    if (current == nullptr) {
        if (!stack.empty()) {
            current = stack.back();
            stack.pop_back();
            ++(*this);
        }
    }
    else {
        if (!current->get_nodes().empty()) {
            for (int i = static_cast<int>(current->get_nodes().size()) - 1; i >= 0; --i) {
                stack.push_back(current->get_nodes()[i].get());
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