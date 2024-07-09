#include "hi.parser/html5.h"

namespace hi
{

std::string DOM::toString() const {
  std::ostringstream html;
  html << "<!DOCTYPE html>\n<html>\n";
  html << head.toString();
  html << body.toString();
  html << "</html>";
  return html.str();
}

namespace detail
{

HTML5Element::HTML5Element(std::variant<HTML5Element::Native, HTML5Element::Custom> type)
{
  std::visit([this](auto&& arg) {
    *this = HTML5Element(std::forward<decltype(arg)>(arg));
  }, type);
}

HTML5Element::HTML5Element(Native type)
  : type_(type), parent_(nullptr)
{}

HTML5Element::HTML5Element(Custom type)
  : type_(type), parent_(nullptr)
{}


void HTML5Element::addChild(std::shared_ptr<HTML5Element> child) {
    children_.push_back(child);
}

std::vector<std::shared_ptr<HTML5Element>> HTML5Element::getChildren() const {
    return children_;
}

void HTML5Element::removeChild(std::shared_ptr<HTML5Element> child) {
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        children_.erase(it);
    }
}

void HTML5Element::clearChildren() {
    children_.clear();
}

void HTML5Element::setType(std::variant<Native, Custom> type) noexcept {
    type_ = type;
}

std::variant<HTML5Element::Native, HTML5Element::Custom> HTML5Element::getType() const noexcept {
    return type_;
}

void HTML5Element::setParent(HTML5Element* parent) {
    parent_ = parent;
}

HTML5Element* HTML5Element::getParent() const {
    return parent_;
}

void HTML5Element::setAttr(const std::string& key, const std::string& value) {
    attributes_[key] = value;
}

std::string HTML5Element::getAttr(const std::string& key) const {
    auto it = attributes_.find(key);
    if (it != attributes_.end()) {
        return it->second;
    }
    throw exception::InvalidAttribute("Attribute " + key + " not found");
}

bool HTML5Element::hasAttr(const std::string& key) const noexcept {
    return attributes_.find(key) != attributes_.end();
}

void HTML5Element::removeAttr(const std::string& key) {
    attributes_.erase(key);
}

std::unordered_map<std::string, std::string> HTML5Element::getAllAttrs() const {
    return attributes_;
}


} // namespace detail

const std::unordered_map<std::string, Tag::Native> Tag::kNativeMap = Tag::s_createNativeMap();
const std::unordered_map<Tag::Native, std::string> Tag::kNativeMapInverse = Tag::s_createNativeMapInverse();


Tag& Tag::operator<<(const Tag& child) {
  element_->addChild(child.element_);
  return *this;
}

std::string Tag::toString(const std::string& indent, bool show_children, bool show_attrs) const {
  return s_toString(element_, indent, show_children, show_attrs);
}

std::variant<Tag::Native, Tag::Custom> Tag::getType() const noexcept {
  return element_->getType();
}

std::string Tag::getName() const {
  return s_getName(getType());
}

constexpr bool Tag::isCustom() const noexcept {
  return std::visit([](auto&& arg) -> bool {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, Native> || std::is_same_v<T, Custom>)
      return detail::EnumRangeChecker::inRange<T, Tag::Global, Tag::Event>(arg);
    else
      return false;
  }, element_->getType());
}

std::string Tag::s_toString(
  std::shared_ptr<detail::HTML5Element> element, 
  const std::string& indent, 
  bool show_children, 
  bool show_attrs)
{
  std::ostringstream html;
  std::stack<std::pair<std::shared_ptr<detail::HTML5Element>, int>> stack;
  stack.push({std::move(element), 0});
  while (!stack.empty()) {
    auto [current_element, level] = std::move(stack.top());
    stack.pop();

    std::string name = Tag::s_getName(current_element->getType());
    std::string current_indent(level * indent.length(), ' ');
    html << current_indent << "<" << name << " ";

    if (show_attrs) {
      for (const auto& [key, value] : current_element->getAllAttrs()) {
          html << key << "=\"" << value << "\" ";
      }
    }
    html << ">\n";
    
    if (show_children) {
        const auto& children = current_element->getChildren();
        if (!children.empty()) {
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                stack.push({*it, level + 1});
            }
        }
    }
    html << current_indent << "</" << name << ">\n";
  }
  return html.str();
}

