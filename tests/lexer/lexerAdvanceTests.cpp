#include <gtest/gtest.h>
#include <sstream>
#include "../../src/Lexer/Lexer.h"
#include "../../src/Token/TokenType.h"
#include "../../src/ErrorHandler/InterpreterExceptions.h"

using namespace std;
using namespace dec;

TEST(AdvanceLexerTests, DecimalTokenValue)
{
    string input = "100 "
                   "0.12\n"
                   "0\n"
                   "100000000\n"
                   "100000000.100232\n"
                   "100000000000000000000000000000";
    stringstream inputStream{input};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    Position pos = {1, 3, 3, 3};
    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    EXPECT_EQ(token.getDecimal(), decimal<MAX_DECIMAL_POINTS>("100"));
    EXPECT_EQ(token.getPosition(), pos);

    token = lexer.getNextToken();
    pos = {1, 8, 8, 4};
    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    EXPECT_EQ(token.getDecimal(), decimal<MAX_DECIMAL_POINTS>("0.12"));
    EXPECT_EQ(token.getPosition(), pos);

    token = lexer.getNextToken();
    pos = {2, 1, 10, 1};
    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    EXPECT_EQ(token.getDecimal(), decimal<MAX_DECIMAL_POINTS>("0"));
    EXPECT_EQ(token.getPosition(), pos);

    token = lexer.getNextToken();
    pos = {3, 9, 20, 9};
    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    EXPECT_EQ(token.getDecimal(), decimal<MAX_DECIMAL_POINTS>("100000000"));
    EXPECT_EQ(token.getPosition(), pos);

    token = lexer.getNextToken();
    pos = {4, 16, 37, 16};
    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    EXPECT_EQ(token.getDecimal(), decimal<MAX_DECIMAL_POINTS>("100000000.100232"));
    EXPECT_EQ(token.getPosition(), pos);
    // OVERFLOW
    ASSERT_THROW(lexer.getNextToken(), FatalError);
}

TEST(AdvanceLexerTests, DecimalLeadingZero)
{
    string input = "01000";
    stringstream inputStream{input};
    Lexer lexer(inputStream);
    ASSERT_THROW(lexer.getNextToken(), FatalError);
}

TEST(AdvanceLexerTests, AtSymbolWithoutSpaces)
{
    string input = "a@b\n"
                   "20@USD";
    stringstream inputStream{input};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    Position pos = {1, 1, 1, 1};
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "a");
    EXPECT_EQ(token.getPosition(), pos);

    token = lexer.getNextToken();
    pos = {1, 2, 2, 1};
    EXPECT_EQ(token.getType(), TokenType::AT_TOKEN);
    EXPECT_EQ(token.getString(), "@");
    EXPECT_EQ(token.getPosition(), pos);

    token = lexer.getNextToken();
    pos = {1, 3, 3, 1};
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "b");
    EXPECT_EQ(token.getPosition(), pos);

    token = lexer.getNextToken();
    pos = {2, 2, 6, 2};
    EXPECT_EQ(token.getType(), TokenType::NUMBER_TOKEN);
    EXPECT_EQ(token.getDecimal(), decimal<MAX_DECIMAL_POINTS>("20"));
    EXPECT_EQ(token.getPosition(), pos);

    token = lexer.getNextToken();
    pos = {2, 3, 7, 1};
    EXPECT_EQ(token.getType(), TokenType::AT_TOKEN);
    EXPECT_EQ(token.getString(), "@");
    EXPECT_EQ(token.getPosition(), pos);

    token = lexer.getNextToken();
    pos = {2, 6, 10, 3};
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "USD");
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(AdvanceLexerTests, TextConstWithoutEnding)
{
    string input = "\" Test Text";
    stringstream inputStream{input};
    Lexer lexer(inputStream);
    ASSERT_THROW(lexer.getNextToken(), FatalError);
}

TEST(LexerExceptionsTests, TooLongTextConst)
{
    string input = "\"";
    auto counter = 0;
    while (counter < MAX_TEXTCONST_LENGTH + 1)
    {
        input += "a";
        counter++;
    }
    input += "\"";
    stringstream inputStream{input};
    Lexer lexer(inputStream);
    ASSERT_THROW(lexer.getNextToken(), FatalError);
}

TEST(LexerExceptionsTests, TooLongIdentifier)
{
    string input = "";
    auto counter = 0;
    while (counter < MAX_IDENTIFIER_LENGTH + 1)
    {
        input += "a";
        counter++;
    }
    input += "";
    stringstream inputStream{input};
    Lexer lexer(inputStream);
    ASSERT_THROW(lexer.getNextToken(), FatalError);
}

TEST(LexerExceptionsTests, TooLongComment)
{
    string input = "#";
    auto counter = 0;
    while (counter < MAX_COMMENT_LENGTH + 1)
    {
        input += "a";
        counter++;
    }
    input += "";
    stringstream inputStream{input};
    Lexer lexer(inputStream);
    ASSERT_THROW(lexer.getNextToken(), FatalError);
}

