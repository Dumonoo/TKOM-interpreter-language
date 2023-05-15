#include "CallContext.h"

using namespace std;

CallContext::CallContext(std::string functionName)
    : functionName(functionName)
{
}

void CallContext::addNewScope()
{
    scopes.emplace_back();
}

void CallContext::leaveScope()
{
    if (!scopes.empty())
        scopes.pop_back();
}

bool CallContext::tryRegisterArgument(Type type, std::string variableName)
{
    return scopes.back().tryInsertVariable(type, variableName);
}

bool CallContext::tryRegisterVariable(Type type, std::string variableName)
{

    if (scopes.at(0).isInScope(variableName))
        return false;
    return scopes.back().tryInsertVariable(type, variableName);
}

std::optional<Variable> CallContext::getVariable(string variableName){
    auto it = scopes.rbegin();
    while(it != scopes.rend()){
        if(auto var = it->getVariable(variableName); var){
            return var;
        }
        it++;
    }
    return nullopt;
}

void CallContext::registerVariable(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value)
{
    scopes.back().registerVariable(type, variableName, value);
}

void CallContext::registerVariable(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value, std::string currencyIdentifier, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> denominations)
{
    scopes.back().registerVariable(type, variableName, value, currencyIdentifier, denominations);
}

void CallContext::setNewVariableValue(std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value)
{
    auto it = scopes.rbegin();
    while(it != scopes.rend()){
        if(it->trySetNewVariableValue(variableName, value))
            return;
        it++;
    }
}

void CallContext::setNewVariableValue(std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value, std::string currencyIdentifier, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> denominations)
{
    auto it = scopes.rbegin();
    while(it != scopes.rend()){
        if(it->trySetNewVariableValue(variableName, value, currencyIdentifier, denominations))
            return;
        it++;
    }
}

void CallContext::registerArgument(std::string name, Variable var)
{
    scopes.back().insertArgument(name, var);
}

std::string CallContext::getFunctionName() const
{
    return functionName;
}