#include "EmbeddedFunction.h"

using namespace std;

EmbeddedFunction::EmbeddedFunction(Type type, const string &identifier, const vector<Parameter> &parameters, vector<IState> instructions,  bool obscureParamters)
    :FunctionDefinition(type, identifier, parameters, move(instructions)), obscureParamters(obscureParamters){}

bool EmbeddedFunction::isEmbeded()
{
    return true;
}
bool EmbeddedFunction::isParametersObscure()
{
    return obscureParamters;
}

void EmbeddedFunction::accept(IVisitor &vis)
{
    vis.visit(*this);
}