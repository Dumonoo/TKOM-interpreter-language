#include "Parser.h"
#include <iostream>

using namespace std;

Parser::Parser(Lexer &lexer, ConfigParser &config)
    : lexer(lexer), configParser(config)
{
    initTypeMap();
    initExprMap();
    getNextToken();
}

Program Parser::parse()
{
    while (tryParseFunctionDefinition())
        ;
    return Program(move(functions));
}

void Parser::getNextToken()
{
    currentToken = lexer.getNextToken();
    while (currentToken.getType() == TokenType::COMMENT_TOKEN)
    {
        currentToken = lexer.getNextToken();
    }
}

void Parser::initTypeMap()
{
    typeMap.clear();
    typeMap = {
        {TokenType::VOID_TOKEN, Type::VOID},
        {TokenType::CUR_TOKEN, Type::CUR},
        {TokenType::NUM_TOKEN, Type::NUM},

        {TokenType::PLUS_TOKEN, Type::PLUS},
        {TokenType::MINUS_TOKEN, Type::MINUS},
        {TokenType::MULTIPLY_TOKEN, Type::MULTIPLY},
        {TokenType::DIVISION_TOKEN, Type::DIVISION},
        {TokenType::GREATOREQUAL_TOKEN, Type::GREATER_OR_EQUAL},
        {TokenType::GREATER_TOKEN, Type::GREATER},
        {TokenType::LESSOREQUAL_TOKEN, Type::LESS_OR_EQUAL},
        {TokenType::LESS_TOKEN, Type::LESS},
        {TokenType::ISEQUAL_TOKEN, Type::IS_EQUAL},
        {TokenType::NOTEQUAL_TOKEN, Type::NOT_EQUAL}};
}

void Parser::initExprMap()
{
    exprMap.clear();
    exprMap = {
        {Type::PLUS, [](IExpr left, IExpr right)
         { return make_unique<AddExpr>(move(left), move(right)); }},
        {Type::MINUS, [](IExpr left, IExpr right)
         { return make_unique<SubExpr>(move(left), move(right)); }},
        {Type::MULTIPLY, [](IExpr left, IExpr right)
         { return make_unique<MultExpr>(move(left), move(right)); }},
        {Type::DIVISION, [](IExpr left, IExpr right)
         { return make_unique<DivExpr>(move(left), move(right)); }},
        {Type::GREATER_OR_EQUAL, [](IExpr left, IExpr right)
         { return make_unique<GreaterOrEqualExpr>(move(left), move(right)); }},
        {Type::GREATER, [](IExpr left, IExpr right)
         { return make_unique<GreaterExpr>(move(left), move(right)); }},
        {Type::LESS_OR_EQUAL, [](IExpr left, IExpr right)
         { return make_unique<LessOrEqualExpr>(move(left), move(right)); }},
        {Type::LESS, [](IExpr left, IExpr right)
         { return make_unique<LessExpr>(move(left), move(right)); }},
        {Type::IS_EQUAL, [](IExpr left, IExpr right)
         { return make_unique<IsEqualExpr>(move(left), move(right)); }},
        {Type::NOT_EQUAL, [](IExpr left, IExpr right)
         { return make_unique<NotEqualExpr>(move(left), move(right)); }}};
}

IExpr Parser::getExpr(Type type, IExpr left, IExpr right)
{
    auto it = exprMap.find(type);
    if (it == exprMap.end())
    {
        throw FatalError("getExpr");
    }
    return it->second(move(left), move(right));
}

bool Parser::isTokenCorrect(TokenType type) const
{
    if (currentToken.getType() != type)
        return false;
    return true;
}

bool Parser::checkAndConsume(TokenType type)
{
    if (!isTokenCorrect(type))
        return false;
    getNextToken();
    return true;
}

Type Parser::remap(TokenType type)
{
    auto it = typeMap.find(type);
    if (it == typeMap.end())
    {
        throw FatalError("remap");
    }
    return it->second;
}

