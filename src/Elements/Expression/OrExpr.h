# pragma once
#include "IExpression.h"

class OrExpr : public IExpression
{
private:
    IExpr leftExpr;
    IExpr rightExpr;

public:
    OrExpr(IExpr left, IExpr right);
    const IExpr &getLeft() const;
    const IExpr &getRight() const;
    void accept(IVisitor &vis) override;
};
