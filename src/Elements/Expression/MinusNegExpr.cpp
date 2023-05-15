#include "MinusNegExpr.h"

MinusNegExpr::MinusNegExpr(IExpr expr)
:expr(move(expr)){}

void MinusNegExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &MinusNegExpr::getExpr() const{
    return expr;
}