Type Parser::remapAndConsume()
{
    Type typeMaped = remap(currentToken.getType());
    getNextToken();
    return typeMaped;
}

// funcionDef = typeFun, identifier, "(", parameters, ")", statemantsBlock;
bool Parser::tryParseFunctionDefinition()
{
    if (!(isTokenCorrect(TokenType::NUM_TOKEN) ||
          isTokenCorrect(TokenType::CUR_TOKEN) ||
          isTokenCorrect(TokenType::VOID_TOKEN)))
        return false;
    Type type = remapAndConsume();
    if (!isTokenCorrect(TokenType::IDENTIFIER_TOKEN))
    {
        std::vector<TokenType> expectedTypes = {TokenType::IDENTIFIER_TOKEN};
        UnexpectedToken err(expectedTypes);
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseFunctionDefinition");
    }
    string functionName = currentToken.getString();
    getNextToken();

    if (!checkAndConsume(TokenType::LPAREN_TOKEN))
    {
        MissingElement err("(");
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseFunctionDefinition");
    }
    vector<Parameter> parameters = parseParameters();
    if (!checkAndConsume(TokenType::RPAREN_TOKEN))
    {
        MissingElement err(")");
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseFunctionDefinition");
    }
    auto instructions = tryParseStatementsBlock();
    if (!instructions)
    {
        MissingElement err("{");
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseFunctionDefinition");
    }

    if (!functions.insert({functionName, make_unique<FunctionDefinition>(type, functionName, parameters, move(instructions.value()))}).second)
    {
        RedefinitionOf err(functionName);
        ErrorReporter::reportError(err);
        throw FatalError("tryParseFunctionDefinition");
    }
    return true;
}

// parameters = [parameter, {",", parameter}];
vector<Parameter> Parser::parseParameters()
{
    vector<Parameter> parameters;
    optional<Parameter> parameter = tryParseParameter();
    if (!parameter)
        return parameters;
    parameters.push_back(parameter.value());

    while (checkAndConsume(TokenType::COMMA_TOKEN))
    {
        parameter = tryParseParameter();
        if (!parameter)
        {
            ExpectedParameter err;
            ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
            throw FatalError("parseParameters");
        }
        parameters.push_back(parameter.value());
    }
    return parameters;
}

// parameter = type, identifier;
optional<Parameter> Parser::tryParseParameter()
{
    if (!(isTokenCorrect(TokenType::NUM_TOKEN) ||
          isTokenCorrect(TokenType::CUR_TOKEN)))
        return nullopt;
    Type type = remapAndConsume();
    if (!isTokenCorrect(TokenType::IDENTIFIER_TOKEN))
    {
        std::vector<TokenType> expectedTypes = {TokenType::IDENTIFIER_TOKEN};
        UnexpectedToken err(expectedTypes);
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseParameter");
    }
    string parameterName = currentToken.getString();
    getNextToken();
    return Parameter(type, parameterName);
}
// statementsBlock= "{", {statement}, "}";
// statement = ifState | whileState | returnState | funCallOrAssign | initState;
optional<vector<IState>> Parser::tryParseStatementsBlock()
{
    if (!checkAndConsume(TokenType::LCURLY_TOKEN))
    {
        return nullopt;
    }
    vector<IState> statements;
    IState statement;

    while (
        (statement = tryParseIfStatement()) ||
        (statement = tryParseWhileStatement()) ||
        (statement = tryParseReturnStatement()) ||
        (statement = tryParseFunctionCallOrAsign()) ||
        (statement = tryParseInitStatement()))
    {
        statements.push_back(move(statement));
    }
    if (!checkAndConsume(TokenType::RCURLY_TOKEN))
    {
        MissingElementBefore err("}");
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseStatementsBlock");
    }
    return statements;
}

