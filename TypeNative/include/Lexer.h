#ifndef LEXER_H
#define LEXER_H

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/MemoryBuffer.h"

class Lexer;

class Token
{
	friend class Lexer;

public:
	enum class Kind : unsigned short
	{
		EndOfInput,      // end of input
		Unknown,  // unknown token
		Ident,	  // ident
		Number,   // number
		Comma,    // comma ,
		Colon,    // colon :
		Plus,	  // plus +
		Minus,	  // minus -
		Star,	  // star *
		Slash,	  // slash /
		LParen,  // left parenthesis (
		RParen,  // right parenthesis )
		With,  // with
	};

private:
	Kind kind_;
	llvm::StringRef text_;
	
public:
	Kind getKind() const { return kind_; }
	llvm::StringRef getText() const { return text_; }

	bool is(Kind k) const { return kind_ == k; }
	bool isOneOf(Kind k1, Kind k2) const { return is(k1) || is(k2); }

	template <typename... Ts>
	bool isOneOf(Kind k1, Kind k2, Ts... ks) const
	{
		return is(k1) || isOneOf(k2, ks...);
	}
};

class Lexer
{
	const char* buffer_start_;
	const char* buffer_ptr_;

public:
	Lexer(const llvm::StringRef& buffer)
	{
		buffer_start_ = buffer.begin();
		buffer_ptr_ = buffer_start_;
	}

	void Next(Token& token);

private:
	void FormToken(Token& result, const char* token_end, Token::Kind kind);
};


#endif // LEXER_H