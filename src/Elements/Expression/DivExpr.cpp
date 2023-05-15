#include "DivExpr.h"

using namespace std;

DivExpr::DivExpr(IExpr left, IExpr right)
    : leftExpr(move(left)), rightExpr(move(right)) {}

void DivExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &DivExpr::getLeft() const{
    return leftExpr;
}

const IExpr &DivExpr::getRight() const{
    return rightExpr;
}