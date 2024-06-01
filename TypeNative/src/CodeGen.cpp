#include "CodeGen.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

/**
 * This class is a visitor that traverses the AST and generates LLVM IR.
*/
namespace {
class ToIRVisitor : public ASTVisitor
	{
		Module* module_;
		IRBuilder<> builder_;
		Type* void_type_;
		Type* int32_type_;
		PointerType* ptr_type_;
		Constant* int32_zero_;

		Value* value_;
		StringMap<Value*> name_map_;

	public:
		ToIRVisitor(Module* module)
			: module_(module), builder_(module->getContext())
		{
			void_type_ = Type::getVoidTy(module->getContext());
			int32_type_ = Type::getInt32Ty(module->getContext());
			ptr_type_ = PointerType::get(int32_type_, 0);
			int32_zero_ = ConstantInt::get(int32_type_, 0);
		}

		void run(AST* tree)
		{
			FunctionType* main_func_type = FunctionType::get(
				int32_type_, {int32_type_, ptr_type_}, false);

			Function* main_func = Function::Create(
				main_func_type, GlobalValue::ExternalLinkage, "main", module_);

			BasicBlock* basic_block = BasicBlock::Create(
				module_->getContext(), "entry", main_func);

			builder_.SetInsertPoint(basic_block);

			tree->accept(*this);

			FunctionType* calc_write_func_type = FunctionType::get(
				void_type_, {int32_type_}, false);

			Function* calc_write_func = Function::Create(
				calc_write_func_type, GlobalValue::ExternalLinkage, "calc_write", module_);

			builder_.CreateCall(calc_write_func_type, calc_write_func, { value_ });

			builder_.CreateRet(int32_zero_);
		}

		virtual void visit(WithDecl& node) override
		{
			FunctionType* read_func_type =
				FunctionType::get(int32_type_, { ptr_type_ }, false);

			Function* read_func = Function::Create(
				read_func_type, GlobalValue::ExternalLinkage, "calc_read", module_);

			for (auto it = node.begin(), end = node.end(); it != end; ++it)
			{
				StringRef var = *it;

				Constant* str_text = 
					ConstantDataArray::getString(module_->getContext(), var);

				GlobalVariable* str_var = new GlobalVariable(
					*module_, 
					str_text->getType(), 
					true,
					GlobalValue::ExternalLinkage, 
					str_text, 
					Twine(var).concat(".str"));

				CallInst* call_inst = 
					builder_.CreateCall(read_func_type, read_func, { str_var });

				name_map_[var] = call_inst;
			}

			node.getExpr()->accept(*this);
		}

		virtual void visit(Factor& node) override
		{
			if (node.getKind() == Factor::Ident)
			{
				value_ = name_map_[node.getVal()];
			}
			else
			{
				int int_value;
				node.getVal().getAsInteger(10, int_value);
				value_ = ConstantInt::get(int32_type_, int_value, true);
			}
		}

		virtual void visit(BinaryOp& node) override
		{
			node.getLeft()->accept(*this);
			Value* left = value_;

			node.getRight()->accept(*this);
			Value* right = value_;

			switch (node.getOperator())
			{
			case BinaryOp::Operator::Plus:
				value_ = builder_.CreateNSWAdd(left, right);
				break;
			case BinaryOp::Operator::Minus:
				value_ = builder_.CreateNSWSub(left, right);
				break;
			case BinaryOp::Operator::Mul:
				value_ = builder_.CreateNSWMul(left, right);
				break;
			case BinaryOp::Operator::Div:
				value_ = builder_.CreateSDiv(left, right);
				break;
			}
		}
	};
} // namespace

void CodeGen::compile(AST *Tree) {
  LLVMContext Ctx;
  Module *M = new Module("calc.expr", Ctx);
  ToIRVisitor ToIR(M);
  ToIR.run(Tree);
  M->print(outs(), nullptr);
}