#include <sstream>
#include "ast.hpp"
#include "parser.hpp"

/*
 * Simple template function to convert a value of any type to a string
 * representation.  The type must have an insertion operator (i.e. operator<<).
 */
template <class T>
std::string toString(const T& val) {
  std::ostringstream out;
  out << val;
  return out.str();
}

/*
 * Function to generate GraphView spec for the subtree rooted at any node in
 * an AST.
 *
 * @param node An AST node.
 *
 * @return Returns a string containing a complete GraphView specification to
 *   visualize the AST subtree rooted at node.
 */
llvm::Value* generateGVSpec(ASTNode* node) {
  return node->generateGVSpec();
}

/****************************************************************************
 **
 ** Below is the implementation of generateGVSpec() for each class defined in
 ** ast.hpp.  Please see the documentation in ast.hpp for a desription of
 ** this function.
 **
 ****************************************************************************/

llvm::Value* ASTIdentifier::generateGVSpec() const {
  llvm::Value* val = TheSymbolTable[this->name->c_str()];
  if (!val) {
    std::cerr << "Invalid variable name: " << this->name->c_str() << std::endl;
    return NULL;
  }
  return TheBuilder.CreateLoad(val, this->name->c_str());
}


llvm::Value* ASTFloat::generateGVSpec() const {
  return llvm::ConstantFP::get(TheContext, llvm::APFloat(this->value));
}

/*
llvm::Value* ASTInteger::generateGVSpec(std::string nodeName, std::string& gvSpec) const {
  return llvm::ConstantFP::get(TheContext, llvm::APInt(this->value));
}*/


llvm::Value* ASTBoolean::generateGVSpec() const {
  /*gvSpec += "  " + nodeName
    + " [shape=box,label=\"Boolean: " + toString(this->value) + "\"];\n";*/
}


llvm::Value* ASTBinaryOperatorExpression::generateGVSpec() const {
  llvm::Value* leftValue = this->lhs->generateGVSpec();
	llvm::Value* rightValue = this->rhs->generateGVSpec();
  if (!leftValue || !rightValue) {
    return NULL;
  }
  switch (this->op) {
    case PLUS:
      TheBuilder.CreateFAdd(leftValue, rightValue, "addtmp");
      break;
    case MINUS:
      TheBuilder.CreateFSub(leftValue, rightValue, "subtmp");
      break;
    case TIMES:
      TheBuilder.CreateFMul(leftValue, rightValue, "multmp");
      break;
    case DIVIDEDBY:
      TheBuilder.CreateFDiv(leftValue, rightValue, "divtmp");
      break;
    case EQ:
    leftValue = TheBuilder.CreateFCmpUEQ(leftValue, rightValue, "eqtmp");
    TheBuilder.CreateUIToFP(leftValue, llvm::Type::getFloatTy(TheContext), "booltmp");
      break;
    case NEQ:
    leftValue = TheBuilder.CreateFCmpUNE(leftValue, rightValue, "netmp");
    TheBuilder.CreateUIToFP(leftValue, llvm::Type::getFloatTy(TheContext), "booltmp");
      break;
    case GT:
    leftValue = TheBuilder.CreateFCmpUGT(leftValue, rightValue, "gttmp");
    TheBuilder.CreateUIToFP(leftValue, llvm::Type::getFloatTy(TheContext), "booltmp");
      break;
    case GTE:
    leftValue = TheBuilder.CreateFCmpUGE(leftValue, rightValue, "getmp");
    TheBuilder.CreateUIToFP(leftValue, llvm::Type::getFloatTy(TheContext), "booltmp");
      break;
    case LT:
      leftValue = TheBuilder.CreateFCmpULT(leftValue, rightValue, "lttmp");
      TheBuilder.CreateUIToFP(leftValue, llvm::Type::getFloatTy(TheContext), "booltmp");
      break;
    case LTE:
      leftValue = TheBuilder.CreateFCmpULE(leftValue, rightValue, "letmp");
      TheBuilder.CreateUIToFP(leftValue, llvm::Type::getFloatTy(TheContext), "booltmp");
      break;
    default:
      std::cerr << "Invalid operator:" << op << std::endl;
      return NULL;
    }
}

llvm::AllocaInst* generateEntryBlockAlloca(std::string &name) {
  llvm::Function* currFn =
    TheBuilder.GetInsertBlock()->getParent();
  llvm::IRBuilder<> tmpBuilder(&currFn->getEntryBlock(),
    currFn->getEntryBlock().begin());

  return tmpBuilder.CreateAlloca(llvm::Type::getFloatTy(TheContext), 0, name.c_str());
}

llvm::Value* ASTAssignmentStatement::generateGVSpec() const {
  //llvm::Value* leftValue = this->lhs->generateGVSpec();
	llvm::Value* rightValue = this->rhs->generateGVSpec();
  if (!rightValue) {
    return NULL;
  }
  if ((TheSymbolTable.count(this->lhs->name->c_str())) == 0) {
    // Allocate lhs
    std::string nodeName = this->lhs->name->c_str();
    TheSymbolTable[this->lhs->name->c_str()] = generateEntryBlockAlloca(nodeName);
  }

  return TheBuilder.CreateStore(rightValue, TheSymbolTable[this->lhs->name->c_str()]);
}


