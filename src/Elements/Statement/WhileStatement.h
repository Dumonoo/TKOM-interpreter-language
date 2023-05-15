# pragma once
#include "../Expression/IExpression.h"
#include "IStatement.h"
#include <vector>

class WhileStatement : public IStatement
{
private:
    IExpr condition;
    std::vector<IState> instructions;
public:
    WhileStatement(IExpr condition, std::vector<IState> instructions);
    const IExpr &getCondition() const;
    const std::vector<IState> &getInstructions() const;
    void accept(IVisitor &vis) override;
};
