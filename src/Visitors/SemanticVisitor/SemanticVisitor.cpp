#include "SemanticVisitor.h"
#include "../../ErrorHandler/InterpreterExceptions.h"
#include <iostream>

using namespace std;

SemanticVisitor::SemanticVisitor(Program &program)
    : currentProgram(program){};

void SemanticVisitor::visit(const Program &program)
{
    for (auto &i : currentProgram.getFunctions())
    {
        programEnvironment.prepareNewCallContext(i.first);
        i.second->accept(*this);
        programEnvironment.clearEnvironment();
    }
}
void SemanticVisitor::visit(const EmbeddedFunction &statement)
{
}
void SemanticVisitor::visit(const FunctionDefinition &function)
{
    currentFunctionType = function.getType();
    currentFunctionName = function.getFunctionName();
    programEnvironment.enterNewScope();
    for (auto i : function.getParameters())
    {
        if (!programEnvironment.tryRegisterArgument(i.getType(), i.getIdentifier()))
        {
            ParameterRedefinition err(currentFunctionName, i.getIdentifier());
            ErrorReporter::reportError(err);
            throw FatalError("visit_FunctionDefinition");
        }
    }
    programEnvironment.enterNewScope();
    for (auto &i : function.getInstructions())
    {
        i->accept(*this);
    }
}

void SemanticVisitor::visit(const AssignmentStatement &statement)
{
    auto oldVariable = programEnvironment.getVariable(statement.getIdentifier());
    if (!oldVariable)
    {
        UndefindedVaraibale err(statement.getIdentifier(), currentFunctionName);
        ErrorReporter::reportError(err);
        throw FatalError("visit_AssignmentStatement");
    }
    currentExpressionType.reset();
    statement.getExpr()->accept(*this);

    if (currentExpressionType.value() != oldVariable.value().getType())
    {
        AssignmentInvalidType err(statement.getIdentifier(), oldVariable.value().getType());
        ErrorReporter::reportError(err);
        throw FatalError("visit_AssignmentStatement");
    }
}

void SemanticVisitor::visit(const FunctionCallStatement &statement)
{
    auto &arguments = statement.getArguments();
    auto &functions = currentProgram.getFunctions();
    auto functionName = statement.getIdentifier();
    auto function = functions.find(functionName);

    if (function == functions.end())
    {
        CallOfUndefindedFunction err(functionName, currentFunctionName);
        ErrorReporter::reportError(err);
        throw FatalError("visit_FunctionCallStatement");
    }

    if (function->second->isEmbeded() && function->second->isParametersObscure())
    {
        auto itA = arguments.begin();
        while (itA != arguments.end())
        {
            currentExpressionType.reset();
            itA->get()->accept(*this);
            ++itA;
        }
        return;
    }

    auto parameters = function->second->getParameters();
    if (parameters.size() != arguments.size())
    {
        InvalidArgumentCount err(functionName, currentFunctionName, parameters.size(), arguments.size());
        ErrorReporter::reportError(err);
        throw FatalError("visit_FunctionCallStatement");
    }
    auto itA = arguments.begin();
    auto itB = parameters.begin();
    while (itA != arguments.end() || itB != parameters.end())
    {
        currentExpressionType.reset();
        itA->get()->accept(*this);
        if (currentExpressionType.value() != itB->getType())
        {
            InvalidArgumentType err(functionName, currentFunctionName, itB->getIdentifier(), itB->getType(), currentExpressionType.value());
            ErrorReporter::reportError(err);
            throw FatalError("visit_FunctionCallStatement");
        }
        ++itA;
        ++itB;
    }
}

void SemanticVisitor::visit(const IfStatement &statement)
{
    statement.getCondition()->accept(*this);
    programEnvironment.enterNewScope();
    for (auto &ins : statement.getIfInstructions())
    {
        ins->accept(*this);
    }
    programEnvironment.leaveScope();
    programEnvironment.enterNewScope();
    for (auto &ins : statement.getElseInstructions())
    {
        ins->accept(*this);
    }
    programEnvironment.leaveScope();
}

