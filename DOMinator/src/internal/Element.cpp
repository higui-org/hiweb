#include "dominator/internal/html5/Element.h"

namespace hiweb::internal::tag
{

HTML5Element::HTML5Element(
    TagType type, 
    optional<string> custom_name = std::nullopt)
    :   type_(type), 
        custom_name_(custom_name), 
        parent_(nullptr)
{

}

void HTML5Element::AddChild(std::shared_ptr<HTML5Element> child) 
{
    children_.push_back(child);
    child->setParent(this);
}

string HTML5Element::getHTML() const 
{
    if (custom_name_.has_value()) {
        return getCustomHTML();
    }
    string name = hiweb::tag::tag_list.at(type_);
    string html = "<" + name + ">";
    for (const auto& child : children_) {
        html += child->getHTML();
    }
    html += "</" + name + ">";
    return html;
}
std::string HTML5Element::getCustomHTML() const 
{
    std::string html = "<" + custom_name_.value() + ">";
    for (const auto& child : children_) {
        html += child->getHTML();
    }
    html += "</" + custom_name_.value() + ">";
    return html;
}
void HTML5Element::setParent(HTML5Element* parent) 
{
    this->parent_ = parent;
}
HTML5Element* HTML5Element::getParent() const 
{
    return parent_;
}

} // namespace hiweb::internal::tag