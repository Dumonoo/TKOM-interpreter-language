#include "WhileStatement.h"

using namespace std;

WhileStatement::WhileStatement(IExpr condition, vector<IState> instructions)
    : condition(move(condition)), instructions(move(instructions)) {}

void WhileStatement::accept(IVisitor &v)
{
    v.visit(*this);
}

const std::vector<IState> &WhileStatement::getInstructions() const{
    return instructions;
}

const IExpr &WhileStatement::getCondition() const{
    return condition;
}