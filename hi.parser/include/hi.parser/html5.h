#ifndef HI_HTML5_H
#define HI_HTML5_H

#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>
#include <stdexcept>
#include <variant>
#include <algorithm>
#include <stack>
#include <concepts>
#include <string_view>
#include <array>
#include <utility>

namespace hi {
namespace detail {


class HTML5Element
{
public:
  using Custom = uint32_t;
  using Native = unsigned char;

private:
  std::variant<Native, Custom> type_;
  std::unordered_map<std::string, std::string> attributes_;
  std::vector<std::shared_ptr<HTML5Element>> children_;
  HTML5Element* parent_;

public:
  HTML5Element(std::variant<Native, Custom> type);
  HTML5Element(Native native);
  HTML5Element(Custom custom);

  void addChild(std::shared_ptr<HTML5Element> child);
  std::vector<std::shared_ptr<HTML5Element>> getChildren() const;
  void removeChild(std::shared_ptr<HTML5Element> child);
  void clearChildren();

  void setType(std::variant<Native, Custom> type) noexcept;
  std::variant<Native, Custom> getType() const noexcept;

  void setParent(HTML5Element* parent);
  HTML5Element* getParent() const;

  void setAttr(const std::string& key, const std::string& value);
  std::string getAttr(const std::string& key) const;
  bool hasAttr(const std::string& key) const noexcept;
  void removeAttr(const std::string& key);
  std::unordered_map<std::string, std::string> getAllAttrs() const;
}; // class HTML5Element

struct EnumRangeChecker {
    template<typename T, typename... Enums>
    constexpr static bool inRange(T value) {
        static_assert((... && std::is_enum_v<Enums>), "All types must be enum classes");
        return (... && ((static_cast<int>(Enums::min()) <= static_cast<int>(value)) && (static_cast<int>(value) <= static_cast<int>(Enums::max()))));
    }
};


// Helper function to deduce if the argument is a string literal
template <typename T>
struct is_string_literal : std::false_type {};

template <std::size_t N>
struct is_string_literal<const char(&)[N]> : std::true_type {};

} // namespace detail



class Tag
{
public:
  using Element = detail::HTML5Element;
  using Custom = Element::Custom;
  using Native = Element::Native;
  enum class Global : Native;
  enum class Event : Native;

private:
  std::shared_ptr<Element> element_;

  static const std::unordered_map<std::string, Native> kNativeMap;
  static const std::unordered_map<Native, std::string> kNativeMapInverse;
  static std::unordered_map<std::string, Custom> s_custom_map_;
  static std::unordered_map<Custom, std::string> s_custom_inverse_map_;

public:
  // 
  template <typename T, std::enable_if_t<detail::is_string_literal<T>::value, int> = 0>
  consteval Tag(T tag) { return Tag(s_getType(tag)); }

  template <typename T, std::enable_if_t<!detail::is_string_literal<T>::value && std::is_constructible_v<std::string, T>, int> = 0>
  Tag(T tag) : Tag(s_getType(std::string(tag))) {}
  
  constexpr Tag(std::variant<Native, Custom> tag) : element_(tag) {}
  constexpr Tag(Tag::Global tag) : Tag(static_cast<Native>(tag)) {}
  constexpr Tag(Tag::Event tag) : Tag(static_cast<Native>(tag)) {}

  Tag& operator<<(const Tag& child);

  inline std::string toString(const std::string& indent = "  ", bool show_children = true, bool show_attrs = true) const;
  constexpr std::variant<Native, Custom> getType() const noexcept;
  constexpr std::string getName() const;

  constexpr bool isCustom() const noexcept;

  static constexpr std::variant<Native, Custom> s_getType(const std::string& tag_name) noexcept;
  static constexpr Custom s_getTypeCustom(const std::string& custom_name) noexcept;
  static constexpr Native s_getTypeNative(const std::string& custom_name);
  
  static constexpr std::string s_getName(std::variant<Native, Custom> tag);
  static constexpr std::string s_getName(Native tag);
  static constexpr std::string s_getName(Custom tag);

  friend class HTML5Element;

private:
  static constexpr const std::array<std::pair<std::string_view, detail::HTML5Element::Native>, 174> s_createNativeMap() noexcept;
  static constexpr const std::array<std::pair<detail::HTML5Element::Native, std::string_view>, 174> s_createNativeMapInverse() noexcept;

