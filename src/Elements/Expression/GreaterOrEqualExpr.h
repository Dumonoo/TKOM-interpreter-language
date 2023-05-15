# pragma once
#include "IExpression.h"

class GreaterOrEqualExpr : public IExpression
{
private:
    IExpr leftExpr;
    IExpr rightExpr;

public:
    GreaterOrEqualExpr(IExpr left, IExpr right);
    void accept(IVisitor &vis) override;
    const IExpr &getLeft() const;
    const IExpr &getRight() const;
};
