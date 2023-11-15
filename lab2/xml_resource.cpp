#include "xml_resource.h"

Iterator XML_Resource::find(const std::string& tag, const std::string& content) const {
    for (auto it = begin(); it != end(); ++it) {
        bool tagMatched = tag.empty() || (*it).get_tag() == tag;
        bool contentMatched = content.empty() || (*it).get_content() == content;
        if (tagMatched && contentMatched && !(tag.empty() && content.empty())) {
            return it;
        }
    }
    return end();
}

bool XML_Resource::erase(Iterator pos) {
    if (pos == end()) {
        return false;
    }

    return file.get_root().get()->erase(pos);
}

Iterator XML_Resource::add(Iterator pos, const std::string& tag, const std::string& content) const {
    auto new_node = std::make_unique<Node>(tag, content);
    Node* new_ptr = new_node.get();

    if (pos == end()) {
        file.get_root()->push(std::move(new_node));
    }
    else {
        (*pos).push(std::move(new_node));
    }
    return Iterator(new_ptr);
}