#pragma once
#include "xml_file.h"
#include "iterator.h"

class XML_Resource {
private:
    XML_Resource() = default;
    XML_File file;
    bool erase_recurs(std::vector<std::unique_ptr<Node>>& nodes, Iterator pos);
public:
    Iterator begin() const {
        return Iterator(file.get_root().get());
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    Iterator find(const std::string& tag, const std::string& content = "") const;

    bool erase(Iterator pos);

    Iterator add(Iterator pos, const std::string& tag, const std::string& content) const;

    static XML_Resource create() {
        return XML_Resource();
    }

    void load(const std::string& filePath) {
        file.load(filePath);
    }

    void print() const {
        file.print();
    }

    void save(const std::string& filePath) const {
        file.save(filePath);
    }
    
};

