#include "Environment.h"

using namespace std;

void Environment::prepareNewCallContext(const string &functionName){
    callContextStack.emplace_back(functionName);
}

void Environment::leaveCallContext(){
    callContextStack.pop_back();
}

void Environment::clearEnvironment()
{
    callContextStack.clear();
}

void Environment::enterNewScope()
{
    callContextStack.back().addNewScope();
}

// void Environment::leaveAllScopes(){
//     // callContextStack.back().
// }
void Environment::prepareArgumentsScope(){
    evaluetedArguments.clear();
}

void Environment::leaveScope(){
    callContextStack.back().leaveScope();
}

bool Environment::tryRegisterArgument(Type type, std::string variableName)
{
    return callContextStack.back().tryRegisterVariable(type, variableName);
}

bool Environment::tryRegisterVariable(Type type, std::string variableName)
{
    return callContextStack.back().tryRegisterVariable(type, variableName);
}

void Environment::registerVariable(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value)
{
    callContextStack.back().registerVariable(type, variableName, value);
}

void Environment::registerVariable(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value, std::string currencyIdentifier, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> denominations)
{
    callContextStack.back().registerVariable(type, variableName, value, currencyIdentifier, denominations);
}

std::optional<Variable> Environment::getVariable(std::string variableName)
{
    return callContextStack.back().getVariable(variableName);
}

void Environment::setNewVariableValue(std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value)
{
    callContextStack.back().setNewVariableValue(variableName, value);
}

void Environment::setNewVariableValue(std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value, std::string currencyIdentifier, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> denominations)
{
    callContextStack.back().setNewVariableValue(variableName, value, currencyIdentifier, denominations);
}

void Environment::registerArgument(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value)
{
    evaluetedArguments.push_back(make_pair(variableName, Variable(type, value)));
}

void Environment::registerArgument(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value, std::string currencyIdentifier, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> denominations)
{
    evaluetedArguments.push_back(make_pair(variableName, Variable(type, value, currencyIdentifier, denominations)));
}

void Environment::registerArgument(Type type, std::string variableName, std::string stringValue)
{
    evaluetedArguments.push_back(make_pair(variableName, Variable(type, stringValue)));
}

void Environment::registerArgumentsInScope()
{
    enterNewScope();
    for(auto &arg: evaluetedArguments)
    {
        callContextStack.back().registerArgument(arg.first, arg.second);
    }
}

std::string Environment::getTopCallStackFunctionName() const
{
    return callContextStack.back().getFunctionName();
}

std::vector<std::pair<std::string, Variable>> Environment::getEvaluetedArguments() const
{
    return evaluetedArguments;
}

void Environment::setEvaluetedArguments(std::vector<std::pair<std::string, Variable>> evaArg)
{
    evaluetedArguments = evaArg;
}

















void Environment::siema(){
    cout<<"siema";
}