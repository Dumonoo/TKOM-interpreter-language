#include "NotEqualExpr.h"

NotEqualExpr::NotEqualExpr(IExpr left, IExpr right)
:leftExpr(move(left)), rightExpr(move(right)){}

void NotEqualExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &NotEqualExpr::getLeft() const{
    return leftExpr;
}

const IExpr &NotEqualExpr::getRight() const{
    return rightExpr;
}