llvm::Value* ASTBlock::generateGVSpec() const {
  //gvSpec += "  " + nodeName + " [label=\"Block\"];\n";
  for (int i = 0; i < this->statements.size(); i++) {
    //std::string childNodeName = nodeName + "_" + toString(i);
    //gvSpec += "  " + nodeName + " -> " + childNodeName + ";\n";
    this->statements[i]->generateGVSpec();
  }
}


  llvm::Value* ASTIfStatement::generateGVSpec() const {
  /*std::string conditionNodeName = nodeName + "_cond";
  std::string ifBlockNodeName = nodeName + "_if";
  gvSpec += "  " + nodeName + " [label=\"If\"];\n";
  gvSpec += "  " + nodeName + " -> " + conditionNodeName + ";\n";
  this->condition->generateGVSpec(conditionNodeName, gvSpec);
  gvSpec += "  " + nodeName + " -> " + ifBlockNodeName + ";\n";
  this->ifBlock->generateGVSpec(ifBlockNodeName, gvSpec);

  if (this->elseBlock) {
    std::string elseBlockNodeName = nodeName + "_else";
    gvSpec += "  " + nodeName + " -> " + elseBlockNodeName + ";\n";
    this->elseBlock->generateGVSpec(elseBlockNodeName, gvSpec);
  }*/
}


llvm::Value* ASTWhileStatement::generateGVSpec() const {
/*  std::string conditionNodeName = nodeName + "_cond";
  std::string whileBlockNodeName = nodeName + "_while";
  gvSpec += "  " + nodeName + " [label=\"While\"];\n";
  gvSpec += "  " + nodeName + " -> " + conditionNodeName + ";\n";
  this->condition->generateGVSpec(conditionNodeName, gvSpec);
  gvSpec += "  " + nodeName + " -> " + whileBlockNodeName + ";\n";
  this->whileBlock->generateGVSpec(whileBlockNodeName, gvSpec);*/
}


llvm::Value* ASTBreakStatement::generateGVSpec() const {
  //gvSpec += "  " + nodeName + " [label=\"Break\"];\n";
}

void generateObjCode(const std::string& filename) {
  std::string targetTriple = llvm::sys::getDefaultTargetTriple();

  llvm::InitializeAllTargetInfos();
  llvm::InitializeAllTargets();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmParsers();
  llvm::InitializeAllAsmPrinters();

  std::string error;
  const llvm::Target* target =
    llvm::TargetRegistry::lookupTarget(targetTriple, error);
  if (!target) {
    std::cerr << error << std::endl;
  } else {
    std::string cpu = "generic";
    std::string features = "";
    llvm::TargetOptions options;
    llvm::TargetMachine* targetMachine =
      target->createTargetMachine(targetTriple, cpu, features,
        options, llvm::Optional<llvm::Reloc::Model>());

    TheModule->setDataLayout(targetMachine->createDataLayout());
    TheModule->setTargetTriple(targetTriple);

    std::error_code ec;
    llvm::raw_fd_ostream file(filename, ec, llvm::sys::fs::F_None);
    if (ec) {
      std::cerr << "Could not open output file: " << ec.message() << std::endl;
    } else {
      llvm::TargetMachine::CodeGenFileType type = llvm::TargetMachine::CGFT_ObjectFile;
      llvm::legacy::PassManager pm;
      if (targetMachine->addPassesToEmitFile(pm, file, NULL, type)) {
        std::cerr << "Unable to emit target code" << std::endl;
      } else {
        pm.run(*TheModule);
        file.close();
      }
    }
  }
}

extern int yylex();

extern ASTBlock* programBlock;

void doOptimizations(llvm::Function* fn) {
  llvm::legacy::FunctionPassManager* fpm =
  new llvm::legacy::FunctionPassManager(TheModule);

  fpm->add(llvm::createPromoteMemoryToRegisterPass());
  // fpm->add(llvm::createInstructionCombiningPass());
  fpm->add(llvm::createReassociatePass());
  fpm->add(llvm::createGVNPass());
  fpm->add(llvm::createCFGSimplificationPass());

  fpm->run(*fn);
}

int main(int argc, char const *argv[]) {
  if (!yylex()) {
    TheModule = new llvm::Module("Python compiler", TheContext);

    llvm::FunctionType* fooFnType = llvm::FunctionType::get(
      llvm::Type::getFloatTy(TheContext), false
    );

    llvm::Function* fooFn = llvm::Function::Create(
      fooFnType,
      llvm::GlobalValue::ExternalLinkage,
      "main",
      TheModule
    );

    llvm::BasicBlock* entryBlock =
    llvm::BasicBlock::Create(TheContext, "entry", fooFn);
    TheBuilder.SetInsertPoint(entryBlock);

    if (programBlock) {
      generateGVSpec(programBlock);
    }

    TheBuilder.CreateRetVoid();

    if(argv[1] != NULL)
    {
      std::string s = argv[1];
      if(s == "-O") {
        doOptimizations(fooFn);
      }
    }

    llvm::verifyFunction(*fooFn);
    TheModule->print(llvm::outs(), NULL);


    std::string filename = "output.o";
    generateObjCode(filename);

    delete TheModule;
  }
}
