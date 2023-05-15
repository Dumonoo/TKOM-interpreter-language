#include "Program.h"
#include <iostream>

using namespace std;

Program::Program(std::unordered_map<std::string, std::unique_ptr<FunctionDefinition>> functions)
    : functions(move(functions))
{
}

std::unordered_map<std::string, std::unique_ptr<FunctionDefinition>> const& Program::getFunctions() const
{
    return functions;
}

void Program::addEmbededFunctions()
{
    if(!functions.insert({"print", make_unique<EmbeddedFunction>(Type::VOID, "print",std::vector<Parameter>(),std::vector<IState>(), true)}).second)
    {
        RedefinitionOf err("embeded print");
        ErrorReporter::reportError(err);
        throw FatalError("addEmbededFunctions");
    }
    if(!functions.insert({"scanNum", make_unique<EmbeddedFunction>(Type::NUM, "scanNum",std::vector<Parameter>(),std::vector<IState>(), false)}).second)
    {
        RedefinitionOf err("embeded scanNum");
        ErrorReporter::reportError(err);
        throw FatalError("addEmbededFunctions");
    }
    if(!functions.insert({"scanCur", make_unique<EmbeddedFunction>(Type::CUR, "scanCur",std::vector<Parameter>(),std::vector<IState>(), false)}).second)
    {
        RedefinitionOf err("embeded scanCur");
        ErrorReporter::reportError(err);
        throw FatalError("addEmbededFunctions");
    }
}