std::string Tag::s_getName(Native tag)
{
  auto it = kNativeMapInverse.find(tag);
  if (it == kNativeMapInverse.end())
    throw exception::InvalidTag("Cannot find native type with tag " + std::to_string(static_cast<Native>(tag)));
  return it->second;
}

std::string Tag::s_getName(Custom tag)
{
  auto it = s_custom_inverse_map_.find(tag);
  if (it == s_custom_inverse_map_.end())
    throw exception::InvalidTag("Cannot find custom type with tag " + std::to_string(static_cast<Custom>(tag)));
  return it->second;
}

inline std::string Tag::s_getName(std::variant<Native, Custom> tag) {
    return std::visit([](auto&& arg) -> std::string {
        return Tag::s_getName(arg);
    }, tag);
}

inline std::variant<Tag::Native, Tag::Custom> Tag::s_getType(const std::string& tag_name) noexcept {
  try {
    return s_getTypeNative(tag_name);
  }
  catch(const exception::InvalidTag& e) {
    return s_getTypeCustom(tag_name);   // If it's not a native type, it must be a custom type
  }
}

constexpr Tag::Native Tag::s_getTypeNative(const std::string& name) {
  auto it = kNativeMap.find(name);
  if (it == kNativeMap.end())
    return static_cast<Tag::Native>(Tag::Global::Custom);
  return static_cast<Tag::Native>(it->second);  // Return the type of the tag
}

Tag::Custom Tag::s_getTypeCustom(const std::string& custom_name) noexcept {
  if (s_custom_map_.find(custom_name) == s_custom_map_.end())
  {
    // If the custom tag doesn't exist, add it to the map
    size_t value = s_custom_map_.size();
    s_custom_inverse_map_[value] = custom_name; // Add the custom tag to the inverse map
    s_custom_map_[custom_name] = value;         // Add the custom tag to the map
    return value;
  }
  return static_cast<Custom>(s_custom_map_[custom_name]);  // Return the type of the custom tag
}

