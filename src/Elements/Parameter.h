#pragma once
#include <string>
#include "Type.h"
#include "IElement.h"

class Parameter : public IElement
{
private:
    Type type;
    std::string identifier;

public:
    Parameter(Type type, const std::string &identifier);
    
    Type getType();
    std::string getIdentifier();
    void accept(IVisitor &vis) override;
};