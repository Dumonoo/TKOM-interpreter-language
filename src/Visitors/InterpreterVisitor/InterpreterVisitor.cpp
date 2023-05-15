#include "InterpreterVisitor.h"

using namespace std;

InterpreterVisitor::InterpreterVisitor(Program &program, std::string mainFunctionName, std::unordered_map<std::string, std::unordered_map<std::string, dec::decimal<MAX_DECIMAL_POINTS>>> curMap)
    : currentProgram(program), mainFunctionName(mainFunctionName), curriencies(curMap)
{
    visit(program);
}

void InterpreterVisitor::visit(const Program &program)
{
    auto &functions = currentProgram.getFunctions();
    auto function = functions.find(mainFunctionName);
    if (function == functions.end())
    {
        MissingProperMainFunction err(mainFunctionName);
        ErrorReporter::reportRuntimeError(err);
        throw RunTimeError("visit_Program");
    }
    auto parameters = function->second->getParameters();

    programEnvironment.prepareNewCallContext(mainFunctionName);
    currentFunctionType = function->second->getType();
    if (function->second->getParameters().size() > 0)
    {
        MissingProperMainFunction err(mainFunctionName);
        ErrorReporter::reportRuntimeError(err);
        throw RunTimeError("visit_Program");
    }
    programEnvironment.enterNewScope();
    function->second->accept(*this);
    programEnvironment.leaveCallContext();
}

void InterpreterVisitor::visit(const EmbeddedFunction &statement)
{
    auto embededFunctionName = programEnvironment.getTopCallStackFunctionName();

    if (embededFunctionName == "print")
    {
        auto obscureParameters = programEnvironment.getEvaluetedArguments();
        for (auto &pairArg : obscureParameters)
        {
            std::visit([](const auto &arg)
                       { cout << arg; },
                       pairArg.second.getValue());
        }
    }
    if (embededFunctionName == "scanNum")
    {
        int retries = 3;
        string number;

        while (retries >= 1)
        {
            cin >> number;
            auto num = tryBuildNumber(number);
            if (num)
            {
                currentCurrencyDenominations.reset();
                currentCurrencyIdentifier.reset();
                currentExpressionType = Type::NUM;
                currentValue = num.value();
                return;
            }
            else
            {
                retries -= 1;
            }
        }
        InvalidNumberScanNum err(retries);
        ErrorReporter::reportRuntimeError(err);
        throw RunTimeError("scanNum");
    }
    if (embededFunctionName == "scanCur")
    {
        int retries = 3;
        string currency;
        while (retries >= 1)
        {
            cin >> currency;
            auto curr = curriencies.find(currency);
            if (curr != curriencies.end())
            {
                currentValue = 1;
                currentCurrencyIdentifier = curr->first;
                currentCurrencyDenominations = curr->second;
                currentExpressionType = Type::CUR;
                return;
            }
            else
            {
                for (auto &i : curriencies)
                {
                    cout << i.first << " ";
                }
                cout << endl;
                retries -= 1;
            }
        }
        InvalidCurrencySymbol err(retries);
        ErrorReporter::reportRuntimeError(err);
        throw RunTimeError("scanNum");
    }
}

void InterpreterVisitor::visit(const FunctionDefinition &function)
{
    auto previouseFunctionType = currentFunctionType.value();
    currentFunctionType = function.getType();
    programEnvironment.enterNewScope();
    auto instIter = function.getInstructions().begin();
    while (instIter != function.getInstructions().end() && !isReturning)
    {
        (*instIter).get()->accept(*this);
        ++instIter;
    }
    if (!isReturning && currentFunctionType != Type::VOID)
    {
        NoReturn err(function.getFunctionName());
        ErrorReporter::reportRuntimeError(err);
        throw RunTimeError("visit_FunctionDefinition");
    }
    isReturning = false;
    currentFunctionType = previouseFunctionType;
}

