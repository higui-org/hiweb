#include "hiweb/web.h"

namespace hi::web
{
	Parser::Pointer CreateParser(document::Type type)
	{
		using document::Type;

		switch (type)
		{
		case Type::HTML:
			return std::make_unique<html::HTML>();
		case Type::XML:
			return std::make_unique<xml::XML>();
		case Type::XHTML:
			return std::make_unique<xhtml::XHTML>();
		default:
			throw std::invalid_argument("Unknown document type");
		}
	}
}	// namespace hi::web