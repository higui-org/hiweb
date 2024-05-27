#include "Parser.h"

std::unique_ptr<AST> Parser::Parse()
{
    auto result = ParseCalc();
    Expect(Token::Kind::EndOfInput);
    return result;
}

std::unique_ptr<AST> Parser::ParseCalc()
{
    std::unique_ptr<Expr> expr;
    llvm::SmallVector<llvm::StringRef, 8> vars;

    if (token_.is(Token::Kind::With))
    {
        Advance();

        if (Expect(Token::Kind::Ident))
            return nullptr;

        vars.push_back(token_.getText());
        Advance();

        while (token_.is(Token::Kind::Comma))
        {
            Advance();

            if (Expect(Token::Kind::Ident))
                return nullptr;

            vars.push_back(token_.getText());
            Advance();
        }

        if (Consume(Token::Kind::Colon))
            return nullptr;
    }

    expr = ParseExpr();

    if (vars.empty())
        return expr;
    else
        return std::make_unique<WithDecl>(vars, std::move(expr));
}

std::unique_ptr<Expr> Parser::ParseExpr()
{
    auto lhs = ParseTerm();
    while (token_.isOneOf(Token::Kind::Plus, Token::Kind::Minus))
    {
        BinaryOp::Operator op = token_.is(Token::Kind::Plus) ? 
            BinaryOp::Operator::Add : BinaryOp::Operator::Sub;

        Advance();
        auto rhs = ParseTerm();
        lhs = std::make_unique<BinaryOp>(op, std::move(lhs), std::move(rhs));
    }
    return lhs;
}

std::unique_ptr<Expr> Parser::ParseTerm()
{
    auto lhs = ParseFactor();
    while (token_.isOneOf(Token::Kind::Star, Token::Kind::Slash))
    {
        BinaryOp::Operator op = token_.is(Token::Kind::Star) ? 
            BinaryOp::Operator::Mul : BinaryOp::Operator::Div;

        Advance();
        auto rhs = ParseFactor();
        lhs = std::make_unique<BinaryOp>(op, std::move(lhs), std::move(rhs));
    }
    return lhs;
}

std::unique_ptr<Expr> Parser::ParseFactor()
{
    using Kind = Token::Kind;

    std::unique_ptr<Expr> result;

    switch (token_.getKind())
    {
    case Kind::Number:
        result = std::make_unique<Factor>(Factor::Kind::Number, token_.getText());
        Advance();
        break;
    case Kind::Ident:
        result = std::make_unique<Factor>(Factor::Kind::Ident, token_.getText());
        Advance();
        break;
    case Kind::LParen:
        Advance();
        result = ParseExpr();
        if (!Consume(Kind::RParen))
            break;
    default:
        if (!result)
            Error("Unexpected token");

        while (!token_.isOneOf(
            Kind::RParen, 
            Kind::Star, 
            Kind::Plus, 
            Kind::Minus, 
            Kind::Slash, 
            Kind::EndOfInput))
        {
            Advance();
        }
    }
    return result;
}