void InterpreterVisitor::visit(const AssignmentStatement &statement)
{
    auto oldVariable = programEnvironment.getVariable(statement.getIdentifier());
    currentExpressionType.reset();
    currentValue.reset();
    currentCurrencyIdentifier.reset();
    currentCurrencyDenominations.reset();
    statement.getExpr()->accept(*this);

    if (currentExpressionType.value() == Type::NUM)
        programEnvironment.setNewVariableValue(statement.getIdentifier(), currentValue.value());
    if (currentExpressionType.value() == Type::CUR)
        programEnvironment.setNewVariableValue(statement.getIdentifier(), currentValue.value(), currentCurrencyIdentifier.value(), currentCurrencyDenominations.value());
}

void InterpreterVisitor::visit(const FunctionCallStatement &statement)
{
    auto &arguments = statement.getArguments();
    auto &functions = currentProgram.getFunctions();
    auto functionName = statement.getIdentifier();
    auto function = functions.find(functionName);
    programEnvironment.prepareArgumentsScope();
    if (function->second->isEmbeded() && function->second->isParametersObscure())
    {
        int counter = 0;
        auto itA = arguments.begin();
        while (itA != arguments.end())
        {
            string counterString = "_" + to_string(counter);
            currentExpressionType.reset();
            auto evaluetedArguments = programEnvironment.getEvaluetedArguments();
            itA->get()->accept(*this);
            programEnvironment.setEvaluetedArguments(evaluetedArguments);
            if (currentExpressionType.value() == Type::CUR)
                programEnvironment.registerArgument(Type::CUR, counterString, currentValue.value(), currentCurrencyIdentifier.value(), currentCurrencyDenominations.value());
            if (currentExpressionType.value() == Type::NUM)
                programEnvironment.registerArgument(Type::NUM, counterString, currentValue.value());
            if (currentExpressionType.value() == Type::VOID)
                programEnvironment.registerArgument(Type::VOID, counterString, stringSpecialValue.value());
            ++itA;
            counter++;
        }
    }
    else
    {
        auto parameters = function->second->getParameters();
        auto itA = arguments.begin();
        auto itB = parameters.begin();
        while (itA != arguments.end() || itB != parameters.end())
        {
            currentExpressionType.reset();
            auto evaluetedArguments = programEnvironment.getEvaluetedArguments();
            itA->get()->accept(*this);
            programEnvironment.setEvaluetedArguments(evaluetedArguments);
            if (currentExpressionType.value() == Type::CUR)
                programEnvironment.registerArgument(Type::CUR, itB->getIdentifier(), currentValue.value(), currentCurrencyIdentifier.value(), currentCurrencyDenominations.value());
            if (currentExpressionType.value() == Type::NUM)
                programEnvironment.registerArgument(Type::NUM, itB->getIdentifier(), currentValue.value());
            ++itA;
            ++itB;
        }
    }
    programEnvironment.prepareNewCallContext(functionName);
    programEnvironment.registerArgumentsInScope();
    function->second->accept(*this);
    programEnvironment.leaveCallContext();
}

void InterpreterVisitor::visit(const IfStatement &statement)
{
    statement.getCondition()->accept(*this);
    if (currentValue.value() != 0)
    {
        auto ifInst = statement.getIfInstructions().begin();
        programEnvironment.enterNewScope();
        while (ifInst != statement.getIfInstructions().end() && !isReturning)
        {
            (*ifInst).get()->accept(*this);
            ++ifInst;
        }
        programEnvironment.leaveScope();
    }
    else
    {
        auto elseInst = statement.getElseInstructions().begin();
        programEnvironment.enterNewScope();
        while (elseInst != statement.getElseInstructions().end() && !isReturning)
        {
            (*elseInst).get()->accept(*this);
            ++elseInst;
        }
        programEnvironment.leaveScope();
    }
}

void InterpreterVisitor::visit(const InitializeStatement &statement)
{
    currentExpressionType.reset();
    statement.getInitialValue()->accept(*this);
    if (currentExpressionType.value() == Type::NUM)
        programEnvironment.registerVariable(statement.getType(), statement.getVariableName(), currentValue.value());
    if (currentExpressionType.value() == Type::CUR)
        programEnvironment.registerVariable(statement.getType(), statement.getVariableName(), currentValue.value(), currentCurrencyIdentifier.value(), currentCurrencyDenominations.value());
}

