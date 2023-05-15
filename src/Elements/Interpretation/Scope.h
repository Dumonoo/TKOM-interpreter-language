#include <unordered_map>
#include <vector>
#include <string>
#include <optional>
#include "Variable.h"

class Scope
{
private:
    std::unordered_map<std::string, Variable> variables;

public:
    Scope() = default;
    ~Scope() = default;

    // bool tryInsertArgument(Type type, std::string variableName);
    bool tryInsertVariable(Type type, std::string variableName);

    void registerVariable(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value);
    void registerVariable(Type type, std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value, std::string currencyIdentifier, std::unordered_map<std::string, dec::decimal<MAX_DECIMAL_POINTS>> denominations);

    bool trySetNewVariableValue(std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value);
    bool trySetNewVariableValue(std::string variableName, dec::decimal<MAX_DECIMAL_POINTS> value, std::string currencyIdentifier, std::unordered_map<std::string, dec::decimal<MAX_DECIMAL_POINTS>> denominations);
    bool isInScope(std::string variableName);

    void insertArgument(std::string variableName, Variable var);

    std::optional<Variable> getVariable(std::string variableName);
};