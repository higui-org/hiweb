#ifndef CODEGEN_H
#define CODEGEN_H

#include "AST.h"

class CodeGen
{
public:
	void Generate(AST* tree);
};

#endif // CODEGEN_H