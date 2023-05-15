#pragma once
#include <vector>
#include <string>
#include <optional>
#include "Variable.h"
#include "Scope.h"

class CallContext
{
private:
    std::vector<Scope> scopes;
    std::string functionName;
public:
    std::optional<Variable> getVariable(std::string variableName);
    void addNewScope();
    void leaveScope();
    void leaveAllScopes();

    
    bool tryRegisterArgument(Type type, std::string variableName);
    bool tryRegisterVariable(Type type, std::string variableName);

    void registerVariable(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value);
    void registerVariable(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value, std::string currencyIdentifier, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> denominations);

    void setNewVariableValue(std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value);
    void setNewVariableValue(std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value, std::string currencyIdentifier, std::unordered_map<std::string,dec::decimal<MAX_DECIMAL_POINTS>> denominations);



    void registerArgument(std::string name, Variable var);




    explicit CallContext(std::string functionName);
    ~CallContext() = default;
    std::string getFunctionName() const;
};