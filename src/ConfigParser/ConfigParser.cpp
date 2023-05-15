#include "ConfigParser.h"

using namespace std;

ConfigParser::ConfigParser(Lexer &lexer)
    : lexer(lexer)
{
    getNextToken();
}

void ConfigParser::getNextToken()
{
    currentToken = lexer.getNextToken();
    while (currentToken.getType() == TokenType::COMMENT_TOKEN)
    {
        currentToken = lexer.getNextToken();
    }
}

bool ConfigParser::isTokenCorrect(TokenType type) const
{
    if (currentToken.getType() != type)
        return false;
    return true;
}

bool ConfigParser::checkAndConsume(TokenType type)
{
    if (!isTokenCorrect(type))
        return false;
    getNextToken();
    return true;
}

// configfile = headerCurrency, {currencyLine};
bool ConfigParser::parseConfigFile()
{
    if (!parseConfigHeader())
    {
        MissingConfig err;
        ErrorReporter::reportWarning(err);
        ConfigExample err2;
        ErrorReporter::reportWarning(err2);
        return false;
    }
    while (tryparseCurrencyLine())
        ;
    if (configHeader.size() != curriencies.size())
    {
        MissingDenaminationValues err(configHeader.size(), curriencies.size());
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        ConfigExample err2;
        ErrorReporter::reportError(err2);
        throw FatalConfigError("parseConfigFile");
    }
    return true;
}

// headerCurrency =  "@", currency, {currency}, ";";
bool ConfigParser::parseConfigHeader()
{
    if (!checkAndConsume(TokenType::AT_TOKEN))
        return false;
    while (isTokenCorrect(TokenType::IDENTIFIER_TOKEN))
    {
        string newCurrency = currentToken.getString();
        if (find(configHeader.begin(), configHeader.end(), newCurrency) != configHeader.end())
        {
            HeaderDuplicate err(newCurrency);
            ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
            ConfigExample err2;
            ErrorReporter::reportError(err2);
            throw FatalConfigError("parseConfigHeader");
        }
        configHeader.push_back(newCurrency);
        getNextToken();
    }
    if (!checkAndConsume(TokenType::SEMICOLON_TOKEN))
    {
        std::vector<TokenType> expectedTypes = {};
        MissingElementAfter err(";", expectedTypes);
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        ConfigExample err2;
        ErrorReporter::reportError(err2);
        throw FatalConfigError("parseConfigHeader");
    }
    return true;
}

// currencyLine = currency, {decimalNumber}, ";"
bool ConfigParser::tryparseCurrencyLine()
{
    if (!isTokenCorrect(TokenType::IDENTIFIER_TOKEN))
        return false;
    string currency = currentToken.getString();
    getNextToken();
    if (find(configHeader.begin(), configHeader.end(), currency) == configHeader.end())
    {
        CurrencyNotInHeader err(currency);
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        ConfigExample err2;
        ErrorReporter::reportError(err2);
        throw FatalConfigError("parseConfigHeader");
    }
    vector<dec::decimal<MAX_DECIMAL_POINTS>> tempVect;
    while (isTokenCorrect(TokenType::NUMBER_TOKEN))
    {
        tempVect.push_back(currentToken.getDecimal());
        getNextToken();
    }
    if (tempVect.size() != configHeader.size())
    {
        MissingDenaminationValues err(tempVect.size(), configHeader.size());
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        ConfigExample err2;
        ErrorReporter::reportError(err2);
        throw FatalConfigError("tryparseCurrencyLine");
    }
    if (!checkAndConsume(TokenType::SEMICOLON_TOKEN))
    {
        MissingElementBefore err(";");
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        ConfigExample err2;
        ErrorReporter::reportError(err2);
        throw FatalConfigError("tryparseCurrencyLine");
    }

    auto itA = configHeader.begin();
    auto itB = tempVect.begin();
    unordered_map<string, dec::decimal<MAX_DECIMAL_POINTS>> newConversions;
    while (itA != configHeader.end() || itB != tempVect.end())
    {
        if (!newConversions.try_emplace(*itA, *itB).second)
        {
            MissingDenaminationValues err(tempVect.size(), configHeader.size());
            ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
            ConfigExample err2;
            ErrorReporter::reportError(err2);
            throw FatalConfigError("tryparseCurrencyLine");
        }
        ++itA;
        ++itB;
    }

    if (!curriencies.try_emplace(currency, newConversions).second)
    {
        HeaderDuplicate err(currency);
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        ConfigExample err2;
        ErrorReporter::reportError(err2);
        throw FatalConfigError("tryparseCurrencyLine");
    }
    return true;
}

std::optional<std::unordered_map<std::string, dec::decimal<MAX_DECIMAL_POINTS>>> ConfigParser::getDenominations(const std::string &currency)
{
    auto it = curriencies.find(currency);
    if (it == curriencies.end())
        return nullopt;
    return it->second;
}

std::unordered_map<std::string, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>>> ConfigParser::getCurrencyMap() const
{
    return curriencies;
}