#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include <filesystem>
#include "xml_resource.h"

int main() {
    auto resource = XML_Resource::create();
    resource.load("example.xml");
    std::cout << "Load file: " << std::endl;
    resource.print();
    resource.save("test.xml");
    
    auto it =resource.find("child1","Content 1");
    ++it;

    std::cout << "Find node : Tag: " << (*it).get_tag() << ", Content: " << (*it).get_content() << std::endl;
    auto it1 = resource.add(it, "child3", "Content 3");
    std::cout << "Add node: Tag: " << (*it1).get_tag() << ", Content: " << (*it1).get_content() << std::endl<< std::endl;
    std::cout << "After adding" << std::endl;
    resource.print();
    resource.erase(it1);
    std::cout << "After erase adding node" << std::endl;
    resource.print();

    resource.erase(resource.find("child1"));
    std::cout << "After erase find <child1> node" << std::endl;
    resource.print();

    auto it2 = resource.find("dvsd");
    it2++;
    std::cout << "Iterator on null" << std::endl;
    std::cout << "Tag: " << (*it2).get_tag() << ", Content: " << (*it2).get_content() << std::endl;

};
