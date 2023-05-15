#include "FunctionDefinition.h"

using namespace std;

FunctionDefinition::FunctionDefinition(Type type, const string &identifier, const vector<Parameter> &parameters, vector<IState> instructions)
    : functionType(type), identifier(identifier), parameters(parameters), instructions(move(instructions)) {}

void FunctionDefinition::accept(IVisitor &v)
{
    v.visit(*this);
}

const std::vector<Parameter> &FunctionDefinition::getParameters() const
{
    return parameters;
}

const vector<IState> &FunctionDefinition::getInstructions() const
{
    return instructions;
}

std::string FunctionDefinition::getFunctionName() const
{
    return identifier;
}

Type FunctionDefinition::getType() const
{
    return functionType;
}

bool FunctionDefinition::isEmbeded()
{
    return false;
}

bool FunctionDefinition::isParametersObscure()
{
    return false;
}