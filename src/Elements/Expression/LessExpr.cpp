#include "LessExpr.h"

LessExpr::LessExpr(IExpr left, IExpr right)
    : leftExpr(move(left)), rightExpr(move(right)) {}

void LessExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &LessExpr::getLeft() const{
    return leftExpr;
}

const IExpr &LessExpr::getRight() const{
    return rightExpr;
}