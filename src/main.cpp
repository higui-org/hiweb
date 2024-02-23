#include "hiweb/web.h"

#include <string>

using namespace hi;
using namespace hi::parser::markup;

int main(int argc, char* argv[]) 
{
    parser::Parser::Pointer xml = parser::Create(DocumentType::XML);
    xml->read("text.xml");
    xml->getDOM().getRoot()->ge

    return 0;
}