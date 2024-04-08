#include "hiweb/web.h"

#include <string>

using namespace hi;

int main(int argc, char* argv[]) 
{
    std::unordered_map<std::string, std::string> attr;
    attr["href"] = "https://google.com";
    attr["attribute"] = "some value";

    web::Tag tag("div", "hello world", "identifier", { "class1", "class2" }, attr);

    printf("%s\n", tag.innerMarkup().c_str());


    return 0;
}