void InterpreterVisitor::visit(const ReturnStatement &statement)
{
    currentExpressionType.reset();
    currentValue.reset();
    currentCurrencyIdentifier.reset();
    currentCurrencyDenominations.reset();
    if (auto &retExpr = statement.getReturnExpression(); retExpr)
    {
        retExpr.value()->accept(*this);
    }
    isReturning = true;
}

void InterpreterVisitor::visit(const WhileStatement &statement)
{
    statement.getCondition()->accept(*this);
    auto whileInst = statement.getInstructions().begin();
    programEnvironment.enterNewScope();
    while (currentValue.value() != 0 && !isReturning)
    {
        whileInst = statement.getInstructions().begin();
        while (whileInst != statement.getInstructions().end() && !isReturning)
        {
            (*whileInst).get()->accept(*this);
            ++whileInst;
        }
        if (!isReturning)
            statement.getCondition()->accept(*this);
    }
    programEnvironment.leaveScope();
}

void InterpreterVisitor::visit(const OrExpr &expr)
{
    expr.getLeft()->accept(*this);
    if (currentValue.value() != 0)
        return;
    expr.getRight()->accept(*this);
}

void InterpreterVisitor::visit(const AndExpr &expr)
{
    expr.getLeft()->accept(*this);
    if (currentValue.value() == 0)
    {
        return;
    }
    auto left = currentValue.value();
    expr.getRight()->accept(*this);
    if (left != 0 && currentValue.value() != 0)
        currentValue = 1;
    else
        currentValue = 0;
}

void InterpreterVisitor::visit(const NegationExpr &expr)
{
    expr.getExpr()->accept(*this);
    if (currentValue.value() != 0)
        currentValue = 0;
    else
        currentValue = 1;
}

void InterpreterVisitor::visit(const IsEqualExpr &expr)
{
    expr.getLeft()->accept(*this);
    if (currentExpressionType.value() == Type::CUR)
    {
        auto leftCurrency = currentCurrencyIdentifier.value();
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        auto multiplier = currentCurrencyDenominations.value().find(leftCurrency)->second;
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        if (currentValue.value() * multiplier > MAX_DECIMAL_NUMBER || currentValue.value() * multiplier < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_IsEqualExpr");
        }
        if (leftValue == currentValue.value() * multiplier)
            currentValue = 1;
        else
            currentValue = 0;
    }
    else if (currentExpressionType.value() == Type::NUM)
    {
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        if (leftValue == currentValue.value())
            currentValue = 1;
        else
            currentValue = 0;
    }
    currentExpressionType = Type::NUM;
}

void InterpreterVisitor::visit(const NotEqualExpr &expr)
{
    expr.getLeft()->accept(*this);
    if (currentExpressionType.value() == Type::CUR)
    {
        auto leftCurrency = currentCurrencyIdentifier.value();
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        auto multiplier = currentCurrencyDenominations.value().find(leftCurrency)->second;
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        if (currentValue.value() * multiplier > MAX_DECIMAL_NUMBER || currentValue.value() * multiplier < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_NotEqualExpr");
        }
        if (leftValue != currentValue.value() * multiplier)
            currentValue = 1;
        else
            currentValue = 0;
    }
    else if (currentExpressionType.value() == Type::NUM)
    {
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        if (leftValue != currentValue.value())
            currentValue = 1;
        else
            currentValue = 0;
    }
    currentExpressionType = Type::NUM;
}

void InterpreterVisitor::visit(const LessOrEqualExpr &expr)
{
    expr.getLeft()->accept(*this);
    if (currentExpressionType.value() == Type::CUR)
    {
        auto leftCurrency = currentCurrencyIdentifier.value();
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        auto multiplier = currentCurrencyDenominations.value().find(leftCurrency)->second;
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        if (currentValue.value() * multiplier > MAX_DECIMAL_NUMBER || currentValue.value() * multiplier < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_LessOrEqualExpr");
        }
        if (leftValue <= currentValue.value() * multiplier)
            currentValue = 1;
        else
            currentValue = 0;
    }
    else if (currentExpressionType.value() == Type::NUM)
    {
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        if (leftValue <= currentValue.value())
            currentValue = 1;
        else
            currentValue = 0;
    }
    currentExpressionType = Type::NUM;
}

