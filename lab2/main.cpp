#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include "xml_resource.h"

int main() {
    auto resource = XML_Resource::create();
    resource.load("example.xml");
    resource.print();
    resource.save("test.xml");
    
    auto it =resource.find("childNode2","Content 2");
    ++it;

    std::cout << "Tag: " << (*it).get_tag() << ", Content: " << (*it).get_content() << std::endl;
    auto it1 = resource.add(it, "chdsgdgdsg", "Content 6");
    std::cout << "Tag: " << (*it1).get_tag() << ", Content: " << (*it1).get_content() << std::endl;
    resource.print();
    resource.erase(it1);
    resource.print();
    auto it2 = resource.find("dvsd");
    it2++;
    std::cout << "Tag: " << (*it2).get_tag() << ", Content: " << (*it2).get_content() << std::endl;

};
