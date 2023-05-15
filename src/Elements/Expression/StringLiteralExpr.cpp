#include "StringLiteralExpr.h"
#include <iostream>

using namespace std;

StringLiteralExpr::StringLiteralExpr(const string &stringLiteral)
    : stringLiteral(stringLiteral)
{
}
void StringLiteralExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

std::string StringLiteralExpr::getStringLiteral() const
{
    return stringLiteral;
}