#include "AssignmentStatement.h"



using namespace std;

AssignmentStatement::AssignmentStatement(const string &identifier, IExpr toAssign)
:identifier(identifier), toAssign(move(toAssign)){}

void AssignmentStatement::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &AssignmentStatement::getExpr() const{
    return toAssign;
}

string AssignmentStatement::getIdentifier() const
{
    return identifier;
}