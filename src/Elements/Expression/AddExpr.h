# pragma once
#include "IExpression.h"

class AddExpr : public IExpression
{
private:
    IExpr leftExpr;
    IExpr rightExpr;

public:
    AddExpr(IExpr left, IExpr right);
    void accept(IVisitor &vis) override;
    const IExpr &getLeft() const;
    const IExpr &getRight() const;
};