#ifndef HiWeb_PARSER_XHTML_XHTML_H
#define HiWeb_PARSER_XHTML_XHTML_H

#include "hiweb/parser/base.h"

#include <string>

namespace hi::web::impl::xhtml
{
	class XHTML : public Parser
	{
	public:
		XHTML() noexcept = default;

		void read(const std::string& filename) override;

	private:

	};
}

#endif // HiWeb_PARSER_XHTML_XHTML_H