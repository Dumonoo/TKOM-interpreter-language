# pragma once
#include "IExpression.h"

class MultExpr : public IExpression
{
private:
    IExpr leftExpr;
    IExpr rightExpr;

public:
    MultExpr(IExpr left, IExpr right);
    void accept(IVisitor &vis) override;
    const IExpr &getLeft() const;
    const IExpr &getRight() const;
};