#include "ReturnStatement.h"

using namespace std;

ReturnStatement::ReturnStatement(IExpr retExpr)
:returnExpression(move(retExpr)){}

void ReturnStatement::accept(IVisitor &v)
{
    v.visit(*this);
}

const std::optional<IExpr> &ReturnStatement::getReturnExpression() const{
    return returnExpression;
}