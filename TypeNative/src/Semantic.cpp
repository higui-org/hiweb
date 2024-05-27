#include "Semantic.h"

namespace
{
	class DeclChecker : public ASTVisitor
	{
		llvm::StringSet<> scope_;
		bool has_error_;

		enum class ErrorType
		{
			Twice, 
			Not,
		};

		void Error(ErrorType type, const llvm::StringRef var_name)
		{
			llvm::errs() << "Variable " << var_name << " "
				<< (type == ErrorType::Twice ? "declared twice" : "not declared") << "\n";

			has_error_ = true;
		}

	public:
		DeclChecker() : has_error_(false) {}

		bool HasError() const { return has_error_; }

		virtual void Visit(Factor& node) override
		{
			if (node.getKind() == Factor::Kind::Ident)
			{
				if (scope_.find(node.getValue()) == scope_.end())
					Error(ErrorType::Not, node.getValue());
			}
		}

		virtual void Visit(BinaryOp& node) override
		{
			if (node.getLHS())
				node.getLHS()->Accept(*this);
			else
				has_error_ = true;

			if (node.getRHS())
				node.getRHS()->Accept(*this);
			else
				has_error_ = true;
		}

		virtual void Visit(WithDecl& node) override
		{
			for (auto i = node.begin(), e = node.end(); i != e; ++i)
			{
				if (!scope_.insert(*i).second)
					Error(ErrorType::Twice, *i);
			}

			if (node.getExpr())
				node.getExpr()->Accept(*this);
			else
				has_error_ = true;
		}
	}; // class DeclChecker

} // namespace

bool Semantic::Check(AST* tree)
{
	if (!tree)
		return false;

	DeclChecker checker;
	tree->Accept(checker);
	return checker.HasError();
}