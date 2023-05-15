#include "FunCallExpr.h"

using namespace std;

FunCallExpr::FunCallExpr(const string &identifier, vector<IExpr> arguments)
    : identifier(identifier), arguments(move(arguments)) {}

void FunCallExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const std::vector<IExpr> &FunCallExpr::getArguments() const{
    return arguments;
}

std::string FunCallExpr::getFunctionIdentifer() const{
    return identifier;
}