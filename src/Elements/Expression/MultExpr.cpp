#include "MultExpr.h"

MultExpr::MultExpr(IExpr left, IExpr right)
    : leftExpr(move(left)), rightExpr(move(right)) {}

void MultExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &MultExpr::getLeft() const{
    return leftExpr;
}

const IExpr &MultExpr::getRight() const{
    return rightExpr;
}