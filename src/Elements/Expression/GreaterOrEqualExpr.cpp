#include "GreaterOrEqualExpr.h"

GreaterOrEqualExpr::GreaterOrEqualExpr(IExpr left, IExpr right)
    : leftExpr(move(left)), rightExpr(move(right)) {}

void GreaterOrEqualExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &GreaterOrEqualExpr::getLeft() const{
    return leftExpr;
}

const IExpr &GreaterOrEqualExpr::getRight() const{
    return rightExpr;
}