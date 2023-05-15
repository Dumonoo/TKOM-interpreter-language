# pragma once
#include "IExpression.h"

class SubExpr : public IExpression
{
private:
    IExpr leftExpr;
    IExpr rightExpr;

public:
    SubExpr(IExpr left, IExpr right);
    void accept(IVisitor &vis) override;
    const IExpr &getLeft() const;
    const IExpr &getRight() const;
};