TEST(LexerExceptionsTests, DecimalOverflow)
{
    string input = to_string(MAX_DECIMAL_NUMBER + 1);
    stringstream inputStream{input};
    Lexer lexer(inputStream);
    ASSERT_THROW(lexer.getNextToken(), FatalError);
}

TEST(LexerExceptionsTests, DecimalOverflowWithDecimalPlaces)
{
    string decimalPoints = "1234567890";
    string input1 = to_string(MAX_DECIMAL_NUMBER);
    string input2 = to_string(MAX_DECIMAL_NUMBER + 1);
    stringstream inputStream{input1 + '.' + decimalPoints + "@" + input2 + '.' + decimalPoints};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getDecimal(), decimal_cast<MAX_DECIMAL_POINTS>(input1 + '.' + decimalPoints.substr(0, MAX_DECIMAL_POINTS)));
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::AT_TOKEN);
    ASSERT_THROW(lexer.getNextToken(), FatalError);
}

TEST(EscapeCharactersTest, Escaping1)
{
    string input = "\"\\\"\"";
    string expected = "\"";
    stringstream inputStream{input};
    Position pos = {1, 4, 4, 4};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::TEXTCONST_TOKEN);
    EXPECT_EQ(token.getString(), expected);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(EscapeCharactersTest, Escaping2)
{
    string input = "\"\\\\\"";
    string expected = "\\";
    stringstream inputStream{input};
    Position pos = {1, 4, 4, 4};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::TEXTCONST_TOKEN);
    EXPECT_EQ(token.getString(), expected);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(EscapeCharactersTest, Escaping3)
{
    string input = "\"\\n\"";
    string expected = "\n";
    stringstream inputStream{input};
    Position pos = {1, 4, 4, 4};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::TEXTCONST_TOKEN);
    EXPECT_EQ(token.getString(), expected);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(EscapeCharactersTest, Escaping4)
{
    string input = "\"\\r\"";
    string expected = "\r";
    stringstream inputStream{input};
    Position pos = {1, 4, 4, 4};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::TEXTCONST_TOKEN);
    EXPECT_EQ(token.getString(), expected);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(EscapeCharactersTest, Escaping5)
{
    string input = "\"\\t\"";
    string expected = "\t";
    stringstream inputStream{input};
    Position pos = {1, 4, 4, 4};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::TEXTCONST_TOKEN);
    EXPECT_EQ(token.getString(), expected);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(EscapeCharactersTest, Escaping6)
{
    string input = "\"\\v\"";
    string expected = "\v";
    stringstream inputStream{input};
    Position pos = {1, 4, 4, 4};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::TEXTCONST_TOKEN);
    EXPECT_EQ(token.getString(), expected);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(EscapeCharactersTest, EscapingUnknownCharacter)
{
    string input = "\"\\$\"";
    string expected = "$";
    stringstream inputStream{input};
    Position pos = {1, 4, 4, 4};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::TEXTCONST_TOKEN);
    EXPECT_EQ(token.getString(), expected);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(AdvanceLexerTests, EmptyStream)
{
    string input = "";
    stringstream inputStream{input};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ETX_TOKEN);
}

TEST(AdvanceLexerTests, MultipleETX1)
{
    string input = "";
    stringstream inputStream{input};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    Position pos = {1, 0, 0, 0};
    EXPECT_EQ(token.getType(), TokenType::ETX_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ETX_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ETX_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ETX_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ETX_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ETX_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(AdvanceLexerTests, MultipleETX2)
{
    string input = "a";
    stringstream inputStream{input};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    Position pos = {1, 1, 1, 1};
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);

    pos = {1, 1, 1, 1};
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ETX_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ETX_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ETX_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ETX_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ETX_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);
    token = lexer.getNextToken();
    EXPECT_EQ(token.getType(), TokenType::ETX_TOKEN);
    EXPECT_EQ(token.getPosition(), pos);
}

TEST(AdvanceLexerTests, NewLineCharacters)
{
    string input = "a\n"
                   "b\r\n"
                   "c\r"
                   "d\036"
                   "e\n\r"
                   "f\233";
    stringstream inputStream{input};
    Lexer lexer(inputStream);
    Token token = lexer.getNextToken();
    // We check if all letters get proper positions base on skiping new lines
    Position pos = {1, 1, 1, 1};
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "a");
    EXPECT_EQ(token.getPosition(), pos);

    token = lexer.getNextToken();
    pos = {2, 1, 3, 1};
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "b");
    EXPECT_EQ(token.getPosition(), pos);

    token = lexer.getNextToken();
    pos = {3, 1, 6, 1};
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "c");
    EXPECT_EQ(token.getPosition(), pos);

    token = lexer.getNextToken();
    pos = {4, 1, 8, 1};
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "d");
    EXPECT_EQ(token.getPosition(), pos);

    token = lexer.getNextToken();
    pos = {5, 1, 10, 1};
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "e");
    EXPECT_EQ(token.getPosition(), pos);

    token = lexer.getNextToken();
    pos = {6, 1, 13, 1};
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER_TOKEN);
    EXPECT_EQ(token.getString(), "f");
    EXPECT_EQ(token.getPosition(), pos);

}
