# pragma once
#include "IExpression.h"
#include <string>

class ConversionExpr : public IExpression
{
private:
    IExpr expr;
    std::string curVariableIdentifier;

public:
    ConversionExpr(IExpr expr, const std::string &identifier);
    void accept(IVisitor &vis) override;
    std::string getCurrencyVariableName() const;
    const IExpr &getExpr() const;
};