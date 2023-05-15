#include "Variable.h"

Variable::Variable(Type type)
    : type(type) {}

Variable::Variable(Type type, dec::decimal<MAX_DECIMAL_POINTS> value)
    : type(type), value(value)
{
}

Variable::Variable(Type type, dec::decimal<MAX_DECIMAL_POINTS> value, const std::string &currencyIdentifier, const std::unordered_map<std::string, dec::decimal<MAX_DECIMAL_POINTS>> &denaminations)
    : type(type), value(value), currencyIdentifier(currencyIdentifier), denominations(denaminations)
{
}

Variable::Variable(Type type, std::string value)
    : type(type), value(value)
{
}

Type Variable::getType() const
{
    return type;
}

void Variable::setValue(dec::decimal<MAX_DECIMAL_POINTS> val)
{
    this->value = val;
}

void Variable::setValue(dec::decimal<MAX_DECIMAL_POINTS> val, const std::string &curIdent, const std::unordered_map<std::string, dec::decimal<MAX_DECIMAL_POINTS>> &den)
{
    this->value = val;
    this->currencyIdentifier = curIdent;
    this->denominations = den;
}

std::variant<dec::decimal<MAX_DECIMAL_POINTS>, std::string> Variable::getValue() const
{
    return value;
}

dec::decimal<MAX_DECIMAL_POINTS> Variable::getNumValue() const
{
    return get<dec::decimal<MAX_DECIMAL_POINTS>>(value);
}

std::string Variable::getCurrencyIdentifier() const
{
    return currencyIdentifier.value();
}

std::unordered_map<std::string, dec::decimal<MAX_DECIMAL_POINTS>> Variable::getDenominations() const
{
    return denominations.value();
}
