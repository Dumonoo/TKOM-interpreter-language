// #include <iostream>
// #include <string>
// #include <string_view>
// #include <source_location>
#include <math.h>
#include <memory>

#include "Lexer.h"

#include "../utils/utils.h"

using namespace std;
using namespace dec;

Lexer::Lexer(istream &stream)
    : charactersStream(stream)
{
    initLexer();
}

void Lexer::initLexer()
{
    initPosition();
    initKeywordsMap();
}

void Lexer::initPosition()
{
    currentPosition.rowNumber = 1;
    currentPosition.columnNumber = 0;
    currentPosition.streamPosition = 0;
    currentPosition.tokenLength = 0;
    getNextCharacter();
}

void Lexer::initKeywordsMap()
{
    keywordsMap.clear();
    keywordsMap = {
        {"void", TokenType::VOID_TOKEN},
        {"cur", TokenType::CUR_TOKEN},
        {"num", TokenType::NUM_TOKEN},
        {"if", TokenType::IF_TOKEN},
        {"else", TokenType::ELSE_TOKEN},
        {"while", TokenType::WHILE_TOKEN},
        {"return", TokenType::RETURN_TOKEN},
        {"and", TokenType::AND_TOKEN},
        {"or", TokenType::OR_TOKEN}};
}

TokenType Lexer::findKeyword(const string &identifier)
{
    unordered_map<string, TokenType>::iterator it = keywordsMap.find(identifier);
    if (it == keywordsMap.end())
        return TokenType::IDENTIFIER_TOKEN;
    return it->second;
}

void Lexer::moveInStream()
{
    currentCharacter = (char)charactersStream.get();
}

void Lexer::getNextCharacter()
{
    previousPosition = currentPosition;
    moveInStream();
    currentPosition.columnNumber += 1;
    currentPosition.tokenLength += 1;
    if (!(isEtxCharacter(currentCharacter) || charactersStream.eof()))
        currentPosition.streamPosition = (unsigned int)charactersStream.tellg();

    if ((int)currentCharacter == 21 || (int)currentCharacter == 155 || (int)currentCharacter == 30)
    {
        currentPosition.rowNumber += 1;
        currentPosition.columnNumber = 0;
        currentCharacter = '\n';
    }
    else if ((int)currentCharacter == 10)
    {
        currentPosition.rowNumber += 1;
        currentPosition.columnNumber = 0;
        if (charactersStream.peek() == 13)
        {
            moveInStream();
            currentCharacter = '\n';
        }
    }
    else if ((int)currentCharacter == 13)
    {
        currentPosition.rowNumber += 1;
        currentPosition.columnNumber = 0;
        currentCharacter = '\n';

        if (charactersStream.peek() == 10)
        {
            moveInStream();
            currentCharacter = '\n';
        }
    }
}
istream & Lexer::getCharacterStream(){
    return charactersStream;
}

Token Lexer::getNextToken()
{
    skipWhites();
    currentPosition.tokenLength = 1;

    if (tryBuildETX())
        return token;
    if (tryBuildComment())
        return token;
    if (tryBuildIdentifierOrKeyword())
        return token;
    if (tryBuildTextConst())
        return token;
    if (tryBuildNumber())
        return token;
    if (tryBuildOperator())
        return token;

    token = Token(TokenType::UNDEFINED_TOKEN, to_string(currentCharacter), currentPosition);
    UndefinedToken e;
    ErrorReporter::reportError(e, currentPosition,charactersStream);
    getNextCharacter();
    throw FatalError("getNextToken");
}

void Lexer::skipWhites()
{
    while (isspace(currentCharacter))
    {
        getNextCharacter();
    }
}

char Lexer::tryGetEscapeCharacter()
{
    switch (currentCharacter)
    {
    case '"':
        return '\"';
    case '\\':
        return '\\';
    case 'n':
        return '\n';
    case 'r':
        return '\r';
    case 't':
        return '\t';
    case 'v':
        return '\v';
    default:
        UnknowEscapeCharacter e;
        ErrorReporter::reportWarning(e, currentPosition, charactersStream);
        return currentCharacter;
    }
}

