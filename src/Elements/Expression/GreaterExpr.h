# pragma once
#include "IExpression.h"

class GreaterExpr : public IExpression
{
private:
    IExpr leftExpr;
    IExpr rightExpr;

public:
    GreaterExpr(IExpr left, IExpr right);
    void accept(IVisitor &vis) override;
    const IExpr &getLeft() const;
    const IExpr &getRight() const;
};