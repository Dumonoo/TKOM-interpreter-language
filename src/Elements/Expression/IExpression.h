#pragma once
#include <memory>
#include "../IElement.h"

class IExpression : public IElement{
    public:
        IExpression() = default;
        virtual ~IExpression() = default;
        virtual void accept(IVisitor &) = 0;
};

using IExpr = std::unique_ptr<IExpression>;