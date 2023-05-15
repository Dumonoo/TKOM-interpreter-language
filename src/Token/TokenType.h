#pragma once
#include <stdint.h>
#include <limits>
#include <math.h>
#include <tuple>
#include <unordered_map>

#define MAX_DECIMAL_POINTS 4
#define DECIMAL_DISPLAY_PRECISION 2
#define MAX_CALCULATIONS_PRECISION 2 * MAX_DECIMAL_POINTS
#define MAX_IDENTIFIER_LENGTH 30
#define MAX_TEXTCONST_LENGTH 200
#define MAX_COMMENT_LENGTH 400
#define MAX_DECIMAL_NUMBER (long)((std::numeric_limits<long>::max)()/pow(10, MAX_CALCULATIONS_PRECISION))
#define MIN_DECIMAL_NUMBER (std::numeric_limits<long>::min)()/MAX_CALCULATIONS_PRECISION
#define MAX_LOG (std::numeric_limits<long>::max)()



enum class TokenType
{
    UNDEFINED_TOKEN,
    IDENTIFIER_TOKEN,
    NUM_TOKEN,
    CUR_TOKEN,
    VOID_TOKEN,
    IF_TOKEN,
    ELSE_TOKEN,
    WHILE_TOKEN,
    RETURN_TOKEN,
    AND_TOKEN,
    OR_TOKEN,
    ETX_TOKEN,
    COMMENT_TOKEN,
    TEXTCONST_TOKEN,
    NUMBER_TOKEN,
    
    GREATOREQUAL_TOKEN,
    LESSOREQUAL_TOKEN,
    ISEQUAL_TOKEN,
    NOTEQUAL_TOKEN,
    GREATER_TOKEN,
    LESS_TOKEN,
    MINUS_TOKEN,
    PLUS_TOKEN,
    MULTIPLY_TOKEN,
    DIVISION_TOKEN,
    ASSIGN_TOKEN,
    NEGATION_TOKEN,
    LPAREN_TOKEN,
    RPAREN_TOKEN,
    LCURLY_TOKEN,
    RCURLY_TOKEN,
    COMMA_TOKEN,
    SEMICOLON_TOKEN,
    AT_TOKEN
};

struct Position
{
    unsigned int rowNumber;
    unsigned int columnNumber;
    unsigned int streamPosition;
    unsigned int tokenLength;
    
    friend bool operator ==(const Position& l, const Position& r)
    {
        return   std::tie(l.rowNumber, l.columnNumber, l.streamPosition, l.tokenLength)
              == std::tie(r.rowNumber, r.columnNumber, r.streamPosition, r.tokenLength);
    }
};

static std::unordered_map<TokenType, std::string> tokenTypeNames = {
        {TokenType::UNDEFINED_TOKEN, "UNDEFINED_TOKEN"},
        {TokenType::IDENTIFIER_TOKEN, "IDENTIFIER_TOKEN"},
        {TokenType::NUM_TOKEN, "NUM_TOKEN"},
        {TokenType::CUR_TOKEN, "CUR_TOKEN"},
        {TokenType::VOID_TOKEN, "VOID_TOKEN"},
        {TokenType::IF_TOKEN, "IF_TOKEN"},
        {TokenType::ELSE_TOKEN, "ELSE_TOKEN"},
        {TokenType::WHILE_TOKEN, "WHILE_TOKEN"},
        {TokenType::RETURN_TOKEN, "RETURN_TOKEN"},
        {TokenType::AND_TOKEN, "AND_TOKEN"},
        {TokenType::OR_TOKEN, "OR_TOKEN"},
        {TokenType::ETX_TOKEN, "ETX_TOKEN"},
        {TokenType::COMMENT_TOKEN, "COMMENT_TOKEN"},
        {TokenType::TEXTCONST_TOKEN, "TEXTCONST_TOKEN"},
        {TokenType::NUMBER_TOKEN, "NUMBER_TOKEN"},

        {TokenType::GREATOREQUAL_TOKEN, "GREATOREQUAL_TOKEN"},
        {TokenType::LESSOREQUAL_TOKEN, "LESSOREQUAL_TOKEN"},
        {TokenType::ISEQUAL_TOKEN, "ISEQUAL_TOKEN"},
        {TokenType::NOTEQUAL_TOKEN, "NOTEQUAL_TOKEN"},
        {TokenType::GREATER_TOKEN, "GREATER_TOKEN"},
        {TokenType::LESS_TOKEN, "LESS_TOKEN"},
        {TokenType::MINUS_TOKEN, "MINUS_TOKEN"},
        {TokenType::PLUS_TOKEN, "PLUS_TOKEN"},
        {TokenType::MULTIPLY_TOKEN, "MULTIPLY_TOKEN"},
        {TokenType::DIVISION_TOKEN, "DIVISION_TOKEN"},
        {TokenType::ASSIGN_TOKEN, "ASSIGN_TOKEN"},
        {TokenType::NEGATION_TOKEN, "NEGATION_TOKEN"},
        {TokenType::LPAREN_TOKEN, "LPAREN_TOKEN"},
        {TokenType::RPAREN_TOKEN, "RPAREN_TOKEN"},
        {TokenType::LCURLY_TOKEN, "LCURLY_TOKEN"},
        {TokenType::RCURLY_TOKEN, "RCURLY_TOKEN"},
        {TokenType::COMMA_TOKEN, "COMMA_TOKEN"},
        {TokenType::SEMICOLON_TOKEN, "SEMICOLON_TOKEN"},
        {TokenType::AT_TOKEN, "AT_TOKEN"}};
