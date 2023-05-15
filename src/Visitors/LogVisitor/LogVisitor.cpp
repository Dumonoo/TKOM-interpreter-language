#include "LogVisitor.h"
#include <iostream>

LogVisitor::LogVisitor() = default;
// LogVisitor::LogVisitor(Program &program)
// : program(program){};

void LogVisitor::print(const IElement &element) const
{
    os << std::string(3 * level, ' ')<<' '<< typeid(element).name() << std::endl;
}

void LogVisitor::printIExprVector(const std::vector<IExpr> &expressions)
{
    for (auto &i : expressions)
    {
        nextLevel();
        i->accept(*this);
        previousLevel();
    }
}

void LogVisitor::printIStateVector(const std::vector<IState> &statemensts)
{
    for (auto &i : statemensts)
    {
        nextLevel();
        i->accept(*this);
        previousLevel();
    }
}
void LogVisitor::printLeftAndRight(const IExpr &left, const IExpr &right)
{ 
    nextLevel();
    left->accept(*this);
    right->accept(*this);
    previousLevel();
}

void LogVisitor::nextLevel()
{
    level += 1;
}

void LogVisitor::previousLevel()
{
    if (level - 1 <= 0)
        level = 0;
    else
        level -= 1;
}

void LogVisitor::visit(const Program &program)
{
    for (auto &i : program.getFunctions())
    {
        i.second->accept(*this);
    }
}

void LogVisitor::visit(const FunctionDefinition &function)
{
    print(function);
    for(auto i :function.getParameters())
    {
        nextLevel();
        i.accept(*this);
        previousLevel();
    }
    printIStateVector(function.getInstructions());
}

void LogVisitor::visit(const EmbeddedFunction &function)
{
    print(function);
    // TODO okreslic czy odwiedzamy parametry
    // for(auto i :function.getParameters())
    // {
    //     nextLevel();
    //     i.accept(*this);
    //     previousLevel();
    // }
}

void LogVisitor::visit(const AssignmentStatement &statement)
{
    print(statement);
    nextLevel();
    statement.getExpr()->accept(*this);
    previousLevel();
}


void LogVisitor::visit(const FunctionCallStatement &statement)
{
    print(statement);
    printIExprVector(statement.getArguments());
}

void LogVisitor::visit(const IfStatement &statement)
{
    print(statement);
    // condition
    nextLevel();
    statement.getCondition()->accept(*this);
    previousLevel();
    printIStateVector(statement.getIfInstructions());
    printIStateVector(statement.getElseInstructions());
}

void LogVisitor::visit(const InitializeStatement &statement)
{
    print(statement);
    nextLevel();
    statement.getInitialValue()->accept(*this);
    previousLevel();
}

void LogVisitor::visit(const ReturnStatement &statement)
{
    print(statement);
    if(statement.getReturnExpression())
    {
        nextLevel();
        statement.getReturnExpression().value()->accept(*this);
        previousLevel();
    }
}

void LogVisitor::visit(const WhileStatement &statement)
{
    print(statement);
    // condition
    nextLevel();
    statement.getCondition()->accept(*this);
    previousLevel();
    printIStateVector(statement.getInstructions());
}



void LogVisitor::visit(const OrExpr &expr)
{
    print(expr);
    printLeftAndRight(expr.getLeft(), expr.getRight());
}

void LogVisitor::visit(const AndExpr &expr)
{
    print(expr);
    printLeftAndRight(expr.getLeft(), expr.getRight());
}

void LogVisitor::visit(const NegationExpr &expr)
{
    print(expr);
    nextLevel();
    expr.getExpr()->accept(*this);
    previousLevel();
}

void LogVisitor::visit(const IsEqualExpr &expr)
{
    print(expr);
    printLeftAndRight(expr.getLeft(), expr.getRight());
}

void LogVisitor::visit(const NotEqualExpr &expr)
{
    print(expr);
    printLeftAndRight(expr.getLeft(), expr.getRight());
}

void LogVisitor::visit(const LessOrEqualExpr &expr)
{
    print(expr);
    printLeftAndRight(expr.getLeft(), expr.getRight());
}

void LogVisitor::visit(const LessExpr &expr)
{
    print(expr);
    printLeftAndRight(expr.getLeft(), expr.getRight());
}

void LogVisitor::visit(const GreaterOrEqualExpr &expr)
{
    print(expr);
    printLeftAndRight(expr.getLeft(), expr.getRight());
}

void LogVisitor::visit(const GreaterExpr &expr)
{
    print(expr);
    printLeftAndRight(expr.getLeft(), expr.getRight());
}

void LogVisitor::visit(const AddExpr &expr)
{
    print(expr);
    printLeftAndRight(expr.getLeft(), expr.getRight());
}

void LogVisitor::visit(const SubExpr &expr)
{
    print(expr);
    printLeftAndRight(expr.getLeft(), expr.getRight());
}

void LogVisitor::visit(const MultExpr &expr)
{
    print(expr);
    printLeftAndRight(expr.getLeft(), expr.getRight());
}

void LogVisitor::visit(const DivExpr &expr)
{
    print(expr);
    printLeftAndRight(expr.getLeft(), expr.getRight());
}

void LogVisitor::visit(const MinusNegExpr &expr)
{
    print(expr);
    nextLevel();
    expr.getExpr()->accept(*this);
    previousLevel();
}

void LogVisitor::visit(const CurrencyExpr &expr)
{
    print(expr);
    // refactor this 3 -> 1
    nextLevel();
    expr.getExpr()->accept(*this);
    previousLevel();
}

void LogVisitor::visit(const ConversionExpr &expr)
{
    print(expr);
    nextLevel();
    expr.getExpr()->accept(*this);
    previousLevel();
}

void LogVisitor::visit(const LiteralExpr &expr)
{
    print(expr);
}

void LogVisitor::visit(const IdentifierExpr &expr)
{
    print(expr);
}

void LogVisitor::visit(const FunCallExpr &expr)
{
    print(expr);
}


void LogVisitor::visit(const StringLiteralExpr &expr)
{
    print(expr);
}

void LogVisitor::visit(const Parameter &expr)
{
    print(expr);
}