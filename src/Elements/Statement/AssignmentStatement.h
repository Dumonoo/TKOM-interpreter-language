# pragma once
#include "../Expression/IExpression.h"
#include "IStatement.h"
#include <string>

class AssignmentStatement : public IStatement
{
private:
    std::string identifier;
    IExpr toAssign;

public:
    AssignmentStatement(const std::string &identifier, IExpr toAssign);
    const IExpr &getExpr() const;
    std::string getIdentifier() const;
    void accept(IVisitor &vis) override;
};