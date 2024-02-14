#include "hiweb/web.h"

#include <string>

int main(int argc, char* argv[]) 
{
    std::string filename = "markup.html";
    
    hi::HTML parser(filename);
      

    return 0;
}