#include "OrExpr.h"

OrExpr::OrExpr(IExpr left, IExpr right)
    : leftExpr(move(left)), rightExpr(move(right)) {}

void OrExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &OrExpr::getLeft() const{
    return leftExpr;
}

const IExpr &OrExpr::getRight() const{
    return rightExpr;
}