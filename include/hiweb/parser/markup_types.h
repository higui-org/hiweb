#ifndef HiGUI_PARSER_MARKUP_TYPES_H
#define HiGUI_PARSER_MARKUP_TYPES_H

namespace hi::parser::markup
{
	enum class DocumentType
	{
		HTML,
		XML,
		XHTML,
	};

	enum class Structure
	{
		Title,
		Body,
		Markup,
	};

	enum class Division
	{
		Header,
		Navigation,
		Section,
		Footer,
	};

	enum class Text
	{
		H, h1, h2, h3, h4, h5, h6,
		P,
		HorizontalLine,
		Break,
		Bold,
		Italic,
		Strong
	};


} // namespace hi::parser

#endif // HiGUI_PARSER_MARKUP_TYPES_H