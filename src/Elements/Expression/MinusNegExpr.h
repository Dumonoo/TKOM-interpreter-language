# pragma once
#include "IExpression.h"

class MinusNegExpr : public IExpression
{
private:
    IExpr expr;

public:
    explicit MinusNegExpr(IExpr expr);
    void accept(IVisitor &vis) override;
    const IExpr &getExpr() const;
};
