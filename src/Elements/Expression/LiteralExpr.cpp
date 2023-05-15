#include "LiteralExpr.h"

using namespace dec;

LiteralExpr::LiteralExpr(decimal<MAX_DECIMAL_POINTS> value)
    : value(value) {}

void LiteralExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

dec::decimal<MAX_DECIMAL_POINTS> LiteralExpr::getValue() const
{
    return value;
}