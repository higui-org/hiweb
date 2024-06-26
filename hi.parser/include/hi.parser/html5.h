#ifndef HIWEB_PARSER_HTML5_H
#define HIWEB_PARSER_HTML5_H

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>

#include <glm/glm.hpp>

namespace hiweb
{
  namespace detail
  {
    class Element
    {
      unsigned char type_;
      std::optional<std::string> custom_name_;
      std::vector<std::shared_ptr<Element>> children_;
      std::weak_ptr<Element> parent_;

    public:
      Element(Tag::Type name);
      Element(const std::string& custom_name);

      void AddChild(std::shared_ptr<Element> child);

      std::string getHTML() const;
      std::string getCustomHTML() const;

      void setParent(Element* parent);
      Element* getParent() const;
    }; // class Element
  } // namespace detail


  class Tag
  {
    static const std::unordered_map<std::string, unsigned char> str_map_;
    static const std::unordered_map<unsigned char, std::string> uchar_map_;
    std::shared_ptr<detail::Element> element_;

  public:
    enum class Type : unsigned char;
    enum class Event : unsigned char;

    Tag(Tag::Type type);
    Tag(const std::string& custom_name);

    Tag& operator<<(const Tag& child);

    std::string getHTML() const;
    static Tag::Type getTypeFrom(const std::string& tag_name) const noexcept;
    static std::string getNameFrom(Tag::Type tag_type) const;
    Tag::Type getType() const noexcept;
    std::string getName() const;

  }; // class Tag


  class DOM
  {
    Tag head_;
    Tag body_;

  public:
    DOM();
    DOM(const Tag& head, const Tag& body);
    DOM(const Tag& head);
    DOM(const DOM& other) = default;

    DOM& operator=(const DOM& other) = delete;
    DOM& operator=(DOM&& other) = delete;

    void setHead(const Tag& root);
    const Tag& getHead() const;
    void setBody(const Tag& root);
    const Tag& getBody() const;

    std::string getHTML() const;

  private:
    void ValidateTags() const;

  }; // class DOM



  enum class Tag::Type : unsigned char
  {
    Custom,     // defines a custom tag

    // Sections
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

    // Content Sectioning
    Address,    // defines contact information for the author/owner of a document
    Area,       // defines an area inside an image-map
    Article,    // defines an article
    Aside,      // defines content aside from the page content

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
  }; // enum class Tag::Type

  enum class Tag::Event : unsigned char
  {
    // Window Event Attributes

    // OnAfterPrint uses the last tag member in enum Global.
    OnAfterPrint = static_cast<unsigned char>(Tag::Type::XmlLang) + 1, // after the document is printed
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
    OnWheel           // when the mouse wheel rolls up or down over an element
  }; // enum class Tag::Event


} // namespace hiweb
#endif // HIWEB_PARSER_HTML5_H