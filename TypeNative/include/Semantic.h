#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "AST.h"
#include "Lexer.h"

#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/StringSet.h"

class Semantic
{
public:
	bool Check(AST* tree);

}; // class Semantic

#endif // SEMANTIC_H