#include <gtest/gtest.h>
#include <sstream>
#include "../../src/Lexer/Lexer.h"
#include "../../src/Parser/Parser.h"
#include "../../src/ConfigParser/ConfigParser.h"

void getMockEmptyConfigParser()
{
    // to delete
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();
}

TEST(SimpleStatements, IfStatement1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(1){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, IfStatement2)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(1){} "
                        "else{}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, WhileStatement1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "while(1){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, ReturnStatement1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "return 1;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, ReturnStatement2)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "cur main(){ "
                        "return 1 USD;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, ReturnStatement3)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "return;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, ReturnStatement4)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "cur main(){ "
                        "return 3.23 @ a}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, FunctionCallStatement1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "f(); }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, FunctionCallStatement2)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "print(\"dasd\", \"dasdas\", 1231, a); }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, AssignmentStatement1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "a = 20; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, AssignmentStatement2)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "a = b; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, AssignmentStatement3)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "a = b @ a; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, AssignmentStatement4)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "a = (2 * b) USD; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, InitStatement1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "cur a = 20 USD; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, InitStatement2)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "cur a = 20 @ USD; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, InitStatement3)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "cur a = 20 @ b; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleStatements, InitStatement4)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "num a = 20; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, OrExpr1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(1 or 2 or 3){} }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, OrExpr2)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(a or a or 3){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, OrExpr3)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(a or a or 1 USD == 3 USD){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, AndExpr1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(1 and 0 and 3){} }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, AndExpr2)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(1 and 0 or 3){} }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, AddExpr1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "cur a = 2 + 3;   }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, AddExpr2)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "cur a = 2 + 3 + 3 + 2 + 3 + 3 + 3 + 3 + 3 + 22 USD;    }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, SubExpr1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "num a = 2 - 3;   }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, SubExpr2)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "num a = 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, MultExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "num a = 2 * 3;    }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, MultExpr2)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "num a = 2 * 3 * 2;    }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, DivExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "num a = 2 / 3 ;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, DivExpr2)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "num a = 2 / 3 / 3;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, GreaterOrEqualExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(2>=3){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, GreaterExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(2>3){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, LessOrEqualExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(2<=3){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}


TEST(SimpleExpression, LessExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(2<3){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, IsEqualExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(2==3){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, NotEqualExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(2!=3){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, NegationExpr)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "if(!1){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, MinusNegExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a = -1;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, LiteralExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a = -1.321332;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, FunCallExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a(fun(12), f(22));}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, ParenthesisExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "cur a = f(((((((((((((((20)))))))))))))));}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, ParenthesisExpr2)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "if(((((((((((((((((((((((20 or 1)))))))))and 3 == 2)))))))))))))){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, CurrencyExpr1)
{
    std::string inputConfig = "@ USD PLN; USD 1 2; PLN 3 2;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "cur a =  20 USD; cur b = 20 PLN;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, CurrencyExpr2)
{
    std::string inputConfig = "@ USD PLN; USD 1 2; PLN 3 2;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "cur a =  20 @ USD; cur b = 20 @ PLN;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(SimpleExpression, ConversionExpr1)
{
    std::string inputConfig = "@ USD PLN; USD 1 2; PLN 3 2;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "cur a =  20 @ USD; cur b = 20 @ a;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

TEST(AdvanceExample, ExampleProgram1)
{
    std::string inputConfig = "@ USD PLN; USD 1 2; PLN 3 2;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "cur a =  20 USD; cur b = 20 @ a;"
                        "if(a == b)"
                        "{ a = 2 * b;}"
                        "while(a <= b){a = a + 2 USD; b = b + 1 PLN;}"
                        "return b @ a; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_NO_THROW(parser.parse());
}

