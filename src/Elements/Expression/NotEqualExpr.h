# pragma once
#include "IExpression.h"

class NotEqualExpr : public IExpression
{
private:
    IExpr leftExpr;
    IExpr rightExpr;

public:
    NotEqualExpr(IExpr left, IExpr right);
    const IExpr &getLeft() const;
    const IExpr &getRight() const;
    void accept(IVisitor &vis) override;
};