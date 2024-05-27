#include "CodeGen.h"
#include "Parser.h"
#include "Semantic.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"

static llvm::cl::opt<std::string> input(
	llvm::cl::Positional,
	llvm::cl::desc("<input expression>"), 
	llvm::cl::Required
);

int main(int argc, char** argv)
{
	llvm::InitLLVM X(argc, argv);

	llvm::cl::ParseCommandLineOptions(argc, argv);

	Lexer lexer(input);
	Parser parser(lexer);
	std::unique_ptr<AST> tree = parser.Parse();

	if (!tree || parser.HasError())
	{
		llvm::errs() << "Error: failed to parse input. Syntax errors occured\n";
		return 1;
	}

	Semantic semantic;
	if (semantic.Check(tree.get()))
	{
		llvm::errs() << "Error: failed to check semantics\n";
		return 1;
	}

	CodeGen codegen;
	codegen.Generate(tree.get());

	return 0;
}