bool Lexer::tryBuildETX()
{
    if (isEtxCharacter(currentCharacter))
    {
        token = Token(TokenType::ETX_TOKEN, "ETX", previousPosition);
        return true;
    }
    return false;
}

bool Lexer::tryBuildComment()
{
    if (currentCharacter != '#')
        return false;
    getNextCharacter();

    string comment = "";

    while (!(isNewLineCharacter(currentCharacter) || isEtxCharacter(currentCharacter)))
    {
        if (comment.length() == MAX_COMMENT_LENGTH)
        {
            CommentTooLong e;
            ErrorReporter::reportError(e, currentPosition, charactersStream);
            throw FatalError("tryBuildComment");
        }
        if (!isprint(currentCharacter))
        {
            UnknownCharacter e;
            ErrorReporter::reportError(e, currentPosition, charactersStream);
            throw FatalError("tryBuildComment");
        }
        comment += currentCharacter;
        getNextCharacter();
    }
    token = Token(TokenType::COMMENT_TOKEN, comment, previousPosition);
    return true;
}

bool Lexer::tryBuildIdentifierOrKeyword()
{
    if (!isalpha(currentCharacter))
        return false;
    string identifierOrKeyword = "";
    identifierOrKeyword += currentCharacter;
    getNextCharacter();
    while (isalpha(currentCharacter) || isdigit(currentCharacter))
    {
        if (identifierOrKeyword.length() == MAX_IDENTIFIER_LENGTH)
        {
            TooLongIdentifier e;
            ErrorReporter::reportError(e, currentPosition, charactersStream);
            throw FatalError("tryBuildIdentifierOrKeyword");
        }
        identifierOrKeyword += currentCharacter;
        getNextCharacter();
    }
    TokenType tokenType = findKeyword(identifierOrKeyword);

    if (tokenType == TokenType::IDENTIFIER_TOKEN &&
        findKeyword(toLowerCase(identifierOrKeyword)) != TokenType::IDENTIFIER_TOKEN)
        {
            TooSimilarIdentifier e;
            ErrorReporter::reportWarning(e, previousPosition, charactersStream);
        }
        

    token = Token(tokenType, identifierOrKeyword, previousPosition);
    return true;
}

bool Lexer::tryBuildTextConst()
{
    if (currentCharacter != '"')
        return false;
    getNextCharacter();
    string textConstant = "";
    while (currentCharacter != '"')
    {
        if (isNewLineCharacter(currentCharacter) ||
            isEtxCharacter(currentCharacter) ||
            charactersStream.eof())
        {
            MissingBackSlash e;
            ErrorReporter::reportError(e, previousPosition, charactersStream);
            throw FatalError("tryBuildTextConst");
        }
        if (currentCharacter == '\\')
        {
            getNextCharacter();
            currentCharacter = tryGetEscapeCharacter();
        }
        if (textConstant.length() == MAX_TEXTCONST_LENGTH)
        {
            TextConstantTooLong e;
            ErrorReporter::reportError(e, currentPosition, charactersStream);
            throw FatalError("tryBuildTextConst");
        }
        if (!isprint(currentCharacter) && !isspace(currentCharacter))
        {
            UnknownCharacter e;
            ErrorReporter::reportError(e,currentPosition, charactersStream);
            throw FatalError("tryBuildTextConst");
        }

        textConstant += currentCharacter;
        getNextCharacter();
    }
    token = Token(TokenType::TEXTCONST_TOKEN, textConstant, currentPosition);
    getNextCharacter();
    return true;
}