  static std::string s_toString(
    std::shared_ptr<Element> element, 
    const std::string& indent = "  ", 
    bool show_children = true, 
    bool show_attrs = true);

}; // class Tag



enum class Tag::Global : Tag::Element::Native {
  Custom,     // defines a custom tag

  // Sections
  Address,    // defines contact information for the author/owner of a document
  Area,       // defines an area inside an image-map
  Article,    // defines an article
  Aside,      // defines content aside from the page content
  Footer,     // defines a footer for a document or section
  Header,     // defines a header for a document or section
  Main,       // specifies the main content of a document
  Nav,        // defines navigation links
  Section,    // defines a section in a document

  // Grouping Content
  Div,        // defines a section in a document
  Figure,     // specifies self-contained content
  Figcaption, // defines a caption for a <figure> element
  Hr,         // defines a thematic change in the content
  Ol,         // defines an ordered list
  Ul,         // defines an unordered list
  Li,         // defines a list item
  Dl,         // defines a description list
  Dt,         // defines a term/name in a description list
  Dd,         // defines a description/value of a term in a description list
  Pre,        // defines preformatted text

  // Text Content
  A,          // defines a hyperlink
  B,          // defines bold text
  Em,         // defines emphasized text
  I,          // defines a part of text in an alternate voice or mood
  Mark,       // defines marked/highlighted text
  Small,      // defines smaller text
  Strong,     // defines important text
  Sub,        // defines subscripted text
  Sup,        // defines superscripted text
  U,          // defines text that should be stylistically different from normal text

  // Forms
  Button,     // defines a clickable button
  Datalist,   // specifies a list of pre-defined options for input controls
  Fieldset,   // groups related elements in a form
  Form,       // defines an HTML form for user input
  Input,      // defines an input control
  Label,      // defines a label for an <input> element
  Legend,     // defines a caption for a <fieldset> element
  Meter,      // defines a scalar measurement within a known range (a gauge)
  Optgroup,   // defines a group of related options in a drop-down list
  Option,     // defines an option in a drop-down list
  Output,     // defines the result of a calculation
  Progress,   // represents the progress of a task
  Select,     // defines a drop-down list
  Textarea,   // defines a multiline input control (text area)

  // Interactive Elements
  Details,    // defines additional details that the user can view or hide
  Dialog,     // defines a dialog box or window
  Menu,       // defines a list/menu of commands
  Summary,    // defines a visible heading for a <details> element

  // Embedded Content
  Audio,      // defines sound content
  Canvas,     // used to draw graphics, on the fly, via scripting (usually JavaScript)
  Embed,      // defines a container for an external application or interactive content (a plug-in)
  IFrame,     // defines an inline frame
  Img,        // defines an image
  Object,     // defines an embedded object
  Picture,    // defines a container for multiple image resources
  Source,     // defines multiple media resources for media elements (<video> and <audio>)
  Svg,        // defines a container for SVG graphics
  Video,      // defines a video or movie

  // Tabular Data
  Table,      // defines a table
  Caption,    // defines a table caption
  Col,        // specifies column properties for each column within a <colgroup> element
  Colgroup,   // specifies a group of one or more columns in a table for formatting
  Tbody,      // groups the body content in a table
  Td,         // defines a cell in a table
  Tfoot,      // groups the footer content in a table
  Th,         // defines a header cell in a table
  Thead,      // groups the header content in a table
  Tr,         // defines a row in a table

  // Document Metadata
  Base,       // defines a base URL for all the links in a page
  Body,       // defines the document's body
  Head,       // defines information about the document
  Link,       // defines the relationship between a document and an external resource (most used to link to style sheets)
  Meta,       // defines metadata about an HTML document
  Style,      // defines an inline style for an element
  Title,      // defines a title for the document

  // Scripting
  Noscript,   // defines an alternate content for users that do not support client-side scripts
  Script,     // defines a client-side script
  Template,   // defines a template

  // Demarcating Edits
  Del,        // defines text that has been deleted from a document
  Ins,        // defines a text that has been inserted into a document

  // Text-Level Semantics
  Abbr,       // defines an abbreviation or an acronym
  Bdi,        // isolates a part of text that might be formatted in a different direction from other text outside it
  Bdo,        // overrides the current text direction
  Br,         // defines a single line break
  Cite,       // defines the title of a work
  Code,       // defines a piece of computer code
  Data,       // links the content with a machine-readable translation
  Dfn,        // defines a definition term
  Kbd,        // defines keyboard input
  Q,          // defines a short quotation
  Rp,         // defines what to show in browsers that do not support ruby annotations
  Rt,         // defines an explanation/pronunciation of characters (for East Asian typography)
  Ruby,       // defines a ruby annotation (for East Asian typography)
  Samp,       // defines sample output from a computer program
  Span,       // defines a section in a document
  Time,       // defines a date/time
  Var,        // defines a variable
  Wbr,        // defines a possible line-break

