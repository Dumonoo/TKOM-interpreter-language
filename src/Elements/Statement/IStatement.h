# pragma once

#include "../IElement.h"
#include <memory>


class IStatement :public IElement{
    public:
        IStatement() = default;
        virtual ~IStatement() = default;
        virtual void accept(IVisitor &) = 0;
};

using IState = std::unique_ptr<IStatement>;