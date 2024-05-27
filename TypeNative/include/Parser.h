#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "AST.h"

#include "llvm/Support/raw_ostream.h"

class Parser
{
    Lexer& lexer_;
    Token token_;
    bool has_error_;

    void Error(const std::string& message)
    {
        llvm::errs() << "Error: " << message << " at token: " << token_.getText() << "\n";
        has_error_ = true;
    }

    void Advance() { lexer_.Next(token_); }

    bool Expect(Token::Kind kind)
    {
        if (token_.getKind() != kind)
        {
            Error("Unexpected token");
            return true;
        }
        return false;
    }

    bool Consume(Token::Kind kind)
    {
        if (Expect(kind))
            return true;
        Advance();
        return false;
    }

    std::unique_ptr<AST> ParseCalc();
    std::unique_ptr<Expr> ParseExpr();
    std::unique_ptr<Expr> ParseTerm();
    std::unique_ptr<Expr> ParseFactor();

public:
    Parser(Lexer& lexer) : lexer_(lexer), has_error_(false) { Advance(); }

    bool HasError() const { return has_error_; }

    std::unique_ptr<AST> Parse();
}; // class Parser

#endif // PARSER_H