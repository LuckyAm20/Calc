#include "node.h"

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