// ifState = "if", "(", condition, ")", statementsBlock, ["else", statementsBlock];
IState Parser::tryParseIfStatement()
{
    // Sprawdzić jeszcze else żeby wyświetlić fancy błąd?
    if (!checkAndConsume(TokenType::IF_TOKEN))
        return nullptr;

    if (!checkAndConsume(TokenType::LPAREN_TOKEN))
    {
        std::vector<TokenType> expectedTypes = {TokenType::IF_TOKEN};
        MissingElementAfter err("(", expectedTypes);
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseIfStatement");
    }
    IExpr condition = tryParseCondition();
    if (!condition)
    {
        ExpectedCondition err;
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseIfStatement");
    }
    if (!checkAndConsume(TokenType::RPAREN_TOKEN))
    {
        MissingElementBefore err(")");
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseIfStatement");
    }
    auto ifInstructions = tryParseStatementsBlock();
    if (!ifInstructions)
    {
        MissingElement err("{");
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseIfStatement");
    }
    if (checkAndConsume(TokenType::ELSE_TOKEN))
    {
        auto elseInstructions = tryParseStatementsBlock();
        if (!elseInstructions)
        {
            MissingElement err("{");
            ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
            throw FatalError("tryParseIfStatement");
        }
        return make_unique<IfStatement>(move(condition), move(ifInstructions.value()), move(elseInstructions.value()));
    }
    return make_unique<IfStatement>(move(condition), move(ifInstructions.value()));
}

// whileState = "while", "(", condition, ")", statementsBlock;
IState Parser::tryParseWhileStatement()
{
    if (!checkAndConsume(TokenType::WHILE_TOKEN))
        return nullptr;
    if (!checkAndConsume(TokenType::LPAREN_TOKEN))
    {
        std::vector<TokenType> expectedTypes = {TokenType::WHILE_TOKEN};
        MissingElementAfter err("(", expectedTypes);
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseWhileStatement");
    }
    IExpr condition = tryParseCondition();
    if (!condition)
    {
        ExpectedCondition err;
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseWhileStatement");
    }
    if (!checkAndConsume(TokenType::RPAREN_TOKEN))
    {
        std::vector<TokenType> expectedTypes = {};
        MissingElementBefore err(")", expectedTypes);
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseWhileStatement");
    }
    auto whileInstructions = tryParseStatementsBlock();
    if (!whileInstructions)
    {
        MissingElement err("{");
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseWhileStatement");
    }
    return make_unique<WhileStatement>(move(condition), move(whileInstructions.value()));
}

// returnState = "return", [expression], ";";
IState Parser::tryParseReturnStatement()
{
    if (!checkAndConsume(TokenType::RETURN_TOKEN))
        return nullptr;

    IExpr returnExpression = tryParseExpression();
    if (!checkAndConsume(TokenType::SEMICOLON_TOKEN))
    {
        std::vector<TokenType> expectedTypes = {TokenType::RETURN_TOKEN};
        MissingElementAfter err(";", expectedTypes);
        ErrorReporter::reportWarning(err, currentToken.getPosition(), lexer.getCharacterStream());
    }
    if (returnExpression)
        return make_unique<ReturnStatement>(move(returnExpression));
    return make_unique<ReturnStatement>();
}

// funCallOrAssign= identifier, (funCallState | assignState );
IState Parser::tryParseFunctionCallOrAsign()
{
    if (!isTokenCorrect(TokenType::IDENTIFIER_TOKEN))
        return nullptr;
    string identifier = currentToken.getString();
    getNextToken();
    IState statement;
    if (!((statement = tryParseFunctionCallStatement(identifier)) ||
          (statement = tryParseAssignmentStatement(identifier))))
    {
        std::vector<TokenType> expectedTypes = {TokenType::ASSIGN_TOKEN, TokenType::LPAREN_TOKEN};
        UnexpectedToken err(expectedTypes);
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseFunctionCallOrAsign");
    }
    return statement;
}

