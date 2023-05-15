#pragma once
#include "../Visitors/IVisitor.h"

class IElement
{
public:
    IElement() = default;
    virtual ~IElement() = default;
    virtual void accept(IVisitor &) = 0;
};