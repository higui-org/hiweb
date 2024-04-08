#ifndef HiWeb_PARSER_XML_XML_H
#define HiWeb_PARSER_XML_XML_H

#include "hiweb/parser/base.h"

#include <string>

namespace hi::web::xml
{
	class XML : public Parser
	{
	public:
		XML() noexcept = default;

		void read(const std::string& filename) override;

	private:

	};
}

#endif // HiWeb_PARSER_XML_XML_H