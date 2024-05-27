#include "Lexer.h"

namespace charinfo
{
	LLVM_READNONE inline bool isWhitespace(char c)
	{
		return c == ' ' || c == '\t' || c == '\n' || c == '\r'
			|| c == '\f' || c == '\v';
	}

	LLVM_READNONE inline bool isDigit(char c)
	{
		return c >= '0' && c <= '9';
	}

	LLVM_READNONE inline bool isLetter (char c)
	{
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}
} // namespace charinfo

void Lexer::Next(Token& token)
{
	while (*buffer_ptr_ && charinfo::isWhitespace(*buffer_ptr_))
	{
		++buffer_ptr_;

		if (!*buffer_ptr_)
		{
			token.kind_ = Token::Kind::EndOfInput;
			return;
		}
		else if (charinfo::isDigit(*buffer_ptr_))
		{
			const char* end = buffer_ptr_ + 1;
			while (charinfo::isDigit(*end))
			{
				++end;
			}
			FormToken(token, end, Token::Kind::Number);
			return;
		}
		else
		{
			switch (*buffer_ptr_)
			{
			#define CASE(ch, tok) \
			case ch: FormToken(token, buffer_ptr_ + 1, tok); break
				CASE('+', Token::Kind::Plus);
				CASE('-', Token::Kind::Minus);
				CASE('*', Token::Kind::Star);
				CASE('/', Token::Kind::Slash);
				CASE('(', Token::Kind::LParen);
				CASE(')', Token::Kind::RParen);
				CASE(':', Token::Kind::Colon);
				CASE(',', Token::Kind::Comma);
			#undef CASE
			default:
				FormToken(token, buffer_ptr_ + 1, Token::Kind::Unknown);
			}
			return;
		}
	}
}

void Lexer::FormToken(
	Token& token, 
	const char* token_end,
	Token::Kind kind)
{
	token.kind_ = kind;
	token.text_ = llvm::StringRef(buffer_ptr_, token_end - buffer_ptr_);
	buffer_ptr_ = token_end;
}