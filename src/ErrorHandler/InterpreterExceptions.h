#pragma once
#include <exception>
#include <stdexcept>


struct FatalConfigError : std::runtime_error{
    explicit FatalConfigError(std::string const& functionName) :std::runtime_error(functionName){}
};
struct FatalError : std::runtime_error{
    explicit FatalError(std::string const& functionName) :std::runtime_error(functionName){}
};

struct FileError: std::runtime_error{
    explicit FileError(std::string const& message) : std::runtime_error(message){}
};

struct ParserError : FatalError{
    explicit ParserError(std::string const& message): FatalError(message){}
};

struct RunTimeError : std::runtime_error{
    explicit RunTimeError(std::string const& message) : std::runtime_error(message){}
};