constexpr const std::array<std::pair<std::string_view, detail::HTML5Element::Native>, 174> Tag::s_createNativeMap() noexcept {
  #define CONCAT(a, b) a##b
  #define TO_STRING(name) #name

  #define GLOBAL_TAG(name) {TO_STRING(name), static_cast<detail::HTML5Element::Native>(Tag::Global::name)}
  #define EVENT_TAG(name) {TO_STRING(name), static_cast<detail::HTML5Element::Native>(Tag::Event::name)}

  return {{
  {"custom", static_cast<detail::HTML5Element::Native>(Tag::Global::Custom)},
  GLOBAL_TAG(Address),
  GLOBAL_TAG(Area),
  GLOBAL_TAG(Article),
  GLOBAL_TAG(Aside),
  GLOBAL_TAG(Footer),
  GLOBAL_TAG(Header),
  GLOBAL_TAG(Main),
  GLOBAL_TAG(Nav),
  GLOBAL_TAG(Section),
  // Grouping Content
  GLOBAL_TAG(Div),
  GLOBAL_TAG(Figure),
  GLOBAL_TAG(Figcaption),
  GLOBAL_TAG(Hr),
  GLOBAL_TAG(Ol),
  GLOBAL_TAG(Ul),
  GLOBAL_TAG(Li),
  GLOBAL_TAG(Dl),
  GLOBAL_TAG(Dt),
  GLOBAL_TAG(Dd),
  GLOBAL_TAG(Pre),
  // Text Content
  GLOBAL_TAG(A),
  GLOBAL_TAG(B),
  GLOBAL_TAG(Em),
  GLOBAL_TAG(I),
  GLOBAL_TAG(Mark),
  GLOBAL_TAG(Small),
  GLOBAL_TAG(Strong),
  GLOBAL_TAG(Sub),
  GLOBAL_TAG(Sup),
  GLOBAL_TAG(U),
  // Forms
  GLOBAL_TAG(Button),
  GLOBAL_TAG(Datalist),
  GLOBAL_TAG(Fieldset),
  GLOBAL_TAG(Form),
  GLOBAL_TAG(Input),
  GLOBAL_TAG(Label),
  GLOBAL_TAG(Legend),
  GLOBAL_TAG(Meter),
  GLOBAL_TAG(Optgroup),
  GLOBAL_TAG(Option),
  GLOBAL_TAG(Output),
  GLOBAL_TAG(Progress),
  GLOBAL_TAG(Select),
  GLOBAL_TAG(Textarea),
  // Interactive Elements
  GLOBAL_TAG(Details),
  GLOBAL_TAG(Dialog),
  GLOBAL_TAG(Menu),
  GLOBAL_TAG(Summary),
  // Embedded Content
  GLOBAL_TAG(Audio),
  GLOBAL_TAG(Canvas),
  GLOBAL_TAG(Embed),
  GLOBAL_TAG(IFrame),
  GLOBAL_TAG(Img),
  GLOBAL_TAG(Object),
  GLOBAL_TAG(Picture),
  GLOBAL_TAG(Source),
  GLOBAL_TAG(Svg),
  GLOBAL_TAG(Video),
  // Tabular Data
  GLOBAL_TAG(Table),
  GLOBAL_TAG(Caption),
  GLOBAL_TAG(Col),
  GLOBAL_TAG(Colgroup),
  GLOBAL_TAG(Tbody),
  GLOBAL_TAG(Td),
  GLOBAL_TAG(Tfoot),
  GLOBAL_TAG(Th),
  GLOBAL_TAG(Thead),
  GLOBAL_TAG(Tr),
  // Document Metadata
  GLOBAL_TAG(Base),
  GLOBAL_TAG(Body),
  GLOBAL_TAG(Head),
  GLOBAL_TAG(Link),
  GLOBAL_TAG(Meta),
  GLOBAL_TAG(Style),
  GLOBAL_TAG(Title),
  // Scripting
  GLOBAL_TAG(Noscript),
  GLOBAL_TAG(Script),
  GLOBAL_TAG(Template),
  // Demarcating Edits
  GLOBAL_TAG(Del),
  GLOBAL_TAG(Ins),
  // Text-Level Semantics
  GLOBAL_TAG(Abbr),
  GLOBAL_TAG(Bdi),
  GLOBAL_TAG(Bdo),
  GLOBAL_TAG(Br),
  GLOBAL_TAG(Cite),
  GLOBAL_TAG(Code),
  GLOBAL_TAG(Data),
  GLOBAL_TAG(Dfn),
  GLOBAL_TAG(Kbd),
  GLOBAL_TAG(Q),
  GLOBAL_TAG(Rp),
  GLOBAL_TAG(Rt),
  GLOBAL_TAG(Ruby),
  GLOBAL_TAG(Samp),
  GLOBAL_TAG(Span),
  GLOBAL_TAG(Time),
  GLOBAL_TAG(Var),
  GLOBAL_TAG(Wbr),
  // Obsolete and Deprecated Elements
  GLOBAL_TAG(Acronym),
  GLOBAL_TAG(Big),
  GLOBAL_TAG(Center),
  GLOBAL_TAG(Dir),
  GLOBAL_TAG(Font),
  GLOBAL_TAG(Frame),
  GLOBAL_TAG(Frameset),
  GLOBAL_TAG(Marquee),
  GLOBAL_TAG(MenuItem),
  GLOBAL_TAG(NoFrames),
  GLOBAL_TAG(Nobr),
  GLOBAL_TAG(Param),
  GLOBAL_TAG(PlainText),
  GLOBAL_TAG(Rb),
  GLOBAL_TAG(Rtc),
  GLOBAL_TAG(Strike),
  GLOBAL_TAG(Tt),
  GLOBAL_TAG(Xmp),
  // Attribute
  GLOBAL_TAG(AccessKey),
  GLOBAL_TAG(Class),
  GLOBAL_TAG(ContentEditable),
  GLOBAL_TAG(ContextMenu),
  GLOBAL_TAG(Draggable),
  GLOBAL_TAG(DropZone),
  GLOBAL_TAG(Hidden),
  GLOBAL_TAG(Id),
  GLOBAL_TAG(Lang),
  GLOBAL_TAG(SpellCheck),
  GLOBAL_TAG(TabIndex),
  GLOBAL_TAG(Translate),
  GLOBAL_TAG(XmlLang),
  // Event Attributes
  EVENT_TAG(OnAfterPrint),
  EVENT_TAG(OnBeforePrint),
  EVENT_TAG(OnBeforeUnload),
  EVENT_TAG(OnError),
  EVENT_TAG(OnHashChange),
  EVENT_TAG(OnLoad),
  EVENT_TAG(OnMessage),
  EVENT_TAG(OnOffline),
  EVENT_TAG(OnOnline),
  EVENT_TAG(OnPageHide),
  EVENT_TAG(OnPageShow),
  EVENT_TAG(OnPopState),
  EVENT_TAG(OnResize),
  EVENT_TAG(OnStorage),
  EVENT_TAG(OnUnload),
  EVENT_TAG(OnBlur),
  EVENT_TAG(OnChange),
  EVENT_TAG(OnFocus),
  EVENT_TAG(OnInput),
  EVENT_TAG(OnInvalid),
  EVENT_TAG(OnReset),
  EVENT_TAG(OnSelect),
  EVENT_TAG(OnSearch),
  EVENT_TAG(OnSubmit),
  EVENT_TAG(OnClick),
  EVENT_TAG(OnDblClick),
  EVENT_TAG(OnContextMenu),
  EVENT_TAG(OnDrag),
  EVENT_TAG(OnDragEnd),
  EVENT_TAG(OnDragEnter),
  EVENT_TAG(OnDragLeave),
  EVENT_TAG(OnDragOver),
  EVENT_TAG(OnDragStart),
  EVENT_TAG(OnDrop),
  EVENT_TAG(OnMouseDown),
  EVENT_TAG(OnMouseMove),
  EVENT_TAG(OnMouseOut),
  EVENT_TAG(OnMouseOver),
  EVENT_TAG(OnMouseUp),
  EVENT_TAG(OnMouseWheel),
  EVENT_TAG(OnScroll),
  EVENT_TAG(OnShow),
  EVENT_TAG(OnToggle),
  EVENT_TAG(OnWheel)
}};
  #undef GLOBAL_TAG
  #undef EVENT_TAG
  #undef CONCAT
  #undef TO_STRING
}

