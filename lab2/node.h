#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <functional>

class Node {
public:
    Node(const std::string& tag, const std::string& content) : tag(tag), content(content) {}

    void push(std::unique_ptr<Node> node) {
        nodes.push_back(std::move(node));
    }

    std::string make_str(const int depth = 0) const;
    void process(const std::function<void(const Node&)>& callback) const;
    std::string get_content() const { return content; }

private:
    std::string tag;
    std::string content;
    std::vector<std::unique_ptr<Node>> nodes;
};