void InterpreterVisitor::visit(const LessExpr &expr)
{
    expr.getLeft()->accept(*this);
    if (currentExpressionType.value() == Type::CUR)
    {
        auto leftCurrency = currentCurrencyIdentifier.value();
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        auto multiplier = currentCurrencyDenominations.value().find(leftCurrency)->second;
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        if (currentValue.value() * multiplier > MAX_DECIMAL_NUMBER || currentValue.value() * multiplier < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_LessExpr");
        }
        if (leftValue < currentValue.value() * multiplier)
            currentValue = 1;
        else
            currentValue = 0;
    }
    else if (currentExpressionType.value() == Type::NUM)
    {
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        if (leftValue < currentValue.value())
            currentValue = 1;
        else
            currentValue = 0;
    }
    currentExpressionType = Type::NUM;
}

void InterpreterVisitor::visit(const GreaterOrEqualExpr &expr)
{
    expr.getLeft()->accept(*this);
    if (currentExpressionType.value() == Type::CUR)
    {
        auto leftCurrency = currentCurrencyIdentifier.value();
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        auto multiplier = currentCurrencyDenominations.value().find(leftCurrency)->second;
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        if (currentValue.value() * multiplier > MAX_DECIMAL_NUMBER || currentValue.value() * multiplier < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_GreaterOrEqualExpr");
        }
        if (leftValue >= currentValue.value() * multiplier)
            currentValue = 1;
        else
            currentValue = 0;
    }
    else if (currentExpressionType.value() == Type::NUM)
    {
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        if (leftValue >= currentValue.value())
            currentValue = 1;
        else
            currentValue = 0;
    }
    currentExpressionType = Type::NUM;
}

void InterpreterVisitor::visit(const GreaterExpr &expr)
{
    expr.getLeft()->accept(*this);
    if (currentExpressionType.value() == Type::CUR)
    {
        auto leftCurrency = currentCurrencyIdentifier.value();
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        auto multiplier = currentCurrencyDenominations.value().find(leftCurrency)->second;
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        if (currentValue.value() * multiplier > MAX_DECIMAL_NUMBER || currentValue.value() * multiplier < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_GreaterExpr");
        }
        if (leftValue > currentValue.value() * multiplier)
            currentValue = 1;
        else
            currentValue = 0;
    }
    else if (currentExpressionType.value() == Type::NUM)
    {
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        if (leftValue > currentValue.value())
            currentValue = 1;
        else
            currentValue = 0;
    }
    currentExpressionType = Type::NUM;
}

void InterpreterVisitor::visit(const AddExpr &expr)
{
    expr.getLeft()->accept(*this);
    if (currentExpressionType.value() == Type::CUR)
    {
        auto leftCurrency = currentCurrencyIdentifier.value();
        auto leftDenominations = currentCurrencyDenominations.value();
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        auto multiplier = currentCurrencyDenominations.value().find(leftCurrency)->second;
        currentCurrencyIdentifier = leftCurrency;
        currentCurrencyDenominations = leftDenominations;
        if (leftValue + currentValue.value() * multiplier> MAX_DECIMAL_NUMBER || leftValue + currentValue.value() * multiplier < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_AddExpr");
        }
        currentValue = leftValue + currentValue.value() * multiplier;
        currentExpressionType = Type::CUR;
    }
    else if (currentExpressionType.value() == Type::NUM)
    {
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        if (leftValue + currentValue.value() > MAX_DECIMAL_NUMBER || leftValue + currentValue.value() < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_AddExpr");
        }
        currentValue = leftValue + currentValue.value();
        currentExpressionType = Type::NUM;
    }
}

