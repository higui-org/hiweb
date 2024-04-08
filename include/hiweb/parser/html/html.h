#ifndef HiWeb_PARSER_HTML_HTML_H
#define HiWeb_PARSER_HTML_HTML_H

#include "hiweb/parser/base.h"

#include <string>

namespace hi::web::html
{
	class HTML : public Parser
	{
	public:
		HTML() noexcept = default;

		void read(const std::string& filename) override;
	
	private:

	};
}

#endif // HiWeb_PARSER_HTML_HTML_H