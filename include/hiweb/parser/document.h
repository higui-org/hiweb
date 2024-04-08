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


} // namespace hi::document

#endif // HiWEB_DOCUMENT_H