void InterpreterVisitor::visit(const SubExpr &expr)
{
    expr.getLeft()->accept(*this);
    if (currentExpressionType.value() == Type::CUR)
    {
        auto leftCurrency = currentCurrencyIdentifier.value();
        auto leftDenominations = currentCurrencyDenominations.value();
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        auto multiplier = currentCurrencyDenominations.value().find(leftCurrency)->second;
        currentCurrencyIdentifier = leftCurrency;
        currentCurrencyDenominations = leftDenominations;
        if (leftValue - currentValue.value() * multiplier > MAX_DECIMAL_NUMBER || leftValue - currentValue.value() * multiplier < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_SubExpr");
        }
        currentValue = leftValue - currentValue.value() * multiplier;
        currentExpressionType = Type::CUR;
    }
    else if (currentExpressionType.value() == Type::NUM)
    {
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        if (leftValue - currentValue.value() > MAX_DECIMAL_NUMBER || leftValue - currentValue.value() < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_SubExpr");
        }
        currentValue = leftValue - currentValue.value();
        currentExpressionType = Type::NUM;
    }
}

void InterpreterVisitor::visit(const MultExpr &expr)
{
    expr.getLeft()->accept(*this);
    if (currentExpressionType.value() == Type::CUR)
    {
        auto leftCurrency = currentCurrencyIdentifier.value();
        auto leftDenominations = currentCurrencyDenominations.value();
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        if (leftValue * currentValue.value() > MAX_DECIMAL_NUMBER || leftValue * currentValue.value() < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_MultExpr");
        }
        currentValue = leftValue * currentValue.value();
        currentCurrencyIdentifier = leftCurrency;
        currentCurrencyDenominations = leftDenominations;
    }
    else if (currentExpressionType.value() == Type::NUM)
    {
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        if (leftValue * currentValue.value() > MAX_DECIMAL_NUMBER || leftValue * currentValue.value() < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_MultExpr");
        }
        currentValue = leftValue * currentValue.value();
    }
}

void InterpreterVisitor::visit(const DivExpr &expr)
{
    expr.getLeft()->accept(*this);
    if (currentExpressionType.value() == Type::CUR)
    {
        auto leftCurrency = currentCurrencyIdentifier.value();
        auto leftDenominations = currentCurrencyDenominations.value();
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);

        if (currentExpressionType.value() == Type::CUR)
        {
            auto multiplier = currentCurrencyDenominations.value().find(leftCurrency)->second;
            if ((currentValue.value() * multiplier) == 0)
            {
                ZeroDevision err;
                ErrorReporter::reportRuntimeError(err);
                throw RunTimeError("visit_DivExpr");
            }
            if (leftValue / (currentValue.value() * multiplier) > MAX_DECIMAL_NUMBER || leftValue / (currentValue.value() * multiplier) < -MAX_DECIMAL_NUMBER)
            {
                OverflowOrUnderflow err;
                ErrorReporter::reportRuntimeError(err);
                throw RunTimeError("visit_DivExpr");
            }
            currentValue = leftValue / (currentValue.value() * multiplier);
            currentCurrencyIdentifier.reset();
            currentCurrencyDenominations.reset();
            currentExpressionType = Type::NUM;
        }
        else if (currentExpressionType.value() == Type::NUM)
        {
            if (currentValue.value() == 0)
            {
                ZeroDevision err;
                ErrorReporter::reportRuntimeError(err);
                throw RunTimeError("visit_DivExpr");
            }
            if (leftValue / currentValue.value() > MAX_DECIMAL_NUMBER || leftValue / currentValue.value() < -MAX_DECIMAL_NUMBER)
            {
                OverflowOrUnderflow err;
                ErrorReporter::reportRuntimeError(err);
                throw RunTimeError("visit_DivExpr");
            }
            currentValue = leftValue / currentValue.value();
            currentCurrencyIdentifier = leftCurrency;
            currentCurrencyDenominations = leftDenominations;
            currentExpressionType = Type::CUR;
        }
    }
    else if (currentExpressionType.value() == Type::NUM)
    {
        auto leftValue = currentValue.value();
        expr.getRight()->accept(*this);
        if (currentValue.value() == 0)
        {
            ZeroDevision err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_DivExpr");
        }
        if (leftValue / currentValue.value() > MAX_DECIMAL_NUMBER || leftValue / currentValue.value() < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_DivExpr");
        }
        currentValue = leftValue / currentValue.value();
    }
}

