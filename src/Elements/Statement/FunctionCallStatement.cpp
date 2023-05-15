#include "FunctionCallStatement.h"
#include <iostream>

using namespace std;

FunctionCallStatement::FunctionCallStatement(const string &identifier, vector<IExpr> arguments)
:identifier(identifier), arguments(move(arguments)){}

void FunctionCallStatement::accept(IVisitor &v)
{
    v.visit(*this);
}

const std::vector<IExpr> &FunctionCallStatement::getArguments() const{
    return arguments;
}

std::string FunctionCallStatement::getIdentifier() const{
    return identifier;
}