#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include "xml_file.h"

int main() {
    XML_File file;

    file.load("./example.xml");
    file.print();
    file.save("./test.xml");
};
