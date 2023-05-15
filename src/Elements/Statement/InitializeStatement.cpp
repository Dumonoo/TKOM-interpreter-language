#include "InitializeStatement.h"

using namespace std;

InitializeStatement::InitializeStatement(Type type, const string &identifier, IExpr initialValue)
    : type(type), identifier(identifier), initialValue(move(initialValue)) {}

void InitializeStatement::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &InitializeStatement::getInitialValue() const
{
    return initialValue;
}

Type InitializeStatement::getType() const
{
    return type;
}

string InitializeStatement::getVariableName() const
{
    return identifier;
}