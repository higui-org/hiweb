#ifndef HIWEB_INTERNAL_HTML5_ELEMENT_H
#define HIWEB_INTERNAL_HTML5_ELEMENT_H

#include <memory>
#include <vector>
#include <string>
#include <optional>

#include "dominator/internal/html5/TagList.h"

namespace hiweb::internal::tag
{

class HTML5Element 
{
    using optional = std::optional;
    using string = std::string;
public:
    HTML5Element(
        tag::Type type, 
        optional<string> custom_name = std::nullopt
    );

    void AddChild(std::shared_ptr<HTML5Element> child);

    string getHTML() const;
    string getCustomHTML() const;

    void setParent(HTML5Element* parent);
    HTML5Element* getParent() const;

private:
    tag::Type type_;
    optional<string> custom_name_;
    std::vector<std::shared_ptr<HTML5Element>> children_;
    HTML5Element* parent_;
}; // class Element

} // namespace hiweb::internal::tag

#endif // HIWEB_INTERNAL_HTML5_ELEMENT_H