void SemanticVisitor::visit(const InitializeStatement &statement)
{
    currentExpressionType.reset();
    statement.getInitialValue()->accept(*this);
    if (currentExpressionType.value() != statement.getType())
    {
        InvalidInitialValueType err(currentFunctionName, statement.getVariableName(), statement.getType(), currentExpressionType.value());
        ErrorReporter::reportError(err);
        throw FatalError("visit_InitializeStatement");
    }

    if (!programEnvironment.tryRegisterVariable(statement.getType(), statement.getVariableName()))
    {
        VariableRedeclaration err(statement.getVariableName(), currentFunctionName);
        ErrorReporter::reportError(err);
        throw FatalError("visit_InitializeStatement");
    }
}

void SemanticVisitor::visit(const ReturnStatement &statement)
{

    auto &retExpr = statement.getReturnExpression();
    if (!retExpr)
    {
        if (currentFunctionType.value() != Type::VOID)
        {
            MissingReturnExpression err(currentFunctionName, currentFunctionType.value());
            ErrorReporter::reportError(err);
            throw FatalError("visit_ReturnStatement");
        }
    }
    else
    {
        currentExpressionType.reset();
        retExpr.value()->accept(*this);
        if (currentExpressionType.value() != currentFunctionType.value())
        {
            InvalidReturnType err(currentFunctionName, currentFunctionType.value());
            ErrorReporter::reportError(err);
            throw FatalError("visit_ReturnStatement");
        }
    }
}

void SemanticVisitor::visit(const WhileStatement &statement)
{
    statement.getCondition()->accept(*this);
    programEnvironment.enterNewScope();
    for (auto &ins : statement.getInstructions())
    {
        ins->accept(*this);
    }
    programEnvironment.leaveScope();
}

void SemanticVisitor::visit(const OrExpr &expr)
{
    expr.getLeft()->accept(*this);
    expr.getRight()->accept(*this);
}

void SemanticVisitor::visit(const AndExpr &expr)
{
    expr.getLeft()->accept(*this);
    expr.getRight()->accept(*this);
}

void SemanticVisitor::visit(const NegationExpr &expr)
{
    expr.getExpr()->accept(*this);
}

void SemanticVisitor::visit(const IsEqualExpr &expr)
{
    checkBothSidesTypes(expr.getLeft(), expr.getRight(), Type::IS_EQUAL);
}

void SemanticVisitor::visit(const NotEqualExpr &expr)
{
    checkBothSidesTypes(expr.getLeft(), expr.getRight(), Type::NOT_EQUAL);
}

void SemanticVisitor::visit(const LessOrEqualExpr &expr)
{
    checkBothSidesTypes(expr.getLeft(), expr.getRight(), Type::LESS_OR_EQUAL);
}

void SemanticVisitor::visit(const LessExpr &expr)
{
    checkBothSidesTypes(expr.getLeft(), expr.getRight(), Type::LESS);
}

void SemanticVisitor::visit(const GreaterOrEqualExpr &expr)
{
    checkBothSidesTypes(expr.getLeft(), expr.getRight(), Type::GREATER_OR_EQUAL);
}

void SemanticVisitor::visit(const GreaterExpr &expr)
{
    checkBothSidesTypes(expr.getLeft(), expr.getRight(), Type::GREATER);
}

void SemanticVisitor::visit(const AddExpr &expr)
{
    checkBothSidesTypes(expr.getLeft(), expr.getRight(), Type::PLUS);
}

void SemanticVisitor::visit(const SubExpr &expr)
{
    checkBothSidesTypes(expr.getLeft(), expr.getRight(), Type::MINUS);
}

void SemanticVisitor::visit(const MultExpr &expr)
{
    Type leftType;
    currentExpressionType.reset();
    expr.getLeft()->accept(*this);
    leftType = currentExpressionType.value();
    currentExpressionType.reset();
    expr.getRight()->accept(*this);
    if (leftType == currentExpressionType.value() && leftType == Type::CUR)
    {
        MulitplicationOfTwoCurrencies err(currentFunctionName);
        ErrorReporter::reportError(err);
        throw FatalError("visit_MultExpr");
    }
    else if ((leftType == Type::CUR && currentExpressionType.value() == Type::NUM) || (leftType == Type::NUM && currentExpressionType.value() == Type::CUR))
        currentExpressionType = Type::CUR;

    else if (leftType == currentExpressionType.value() && leftType == Type::NUM)
        currentExpressionType = Type::NUM;
}

