# pragma once
#include "../Expression/IExpression.h"
#include "IStatement.h"
#include <vector>

class IfStatement : public IStatement
{
private:
    IExpr condition;
    std::vector<IState> ifInstructions;
    std::vector<IState> elseInstructions;

public:
    IfStatement(IExpr condition, std::vector<IState> ifInstructions);
    IfStatement(IExpr condition, std::vector<IState> ifInstructions, std::vector<IState> elseInstructions);
    const IExpr &getCondition() const;
    const std::vector<IState> &getIfInstructions() const;
    const std::vector<IState> &getElseInstructions() const;
    void accept(IVisitor &vis) override;
};
