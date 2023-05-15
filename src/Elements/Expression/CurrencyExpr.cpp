#include "CurrencyExpr.h"

using namespace std;

CurrencyExpr::CurrencyExpr(IExpr expr, const std::string &identifier, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> denominations)
    : expr(move(expr)), currencyIdentifier(identifier), denominations(denominations){}

void CurrencyExpr::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &CurrencyExpr::getExpr() const{
    return expr;
}

std::string CurrencyExpr::getCurrencyIdentifier() const
{
    return currencyIdentifier;
}

std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> CurrencyExpr::getDenominations()const{
    return denominations;
}

dec::decimal<MAX_DECIMAL_POINTS> CurrencyExpr::getMultiplier(std::string fromCurrency) const
{
    auto multiplyier = denominations.find(fromCurrency);
    if(multiplyier == denominations.end())
    {
        // throw
    }
    return multiplyier->second;
}