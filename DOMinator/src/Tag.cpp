#include "dominator/html5/Tag.h"

namespace hiweb
{
    Tag::Tag(
        tag::Type type, 
        std::optional<std::string> custom_name = std::nullopt)
        : element(std::make_shared<internal::tag::HTML5Element>(type, custom_name)) 
    {

    }

    Tag& Tag::operator<<(const Tag& child) 
    {
        element->AddChild(child.element);
        return *this;
    }

    std::string Tag::getHTML() const 
    {
        return element->getHTML();
    }
} // namespace hiweb