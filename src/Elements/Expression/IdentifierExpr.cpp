#include "IdentifierExpr.h"

using namespace std;

IdentifierExpr::IdentifierExpr(const string &identifier)
    : identifier(identifier) {}

void IdentifierExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

std::string IdentifierExpr::getIdentifier() const
{
    return identifier;
}