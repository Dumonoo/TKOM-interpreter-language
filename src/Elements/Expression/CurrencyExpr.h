# pragma once
#include "IExpression.h"
#include <string>
#include <unordered_map>
#include "../../Decimal/decimal.h"
#include "../../Token/TokenType.h"

class CurrencyExpr : public IExpression
{
private:
    IExpr expr;
    std::string currencyIdentifier;
    std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> denominations;
public:
    CurrencyExpr(IExpr expr, const std::string &identifier, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> denominations);
    void accept(IVisitor &vis) override;
    
    std::string getCurrencyIdentifier() const;
    std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> getDenominations() const;
    const IExpr &getExpr() const;
    dec::decimal<MAX_DECIMAL_POINTS> getMultiplier(std::string fromCurrency) const;
};