# pragma once
#include "IExpression.h"
#include <string>

class IdentifierExpr : public IExpression
{
private:
    std::string identifier;
public:
    explicit IdentifierExpr(const std::string &identifier);
    void accept(IVisitor &vis) override;
    std::string getIdentifier() const;
};