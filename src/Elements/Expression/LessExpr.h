# pragma once
#include "IExpression.h"

class LessExpr : public IExpression
{
private:
    IExpr leftExpr;
    IExpr rightExpr;

public:
    LessExpr(IExpr left, IExpr right);
    void accept(IVisitor &vis) override;
    const IExpr &getLeft() const;
    const IExpr &getRight() const;
};