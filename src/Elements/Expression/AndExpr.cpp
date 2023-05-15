#include "AndExpr.h"

using namespace std;

AndExpr::AndExpr(IExpr left, IExpr right)
:leftExpr(move(left)), rightExpr(move(right)){}

void AndExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &AndExpr::getLeft() const{
    return leftExpr;
}

const IExpr &AndExpr::getRight() const{
    return rightExpr;
}