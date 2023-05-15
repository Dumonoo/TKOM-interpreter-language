#include <vector>
#include <string>
#include <optional>
#include <unordered_map>
#include <functional>
#include <memory>

#include "../ErrorHandler/InterpreterExceptions.h"
#include "../Decimal/decimal.h"
#include "../Lexer/Lexer.h"
#include "../Token/Token.h"
#include "../Elements/Type.h"
#include "../Elements/OperatorType.h"
#include "../Token/TokenType.h"
#include "../Elements/Program.h"
#include "../Elements/Parameter.h"

#include "../Elements/Statement/IStatement.h"
#include "../Elements/Statement/AssignmentStatement.h"
#include "../Elements/Statement/FunctionCallStatement.h"
#include "../Elements/Statement/FunctionDefinition.h"
#include "../Elements/Statement/IfStatement.h"
#include "../Elements/Statement/InitializeStatement.h"
#include "../Elements/Statement/ReturnStatement.h"
#include "../Elements/Statement/WhileStatement.h"

#include "../Elements/Expression/IExpression.h"
#include "../Elements/Expression/OrExpr.h"
#include "../Elements/Expression/AndExpr.h"
#include "../Elements/Expression/NegationExpr.h"
#include "../Elements/Expression/IsEqualExpr.h"
#include "../Elements/Expression/NotEqualExpr.h"
#include "../Elements/Expression/LessOrEqualExpr.h"
#include "../Elements/Expression/LessExpr.h"
#include "../Elements/Expression/GreaterOrEqualExpr.h"
#include "../Elements/Expression/GreaterExpr.h"
#include "../Elements/Expression/AddExpr.h"
#include "../Elements/Expression/SubExpr.h"
#include "../Elements/Expression/MultExpr.h"
#include "../Elements/Expression/DivExpr.h"
#include "../Elements/Expression/MinusNegExpr.h"
#include "../Elements/Expression/CurrencyExpr.h"
#include "../Elements/Expression/ConversionExpr.h"

#include "../Elements/Expression/LiteralExpr.h"
#include "../Elements/Expression/IdentifierExpr.h"
#include "../Elements/Expression/FunCallExpr.h"

#include "../Elements/Expression/StringLiteralExpr.h"

#include "../ErrorHandler/ErrorReporter.h"
#include "../ConfigParser/ConfigParser.h"

class Parser
{
private:
    Lexer &lexer;
    ConfigParser &configParser;
    Token currentToken;
    std::unordered_map<std::string, std::unique_ptr<FunctionDefinition>> functions;
    std::unordered_map<TokenType, Type> typeMap;
    std::unordered_map<TokenType, OperatorType> operatorTypeMap;
    std::unordered_map<Type, std::function<IExpr(IExpr l, IExpr r)>> exprMap;

    void initTypeMap();
    void initExprMap();

    IExpr getExpr(Type type, IExpr left, IExpr right);

    void getNextToken();
    bool isTokenCorrect(TokenType type) const;
    bool checkAndConsume(TokenType type);
    Type remap(TokenType type);
    Type remapAndConsume();

    bool tryParseFunctionDefinition();

    std::vector<Parameter> parseParameters();
    std::vector<IExpr> parseArguments();

    std::optional<Parameter> tryParseParameter();
    IExpr tryParseArgument();

    std::optional<std::vector<IState>> tryParseStatementsBlock();
    IState tryParseIfStatement();
    IState tryParseWhileStatement();
    IState tryParseReturnStatement();
    IState tryParseFunctionCallOrAsign();
    IState tryParseInitStatement();
    IState tryParseFunctionCallStatement(std::string);
    IState tryParseAssignmentStatement(std::string);

    IExpr tryParseCondition();
    IExpr tryParseLogicFactor();
    IExpr tryParseRelation();
    IExpr tryParseExpression();
    IExpr tryParseFactor();
    IExpr tryParseTerm();
    IExpr tryParseCurrencyConversion();
    IExpr tryParseLiteralExpr();
    IExpr tryParseIdentifierOrFunctionCallExpr();
    IExpr tryParseParenthesisExpr();
    
    IExpr tryParseCurrencyPartExpr(IExpr expr);
    IExpr tryParseStringLiteral();

public:
    Parser(Lexer &lexer, ConfigParser &config);
    Program parse();
};

