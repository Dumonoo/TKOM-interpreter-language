#include <gtest/gtest.h>
#include <sstream>
#include "../../src/Lexer/Lexer.h"
#include "../../src/Parser/Parser.h"
#include "../../src/ConfigParser/ConfigParser.h"

TEST(ThrowStatements, IfStatement1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);

    std::string input = "void main(){ "
                        "if(1)}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, IfStatement2)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);

    std::string input = "void main(){ "
                        "if(){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, IfStatement3)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);

    std::string input = "void main(){ "
                        "if(1){     }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, IfStatement4)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);

    std::string input = "void main(){ "
                        "if(1 {     }}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, IfStatement5)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);

    std::string input = "void main(){ "
                        "if 1 ){     }}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, IfStatement6)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);

    std::string input = "void main(){ "
                        "if(1){ } else }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, IfStatement7)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);

    std::string input = "void main(){ "
                        "if(1){ } else{ }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, IfStatement8)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);

    std::string input = "void main(){ "
                        "if(1){ } else }}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, WhileStatement1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "while(){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, WhileStatement2)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "while 1){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, WhileStatement3)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "while (1 {}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, WhileStatement4)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "while (1) }}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, WhileStatement5)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "while (1){ }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, FunctionCallStatement1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, FunctionCallStatement2)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a(;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, AssignmentStatement1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "a = ; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, ArgumentsMissing)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "a(1,b,); }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, InitStatement1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "cur  = 20 USD; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, InitStatement2)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "cur  a; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, InitStatement3)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "cur  a = ; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowStatements, InitStatement4)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "num  a = \"dsadasd\"; }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, OrExpr1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(1 or ){} }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, AndExpr1)
{
    std::string inputConfig = "";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "void main(){ "
                        "if(1 and ){} }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, NegationExpr)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "if(!){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, GreaterOrEqualExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "if(2>=){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, GreaterOrEqualExpr2)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "if(2>=3 >=){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, GreaterExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "if(2> ){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, LessOrEqualExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "if(2<= ){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, LessExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "if(2< ){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, IsEqualExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "if(2==){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, NotEqualExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "if(2!=){}}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, MinusNegExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a = - ;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, AddExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a = 1 + 2 +;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, SubExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a = 1 - 2 -;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, MultExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a = 1 * 2 *;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, DivExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a = 1 / 2 /;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, ParenthesisExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a = (())}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, ParenthesisExpr2)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a = (()}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, FunCallExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a(1, a,)}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, FunCallExpr2)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a(1, a, b }";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}

TEST(ThrowExpressions, CurrencyExpr1)
{
    std::string inputConfig = "@ USD; USD 1;";
    std::stringstream inputStreamConfig{inputConfig};
    Lexer lexerConfig(inputStreamConfig);
    ConfigParser configParser(lexerConfig);
    configParser.parseConfigFile();

    std::string input = "num main(){ "
                        "a = 20 PLN;}";
    std::stringstream inputStream{input};
    Lexer lexer(inputStream);
    Parser parser(lexer, configParser);
    ASSERT_THROW(parser.parse(), FatalError);
}
