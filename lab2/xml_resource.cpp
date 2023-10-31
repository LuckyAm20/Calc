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