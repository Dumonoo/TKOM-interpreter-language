# pragma once
#include "../Expression/IExpression.h"
#include "IStatement.h"
#include <vector>
#include <string>

class FunctionCallStatement : public IStatement
{
private:
    std::string identifier;
    std::vector<IExpr> arguments;

public:
    FunctionCallStatement(const std::string &identifier, std::vector<IExpr> arguments);
    const std::vector<IExpr> &getArguments() const;
    std::string getIdentifier() const;
    void accept(IVisitor &vis) override;
};