#ifndef ABSTRACT_SYNTAX_TREE_H
#define ABSTRACT_SYNTAX_TREE_H

#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"

class AST;
class Expr;
class Factor;
class BinaryOp;
class WithDecl;

class ASTVisitor
{
public:
	virtual void Visit(AST& ast) {};
	virtual void Visit(Expr& expr) {};
	virtual void Visit(Factor& factor) = 0;
	virtual void Visit(BinaryOp& binaryOp) = 0;
	virtual void Visit(WithDecl& withDecl) = 0;

}; // class ASTVisitor

class AST
{
public:
	virtual ~AST() {}

	virtual void Accept(ASTVisitor& visitor) = 0;

}; // class AST

class Expr : public AST
{
public:
	Expr() {}

}; // class Expr

class Factor : public Expr
{
public:
	enum class Kind
	{
		Ident,
		Number,
	};

private:
	Kind kind_;
	llvm::StringRef value_;

public:
	Factor(Kind kind, llvm::StringRef value)
		: kind_(kind), value_(value)
	{}

	Kind getKind() const { return kind_; }
	llvm::StringRef getValue() const { return value_; }

	virtual void Accept(ASTVisitor& visitor) override
	{
		visitor.Visit(*this);
	}

}; // class Factor

class BinaryOp : public Expr
{
public:
	enum class Operator
	{
		Add,
		Sub,
		Mul,
		Div,
	};

private:
	Operator op_;	// operator
	Expr* lhs_;		// left hand side
	Expr* rhs_;		// right hand side

public:
	BinaryOp(Operator op, Expr* lhs, Expr* rhs)
		: op_(op), lhs_(lhs), rhs_(rhs)
	{}

	Operator getOperator() const { return op_; }
	Expr* getLHS() const { return lhs_; }
	Expr* getRHS() const { return rhs_; }

	virtual void Accept(ASTVisitor& visitor) override
	{
		visitor.Visit(*this);
	}

}; // class BinaryOp

class WithDecl : public AST
{
	using VarVector = llvm::SmallVector<llvm::StringRef, 8>;

	VarVector vars_;
	Expr* expr_;

public:
	WithDecl(VarVector vars, Expr* expr)
		: vars_(vars), expr_(expr)
	{}

	VarVector::const_iterator begin() const { return vars_.begin(); }
	VarVector::const_iterator end() const { return vars_.end(); }

	const VarVector& getVars() const { return vars_; }
	Expr* getExpr() const { return expr_; }

	virtual void Accept(ASTVisitor& visitor) override
	{
		visitor.Visit(*this);
	}

}; // class WithDecl

#endif // ABSTRACT_SYNTAX_TREE_H
