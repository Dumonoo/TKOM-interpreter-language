#include "Parameter.h"
#include "Type.h"
using namespace std;

Parameter::Parameter(Type type, const string &identifier)
: type(type), identifier(identifier)
{}

void Parameter::accept(IVisitor &v)
{
    v.visit(*this);
}

string Parameter::getIdentifier()
{
    return identifier;
}

Type Parameter::getType()
{
    return type;
}