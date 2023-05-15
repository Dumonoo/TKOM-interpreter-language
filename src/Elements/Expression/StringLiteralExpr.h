# pragma once
#include "IExpression.h"
#include <string>

class StringLiteralExpr : public IExpression
{
private:
    std::string stringLiteral;

public:
    explicit StringLiteralExpr(const std::string &stringLiteral);
    std::string getStringLiteral() const;
    void accept(IVisitor &vis) override;
};