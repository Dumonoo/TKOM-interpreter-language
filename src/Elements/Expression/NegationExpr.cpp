#include "NegationExpr.h"

NegationExpr::NegationExpr(IExpr expr)
:expr(move(expr)){}

void NegationExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &NegationExpr::getExpr() const{
    return expr;
}