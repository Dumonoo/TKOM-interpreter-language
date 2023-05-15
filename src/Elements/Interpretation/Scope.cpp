#include "Scope.h"

using namespace std;
// bool tryInsertArgument(Type type, std::string variableName)
// {
//     return variables.insert({variableName, Variable(type)}).second;
// }

bool Scope::tryInsertVariable(Type type, std::string variableName)
{
    return variables.insert({variableName, Variable(type)}).second;
}

bool Scope::isInScope(std::string variableName)
{
    return variables.contains(variableName);
}

std::optional<Variable> Scope::getVariable(string variableName)
{
    auto it = variables.find(variableName);
    if (it == variables.end())
        return nullopt;
    return it->second;
}

void Scope::registerVariable(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value)
{
    variables.insert({variableName, Variable(type, value)});
}

void Scope::registerVariable(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value, std::string currencyIdentifier, std::unordered_map<std::string, dec::decimal<MAX_DECIMAL_POINTS>> denominations)
{
    variables.insert({variableName, Variable(type, value, currencyIdentifier, denominations)});
}

bool Scope::trySetNewVariableValue(std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value)
{
    auto it = variables.find(variableName);
    if (it == variables.end())
        return false;
    it->second.setValue(value);
    return true;
}

bool Scope::trySetNewVariableValue(std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value, std::string currencyIdentifier, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> denominations)
{
    auto it = variables.find(variableName);
    if (it == variables.end())
        return false;
    it->second.setValue(value, currencyIdentifier, denominations);
    return true;
}

void Scope::insertArgument(std::string variableName, Variable var)
{
    variables.insert({variableName, var});
}