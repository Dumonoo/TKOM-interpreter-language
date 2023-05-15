# pragma once
#include <vector>
#include <optional>
#include <unordered_map>
#include <string>
#include <algorithm>
#include "../Lexer/Lexer.h"
#include "../Token/Token.h"
#include "../Token/TokenType.h"
#include "../Decimal/decimal.h"

class ConfigParser
{
private:
    Lexer &lexer;
    Token currentToken;
    std::vector<std::string> configHeader;
    std::unordered_map<std::string, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>>> curriencies;

    void getNextToken();
    bool parseConfigHeader();
    bool parseCurrencyLines();
    bool tryparseCurrencyLine();
    bool isTokenCorrect(TokenType type) const;
    bool checkAndConsume(TokenType type);
    
public:
    bool parseConfigFile();
    explicit ConfigParser(Lexer &lexer);
    std::optional<std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>>> getDenominations( const std::string &currency);
    std::unordered_map<std::string, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>>> getCurrencyMap() const;

};