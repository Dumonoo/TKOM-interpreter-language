# pragma once
#include "IExpression.h"

class NegationExpr : public IExpression
{
private:
    IExpr expr;

public:
    explicit NegationExpr(IExpr expr);
    const IExpr &getExpr() const;
    void accept(IVisitor &vis) override;
};
