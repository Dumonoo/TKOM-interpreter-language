# pragma once
#include "IExpression.h"
#include "../../Decimal/decimal.h"
#include "../../Token/TokenType.h"

class LiteralExpr : public IExpression
{
private:
    dec::decimal<MAX_DECIMAL_POINTS> value;

public:
    explicit LiteralExpr(dec::decimal<MAX_DECIMAL_POINTS> value);
    void accept(IVisitor &vis) override;
    dec::decimal<MAX_DECIMAL_POINTS>  getValue() const;
};