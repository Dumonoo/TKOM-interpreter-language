#include "ConversionExpr.h"

using namespace std;

ConversionExpr::ConversionExpr(IExpr expr, const string &identifier)
    : expr(move(expr)), curVariableIdentifier(identifier) {}

void ConversionExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &ConversionExpr::getExpr() const{
    return expr;
}

std::string ConversionExpr::getCurrencyVariableName() const
{
    return curVariableIdentifier;
}