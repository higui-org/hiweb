#include "hiweb/web.h"

#include <string>
#include <iostream>

using namespace hi;

int main(int argc, char* argv[])
{
    // Tag
    {
        try
        {
            std::unordered_map<std::string, std::string> attr;
            attr["href"] = "https://google.com";
            attr["attribute"] = "some value";

            std::vector<std::string> classes = { "class1", "class2" };

            web::Tag tag("div", "hello world", "identifier", classes, attr);

            tag.setName("span");
            tag.setId("new_id");

            std::cout << "Tag: passed\n";
		}
        catch (const std::exception& e)
        {
			std::cout << "Tag: failed\n";
            std::cout << e.what() << std::endl;
        }
        
    }

    system("pause");

    return 0;
}