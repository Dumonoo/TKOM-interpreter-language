#include <gtest/gtest.h>
#include <sstream>
#include "../../src/Lexer/Lexer.h"
#include "../../src/Token/TokenType.h"
#include "../../src/ErrorHandler/InterpreterExceptions.h"

TEST(SingleTokenRecognition, UndefinedToken)
{
    std::string input = "$";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ASSERT_THROW(lexer.getNextToken(), FatalError);
}

TEST(SingleTokenRecognition, IdentyfierToken)
{
    std::string input = "a1b2";
    Position pos = {1, 4, 4, 4};
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, NumToken)
{
    std::string input = "num";
    Position pos = {1, 3, 3, 3};
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::NUM_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, CurToken)
{
    std::string input = "cur";
    Position pos = {1, 3, 3, 3};
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::CUR_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, VoidToken)
{
    std::string input = "void";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 4, 4, 4};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::VOID_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, IfToken)
{
    std::string input = "if";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 2, 2, 2};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IF_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, ElseToken)
{
    std::string input = "else";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 4, 4, 4};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ELSE_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, WhileToken)
{
    std::string input = "while";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 5, 5, 5};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::WHILE_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, ReturnToken)
{
    std::string input = "return";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 6, 6, 6};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::RETURN_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, AndToken)
{
    std::string input = "and";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 3, 3, 3};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::AND_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, OrToken)
{
    std::string input = "or";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 2, 2, 2};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::OR_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, EtxToken)
{
    std::string input = "";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 0, 0, 0};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ETX_TOKEN);
    EXPECT_EQ(token.getString(), "ETX");
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, CommentToken)
{
    std::string input = "# Komenarz tesowy zaweirajacy # 300 @ USD; :-),./[]1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,.../\\$";
    std::string output = " Komenarz tesowy zaweirajacy # 300 @ USD; :-),./[]1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,.../\\$";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 100, 100, 100};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::COMMENT_TOKEN);
    EXPECT_EQ(token.getString(), output);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, TextConstToken)
{
    // TODO: zdecydowac czy liczyc "" do tokena
    std::string input = "\"Testowy napis 1234567890\"";
    std::string output = "Testowy napis 1234567890";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 26, 26, 26};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::TEXTCONST_TOKEN);
    EXPECT_EQ(token.getString(), output);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, NumberToken)
{
    std::string input = "123.454";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 7, 7, 7};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    EXPECT_EQ(token.getDecimal(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, GreaterOrEqualToken)
{
    std::string input = ">=";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 2, 2, 2};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::GREATOREQUAL_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, LessOrEqualToken)
{
    std::string input = "<=";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 2, 2, 2};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::LESSOREQUAL_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, IsEqualToken)
{
    std::string input = "==";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 2, 2, 2};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ISEQUAL_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, NotEqualToken)
{
    std::string input = "!=";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 2, 2, 2};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::NOTEQUAL_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, GreaterThanToken)
{
    std::string input = ">";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::GREATER_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, LessThenToken)
{
    std::string input = "<";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::LESS_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, MinusToken)
{
    std::string input = "-";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::MINUS_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, PlusToken)
{
    std::string input = "+";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::PLUS_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, MultiplyToken)
{
    std::string input = "*";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::MULTIPLY_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, DivisionToken)
{
    std::string input = "/";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::DIVISION_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, AssignToken)
{
    std::string input = "=";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ASSIGN_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, NegationToken)
{
    std::string input = "!";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::NEGATION_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, LeftParenthesisToken)
{
    std::string input = "(";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::LPAREN_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, RightParenthesisToken)
{
    std::string input = ")";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::RPAREN_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, LeftCurlyToken)
{
    std::string input = "{";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::LCURLY_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, RightCurlyToken)
{
    std::string input = "}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::RCURLY_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, CommaToken)
{
    std::string input = ",";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::COMMA_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, SemicolonToken)
{
    std::string input = ";";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::SEMICOLON_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SingleTokenRecognition, AtToken)
{
    std::string input = "@";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Position pos = {1, 1, 1, 1};
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::AT_TOKEN);
    EXPECT_EQ(token.getString(), input);
    EXPECT_EQ(token.getPosition(), pos);
}
