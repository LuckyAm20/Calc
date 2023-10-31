#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <functional>
#include <iostream>

class Node {
public:
    Node(const std::string& tag, const std::string& content) : tag(tag), content(content) {}

    void push(std::unique_ptr<Node> node) {
        nodes.push_back(std::move(node));
    }

    std::string make_str(const int depth = 0) const;
    void process(const std::function<void(const Node&)>& callback) const;
    std::string get_content() const { return content; }
    std::string get_tag() const { return tag; }
    std::vector<std::unique_ptr<Node>>& get_nodes() { return  nodes; }
private:
    std::string tag;
    std::string content;
    std::vector<std::unique_ptr<Node>> nodes;
};