// funCallState = "(", arguments, ")", ";" ;
IState Parser::tryParseFunctionCallStatement(string functionName)
{
    if (!checkAndConsume(TokenType::LPAREN_TOKEN))
        return nullptr;
    vector<IExpr> arguments = parseArguments();
    if (!checkAndConsume(TokenType::RPAREN_TOKEN))
    {
        MissingElementBefore err(")");
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseFunctionCallStatement");
    }
    if (!checkAndConsume(TokenType::SEMICOLON_TOKEN))
    {
        MissingElementBefore err(";");
        ErrorReporter::reportWarning(err, currentToken.getPosition(), lexer.getCharacterStream());
    }
    return make_unique<FunctionCallStatement>(functionName, move(arguments));
}

// assignState = "=", expression, ";" ;
IState Parser::tryParseAssignmentStatement(string variableName)
{
    if (!checkAndConsume(TokenType::ASSIGN_TOKEN))
        return nullptr;
    IExpr expr = tryParseExpression();
    if (!expr)
    {
        ExpectedExpressionAfter err("=");
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseAssignmentStatement");
    }
    if (!checkAndConsume(TokenType::SEMICOLON_TOKEN))
    {
        MissingElementBefore err(";");
        ErrorReporter::reportWarning(err, currentToken.getPosition(), lexer.getCharacterStream());
    }
    return make_unique<AssignmentStatement>(variableName, move(expr));
}
// arguments = [ argument, {",", argument}];
vector<IExpr> Parser::parseArguments()
{
    vector<IExpr> arguments;
    IExpr argument = tryParseArgument();
    if (!argument)
        return arguments;
    arguments.push_back(move(argument));
    while (checkAndConsume(TokenType::COMMA_TOKEN))
    {
        argument = tryParseArgument();
        if (!argument)
        {
            ExpectedArgument err;
            ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
            throw FatalError("parseArguments");
        }
        arguments.push_back(move(argument));
    }
    return arguments;
}

// initState = type, identifier, "=", expression, ";";
IState Parser::tryParseInitStatement()
{
    if (!(isTokenCorrect(TokenType::NUM_TOKEN) || isTokenCorrect(TokenType::CUR_TOKEN)))
        return nullptr;
    Type type = remapAndConsume();
    if (!isTokenCorrect(TokenType::IDENTIFIER_TOKEN))
    {
        std::vector<TokenType> expectedTypes = {TokenType::IDENTIFIER_TOKEN};
        UnexpectedToken err(expectedTypes);
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseInitStatement");
    }
    string variableName = currentToken.getString();
    getNextToken();
    if (!checkAndConsume(TokenType::ASSIGN_TOKEN))
    {
        MissingElementBefore err("=");
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseInitStatement");
    }
    IExpr expr = tryParseExpression();
    if (!expr)
    {
        ExpectedExpressionAfter err("=");
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseInitStatement");
    }
    if (!checkAndConsume(TokenType::SEMICOLON_TOKEN))
    {
        std::vector<TokenType> expectedTypes = {};
        MissingElementBefore err(";", expectedTypes);
        ErrorReporter::reportWarning(err, currentToken.getPosition(), lexer.getCharacterStream());
    }
    return make_unique<InitializeStatement>(type, variableName, move(expr));
}

// argument = expression | stringLiteral;
IExpr Parser::tryParseArgument()
{
    IExpr expr;
    if (!((expr = tryParseExpression()) ||
          (expr = tryParseStringLiteral())))
        return nullptr;
    return expr;
}

IExpr Parser::tryParseStringLiteral()
{
    if (!isTokenCorrect(TokenType::TEXTCONST_TOKEN))
        return nullptr;
    string textConstant = currentToken.getString();
    getNextToken();
    return make_unique<StringLiteralExpr>(textConstant);
}

// condition = logicFactor, {orOpr, logicFactor};
IExpr Parser::tryParseCondition()
{
    IExpr leftExpr = tryParseLogicFactor();
    if (!leftExpr)
        return nullptr;
    while (isTokenCorrect(TokenType::OR_TOKEN))
    {
        getNextToken();
        IExpr rightExpr = tryParseLogicFactor();
        if (!rightExpr)
        {
            ExpectedExpressionBefore err("");
            ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
            throw FatalError("tryParseCondition");
        }
        leftExpr = make_unique<OrExpr>(move(leftExpr), move(rightExpr));
    }
    return leftExpr;
}

