#pragma once
#include <variant>
#include <optional>
#include <string>
#include "../Type.h"
#include "../../Decimal/decimal.h"
#include "../../Token/TokenType.h"


class Variable{
private:
    Type type;
    std::variant<dec::decimal<MAX_DECIMAL_POINTS>, std::string> value;
    // dec::decimal<MAX_DECIMAL_POINTS> value;
    std::optional<std::string> currencyIdentifier;
    std::optional<std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>>> denominations;
public:
    Variable(Type type, dec::decimal<MAX_DECIMAL_POINTS> value);
    Variable(Type type, dec::decimal<MAX_DECIMAL_POINTS> value, const std::string& currencyIdentifier, const std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> &denaminations);
    explicit Variable(Type type);
    Variable(Type type, std::string value);

    void setValue(dec::decimal<MAX_DECIMAL_POINTS> value);
    void setValue(dec::decimal<MAX_DECIMAL_POINTS> value, const std::string& currencyIdentifier, const std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> &denaminations);
    Type getType() const;
    
    std::variant<dec::decimal<MAX_DECIMAL_POINTS>, std::string> getValue() const;

    dec::decimal<MAX_DECIMAL_POINTS> getNumValue() const;
    
    std::string getCurrencyIdentifier() const;
    std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> getDenominations() const;
};