void InterpreterVisitor::visit(const MinusNegExpr &expr)
{
    expr.getExpr()->accept(*this);
    currentValue = dec::decimal<MAX_DECIMAL_POINTS>("-1") * currentValue.value();
}

void InterpreterVisitor::visit(const CurrencyExpr &expr)
{
    currentExpressionType.reset();
    expr.getExpr()->accept(*this);
    if (currentExpressionType == Type::NUM)
    {
        currentExpressionType = Type::CUR;
        currentCurrencyIdentifier = expr.getCurrencyIdentifier();
        currentCurrencyDenominations = expr.getDenominations();
        return;
    }
    else if (currentExpressionType == Type::CUR)
    {
        auto multiplier = currentCurrencyDenominations.value().find(expr.getCurrencyIdentifier());
        if (currentValue.value() * multiplier->second > MAX_DECIMAL_NUMBER || currentValue.value() * multiplier->second < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_CurrencyExpr");
        }
        currentValue = currentValue.value() * multiplier->second;
        currentCurrencyIdentifier = expr.getCurrencyIdentifier();
        currentCurrencyDenominations = expr.getDenominations();
        currentExpressionType = Type::CUR;
    }
}

void InterpreterVisitor::visit(const ConversionExpr &expr)
{
    auto currencyVariable = programEnvironment.getVariable(expr.getCurrencyVariableName());
    expr.getExpr()->accept(*this);
    if (currentExpressionType == Type::NUM)
    {
        currentExpressionType = Type::CUR;
        currentCurrencyIdentifier = currencyVariable.value().getCurrencyIdentifier();
        currentCurrencyDenominations = currencyVariable.value().getDenominations();
    }
    else if (currentExpressionType == Type::CUR)
    {
        auto multiplier = currentCurrencyDenominations.value().find(currencyVariable.value().getCurrencyIdentifier());
        if (currentValue.value() * multiplier->second > MAX_DECIMAL_NUMBER || currentValue.value() * multiplier->second < -MAX_DECIMAL_NUMBER)
        {
            OverflowOrUnderflow err;
            ErrorReporter::reportRuntimeError(err);
            throw RunTimeError("visit_ConversionExpr");
        }
        currentValue = currentValue.value() * multiplier->second;
        currentCurrencyIdentifier = currencyVariable.value().getCurrencyIdentifier();
        currentCurrencyDenominations = currencyVariable.value().getDenominations();
        currentExpressionType = Type::CUR;
    }
}

void InterpreterVisitor::visit(const LiteralExpr &expr)
{
    currentExpressionType = Type::NUM;
    currentCurrencyIdentifier.reset();
    currentCurrencyDenominations.reset();
    currentValue = expr.getValue();
}

void InterpreterVisitor::visit(const IdentifierExpr &expr)
{
    auto variable = programEnvironment.getVariable(expr.getIdentifier());
    currentExpressionType = variable.value().getType();
    if (currentExpressionType.value() == Type::NUM)
    {
        currentCurrencyIdentifier.reset();
        currentCurrencyDenominations.reset();
        currentValue = variable.value().getNumValue();
    }
    if (currentExpressionType.value() == Type::CUR)
    {
        currentCurrencyIdentifier = variable.value().getCurrencyIdentifier();
        currentCurrencyDenominations = variable.value().getDenominations();
        currentValue = variable.value().getNumValue();
    }
}

