# pragma once
#include "../Expression/IExpression.h"
#include "IStatement.h"
#include <vector>
#include <optional>

class ReturnStatement : public IStatement
{
private:
    std::optional<IExpr> returnExpression;
public:
    ReturnStatement() = default;
    explicit ReturnStatement(IExpr retExpr);
    const std::optional<IExpr> &getReturnExpression() const;
    void accept(IVisitor &vis) override;
};