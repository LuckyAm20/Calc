#pragma once
#include "xml_file.h"


class XML_Resource {
private:
    XML_Resource() = default;
    XML_File file;
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

    void load(const std::string& file_path) {
        try {
            file.load(file_path);
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Runtime error: " << e.what() << std::endl;
        }
        
    }

    void print() const {
        file.print();
    }

    void save(const std::string& file_path) const {
        try {
            file.save(file_path);
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Runtime error: " << e.what() << std::endl;
        }
    }
    
};

