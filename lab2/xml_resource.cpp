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

bool XML_Resource::erase_recurs(std::vector<std::unique_ptr<Node>>& nodes, Iterator pos) {
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if (it->get() == &(*pos)) {
            nodes.erase(it);
            return true;
        }

        if (erase_recurs((*it)->get_nodes(), pos)) {
            return true;
        }
    }
    return false;
}

bool XML_Resource::erase(Iterator pos) {
    if (pos == end()) {
        return false;
    }

    auto& nodes = file.getNodes();
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if (it->get() == &(*pos)) {
            nodes.erase(it);
            return true;
        }

        if (erase_recurs((*it)->get_nodes(), pos)) {
            return true;
        }
    }
    return false;
}

Iterator XML_Resource::add(Iterator pos, const std::string& tag, const std::string& content) const {
    auto new_node = std::make_unique<Node>(tag, content);
    Node* new_ptr = new_node.get();

    if (pos == end()) {
        file.getNodes().push_back(std::move(new_node));
    }
    else {
        (*pos).push(std::move(new_node));
    }
    return Iterator(new_ptr);
}