// logicFactor = relation, {andOpr, relation};
IExpr Parser::tryParseLogicFactor()
{
    IExpr leftExpr = tryParseRelation();
    if (!leftExpr)
        return nullptr;
    while (isTokenCorrect(TokenType::AND_TOKEN))
    {
        getNextToken();
        IExpr rightExpr = tryParseRelation();
        if (!rightExpr)
        {
            ExpectedExpressionBefore err("");
            ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
            throw FatalError("tryParseLogicFactor");
        }
        leftExpr = make_unique<AndExpr>(move(leftExpr), move(rightExpr));
    }
    return leftExpr;
}

// relation = [negOpr], expression, [relOpr, expression];
// expression , [relOpr, expression]
// negOpr , expression , relOpr, expression
IExpr Parser::tryParseRelation()
{
    bool negate = checkAndConsume(TokenType::NEGATION_TOKEN);
    if (negate)
        cout << "BYLA NEGACJA" << endl;
    IExpr leftExpr = tryParseExpression();
    if (!leftExpr)
    {
        if (negate)
        {
            ExpectedExpressionAfter err("!");
            ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
            throw FatalError("tryParseRelation");
        }
        return nullptr;
    }
    if (isTokenCorrect(TokenType::GREATOREQUAL_TOKEN) ||
        isTokenCorrect(TokenType::GREATER_TOKEN) ||
        isTokenCorrect(TokenType::LESSOREQUAL_TOKEN) ||
        isTokenCorrect(TokenType::LESS_TOKEN) ||
        isTokenCorrect(TokenType::ISEQUAL_TOKEN) ||
        isTokenCorrect(TokenType::NOTEQUAL_TOKEN))
    {
        Type type = remapAndConsume();
        IExpr rightExpr = tryParseExpression();
        if (!rightExpr)
        {
            ExpectedExpressionBefore err("");
            ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
            throw FatalError("tryParseRelation");
        }
        leftExpr = getExpr(type, move(leftExpr), move(rightExpr));
    }
    if (negate)
    {
        leftExpr = make_unique<NegationExpr>(move(leftExpr));
    }
    return leftExpr;
}

// expression = factor, {addOpr, factor};
IExpr Parser::tryParseExpression()
{
    IExpr leftExpr = tryParseFactor();
    if (!leftExpr)
        return nullptr;
    while (isTokenCorrect(TokenType::PLUS_TOKEN) || isTokenCorrect(TokenType::MINUS_TOKEN))
    {
        Type type = remapAndConsume();
        IExpr rightExpr = tryParseFactor();
        if (!rightExpr)
        {
            ExpectedExpressionBefore err("");
            ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
            throw FatalError("tryParseExpression");
        }
        leftExpr = getExpr(type, move(leftExpr), move(rightExpr));
    }
    return leftExpr;
}

// factor = term, {multiOpr, term};
IExpr Parser::tryParseFactor()
{
    IExpr leftExpr = tryParseTerm();
    if (!leftExpr)
        return nullptr;
    while (isTokenCorrect(TokenType::MULTIPLY_TOKEN) || isTokenCorrect(TokenType::DIVISION_TOKEN))
    {
        Type type = remapAndConsume();
        IExpr rightExpr = tryParseTerm();
        if (!rightExpr)
        {
            ExpectedExpressionBefore err("");
            ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
            throw FatalError("tryParseFactor");
        }
        leftExpr = getExpr(type, move(leftExpr), move(rightExpr));
    }
    return leftExpr;
}

