#include "GreaterExpr.h"

GreaterExpr::GreaterExpr(IExpr left, IExpr right)
    : leftExpr(move(left)), rightExpr(move(right)) {}

void GreaterExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &GreaterExpr::getLeft() const{
    return leftExpr;
}

const IExpr &GreaterExpr::getRight() const{
    return rightExpr;
}