constexpr const std::array<std::pair<Tag::Native, std::string_view>, 174> Tag::s_createNativeMapInverse() noexcept {

  #define CONCAT(a, b) a##b
  #define TO_STRING(name) #name

  #define GLOBAL_TAG(name) {static_cast<detail::HTML5Element::Native>(Tag::Global::name), TO_STRING(name)}
  #define EVENT_TAG(name) {static_cast<detail::HTML5Element::Native>(Tag::Event::name), TO_STRING(name)}
  return {{
    {static_cast<detail::HTML5Element::Native>(Tag::Global::Custom), TO_STRING(custom)},
    GLOBAL_TAG(Address),
    GLOBAL_TAG(Area),
    GLOBAL_TAG(Article),
    GLOBAL_TAG(Aside),
    GLOBAL_TAG(Footer),
    GLOBAL_TAG(Header),
    GLOBAL_TAG(Main),
    GLOBAL_TAG(Nav),
    GLOBAL_TAG(Section),
    // Grouping Content
    GLOBAL_TAG(Div),
    GLOBAL_TAG(Figure),
    GLOBAL_TAG(Figcaption),
    GLOBAL_TAG(Hr),
    GLOBAL_TAG(Ol),
    GLOBAL_TAG(Ul),
    GLOBAL_TAG(Li),
    GLOBAL_TAG(Dl),
    GLOBAL_TAG(Dt),
    GLOBAL_TAG(Dd),
    GLOBAL_TAG(Pre),
    // Text Content
    GLOBAL_TAG(A),
    GLOBAL_TAG(B),
    GLOBAL_TAG(Em),
    GLOBAL_TAG(I),
    GLOBAL_TAG(Mark),
    GLOBAL_TAG(Small),
    GLOBAL_TAG(Strong),
    GLOBAL_TAG(Sub),
    GLOBAL_TAG(Sup),
    GLOBAL_TAG(U),
    // Forms
    GLOBAL_TAG(Button),
    GLOBAL_TAG(Datalist),
    GLOBAL_TAG(Fieldset),
    GLOBAL_TAG(Form),
    GLOBAL_TAG(Input),
    GLOBAL_TAG(Label),
    GLOBAL_TAG(Legend),
    GLOBAL_TAG(Meter),
    GLOBAL_TAG(Optgroup),
    GLOBAL_TAG(Option),
    GLOBAL_TAG(Output),
    GLOBAL_TAG(Progress),
    GLOBAL_TAG(Select),
    GLOBAL_TAG(Textarea),
    // Interactive Elements
    GLOBAL_TAG(Details),
    GLOBAL_TAG(Dialog),
    GLOBAL_TAG(Menu),
    GLOBAL_TAG(Summary),
    // Embedded Content
    GLOBAL_TAG(Audio),
    GLOBAL_TAG(Canvas),
    GLOBAL_TAG(Embed),
    GLOBAL_TAG(IFrame),
    GLOBAL_TAG(Img),
    GLOBAL_TAG(Object),
    GLOBAL_TAG(Picture),
    GLOBAL_TAG(Source),
    GLOBAL_TAG(Svg),
    GLOBAL_TAG(Video),
    // Tabular Data
    GLOBAL_TAG(Table),
    GLOBAL_TAG(Caption),
    GLOBAL_TAG(Col),
    GLOBAL_TAG(Colgroup),
    GLOBAL_TAG(Tbody),
    GLOBAL_TAG(Td),
    GLOBAL_TAG(Tfoot),
    GLOBAL_TAG(Th),
    GLOBAL_TAG(Thead),
    GLOBAL_TAG(Tr),
    // Document Metadata
    GLOBAL_TAG(Base),
    GLOBAL_TAG(Body),
    GLOBAL_TAG(Head),
    GLOBAL_TAG(Link),
    GLOBAL_TAG(Meta),
    GLOBAL_TAG(Style),
    GLOBAL_TAG(Title),
    // Scripting
    GLOBAL_TAG(Noscript),
    GLOBAL_TAG(Script),
    GLOBAL_TAG(Template),
    // Demarcating Edits
    GLOBAL_TAG(Del),
    GLOBAL_TAG(Ins),
    // Text-Level Semantics
    GLOBAL_TAG(Abbr),
    GLOBAL_TAG(Bdi),
    GLOBAL_TAG(Bdo),
    GLOBAL_TAG(Br),
    GLOBAL_TAG(Cite),
    GLOBAL_TAG(Code),
    GLOBAL_TAG(Data),
    GLOBAL_TAG(Dfn),
    GLOBAL_TAG(Kbd),
    GLOBAL_TAG(Q),
    GLOBAL_TAG(Rp),
    GLOBAL_TAG(Rt),
    GLOBAL_TAG(Ruby),
    GLOBAL_TAG(Samp),
    GLOBAL_TAG(Span),
    GLOBAL_TAG(Time),
    GLOBAL_TAG(Var),
    GLOBAL_TAG(Wbr),
    // Obsolete and Deprecated Elements
    GLOBAL_TAG(Acronym),
    GLOBAL_TAG(Big),
    GLOBAL_TAG(Center),
    GLOBAL_TAG(Dir),
    GLOBAL_TAG(Font),
    GLOBAL_TAG(Frame),
    GLOBAL_TAG(Frameset),
    GLOBAL_TAG(Marquee),
    GLOBAL_TAG(MenuItem),
    GLOBAL_TAG(NoFrames),
    GLOBAL_TAG(Nobr),
    GLOBAL_TAG(Param),
    GLOBAL_TAG(PlainText),
    GLOBAL_TAG(Rb),
    GLOBAL_TAG(Rtc),
    GLOBAL_TAG(Strike),
    GLOBAL_TAG(Tt),
    GLOBAL_TAG(Xmp),
    // Attribute
    GLOBAL_TAG(AccessKey),
    GLOBAL_TAG(Class),
    GLOBAL_TAG(ContentEditable),
    GLOBAL_TAG(ContextMenu),
    GLOBAL_TAG(Draggable),
    GLOBAL_TAG(DropZone),
    GLOBAL_TAG(Hidden),
    GLOBAL_TAG(Id),
    GLOBAL_TAG(Lang),
    GLOBAL_TAG(SpellCheck),
    GLOBAL_TAG(TabIndex),
    GLOBAL_TAG(Translate),
    GLOBAL_TAG(XmlLang),
    // Event Attributes
    EVENT_TAG(OnAfterPrint),
    EVENT_TAG(OnBeforePrint),
    EVENT_TAG(OnBeforeUnload),
    EVENT_TAG(OnError),
    EVENT_TAG(OnHashChange),
    EVENT_TAG(OnLoad),
    EVENT_TAG(OnMessage),
    EVENT_TAG(OnOffline),
    EVENT_TAG(OnOnline),
    EVENT_TAG(OnPageHide),
    EVENT_TAG(OnPageShow),
    EVENT_TAG(OnPopState),
    EVENT_TAG(OnResize),
    EVENT_TAG(OnStorage),
    EVENT_TAG(OnUnload),
    EVENT_TAG(OnBlur),
    EVENT_TAG(OnChange),
    EVENT_TAG(OnFocus),
    EVENT_TAG(OnInput),
    EVENT_TAG(OnInvalid),
    EVENT_TAG(OnReset),
    EVENT_TAG(OnSelect),
    EVENT_TAG(OnSearch),
    EVENT_TAG(OnSubmit),
    EVENT_TAG(OnClick),
    EVENT_TAG(OnDblClick),
    EVENT_TAG(OnContextMenu),
    EVENT_TAG(OnDrag),
    EVENT_TAG(OnDragEnd),
    EVENT_TAG(OnDragEnter),
    EVENT_TAG(OnDragLeave),
    EVENT_TAG(OnDragOver),
    EVENT_TAG(OnDragStart),
    EVENT_TAG(OnDrop),
    EVENT_TAG(OnMouseDown),
    EVENT_TAG(OnMouseMove),
    EVENT_TAG(OnMouseOut),
    EVENT_TAG(OnMouseOver),
    EVENT_TAG(OnMouseUp),
    EVENT_TAG(OnMouseWheel),
    EVENT_TAG(OnScroll),
    EVENT_TAG(OnShow),
    EVENT_TAG(OnToggle),
    EVENT_TAG(OnWheel)
    }};
  #undef GLOBAL_TAG
  #undef EVENT_TAG
  #undef CONCAT
  #undef TO_STRING
}


} // namespace hi