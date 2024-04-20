#ifndef HiWEB_DOCUMENT_H
#define HiWEB_DOCUMENT_H

namespace hi::web::document
{
    enum class Type
    {
        HTML,
        XML,
        XHTML
    };

    enum class Structure
    {
        Title,
        Body,
        Markup
    };

    enum class Section
    {
        Header,
        Navigation,
        Section,
        Footer
    };

    enum class Text
    {
        Heading1,
        Heading2,
        Heading3,
        Heading4,
        Heading5,
        Heading6,
        Paragraph,
        HorizontalLine,
        LineBreak,
        Bold,
        Italic,
        Strong
    };

    enum class Attribute
    {
        Id,
        Class,
        Style,
        Title,
        Href,
        Src,
        Alt,
        Width,
        Height,
        Type,
        Name,
        Value,
        Placeholder,
        Disabled,
        Checked,
        Readonly,
        Required,
        Maxlength,
        Pattern,
        Min,
        Max,
        Step,
        Autocomplete,
        Autofocus,
        Multiple,
        Form,
        Formaction,
        Formenctype,
        Formmethod,
        Formnovalidate,
        Formtarget,
        Rel,
        Target
    };

    enum class InputType
    {
        Text,
        Password,
        Submit,
        Reset,
        Radio,
        Checkbox,
        Button,
        Color,
        Date,
        DatetimeLocal,
        Email,
        File,
        Hidden,
        Image,
        Month,
        Number,
        Range,
        Search,
        Tel,
        Time,
        Url,
        Week
    };

    /**
    * @class StringIndex
    * @brief A complex structure of a string and variables in it.
    *
    * This structure is used to reference various textual components of the tag such as name, ID, classes, and attributes
    * without storing multiple copies of the same strings.
    */
    class StringIndex
    {
    public:
        StringIndex() noexcept : _off_begin(0), _off_end(0) {}

        /** 
        * @brief Gets the starting index of the substring.
		* @return The starting index of the substring.
        */
        unsigned int begin() const noexcept { return _off_begin; }

        /** 
        * @brief Gets the ending index of the substring.
        * @return The ending index of the substring.
        */
        unsigned int end() const noexcept { return _off_end; }

    private:
        std::string data; ///< Stores all text related to the string
        unsigned int _off_begin; ///< Starting index of the substring
        unsigned int _off_end;   ///< Ending index (exclusive) of the substring
    };

} // namespace hi::document

#endif // HiWEB_DOCUMENT_H