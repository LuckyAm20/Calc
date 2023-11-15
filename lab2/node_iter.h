#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <functional>
#include <iostream>
class Node;

class Iterator {
private:
    Node* current;
    std::vector<Node*> stack;

public:
    Iterator(Node* node) : current(node) {}
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

class Node {
private:
    std::string tag;
    std::string content;
    std::vector<std::unique_ptr<Node>> nodes;
    bool erase_recurs(std::vector<std::unique_ptr<Node>>& nodes, Iterator pos);
public:
    Node(const std::string& tag, const std::string& content) : tag(tag), content(content) {}

    void push(std::unique_ptr<Node> node) {
        nodes.push_back(std::move(node));
    }

    std::string make_str(const int depth = 0) const;
    void process(const std::function<void(const Node&)>& callback) const;
    std::string get_content() const { return content; }
    std::string get_tag() const { return tag; }
    const std::vector<std::unique_ptr<Node>>& get_nodes() const { return nodes; }
    bool erase(Iterator pos);
};