// term = [minOpr], currencyConv;
IExpr Parser::tryParseTerm()
{
    bool minusNegation = checkAndConsume(TokenType::MINUS_TOKEN);
    IExpr expr = tryParseCurrencyConversion();

    if (!expr)
    {
        if (minusNegation)
        {
            ExpectedExpressionAfter err("-");
            ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
            throw FatalError("tryParseTerm");
        }
        return nullptr;
    }
    if (minusNegation)
        return make_unique<MinusNegExpr>(move(expr));
    return expr;
}
// currencyConv = (literal | identOrFuncall | parenthesis) [currentPart];
IExpr Parser::tryParseCurrencyConversion()
{
    IExpr expr;

    if (!((expr = tryParseLiteralExpr()) ||
          (expr = tryParseIdentifierOrFunctionCallExpr()) ||
          (expr = tryParseParenthesisExpr())))
    {
        return nullptr;
    }
    expr = tryParseCurrencyPartExpr(move(expr));
    return expr;
}

// literal = decimalNumber;
IExpr Parser::tryParseLiteralExpr()
{
    if (!isTokenCorrect(TokenType::NUMBER_TOKEN))
        return nullptr;
    dec::decimal<MAX_DECIMAL_POINTS> decimalValue = currentToken.getDecimal();
    getNextToken();
    return make_unique<LiteralExpr>(decimalValue);
}

// identOrFuncall = identifier, ["(", arguments, ")"];
IExpr Parser::tryParseIdentifierOrFunctionCallExpr()
{
    if (!isTokenCorrect(TokenType::IDENTIFIER_TOKEN))
        return nullptr;
    string identifier = currentToken.getString();
    getNextToken();
    if (checkAndConsume(TokenType::LPAREN_TOKEN))
    {
        vector<IExpr> arguments = parseArguments();

        if (!checkAndConsume(TokenType::RPAREN_TOKEN))
        {
            MissingElementBefore err(")");
            ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
            throw FatalError("tryParseIdentifierOrFunctionCallExpr");
        }
        return make_unique<FunCallExpr>(identifier, move(arguments));
    }
    return make_unique<IdentifierExpr>(identifier);
}

// parenthesis = "(", condition, ")";
IExpr Parser::tryParseParenthesisExpr()
{
    if (!checkAndConsume(TokenType::LPAREN_TOKEN))
        return nullptr;
    IExpr condition = tryParseCondition();
    if (!condition)
    {
        ExpectedExpressionBefore err("");
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseParenthesisExpr");
    }
    if (!checkAndConsume(TokenType::RPAREN_TOKEN))
    {
        MissingElementBefore err(")");
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseParenthesisExpr");
    }
    // return make_unique<ParenthesisExpr>(move(condition));
    return condition;
}

// currencyPart = identifier | "@", identifier;
IExpr Parser::tryParseCurrencyPartExpr(IExpr expr)
{
    if (!(isTokenCorrect(TokenType::IDENTIFIER_TOKEN) || isTokenCorrect(TokenType::AT_TOKEN)))
        return expr;

    if (checkAndConsume(TokenType::AT_TOKEN))
    {
        if (!isTokenCorrect(TokenType::IDENTIFIER_TOKEN))
        {
            std::vector<TokenType> expectedTypes = {TokenType::IDENTIFIER_TOKEN};
            UnexpectedToken err(expectedTypes);
            ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
            throw FatalError("tryParseCurrencyPartExpr");
        }
        string currencyVariableName = currentToken.getString();
        if (auto denominations = configParser.getDenominations(currencyVariableName); denominations)
        {
            CurrencyInIdentifierInConversion err(currencyVariableName);
            ErrorReporter::reportWarning(err, currentToken.getPosition(), lexer.getCharacterStream());
            getNextToken();
            return make_unique<CurrencyExpr>(move(expr), currencyVariableName, denominations.value());
        }
        getNextToken();
        return make_unique<ConversionExpr>(move(expr), currencyVariableName);
    }
    string currencyName = currentToken.getString();
    auto denominations = configParser.getDenominations(currencyName);
    if (!denominations)
    {
        UnknownCurrency err(currencyName);
        ErrorReporter::reportError(err, currentToken.getPosition(), lexer.getCharacterStream());
        throw FatalError("tryParseCurrencyPartExpr");
    }
    getNextToken();
    return make_unique<CurrencyExpr>(move(expr), currencyName, denominations.value());
}