  // Obsolete and Deprecated Elements
  Acronym,    // deprecated: defines an acronym (Use <abbr> instead)
  Big,        // deprecated: defines big text (Use CSS instead)
  Center,     // deprecated: defines centered text (Use CSS instead)
  Dir,        // obsolete: defines a directory list (Use <ul> instead)
  Font,       // deprecated: defines font, color, and size for text (Use CSS instead)
  Frame,      // obsolete: defines a window (a frame) in a frameset (Use <iframe> instead)
  Frameset,   // obsolete: defines a set of frames (Use <iframe> instead)
  Marquee,    // deprecated: defines a marquee (scrolling text) (Use CSS animations instead)
  MenuItem,   // deprecated: defines a command/menu item that the user can invoke from a popup menu (Use <button> or <li> instead)
  NoFrames,   // obsolete: defines an alternate content for browsers that do not support frames (No longer needed)
  Nobr,       // deprecated: defines text that should not contain line breaks or wrap (Use CSS instead)
  Param,      // removed from the web standards: defines parameters for an object element (Still use <param>, but it's mainly for <object>)
  PlainText,  // obsolete: defines plain text (Use <pre> instead)
  Rb,         // partially supported: defines the base text component of a ruby annotation (Use <rb> with caution; full support in Firefox only)
  Rtc,        // deprecated: defines ruby text containers used to display the annotations of characters in ruby text (Use <rp> instead)
  Strike,     // deprecated: defines strikethrough text (Use <del> or <s> instead)
  Tt,         // deprecated: defines teletype text (Use <code> instead)
  Xmp,        // obsolete: defines preformatted text (Use <pre> instead)

  // Attribute
  AccessKey,  // defines a keyboard shortcut to activate or add focus to the element
  Class,      // defines one or more class names for an element (refers to a class in a style sheet)
  ContentEditable, // defines whether the content of an element is editable or not
  ContextMenu, // defines a context menu for an element
  Draggable,  // defines whether an element is draggable or not
  DropZone,   // specifies whether the dragged data is copied, moved, or linked, when dropped
  Hidden,     // defines whether an element is hidden or not
  Id,         // defines a unique id for an element
  Lang,       // defines the language of the element
  SpellCheck, // defines whether the element must have its spelling and grammar checked or not
  TabIndex,   // defines the tab order of an element
  Translate,  // specifies whether the content of an element should be translated or not
  // DO NOT change the order for XmlLang. 
  // enum Event uses "XmlLang + 1" as the first member value.
  XmlLang,    // defines the language of the element's content
  }; // enum class Tag::Global

enum class Tag::Event : Tag::Element::Native {
  // Window Event Attributes
  
  // OnAfterPrint uses the last tag member in enum Global.
  OnAfterPrint = static_cast<Tag::Element::Native>(Tag::Global::XmlLang) + 1, // after the document is printed
  OnBeforePrint,    // before the document is printed
  OnBeforeUnload,   // before the document is unloaded
  OnError,          // when an error occurs
  OnHashChange,     // when there have been changes to the anchor part of a URL
  OnLoad,           // after the document has loaded
  OnMessage,        // when the message is triggered
  OnOffline,        // when the browser starts to work offline
  OnOnline,         // when the browser starts to work online
  OnPageHide,       // when the page is hidden
  OnPageShow,       // when the page is shown
  OnPopState,       // when the window's history changes
  OnResize,         // when the browser window is resized
  OnStorage,        // when a web storage area is updated
  OnUnload,         // when the document is about to be unloaded

  // Form Events
  OnBlur,           // when an element loses focus
  OnChange,         // when the content of a form element, the selection, or the checked state have changed (for <input>, <select>, and <textarea>)
  OnFocus,          // when an element gets focus
  OnInput,          // when an element gets user input
  OnInvalid,        // when an element is invalid
  OnReset,          // when a form is reset
  OnSelect,         // when some text is selected
  OnSearch,         // when the user writes something in a search field (for <input="search">)
  OnSubmit,         // when a form is submitted

