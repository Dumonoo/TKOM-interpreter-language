#include "IsEqualExpr.h"

IsEqualExpr::IsEqualExpr(IExpr left, IExpr right)
    : leftExpr(move(left)), rightExpr(move(right)) {}

void IsEqualExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &IsEqualExpr::getLeft() const{
    return leftExpr;
}

const IExpr &IsEqualExpr::getRight() const{
    return rightExpr;
}