bool Lexer::tryBuildNumber()
{
    if (!isdigit(currentCharacter))
        return false;

    ulong integral_part = 0;
    if (currentCharacter != '0')
    {
        integral_part += currentCharacter - '0';
        getNextCharacter();
        while (isdigit(currentCharacter))
        {
            if (integral_part * 10 + currentCharacter - '0' > MAX_DECIMAL_NUMBER)
            {
                NumberOverflow e;
                ErrorReporter::reportError(e, currentPosition, charactersStream);
                throw FatalError("tryBuildNumber");
            }
            integral_part = integral_part * 10 + currentCharacter - '0';
            getNextCharacter();
        }
    }
    else
    {
        getNextCharacter();
    }
    if (currentCharacter == '.')
    {
        ulong fraction_part = 0;
        int decimal_places = 0;
        getNextCharacter();
        while (isdigit(currentCharacter))
        {
            if (decimal_places < MAX_DECIMAL_POINTS)
            {
                fraction_part = fraction_part * 10 + currentCharacter - '0';
            }
            decimal_places += 1;
            getNextCharacter();
        }
        if (decimal_places > MAX_DECIMAL_POINTS)
        {
            LostPrecision e;
            ErrorReporter::reportWarning(e, previousPosition, charactersStream);
        }

        token = Token(TokenType::NUMBER_TOKEN, decimal<MAX_DECIMAL_POINTS>(integral_part + fraction_part / pow(10, min(MAX_DECIMAL_POINTS, decimal_places))), previousPosition);
        return true;
    }
    else if (isdigit(currentCharacter))
    {
        LeadingZero e;
        ErrorReporter::reportError(e, currentPosition, charactersStream);
        throw FatalError("tryBuildNumber");
    }
    else
    {
        token = Token(TokenType::NUMBER_TOKEN, decimal<MAX_DECIMAL_POINTS>((long)integral_part), previousPosition);
        return true;
    }
}

bool Lexer::tryBuildOperator(TokenType single, const string &singleText, TokenType multi, const string &multiText)
{
    if (charactersStream.peek() != '=')
    {
        token = Token(single, singleText, currentPosition);
        getNextCharacter();
        return true;
    }
    getNextCharacter();
    token = Token(multi, multiText, currentPosition);
    getNextCharacter();
    return true;
}

bool Lexer::tryBuildOperator(TokenType single, const string &singleText)
{
    token = Token(single, singleText, currentPosition);
    getNextCharacter();
    return true;
}

bool Lexer::tryBuildOperator()
{
    switch (currentCharacter)
    {
    case '>':
        return tryBuildOperator(TokenType::GREATER_TOKEN, ">", TokenType::GREATOREQUAL_TOKEN, ">=");
    case '<':
        return tryBuildOperator(TokenType::LESS_TOKEN, "<", TokenType::LESSOREQUAL_TOKEN, "<=");
    case '=':
        return tryBuildOperator(TokenType::ASSIGN_TOKEN, "=", TokenType::ISEQUAL_TOKEN, "==");
    case '!':
        return tryBuildOperator(TokenType::NEGATION_TOKEN, "!", TokenType::NOTEQUAL_TOKEN, "!=");
    case '-':
        return tryBuildOperator(TokenType::MINUS_TOKEN, "-");
    case '+':
        return tryBuildOperator(TokenType::PLUS_TOKEN, "+");
    case '*':
        return tryBuildOperator(TokenType::MULTIPLY_TOKEN, "*");
    case '/':
        return tryBuildOperator(TokenType::DIVISION_TOKEN, "/");
    case '(':
        return tryBuildOperator(TokenType::LPAREN_TOKEN, "(");
    case ')':
        return tryBuildOperator(TokenType::RPAREN_TOKEN, ")");
    case '{':
        return tryBuildOperator(TokenType::LCURLY_TOKEN, "{");
    case '}':
        return tryBuildOperator(TokenType::RCURLY_TOKEN, "}");
    case ',':
        return tryBuildOperator(TokenType::COMMA_TOKEN, ",");
    case ';':
        return tryBuildOperator(TokenType::SEMICOLON_TOKEN, ";");
    case '@':
        return tryBuildOperator(TokenType::AT_TOKEN, "@");
    default:
        return false;
    }
}