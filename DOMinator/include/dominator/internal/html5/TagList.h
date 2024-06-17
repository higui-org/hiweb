#ifndef HIWEB_INTERNAL_HTML5_LIST_H
#define HIWEB_INTERNAL_HTML5_LIST_H


namespace hiweb::tag
{

enum Type : unsigned char 
{
    custom,     // Defines a custom tag

    // Global Attributes
    a,          // Defines a hyperlink
    abbr,       // Defines an abbreviation or an acronym
    address,    // Defines contact information for the author/owner of a document
    area,       // Defines an area inside an image-map
    article,    // Defines an article
    aside,      // Defines content aside from the page content
    audio,      // Defines sound content
    b,          // Defines bold text
    base,       // Defines a base URL for all the links in a page
    bdi,        // Isolates a part of text that might be formatted in a different direction from other text outside it
    bdo,        // Overrides the current text direction
    blockquote, // Defines a section that is quoted from another source
    body,       // Defines the document's body
    br,         // Defines a single line break
    button,     // Defines a clickable button
    canvas,     // Used to draw graphics, on the fly, via scripting (usually JavaScript)
    caption,    // Defines a table caption
    cite,       // Defines the title of a work
    code,       // Defines a piece of computer code
    col,        // Specifies column properties for each column within a <colgroup> element
    colgroup,   // Specifies a group of one or more columns in a table for formatting
    data,       // Links the content with a machine-readable translation
    datalist,   // Specifies a list of pre-defined options for input controls
    dd,         // Defines a description/value of a term in a description list
    del,        // Defines text that has been deleted from a document
    details,    // Defines additional details that the user can view or hide
    dfn,        // Defines a definition term
    dialog,     // Defines a dialog box or window
    div,        // Defines a section in a document
    dl,         // Defines a description list
    dt,         // Defines a term/name in a description list
    em,         // Defines emphasized text
    embed,      // Defines a container for an external application or interactive content (a plug-in)
    fieldset,   // Groups related elements in a form
    figcaption, // Defines a caption for a <figure> element
    figure,     // Specifies self-contained content
    footer,     // Defines a footer for a document or section
    form,       // Defines an HTML form for user input
    head,       // Defines information about the document
    header,     // Defines a header for a document or section
    hgroup,     // Groups heading (<h1> to <h6>) elements
    h1, h2, h3, h4, h5, h6,
    hr,         // Defines a thematic change in the content
    html,       // Defines the root of an HTML document
    i,          // Defines a part of text in an alternate voice or mood
    iframe,     // Defines an inline frame
    img,        // Defines an image
    input,      // Defines an input control
    ins,        // Defines a text that has been inserted into a document
    kbd,        // Defines keyboard input
    keygen,     // DELETED SINCE HTML5.2 // Defines a key-pair generator field (for forms)
    label,      // Defines a label for an <input> element
    legend,     // Defines a caption for a <fieldset> element
    li,         // Defines a list item
    link,       // Defines the relationship between a document and an external resource (most used to link to style sheets)
    main,       // Specifies the main content of a document
    map,        // Defines a client-side image-map
    mark,       // Defines marked/highlighted text
    menu,       // Defines a list/menu of commands
    menuitem,   // DELETED SINCE HTML5.2 // Defines a command/menu item that the user can invoke from a popup menu
    meta,       // Defines metadata about an HTML document
    meter,      // Defines a scalar measurement within a known range (a gauge)
    nav,        // Defines navigation links
    noscript,   // Defines an alternate content for users that do not support client-side scripts
    object,     // Defines an embedded object
    ol,         // Defines an ordered list
    optgroup,   // Defines a group of related options in a drop-down list
    option,     // Defines an option in a drop-down list
    output,     // Defines the result of a calculation
    p,          // Defines a paragraph
    param,      // Defines a parameter for an object
    picture,    // Defines a container for multiple image resources
    pre,        // Defines preformatted text
    progress,   // Represents the progress of a task
    q,          // Defines a short quotation
    rp,         // Defines what to show in browsers that do not support ruby annotations
    rt,         // Defines an explanation/pronunciation of characters (for East Asian typography)
    ruby,       // Defines a ruby annotation (for East Asian typography)
    s,          // Defines text that is no longer correct
    samp,       // Defines sample output from a computer program
    script,     // Defines a client-side script
    section,    // Defines a section in a document
    select,     // Defines a drop-down list
    small,      // Defines smaller text
    source,     // Defines multiple media resources for media elements (<video> and <audio>)
    span,       // Defines a section in a document
    strong,     // Defines important text
    sub,        // Defines subscripted text
    summary,    // Defines a visible heading for a <details> element
    sup,        // Defines superscripted text
    svg,        // Defines a container for SVG graphics
    table,      // Defines a table
    tbody,      // Groups the body content in a table
    td,         // Defines a cell in a table
    template_,  // Defines a template
    textarea,   // Defines a multiline input control (text area)
    tfoot,      // Groups the footer content in a table
    th,         // Defines a header cell in a table
    thead,      // Groups the header content in a table
    time,       // Defines a date/time
    title,      // Defines a title for the document
    tr,         // Defines a row in a table
    track,      // Defines text tracks for <video> and <audio>
    u,          // Defines text that should be stylistically different from normal text
    ul,         // Defines an unordered list
    var,        // Defines a variable
    video,      // Defines a video or movie
    wbr,        // Defines a possible line-break
    accesskey,  // Defines a keyboard shortcut to activate or add focus to the element
    class_,     // Defines one or more class names for an element (refers to a class in a style sheet)
    contenteditable, // Defines whether the content of an element is editable or not
    contextmenu, // Defines a context menu for an element
    data_,      // Adds a custom attribute to an element
    dir,        // Defines the text direction
    draggable,  // Defines whether an element is draggable or not
    dropzone,   // Specifies whether the dragged data is copied, moved, or linked, when dropped
    hidden,     // Defines whether an element is hidden or not
    id,         // Defines a unique id for an element
    lang,       // Defines the language of the element
    spellcheck, // Defines whether the element must have its spelling and grammar checked or not
    style,      // Defines an inline style for an element
    tabindex,   // Defines the tab order of an element
    translate,  // Specifies whether the content of an element should be translated or not
    xml_lang,   // Defines the language of the element's content
}; // enum Type

enum Event : unsigned char 
{
    // Window Event Attributes
    onafterprint = tag::xml_lang + 1, // after the document is printed
    onbeforeprint,    // before the document is printed
    onbeforeunload,   // before the document is unloaded
    onerror,          // when an error occurs
    onhashchange,     // when there has been changes to the anchor part of a URL
    onload,           // after the document has loaded
    onmessage,        // when the message is triggered
    onoffline,        // when the browser starts to work offline
    ononline,         // when the browser starts to work online
    onpagehide,       // when the page is hidden
    onpageshow,       // when the page is shown
    onpopstate,       // when the window's history changes
    onresize,         // when the browser window is resized
    onstorage,        // when a web storage area is updated
    onunload,         // when the document is about to be unloaded

