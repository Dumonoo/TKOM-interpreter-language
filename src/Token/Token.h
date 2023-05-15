#pragma once
#include <variant>
#include <string>
#include <unordered_map>
#include "TokenType.h"
#include "../Decimal/decimal.h"


class Token
{
private:
    TokenType type;
    std::variant<std::string, dec::decimal<MAX_DECIMAL_POINTS>> value;
    Position position;
    static std::unordered_map<TokenType, std::string> logMap;

public:
    Token();
    ~Token() = default;
    Token(TokenType typ, std::string val, Position pos);
    Token(TokenType typ, dec::decimal<MAX_DECIMAL_POINTS> val, Position pos);

    TokenType getType() const;
    std::string getString() const;
    dec::decimal<MAX_DECIMAL_POINTS> getDecimal() const;
    Position getPosition() const;
    bool isETX()const;
    
    // Only for presentation purposes.
    static void initLogger();
    void logToken();
};
