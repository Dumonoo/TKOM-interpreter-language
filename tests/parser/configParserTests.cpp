#include <gtest/gtest.h>
#include <sstream>
#include "../../src/Lexer/Lexer.h"
#include "../../src/ConfigParser/ConfigParser.h"
// #include "../../src/Parser/Parser.h"

TEST(SimpleConfigTests, EmptyStream)
{
    std::string input = "";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_NO_THROW(configParser.parseConfigFile());
}

TEST(SimpleConfigTests, AtAndEmptyStream)
{
    std::string input = "@ ";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_THROW(configParser.parseConfigFile(), FatalConfigError);
}


TEST(SimpleConfigTests, AtAndPartHeaderStream1)
{
    std::string input = "@ USD";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_THROW(configParser.parseConfigFile(), FatalConfigError);
}

TEST(SimpleConfigTests, AtAndFullHeaderStream2)
{
    std::string input = "@ USD CAD;";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_THROW(configParser.parseConfigFile(), FatalConfigError);
}

TEST(SimpleConfigTests, MissingCurrecy)
{
    std::string input = "@ USD CAD;\n"
                        "PLN 1 1";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_THROW(configParser.parseConfigFile(), FatalConfigError);
}

TEST(SimpleConfigTests, MissingCurrecy2)
{
    std::string input = "@ USD CAD;\n"
                        "USD 1 1";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_THROW(configParser.parseConfigFile(), FatalConfigError);
}
TEST(SimpleConfigTests, MissingCurrecy3)
{
    std::string input = "@ USD CAD;\n"
                        "USD 1 1 ;\n"
                        "PLN 1 1 ;";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_THROW(configParser.parseConfigFile(), FatalConfigError);
}


TEST(SimpleConfigTests, MissingSemicolon1)
{
    std::string input = "@ USD CAD\n"
                        "USD 1 1 ;\n"
                        "PLN 1 1 ;";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_THROW(configParser.parseConfigFile(), FatalConfigError);
}

TEST(SimpleConfigTests, MissingSemicolon2)
{
    std::string input = "@ USD CAD;\n"
                        "USD 1 1 \n"
                        "PLN 1 1 ;";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_THROW(configParser.parseConfigFile(), FatalConfigError);
}

TEST(SimpleConfigTests, MissingSemicolon3)
{
    std::string input = "@ USD CAD;\n"
                        "USD 1 1 ;\n"
                        "PLN 1 1 ";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_THROW(configParser.parseConfigFile(), FatalConfigError);
}

TEST(SimpleConfigTests, LooksBadButItsGood)
{
    std::string input = "@ USD; USD 1;\n";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_NO_THROW(configParser.parseConfigFile());
}
TEST(SimpleConfigTests, AllGoodConfig)
{
    std::string input = "@ USD CAD;\n"
                        "USD 1 1 ;\n"
                        "CAD 1 1 ;";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_NO_THROW(configParser.parseConfigFile());
}


TEST(SimpleConfigTests, OverflowInConfig)
{
    std::string input = "@ USD CAD;\n"
                        "USD 1000000000000000000000000000 1 ;\n"
                        "PLN 1 1 ";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_THROW(configParser.parseConfigFile(), FatalError);
}

TEST(SimpleConfigTests, CurrencyMissMatch)
{
    std::string input = "@ USD CAD;\n"
                        "PLN 1 1 ;\n"
                        "CAD 1 1 ;";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_THROW(configParser.parseConfigFile(), FatalConfigError);
}

TEST(SimpleConfigTests, CurrencyMissMatch2)
{
    std::string input = "@ USD CAD; PLN\n"
                        "PLN 1 1 ;\n"
                        "CAD 1 1 ;";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_THROW(configParser.parseConfigFile(), FatalConfigError);
}

TEST(SimpleConfigTests, AllGood2)
{
    std::string input = "@ USD CAD PLN;\n"
                        "PLN 1 1 1;\n"
                        "CAD 1 1 1; USD 1 1 1;";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    ConfigParser configParser(lexer);
    ASSERT_NO_THROW(configParser.parseConfigFile());
}