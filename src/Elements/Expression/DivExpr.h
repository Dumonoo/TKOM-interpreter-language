# pragma once
#include "IExpression.h"

class DivExpr : public IExpression
{
private:
    IExpr leftExpr;
    IExpr rightExpr;

public:
    DivExpr(IExpr left, IExpr right);
    void accept(IVisitor &vis) override;
    const IExpr &getLeft() const;
    const IExpr &getRight() const;
};