void InterpreterVisitor::visit(const FunCallExpr &expr)
{
    auto &arguments = expr.getArguments();
    auto &functions = currentProgram.getFunctions();
    auto functionName = expr.getFunctionIdentifer();
    auto function = functions.find(functionName);
    programEnvironment.prepareArgumentsScope();
    if (function->second->isEmbeded() && function->second->isParametersObscure())
    {
        int counter = 0;
        auto itA = arguments.begin();
        while (itA != arguments.end())
        {
            string counterString = "_" + to_string(counter);
            currentExpressionType.reset();
            auto evaluetedArguments = programEnvironment.getEvaluetedArguments();
            itA->get()->accept(*this);
            programEnvironment.setEvaluetedArguments(evaluetedArguments);
            if (currentExpressionType.value() == Type::CUR)
                programEnvironment.registerArgument(Type::CUR, counterString, currentValue.value(), currentCurrencyIdentifier.value(), currentCurrencyDenominations.value());
            if (currentExpressionType.value() == Type::NUM)
                programEnvironment.registerArgument(Type::NUM, counterString, currentValue.value());
            if (currentExpressionType.value() == Type::VOID)
                programEnvironment.registerArgument(Type::VOID, counterString, stringSpecialValue.value());
            ++itA;
            counter++;
        }
    }
    else
    {
        auto parameters = function->second->getParameters();
        auto itA = arguments.begin();
        auto itB = parameters.begin();
        while (itA != arguments.end() || itB != parameters.end())
        {
            currentExpressionType.reset();
            auto evaluetedArguments = programEnvironment.getEvaluetedArguments();
            itA->get()->accept(*this);
            programEnvironment.setEvaluetedArguments(evaluetedArguments);
            if (currentExpressionType.value() == Type::CUR)
                programEnvironment.registerArgument(Type::CUR, itB->getIdentifier(), currentValue.value(), currentCurrencyIdentifier.value(), currentCurrencyDenominations.value());
            if (currentExpressionType.value() == Type::NUM)
                programEnvironment.registerArgument(Type::NUM, itB->getIdentifier(), currentValue.value());
            ++itA;
            ++itB;
        }
    }
    programEnvironment.prepareNewCallContext(functionName);
    programEnvironment.registerArgumentsInScope();
    function->second->accept(*this);
    programEnvironment.leaveCallContext();
    currentExpressionType = function->second->getType();
}

void InterpreterVisitor::visit(const StringLiteralExpr &expr)
{
    currentExpressionType = Type::VOID;
    currentCurrencyIdentifier.reset();
    currentCurrencyDenominations.reset();
    currentValue.reset();
    stringSpecialValue = expr.getStringLiteral();
}

void InterpreterVisitor::visit(const Parameter &expr)
{
}

std::optional<dec::decimal<MAX_DECIMAL_POINTS>> InterpreterVisitor::tryBuildNumber(std::string num)
{
    int length = num.length();
    if (!isdigit(num[0]) || length == 0)
        return nullopt;
    ulong integral_part = 0;
    int counter = 0;
    if (num[counter] != '0')
    {
        integral_part += num[counter] - '0';
        counter += 1;
        while (counter < length && isdigit(num[counter]))
        {
            if (integral_part * 10 + num[counter] - '0' > MAX_DECIMAL_NUMBER)
            {
                return nullopt;
            }
            integral_part = integral_part * 10 + num[counter] - '0';
            counter += 1;
        }
        if (counter < length && !isdigit(num[counter]) && num[counter] != '.')
            return nullopt;
    }
    else
    {
        counter += 1;
    }

    if (counter < length && num[counter] == '.')
    {
        ulong fraction_part = 0;
        int decimal_places = 0;
        counter += 1;
        while (counter < length && isdigit(num[counter]))
        {
            if (decimal_places < MAX_DECIMAL_POINTS)
            {
                fraction_part = fraction_part * 10 + num[counter] - '0';
            }
            decimal_places += 1;
            counter += 1;
        }
        if (counter < length && !isdigit(num[counter]))
            return nullopt;
        return dec::decimal<MAX_DECIMAL_POINTS>(integral_part + fraction_part / pow(10, min(MAX_DECIMAL_POINTS, decimal_places)));
    }
    else if (counter < length && isdigit(num[counter]))
    {
        return nullopt;
    }
    else
    {
        return dec::decimal<MAX_DECIMAL_POINTS>((long)integral_part);
    }
}
