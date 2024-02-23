#ifndef HiWeb_H
#define HiWeb_H

#include "hiweb/parser/base.h"
#include "hiweb/parser/markup_types.h"

#include "hiweb/parser/html/html.h"
#include "hiweb/parser/xml/xml.h"
#include "hiweb/parser/xhtml/xhtml.h"

#include "hiweb/wrappers.h"

namespace hi::web
{
	Parser::Pointer Create(markup::DocumentType type)
	{
		using markup::DocumentType;

		switch (type)
		{
		case DocumentType::HTML:
			return std::make_unique<impl::html::HTML>();
		case DocumentType::XML:
			return std::make_unique<impl::xml::XML>();
		case DocumentType::XHTML:
			return std::make_unique<impl::xhtml::XHTML>();
		default:
			throw std::invalid_argument("Unknown DocumentType");
		}
	}
}

#endif // HiWeb_H