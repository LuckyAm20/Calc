#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include "node_iter.h"

class XML_File {
public:
    XML_File() : root(nullptr) {}

    void parse(const std::string& data) {
        int pos = 0;
        root = parse_node(data, pos);
    }

    void load(const std::string& file_path) {
        const std::string data = read_file(file_path);
        parse(data);
    }

    void save(const std::string& file_path) const {
        const std::string data = make_str();
        write_file(file_path, data);
    }

    void print() const {
        const std::string data = make_str();
        std::cout << data << std::endl;
    }

    void process(const std::function<void(const Node&)>& callback) const {
        root->process(callback);
    }

    const std::unique_ptr<Node>& get_root() const {
        return root;
    }

private:
    std::unique_ptr<Node> root;

    std::unique_ptr<Node> parse_node(const std::string& data, int& pos) const;
    std::string get_next_tag(const std::string& data, int& pos) const;
    std::string get_next_content(const std::string& data, int& pos) const;
    std::string read_file(const std::string& file_path) const;
    void write_file(const std::string& file_path, const std::string& file_content) const;
    std::string trim(const std::string& str) const;

    std::string make_str() const {
        return root->make_str();
    }
    
};
