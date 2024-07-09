#include "hi.parser/html5.h"
#include <iostream>

using namespace hi;

int main() {
    std::string d = "div";
    Tag div("div");

    
    std::cout << div.toString() << std::endl;

    return 0;
}