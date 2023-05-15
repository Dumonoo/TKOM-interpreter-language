#include <gtest/gtest.h>
#include <sstream>
#include "../../src/Lexer/Lexer.h"
#include "../../src/Token/TokenType.h"
#include "../../src/ErrorHandler/InterpreterExceptions.h"

TEST(SimpleExampleTests, VoidFunctionDefinition)
{
    std::string input = "void testFunction(cur aB1, num B23)\n"
                        "{\n"
                        "num a = 20;\n"
                        "print(\"printing:\" , a);"
                        "}\n";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::VOID_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "testFunction");

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::LPAREN_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::CUR_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "aB1");

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::COMMA_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::NUM_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "B23");

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::RPAREN_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::LCURLY_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::NUM_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "a");

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ASSIGN_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    // tutaj bląd
    EXPECT_EQ(token.getDecimal(), dec::decimal<MAX_DECIMAL_POINTS>("20"));

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::SEMICOLON_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "print");

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::LPAREN_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::TEXTCONST_TOKEN);
    EXPECT_EQ(token.getString(), "printing:");

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::COMMA_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "a");

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::RPAREN_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::SEMICOLON_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::RCURLY_TOKEN);
}

TEST(SimpleExampleTests, IfStatement)
{
    std::string input = "if(1 <= 0 or a >= b)\n"
                        "{\n"
                        "}\n";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IF_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::LPAREN_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    EXPECT_EQ(token.getDecimal(), dec::decimal<MAX_DECIMAL_POINTS>("1"));

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::LESSOREQUAL_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    EXPECT_EQ(token.getDecimal(), dec::decimal<MAX_DECIMAL_POINTS>("0"));

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::OR_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "a");

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::GREATOREQUAL_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "b");

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::RPAREN_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::LCURLY_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::RCURLY_TOKEN);
}

TEST(SimpleExampleTests, WhileStatement)
{
    std::string input = "while(1 <= 0 and a >= b)\n"
                        "{\n"
                        "}\n";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::WHILE_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::LPAREN_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    EXPECT_EQ(token.getDecimal(), dec::decimal<MAX_DECIMAL_POINTS>("1"));

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::LESSOREQUAL_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    EXPECT_EQ(token.getDecimal(), dec::decimal<MAX_DECIMAL_POINTS>("0"));

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::AND_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "a");

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::GREATOREQUAL_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "b");

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::RPAREN_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::LCURLY_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::RCURLY_TOKEN);
}

TEST(SimpleExampleTests, FunctionCall)
{
    std::string input = "calculateEarthEarnings(90000000, 1000 USD);";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "calculateEarthEarnings");

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::LPAREN_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    EXPECT_EQ(token.getDecimal(), dec::decimal<MAX_DECIMAL_POINTS>("90000000"));

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::COMMA_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    EXPECT_EQ(token.getDecimal(), dec::decimal<MAX_DECIMAL_POINTS>("1000"));

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "USD");

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::RPAREN_TOKEN);

    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::SEMICOLON_TOKEN);
}

TEST(SimpleExampleTests, AtTokenUsageExamples)
{
    std::string input = "20 @ a; \n"
                        "b@USD;\n"
                        "c@ b;\n"
                        "- d @CAD ;";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    Position pos = {1, 2, 2, 2};

    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    EXPECT_EQ(token.getDecimal(), dec::decimal<MAX_DECIMAL_POINTS>("20"));
    EXPECT_EQ(token.getPosition(), pos);

    pos = {1, 4, 4, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::AT_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);

    pos = {1, 6, 6, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "a");
    EXPECT_EQ(token.getPosition(), pos);

    pos = {1, 7, 7, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::SEMICOLON_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);

    pos = {2, 1, 10, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "b");
    EXPECT_EQ(token.getPosition(), pos);

    pos = {2, 2, 11, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::AT_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);

    pos = {2, 5, 14, 3};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "USD");
    EXPECT_EQ(token.getPosition(), pos);

    pos = {2, 6, 15, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::SEMICOLON_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);

    pos = {3, 1, 17, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "c");
    EXPECT_EQ(token.getPosition(), pos);

    pos = {3, 2, 18, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::AT_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);

    pos = {3, 4, 20, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "b");
    EXPECT_EQ(token.getPosition(), pos);

    pos = {3, 5, 21, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::SEMICOLON_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);

    pos = {4, 1, 23, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::MINUS_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);

    pos = {4, 3, 25, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "d");
    EXPECT_EQ(token.getPosition(), pos);

    pos = {4, 5, 27, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::AT_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);

    pos = {4, 8, 30, 3};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "CAD");
    EXPECT_EQ(token.getPosition(), pos);

    pos = {4, 10, 32, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::SEMICOLON_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(SimpleExampleTests, MissingQuotationEnd)
{
    std::string input = "\"";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ASSERT_THROW(lexer.getNextToken(), FatalError);
}