    // Form Events
    onblur,           // when an element loses focus
    onchange,         // when the content of a form element, the selection, or the checked state have changed (for <input>, <select>, and <textarea>)
    onfocus,          // when an element gets focus
    oninput,          // when an element gets user input
    oninvalid,        // when an element is invalid
    onreset,          // when a form is reset
    onselect,         // when some text is selected
    onsearch,         // when the user writes something in a search field (for <input="search">)
    onsubmit,         // when a form is submitted

    // Mouse Events
    onclick,          // when the element is clicked
    ondblclick,       // when the element is double-clicked
    oncontextmenu,    // when the element is right-clicked
    ondrag,           // when the element is being dragged
    ondragend,        // when the element has been dragged
    ondragenter,      // when the dragged element enters the drop target
    ondragleave,      // when the dragged element leaves the drop target
    ondragover,       // when the dragged element is over the drop target
    ondragstart,      // when the dragging of the element starts
    ondrop,           // when the dragged element is dropped on the drop target
    onmousedown,      // when a mouse button is pressed down on an element
    onmousemove,      // when the mouse pointer moves over an element
    onmouseout,       // when the mouse pointer moves out of an element
    onmouseover,      // when the mouse pointer moves over an element
    onmouseup,        // when a mouse button is released over an element
    onmousewheel,     // when the mouse wheel rolls up or down over an element
    onscroll,         // when an element's scrollbar is being scrolled
    onshow,           // when the element is shown as a context menu
    ontoggle,         // when the element is opened or closed
    onwheel           // when the mouse wheel rolls up or down over an element
}; // enum Event

} // namespace hiweb::tag

#endif // HIWEB_INTERNAL_HTML5_LIST_H