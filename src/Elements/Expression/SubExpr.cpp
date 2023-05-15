#include "SubExpr.h"

SubExpr::SubExpr(IExpr left, IExpr right)
    : leftExpr(move(left)), rightExpr(move(right)) {}

void SubExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &SubExpr::getLeft() const{
    return leftExpr;
}

const IExpr &SubExpr::getRight() const{
    return rightExpr;
}