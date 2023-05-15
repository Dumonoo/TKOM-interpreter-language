# pragma once
#include "IStatement.h"
#include "../Parameter.h"
#include <string>
#include <vector>

class FunctionDefinition: public IStatement
{
private:
    Type functionType;
    std::string identifier;
    std::vector<Parameter> parameters;
    std::vector<IState> instructions;

public:
    FunctionDefinition(Type type, const std::string &identifier, const std::vector<Parameter> &parameters, std::vector<IState> instructions);
    const std::vector<Parameter> &getParameters() const;
    const std::vector<IState> &getInstructions() const;
    std::string getFunctionName() const;
    Type getType() const;
    
    virtual bool isEmbeded();
    virtual bool isParametersObscure();

    void accept(IVisitor &vis) override;
};