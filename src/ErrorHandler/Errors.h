#pragma once
#include "ErrVisitors/IErrVisitor.h"
#include <string>
#include <vector>
#include "../Token/TokenType.h"
#include "../Elements/Type.h"

class IError
{
public:
    IError() = default;
    virtual ~IError() = default;
    virtual std::string accept(IErrVisitor &) = 0;
};

class UndefinedToken : public IError
{
public:
    UndefinedToken() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this);
    };
};

class UnknowEscapeCharacter : public IError
{
public:
    UnknowEscapeCharacter() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this);
    };
};

class CommentTooLong : public IError
{
    long long maxLength = MAX_COMMENT_LENGTH;

public:
    CommentTooLong() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + std::to_string(maxLength);
    };
};

class TextConstantTooLong : public IError
{
    long long maxLength = MAX_TEXTCONST_LENGTH;

public:
    TextConstantTooLong() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + std::to_string(maxLength);
    };
};

class UnknownCharacter : public IError
{
public:
    UnknownCharacter() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this);
    };
};

class LeadingZero : public IError
{
public:
    LeadingZero() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this);
    };
};

class LostPrecision : public IError
{

    long long maxPrecision = MAX_DECIMAL_POINTS;

public:
    LostPrecision() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + std::to_string(maxPrecision);
    };
};

class NumberOverflow : public IError
{
    long long maxNumber = MAX_DECIMAL_NUMBER;

public:
    NumberOverflow() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + std::to_string(maxNumber);
    };
};

class MissingBackSlash : public IError
{
public:
    MissingBackSlash() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this);
    };
};

class TooSimilarIdentifier : public IError
{
public:
    TooSimilarIdentifier() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this);
    };
};

class TooLongIdentifier : public IError
{
    long long maxLength = MAX_IDENTIFIER_LENGTH;

public:
    TooLongIdentifier() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + std::to_string(maxLength);
    };
};

class MissingFile : public IError
{
public:
    MissingFile() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this);
    };
};

// Parser

class UnexpectedToken : public IError
{
    std::vector<TokenType> expectedTypes;

public:
    explicit UnexpectedToken(const std::vector<TokenType> &expectedTypes)
        : expectedTypes(expectedTypes){};
    std::string accept(IErrVisitor &v) override
    {
        std::string expectedMsg = "";
        for (auto &i : expectedTypes)
        {
            auto it = tokenTypeNames.find(i);
            if (it == tokenTypeNames.end())
                ;
            else
                expectedMsg += it->second + " ";
        }
        return v.visit(*this) + expectedMsg;
    };
};

class RedefinitionOf : public IError
{
    std::string identifier;

public:
    explicit RedefinitionOf(std::string const &s)
        : identifier(s){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + identifier;
    };
};

class ExpectedParameter : public IError
{
public:
    ExpectedParameter() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this);
    };
};

class ExpectedArgument : public IError
{
public:
    ExpectedArgument() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this);
    };
};

class ExpectedCondition : public IError
{
public:
    ExpectedCondition() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this);
    };
};

class MissingElement : public IError
{
    std::string element;

public:
    explicit MissingElement(const std::string &element)
        : element(element) {}
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + element;
    };
};

class MissingElementBefore : public IError
{
    std::string element;
    std::vector<TokenType> expectedTypes;

public:
    explicit MissingElementBefore(const std::string &element)
        : element(element) {}
    MissingElementBefore(const std::string &element, const std::vector<TokenType> &expectedTypes)
        : element(element), expectedTypes(expectedTypes) {}
    std::string accept(IErrVisitor &v) override
    {
        std::string expectedMsg = "";
        for (auto &i : expectedTypes)
        {
            auto it = tokenTypeNames.find(i);
            if (it == tokenTypeNames.end())
                ;
            else
                expectedMsg += it->second + " ";
        }
        MissingElement el(element);
        return v.visit(el) + element + v.visit(*this) + expectedMsg;
    };
};

class MissingElementAfter : public IError
{
    std::string element;
    std::vector<TokenType> expectedTypes;

public:
    MissingElementAfter(const std::string &element, const std::vector<TokenType> &expectedTypes)
        : element(element), expectedTypes(expectedTypes) {}
    std::string accept(IErrVisitor &v) override
    {
        std::string expectedMsg = "";
        for (auto &i : expectedTypes)
        {
            auto it = tokenTypeNames.find(i);
            if (it == tokenTypeNames.end())
                ;
            else
                expectedMsg += it->second + " ";
        }
        MissingElement el(element);
        return v.visit(el) + element + v.visit(*this) + expectedMsg;
    };
};

class ExpectedExpressionAfter : public IError
{
    std::string element;

public:
    explicit ExpectedExpressionAfter(const std::string &element)
        : element(element) {}
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + element;
    };
};

class ExpectedExpressionBefore : public IError
{
    std::string element;

public:
    explicit ExpectedExpressionBefore(const std::string &element)
        : element(element) {}
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + element;
    };
};

class CurrencyInIdentifierInConversion : public IError
{
    std::string currency;

public:
    explicit CurrencyInIdentifierInConversion(const std::string &currency)
        : currency(currency) {}
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + currency;
    };
};

class UnknownCurrency : public IError
{
    std::string currency;

public:
    explicit UnknownCurrency(const std::string &currency)
        : currency(currency) {}
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + currency;
    };
};

class HeaderDuplicate : public IError
{
    std::string currency;

public:
    explicit HeaderDuplicate(const std::string &currency)
        : currency(currency) {}
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + currency;
    };
};

class CurrencyNotInHeader : public IError
{
    std::string currency;

public:
    explicit CurrencyNotInHeader(const std::string &currency)
        : currency(currency) {}
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + currency;
    };
};