  // Mouse Events
  OnClick,          // when the element is clicked
  OnDblClick,       // when the element is double-clicked
  OnContextMenu,    // when the element is right-clicked
  OnDrag,           // when the element is being dragged
  OnDragEnd,        // when the element has been dragged
  OnDragEnter,      // when the dragged element enters the drop target
  OnDragLeave,      // when the dragged element leaves the drop target
  OnDragOver,       // when the dragged element is over the drop target
  OnDragStart,      // when the dragging of the element starts
  OnDrop,           // when the dragged element is dropped on the drop target
  OnMouseDown,      // when a mouse button is pressed down on an element
  OnMouseMove,      // when the mouse pointer moves over an element
  OnMouseOut,       // when the mouse pointer moves out of an element
  OnMouseOver,      // when the mouse pointer moves over an element
  OnMouseUp,        // when a mouse button is released over an element
  OnMouseWheel,     // when the mouse wheel rolls up or down over an element
  OnScroll,         // when an element's scrollbar is being scrolled
  OnShow,           // when the element is shown as a context menu
  OnToggle,         // when the element is opened or closed
  OnWheel,           // when the mouse wheel rolls up or down over an element
  __END__ // DO NOT use. DOT NOT change the order for __END__.
  }; // enum class Tag::Event

static constexpr std::array<std::string_view, 174> htmlTags = {{
  "custom", "address", "area", "article", "aside", "footer", "header", "main", "nav", "section",
  "div", "figure", "figcaption", "hr", "ol", "ul", "li", "dl", "dt", "dd", "pre", "a", "b", "em", "i", "mark", "small",
  "strong", "sub", "sup", "u", "button", "datalist", "fieldset", "form", "input", "label", "legend", "meter", 
  "optgroup", "option", "output", "progress", "select", "textarea", "details", "dialog", "menu", "summary", 
  "audio", "canvas", "embed", "iframe", "img", "object", "picture", "source", "svg", "video", "table", 
  "caption", "col", "colgroup", "tbody", "td", "tfoot", "th", "thead", "tr", "base", "body", "head", "link", 
  "meta", "style", "title", "noscript", "script", "template", "del", "ins", "abbr", "bdi", "bdo", "br", 
  "cite", "code", "data", "dfn", "kbd", "q", "rp", "rt", "ruby", "samp", "span", "time", "var", "wbr", 
  "acronym", "big", "center", "dir", "font", "frame", "frameset", "marquee", "menuitem", "noframes", "nobr", 
  "param", "plaintext", "rb", "rtc", "strike", "tt", "xmp", "accesskey", "class", "contenteditable", 
  "contextmenu", "draggable", "dropzone", "hidden", "id", "lang", "spellcheck", "tabindex", "translate", 
  "xmllang", "onafterprint", "onbeforeprint", "onbeforeunload", "onerror", "onhashchange", "onload", 
  "onmessage", "onoffline", "ononline", "onpagehide", "onpageshow", "onpopstate", "onresize", "onstorage", 
  "onunload", "onblur", "onchange", "onfocus", "oninput", "oninvalid", "onreset", "onselect", "onsearch", 
  "onsubmit", "onclick", "ondblclick", "oncontextmenu", "ondrag", "ondragend", "ondragenter", "ondragleave", 
  "ondragover", "ondragstart", "ondrop", "onmousedown", "onmousemove", "onmouseout", "onmouseover", 
  "onmouseup", "onmousewheel", "onscroll", "onshow", "ontoggle", "onwheel"
}};



struct DOM {
  Tag head;
  Tag body;

  DOM() : head("head"), body("body") {}

  std::string toString() const;
}; // class DOM


namespace exception
{
  class Error : public std::exception {
  public:
      explicit Error(const std::string& message) 
        : message_("hi::exception::Error says " + message) 
      {}
      virtual const char* what() const noexcept override {
          return message_.c_str();
      }
  private:
      std::string message_;
  }; // class Error

  class InvalidTag : public Error { 
  public:
      InvalidTag(const std::string& message) 
        : Error("Invalid tag type was received. " + message) 
      {}
  }; // class InvalidTag

  class InvalidAttribute : public Error {
  public:
      InvalidAttribute(const std::string& message) 
        : Error("Invalid attribute was received. " + message) 
      {}
  }; // class InvalidAttribute

  class InvalidEvent : public Error {
  public:
      InvalidEvent(const std::string& message) 
        : Error("Invalid event was received. " + message) 
      {}
  }; // class InvalidEvent

} // namespace exception

} // namespace hi
#endif // HI_HTML5_H