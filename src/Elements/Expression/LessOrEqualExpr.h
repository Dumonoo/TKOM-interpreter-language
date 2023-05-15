# pragma once
#include "IExpression.h"

class LessOrEqualExpr : public IExpression
{
private:
    IExpr leftExpr;
    IExpr rightExpr;

public:
    LessOrEqualExpr(IExpr left, IExpr right);
    void accept(IVisitor &vis) override;
    const IExpr &getLeft() const;
    const IExpr &getRight() const;
};