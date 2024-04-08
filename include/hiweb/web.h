#ifndef HiWEB_WEB_H
#define HiWEB_WEB_H

#include "hiweb/parser/base.h"
#include "hiweb/parser/document.h"

#include "hiweb/parser/html/html.h"
#include "hiweb/parser/xml/xml.h"
#include "hiweb/parser/xhtml/xhtml.h"

namespace hi::web
{
	Parser::Pointer CreateParser(document::Type type);
}	// namespace hi::web

#endif // HiWEB_WEB_H