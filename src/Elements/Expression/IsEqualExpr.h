# pragma once
#include "IExpression.h"

class IsEqualExpr : public IExpression
{
private:
    IExpr leftExpr;
    IExpr rightExpr;

public:
    IsEqualExpr(IExpr left, IExpr right);
    const IExpr &getLeft() const;
    const IExpr &getRight() const;
    void accept(IVisitor &vis) override;
};