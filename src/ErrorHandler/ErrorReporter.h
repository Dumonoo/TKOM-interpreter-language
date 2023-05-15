#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "../Token/Token.h"
#include "../Token/TokenType.h"

#include "Errors.h"
#include "ErrVisitors/IErrVisitor.h"

class ErrorReporter
{
private:
    static std::vector<std::string> warningRaports;
    static std::vector<std::string> errorRaports;
    static std::vector<std::string> runtimeRaports;

    static std::unique_ptr<IErrVisitor> errVisitor;
    static void clearErrorRaports();
    static std::string prepareStreamMessage(const std::string &type, const std::string &message, Position postion, std::istream &inputStream);
    static std::string prepareStreamMessage(const std::string &type, const std::string &msg);
public:
    static void reportError(IError &);
    static void reportWarning(IError &);
    static void reportRuntimeError(IError &);

    static void reportError(IError &, Position position, std::istream &inputStream);
    static void reportWarning(IError &, Position position, std::istream &inputStream);

    static void printWarnings(std::ostream &os, std::string const &fileName);
    static void printErrors(std::ostream &os, std::string const &fileName);
    static void printRuntime(std::ostream &os);
    static void printAll(std::ostream &os, std::string const &fileName);

    ErrorReporter() = delete;
};