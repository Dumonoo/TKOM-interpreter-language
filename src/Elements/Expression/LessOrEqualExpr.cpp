#include "LessOrEqualExpr.h"

LessOrEqualExpr::LessOrEqualExpr(IExpr left, IExpr right)
:leftExpr(move(left)), rightExpr(move(right)){}

void LessOrEqualExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &LessOrEqualExpr::getLeft() const{
    return leftExpr;
}

const IExpr &LessOrEqualExpr::getRight() const{
    return rightExpr;
}