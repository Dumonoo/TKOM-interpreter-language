#include <iostream>
#include "ErrorReporter.h"
#include "ErrVisitors/ErrVisitorEng.h"

using namespace std;

vector<string> ErrorReporter::warningRaports;
vector<string> ErrorReporter::errorRaports;
vector<string> ErrorReporter::runtimeRaports;
unique_ptr<IErrVisitor> ErrorReporter::errVisitor = make_unique<ErrVisitorEng>();

string ErrorReporter::prepareStreamMessage(const string &type, const string &msg, Position pos, istream &is)
{
    string positionString = '(' + to_string(pos.rowNumber) + ':' + to_string(pos.columnNumber) + ')';
    string finalMessage = positionString + " [" + type + "]: " + msg;

    auto oldPos = is.tellg();
    auto startPoint = pos.columnNumber >= 130 ? pos.streamPosition - 60 : pos.streamPosition - pos.columnNumber;
    if (is.eof())
        is.clear();
    is.seekg(startPoint);
    string messageInfoPart = "";

    int counter = 0;
    while (is.tellg() < pos.streamPosition)
    {
        messageInfoPart += (char)is.get();
        counter++;
    }
    messageInfoPart += '\n';
    for (auto i = 0; i < counter; i++)
    {
        if (i < counter - pos.tokenLength)
            messageInfoPart += ' ';
        else if (i == counter - pos.tokenLength)
        {
            messageInfoPart += '^';
        }
        else
        {
            messageInfoPart += '~';
        }
    }
    finalMessage += '\n' + messageInfoPart;
    is.seekg(oldPos);
    return finalMessage;
}

string ErrorReporter::prepareStreamMessage(const string &type, const string &msg)
{
    string finalMessage = " [" + type + "]: " + msg;
    return finalMessage;
}

void ErrorReporter::printWarnings(std::ostream &os, string const &fileName)
{
    for (auto const &i : ErrorReporter::warningRaports)
        os << fileName << " " << i << endl;
}

void ErrorReporter::printErrors(std::ostream &os, string const &fileName)
{
    for (auto const &i : ErrorReporter::errorRaports)
        os << fileName << " " << i << endl;
}

void ErrorReporter::printRuntime(std::ostream &os)
{
    for (auto const &i : ErrorReporter::runtimeRaports)
        os << i << endl;
}

void ErrorReporter::printAll(std::ostream &os, string const &fileName)
{
    ErrorReporter::printWarnings(os, fileName);
    ErrorReporter::printErrors(os, fileName);
    ErrorReporter::clearErrorRaports();
}

void ErrorReporter::clearErrorRaports()
{
    ErrorReporter::errorRaports.clear();
    ErrorReporter::warningRaports.clear();
}

void ErrorReporter::reportError(IError &err)
{
    string type = "Error";
    auto ptr = ErrorReporter::errVisitor.get();
    ErrorReporter::errorRaports.push_back(ErrorReporter::prepareStreamMessage(type, err.accept(*ptr)));
}

void ErrorReporter::reportWarning(IError &err)
{
    string type = "Warning";
    auto ptr = ErrorReporter::errVisitor.get();
    ErrorReporter::warningRaports.push_back(ErrorReporter::prepareStreamMessage(type, err.accept(*ptr)));
}

void ErrorReporter::reportRuntimeError(IError &err)
{
    string type = "Runtime Error";
    auto ptr = ErrorReporter::errVisitor.get();
    ErrorReporter::runtimeRaports.push_back(ErrorReporter::prepareStreamMessage(type, err.accept(*ptr)));
}

void ErrorReporter::reportError(IError &err, Position position, std::istream &inputStream)
{
    string type = "Error";
    auto ptr = ErrorReporter::errVisitor.get();
    ErrorReporter::errorRaports.push_back(ErrorReporter::prepareStreamMessage(type, err.accept(*ptr), position, inputStream));
}

void ErrorReporter::reportWarning(IError &err, Position position, std::istream &inputStream)
{
    string type = "Warning";
    auto ptr = ErrorReporter::errVisitor.get();
    ErrorReporter::warningRaports.push_back(ErrorReporter::prepareStreamMessage(type, err.accept(*ptr), position, inputStream));
}
