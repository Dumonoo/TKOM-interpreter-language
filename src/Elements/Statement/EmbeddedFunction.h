#pragma once
// #include "IStatement.h"
#include "FunctionDefinition.h"
#include "../Parameter.h"
#include <string>
#include <vector>

class EmbeddedFunction : public FunctionDefinition
{
private:
    Type functionType;
    std::string identifier;
    std::vector<Parameter> parameters;
    std::vector<IState> instructions;
    bool obscureParamters;

public:
    // EmbeddedFunction() = default;
    EmbeddedFunction(Type type, const std::string &identifier, const std::vector<Parameter> &parameters, std::vector<IState> instructions, bool obscureParamters);
    // const std::vector<Parameter> &getParameters() const;
    // const std::vector<IState> &getInstructions() const;
    // std::string getFunctionName() const;
    // Type getType() const;
    // TODO poprawic
    bool isEmbeded() override;
    bool isParametersObscure() override;
    void accept(IVisitor &vis) override;
};