class MissingDenaminationValues : public IError
{
    std::size_t a;
    std::size_t b;

public:
    explicit MissingDenaminationValues(std::size_t a, std::size_t b)
        : a(a), b(b) {}
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + std::to_string(a) + " " + std::to_string(b);
    };
};

class ConfigExample : public IError
{
public:
    ConfigExample() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this);
    };
};

class MissingConfig : public IError
{
public:
    MissingConfig() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this);
    };
};

// Semantic check
class ParameterRedefinition : public IError
{
    std::string function;
    std::string parameter;

public:
    ParameterRedefinition(const std::string &functionName, const std::string &text2)
        : function(functionName), parameter(text2){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + " (" + parameter + ":" + function + ")";
    };
};

class UndefindedVaraibale : public IError
{
    std::string variableName;
    std::string function;

public:
    UndefindedVaraibale(const std::string &text, const std::string &text2)
        : variableName(text), function(text2){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + " (" + variableName + ":" + function + ")";
    };
};

class AssignmentInvalidType : public IError
{
    std::string variableName;
    Type typ;

public:
    AssignmentInvalidType(const std::string &text, Type type)
        : variableName(text), typ(type){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + " (" + variableName + ":" + v.visit(typ) + ")";
    };
};

class CallOfUndefindedFunction : public IError
{
    std::string function;
    std::string function2;

public:
    CallOfUndefindedFunction(const std::string &text, const std::string &text2)
        : function(text), function2(text2){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + " (" + function + ":" + function2 + ")";
    };
};

class InvalidArgumentCount : public IError
{
    std::string function;
    std::string function2;
    int expected;
    int given;

public:
    InvalidArgumentCount(const std::string &text, const std::string &text2, int in, int in2)
        : function(text), function2(text2), expected(in), given(in2){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + " (" + function + ":" + function2 + ":" + std::to_string(expected) + ":" + std::to_string(given) + ")";
    };
};

class InvalidArgumentType : public IError
{
    std::string function;
    std::string function2;
    std::string parameter;
    Type expected;
    Type given;

public:
    InvalidArgumentType(const std::string &text, const std::string &text2, const std::string &text3, Type in, Type in2)
        : function(text), function2(text2), parameter(text3), expected(in), given(in2){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + " (" + function + ":" + function2 + ":" + parameter + ":" + v.visit(expected) + ":" + v.visit(given) + ")";
    };
};

class InvalidInitialValueType : public IError
{
    std::string function;
    std::string variable;
    Type expected;
    Type given;

public:
    InvalidInitialValueType(const std::string &text, const std::string &text2, Type in, Type in2)
        : function(text), variable(text2), expected(in), given(in2){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + " (" + function + ":" + variable + ":" + v.visit(expected) + ":" + v.visit(given) + ")";
    };
};

class VariableRedeclaration : public IError
{
    std::string function;
    std::string variable;

public:
    VariableRedeclaration(const std::string &text, const std::string &text2)
        : function(text), variable(text2){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + " (" + variable + ":" + function + ")";
    };
};

class MissingReturnExpression : public IError
{
    std::string function;
    Type expected;

public:
    MissingReturnExpression(const std::string &text, Type in)
        : function(text), expected(in){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + " (" + function + ":" + v.visit(expected) + ")";
    };
};

class InvalidReturnType : public IError
{
    std::string function;
    Type expected;

public:
    InvalidReturnType(const std::string &text, Type in)
        : function(text), expected(in){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + " (" + function + ":" + v.visit(expected) + ")";
    };
};

class MulitplicationOfTwoCurrencies : public IError
{
    std::string function;

public:
    explicit MulitplicationOfTwoCurrencies(const std::string &text)
        : function(text){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + function;
    };
};

class DividingNumberByCurrency : public IError
{
    std::string function;

public:
    explicit DividingNumberByCurrency(const std::string &text)
        : function(text){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + function;
    };
};

class ConversionToNumeric : public IError
{
    std::string function;
    std::string variable;

public:
    explicit ConversionToNumeric(const std::string &text, const std::string &text2)
        : function(text), variable(text2){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + " (" + function + ":" + variable + ")";
    };
};

class MissMatchOperandTypes : public IError
{
    std::string function;
    Type oper;
    Type type1;
    Type type2;

public:
    explicit MissMatchOperandTypes(const std::string &text, Type in1, Type in2, Type in3)
        : function(text), oper(in1), type1(in2), type2(in3){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + " (" + function + ":" + v.visit(oper) + ":" + v.visit(type1) + ":" + v.visit(type2) + ")";
    };
};

class InvalidNumberScanNum : public IError
{
    int number;

public:
    explicit InvalidNumberScanNum(int in)
        : number(in){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + std::to_string(number);
    };
};

class InvalidCurrencySymbol : public IError
{
    int number;

public:
    explicit InvalidCurrencySymbol(int in)
        : number(in){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + std::to_string(number);
    };
};

class NoReturn : public IError
{
    std::string functionName;

public:
    explicit NoReturn(const std::string &text)
        : functionName(text){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + functionName;
    };
};

class OverflowOrUnderflow : public IError
{

public:
    OverflowOrUnderflow() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this);
    };
};

class ZeroDevision : public IError
{

public:
    ZeroDevision() = default;
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this);
    };
};

class MissingProperMainFunction : public IError
{

public:
    std::string functionName;
public:
    explicit MissingProperMainFunction(const std::string &text)
        : functionName(text){};
    std::string accept(IErrVisitor &v) override
    {
        return v.visit(*this) + functionName;
    };
};