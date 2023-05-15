# pragma once
#include "IExpression.h"

class AndExpr : public IExpression
{
private:
    IExpr leftExpr;
    IExpr rightExpr;

public:
    AndExpr(IExpr left, IExpr right);
    const IExpr &getLeft() const;
    const IExpr &getRight() const;
    void accept(IVisitor &vis) override;
};