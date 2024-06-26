#include "hi.parser/html5.h"

namespace hiweb
{
  

  namespace detail
  {
    Element::Element(const std::string& custom_name)
    {
      custom_name_ = custom_name;


    }

    void Element::AddChild(std::shared_ptr<Element> child);

    std::string Element::getHTML() const;
    std::string Element::getCustomHTML() const;

    void Element::setParent(Element* parent);
    Element* Element::getParent() const;

  } // namespace detail


  DOM::DOM() 
    : head_(Tag::Type::Head), body_(Tag::Type::Body) 
  {}

  DOM::DOM(const Tag& head, const Tag& body) 
    : head_(head), body_(body)
  {
    ValidateTags();
  }

  DOM::DOM(const Tag& head) 
    : head_(head), body_(Tag::Type::Body)
  {
    ValidateTags();
  }

  void DOM::setHead(const Tag& root) { head_ = root;}
  const Tag& DOM::getHead() const { return head_;}
  void DOM::setBody(const Tag& root) { body_ = root;}
  const Tag& DOM::getBody() const { return body_;}

  std::string DOM::getHTML() const
  {
    std::string html = "<!DOCTYPE html>\n<html>\n";
    html += head_.getHTML();
    html += body_.getHTML();
    html += "</html>";
    return html;
  }

  void DOM::ValidateTags() const
  {
    if (head_.getType() != Tag::Type::Head)
      throw std::invalid_argument("Head tag must be of type Head");

    if (body_.getType() != Tag::Type::Body)
      throw std::invalid_argument("Body tag must be of type Body");

  }



} // namespace hiweb