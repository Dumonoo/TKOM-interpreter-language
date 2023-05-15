#include "IfStatement.h"

using namespace std;

IfStatement::IfStatement(IExpr condition, vector<IState> ifInstructions)
    : condition(move(condition)), ifInstructions(move(ifInstructions)) {}

IfStatement::IfStatement(IExpr condition, vector<IState> ifInstructions, vector<IState> elseInstructions)
:condition(move(condition)), ifInstructions(move(ifInstructions)), elseInstructions(move(elseInstructions)){}

void IfStatement::accept(IVisitor &v)
{
    v.visit(*this);
}

const IExpr &IfStatement::getCondition() const{
    return condition;
}

const std::vector<IState> &IfStatement::getIfInstructions() const{
    return ifInstructions;
}

const std::vector<IState> &IfStatement::getElseInstructions() const{
    return elseInstructions;
}