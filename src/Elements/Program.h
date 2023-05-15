#pragma once
#include <unordered_map>
#include <string>
#include "Statement/FunctionDefinition.h"
#include "Statement/EmbeddedFunction.h"
#include <memory>
#include "../ErrorHandler/InterpreterExceptions.h"
#include "../ErrorHandler/ErrorReporter.h"

class Program
{
private:
    std::unordered_map<std::string, std::unique_ptr<FunctionDefinition>> functions;

public:
    Program() = default;
    explicit Program(std::unordered_map<std::string, std::unique_ptr<FunctionDefinition>> functions);
    std::unordered_map<std::string, std::unique_ptr<FunctionDefinition>> const& getFunctions() const;
    void addEmbededFunctions();
};