void SemanticVisitor::visit(const DivExpr &expr)
{
    Type leftType;
    currentExpressionType.reset();
    expr.getLeft()->accept(*this);
    leftType = currentExpressionType.value();
    currentExpressionType.reset();
    expr.getRight()->accept(*this);
    if (leftType == Type::NUM && currentExpressionType.value() == Type::CUR)
    {
        DividingNumberByCurrency err(currentFunctionName);
        ErrorReporter::reportError(err);
        throw FatalError("visit_DivExpr");
    }
    else if ((leftType == Type::CUR && currentExpressionType.value() == Type::CUR) || (leftType == Type::NUM && currentExpressionType.value() == Type::NUM))
        currentExpressionType = Type::NUM;

    else if (leftType == Type::CUR && currentExpressionType.value() == Type::NUM)
        currentExpressionType = Type::CUR;
}

void SemanticVisitor::visit(const MinusNegExpr &expr)
{
    expr.getExpr()->accept(*this);
}

void SemanticVisitor::visit(const CurrencyExpr &expr)
{
    expr.getExpr()->accept(*this);
    currentExpressionType = Type::CUR;
}

void SemanticVisitor::visit(const ConversionExpr &expr)
{
    auto currencyVariable = programEnvironment.getVariable(expr.getCurrencyVariableName());
    if (!currencyVariable)
    {
        UndefindedVaraibale err(expr.getCurrencyVariableName(), currentFunctionName);
        ErrorReporter::reportError(err);
        throw FatalError("visit_ConversionExpr");
    }
    if (currencyVariable.value().getType() != Type::CUR)
    {
        ConversionToNumeric err(currentFunctionName, expr.getCurrencyVariableName());
        ErrorReporter::reportError(err);
        throw FatalError("visit_ConversionExpr");
    }
    expr.getExpr()->accept(*this);
    currentExpressionType = Type::CUR;
}

void SemanticVisitor::visit(const LiteralExpr &expr)
{
    currentExpressionType = Type::NUM;
}

void SemanticVisitor::visit(const IdentifierExpr &expr)
{
    auto variable = programEnvironment.getVariable(expr.getIdentifier());
    if (!variable)
    {
        UndefindedVaraibale err(expr.getIdentifier(), currentFunctionName);
        ErrorReporter::reportError(err);
        throw FatalError("visit_IdentifierExpr");
    }
    currentExpressionType = variable.value().getType();
}

void SemanticVisitor::visit(const FunCallExpr &expr)
{
    auto &arguments = expr.getArguments();
    auto &functions = currentProgram.getFunctions();
    auto functionName = expr.getFunctionIdentifer();

    auto function = functions.find(functionName);
    if (function == functions.end())
    {
        CallOfUndefindedFunction err(functionName, currentFunctionName);
        ErrorReporter::reportError(err);
        throw FatalError("visit_FunctionCallStatement");
    }
    if (function->second->isEmbeded() && function->second->isParametersObscure())
    {
        currentExpressionType = function->second->getType();
        return;
    }
    auto parameters = function->second->getParameters();
    if (parameters.size() != arguments.size())
    {
        InvalidArgumentCount err(functionName, currentFunctionName, parameters.size(), arguments.size());
        ErrorReporter::reportError(err);
        throw FatalError("visit_FunctionCallStatement");
    }
    auto itA = arguments.begin();
    auto itB = parameters.begin();
    while (itA != arguments.end() || itB != parameters.end())
    {
        currentExpressionType.reset();
        itA->get()->accept(*this);
        if (currentExpressionType.value() != itB->getType())
        {
            InvalidArgumentCount err(functionName, currentFunctionName, parameters.size(), arguments.size());
            ErrorReporter::reportError(err);
            throw FatalError("visit_FunctionCallStatement");
        }
        ++itA;
        ++itB;
    }
    currentExpressionType = function->second->getType();
}

void SemanticVisitor::visit(const StringLiteralExpr &expr)
{
    currentExpressionType = Type::VOID;
}

void SemanticVisitor::visit(const Parameter &expr)
{

}

void SemanticVisitor::checkBothSidesTypes(const IExpr &left, const IExpr &right, Type t)
{
    Type leftType;
    currentExpressionType.reset();
    left->accept(*this);
    leftType = currentExpressionType.value();
    currentExpressionType.reset();
    right->accept(*this);
    if (leftType != currentExpressionType.value())
    {
        MissMatchOperandTypes err(currentFunctionName, t, leftType, currentExpressionType.value());
        ErrorReporter::reportError(err);
        throw FatalError("checkBothSidesTypes");
    }
}