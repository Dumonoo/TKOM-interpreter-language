# pragma once
#include "IExpression.h"
#include <string>
#include <vector>

class FunCallExpr : public IExpression
{
private:
    std::string identifier;
    std::vector<IExpr> arguments;

public:
    FunCallExpr(const std::string &identifier, std::vector<IExpr> arguments);
    void accept(IVisitor &vis) override;
    
    const std::vector<IExpr> &getArguments() const;
    std::string getFunctionIdentifer() const;
};