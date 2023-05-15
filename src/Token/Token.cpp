#include <string>
#include <iostream>
#include "Token.h"
// #include "TokenType.h"

using namespace std;
using namespace dec;

unordered_map<TokenType, std::string> Token::logMap;

Token::Token()
    : type(TokenType::UNDEFINED_TOKEN)
{
}

Token::Token(TokenType typ, string val, Position pos)
    : type(typ), value(val), position(pos)
{
}

Token::Token(TokenType typ, decimal<MAX_DECIMAL_POINTS> val, Position pos)
    : type(typ), value(val), position(pos)
{
}

TokenType Token::getType() const
{
    return type;
}

string Token::getString() const
{
    return get<string>(value);
}

decimal<MAX_DECIMAL_POINTS> Token::getDecimal() const
{
    return get<decimal<MAX_DECIMAL_POINTS>>(value);
}

Position Token::getPosition() const{
    return position;
}

void Token::initLogger()
{
    Token::logMap.clear();
    Token::logMap = {
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
}

void Token::logToken(){
       auto it = logMap.find(type);
       string tokenText = "";
    if (it == logMap.end())
        tokenText = "UNKNOW";
    else
        tokenText = it->second;
    cout<<"LOG: "<< tokenText <<"("<<position.rowNumber<<","<<position.columnNumber<<","<<position.streamPosition<<","<<position.tokenLength<<") ";
    visit([](const auto &x) {cout<<x;}, value);
    cout<<endl;    
}

bool Token::isETX() const
{
    return type == TokenType::ETX_TOKEN;
}
