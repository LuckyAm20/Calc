#include "xml_file.h"

std::unique_ptr<Node> XML_File::parse_node(const std::string& data, int& pos) const {
    std::string tag = get_next_tag(data, pos);
    std::string content = get_next_content(data, pos);
    auto node = std::make_unique<Node>(tag, content);

    std::string next_tag = get_next_tag(data, pos);

    while (next_tag != ("/" + tag) && pos < data.size()) {
        pos -= static_cast<int>(next_tag.size()) + 2;
        node->push(parse_node(data, pos));
        next_tag = get_next_tag(data, pos);
    }
    return node;
}

std::string XML_File::get_next_tag(const std::string& data, int& pos) const {
    pos = static_cast<int>(data.find("<", pos)) + 1;
    int end = static_cast<int>(data.find(">", pos));
    std::string tag = data.substr(pos, end - pos);
    pos = end + 1;
    return tag;
}

std::string XML_File::get_next_content(const std::string& data, int& pos) const {
    int start = pos;
    pos = static_cast<int>(data.find("<", pos));
    return trim(data.substr(start, pos - start));
}

std::string XML_File::read_file(const std::string& file_path) const {
    std::ifstream file(file_path);

    if (!file) {
        throw std::runtime_error("File not found");
    }

    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void XML_File::write_file(const std::string& file_path, const std::string& file_content) const {
    std::ofstream file(file_path);

    if (!file) {
        throw std::runtime_error("File not found");
    }

    file << file_content;
}

std::string XML_File::trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\n");
    if (start == std::string::npos)
        return "";

    size_t end = str.find_last_not_of(" \t\n");
    return str.substr(start, end - start + 1);
}