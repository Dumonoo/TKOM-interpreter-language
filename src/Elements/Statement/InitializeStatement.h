# pragma once
#include "../Expression/IExpression.h"
#include "IStatement.h"
#include "../Type.h"
#include <string>

class InitializeStatement: public IStatement{
    private:
    Type type;
    std::string identifier;
    IExpr initialValue;

public:
    InitializeStatement(Type type, const std::string &identifier, IExpr initialValue);
    const IExpr &getInitialValue() const;

    Type getType() const;
    std::string getVariableName() const;
    void accept(IVisitor &vis) override;
};