#pragma once
#include <vector>
#include <string>
#include "CallContext.h"
#include <iostream>

class Environment
{
private:
    int t;
    std::vector<CallContext> callContextStack;
    std::vector<std::pair<std::string, Variable>> evaluetedArguments;

public:
    Environment() = default;
    ~Environment() = default;

    void prepareNewCallContext(const std::string &functionName);
    void clearEnvironment();

    void enterNewScope();
    void leaveScope();
    void leaveAllScopes();

    void prepareArgumentsScope();

    bool tryRegisterArgument();
    bool tryRegisterArgument(Type type, std::string variableName);
    bool tryRegisterVariable(Type type, std::string variableName);
    // dla num
    void registerVariable(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value);
    // dla cur
    void registerVariable(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value, std::string currencyIdentifier, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> denominations);

    // dla num
    void registerArgument(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value);
    // dla cur
    void registerArgument(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value, std::string currencyIdentifier, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> denominations);
    // dla stringExpr
    void registerArgument(Type type, std::string variableName, std::string stringValue);

    void registerArgumentsInScope();


    void setNewVariableValue(std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value);
    void setNewVariableValue(std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value, std::string currencyIdentifier, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> denominations);

    void siema();
    // void registerVariable()
    void enterNewCallContext();
    void leaveCallContext();
    std::optional<Variable> getVariable(std::string variableName);

    std::string getTopCallStackFunctionName() const;
    std::vector<std::pair<std::string, Variable>> getEvaluetedArguments() const;
    void setEvaluetedArguments(std::vector<std::pair<std::string, Variable>> evaArg);
};