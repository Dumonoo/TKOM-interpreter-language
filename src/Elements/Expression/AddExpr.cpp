#include "AddExpr.h"

using namespace std;

AddExpr::AddExpr(IExpr left, IExpr right)
    : leftExpr(move(left)), rightExpr(move(right)) {}

void AddExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &AddExpr::getLeft() const{
    return leftExpr;
}

const IExpr &AddExpr::getRight() const{
    return rightExpr;
}