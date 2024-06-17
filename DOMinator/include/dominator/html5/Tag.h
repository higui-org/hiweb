#ifndef HIWEB_HTML5_TAG_H
#define HIWEB_HTML5_TAG_H

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <optional>

#include "dominator/internal/html5/TagList.h"
#include "dominator/internal/html5/Element.h"

namespace hiweb 
{
#define HIWEB_DEFINE_TAG_FUNCTION(tag) \
    inline hiweb::Tag tag(const std::string& content) { \
        return hiweb::Tag(hiweb::Tag::tag, content); \
    }


class Tag 
{
    using optional = std::optional;
    using string = std::string;

    using Element = internal::tag::HTML5Element;
public:
    Tag(tag::Type type, std::nullopt);

    Tag& operator<<(const Tag& child);

    string getHTML() const;

private:
    std::shared_ptr<Element> element;
};

} // namespace hiweb

#endif // HIWEB_HTML5_TAG_H