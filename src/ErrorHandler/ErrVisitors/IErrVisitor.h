#pragma once
#include <string>

class UndefinedToken;
class UnknowEscapeCharacter;
class CommentTooLong;
class TextConstantTooLong;
class UnknownCharacter;
class LeadingZero;
class LostPrecision;
class NumberOverflow;
class MissingBackSlash;
class TooSimilarIdentifier;
class TooLongIdentifier;
class MissingFile;

class UnexpectedToken;
class RedefinitionOf;
class ExpectedParameter;
class ExpectedCondition;
class MissingElement;
class ExpectedExpressionAfter;
class MissingElementBefore;
class MissingElementAfter;
class ExpectedArgument;
class ExpectedExpressionBefore;

class UnknownCurrency;
class CurrencyInIdentifierInConversion;

class HeaderDuplicate;
class CurrencyNotInHeader;
class MissingDenaminationValues;
class ConfigExample;
class MissingConfig;

// Semantic check
class ParameterRedefinition;

class UndefindedVaraibale;
class AssignmentInvalidType;
enum class Type;
class CallOfUndefindedFunction;
class InvalidArgumentCount;
class InvalidArgumentType;
class InvalidInitialValueType;
class VariableRedeclaration;
class MissingReturnExpression;
class InvalidReturnType;
class MulitplicationOfTwoCurrencies;
class DividingNumberByCurrency;
class ConversionToNumeric;
class MissMatchOperandTypes;
class InvalidNumberScanNum;
class InvalidCurrencySymbol;
class NoReturn;
class OverflowOrUnderflow;
class ZeroDevision;
class MissingProperMainFunction;

class IErrVisitor
{

public:
    IErrVisitor() = default;
    virtual ~IErrVisitor() = default;

    virtual std::string visit(UndefinedToken &) = 0;
    virtual std::string visit(UnknowEscapeCharacter &) = 0;
    virtual std::string visit(CommentTooLong &) = 0;
    virtual std::string visit(TextConstantTooLong &) = 0;
    virtual std::string visit(UnknownCharacter &) = 0;
    virtual std::string visit(LeadingZero &) = 0;
    virtual std::string visit(LostPrecision &) = 0;
    virtual std::string visit(NumberOverflow &) = 0;
    virtual std::string visit(MissingBackSlash &) = 0;
    virtual std::string visit(TooSimilarIdentifier &) = 0;
    virtual std::string visit(TooLongIdentifier &) = 0;
    virtual std::string visit(MissingFile &) = 0;

    // parser
    virtual std::string visit(UnexpectedToken &) = 0;

    virtual std::string visit(RedefinitionOf &) = 0;

    virtual std::string visit(ExpectedParameter &) = 0;
    virtual std::string visit(ExpectedCondition &) = 0;

    virtual std::string visit(MissingElement &) = 0;

    virtual std::string visit(ExpectedExpressionAfter &) = 0;
    virtual std::string visit(ExpectedExpressionBefore &) = 0;

    virtual std::string visit(MissingElementBefore &) = 0;
    virtual std::string visit(MissingElementAfter &) = 0;
    virtual std::string visit(ExpectedArgument &) = 0;

    virtual std::string visit(CurrencyInIdentifierInConversion &) = 0;
    virtual std::string visit(UnknownCurrency &) = 0;

    // Config Parser
    virtual std::string visit(HeaderDuplicate &) = 0;
    virtual std::string visit(CurrencyNotInHeader &) = 0;
    virtual std::string visit(MissingDenaminationValues &) = 0;
    virtual std::string visit(ConfigExample &) = 0;
    virtual std::string visit(MissingConfig &) = 0;

    // SemanticVisitor
    virtual std::string visit(ParameterRedefinition &) = 0;
    virtual std::string visit(UndefindedVaraibale &) = 0;
    virtual std::string visit(AssignmentInvalidType &) = 0;
    virtual std::string visit(Type &) = 0;
    virtual std::string visit(CallOfUndefindedFunction &) = 0;
    virtual std::string visit(InvalidArgumentCount &) = 0;
    virtual std::string visit(InvalidArgumentType &) = 0;
    virtual std::string visit(InvalidInitialValueType &) = 0;
    virtual std::string visit(VariableRedeclaration &) = 0;
    virtual std::string visit(MissingReturnExpression &) = 0;
    virtual std::string visit(InvalidReturnType &) = 0;
    virtual std::string visit(MulitplicationOfTwoCurrencies &) = 0;
    virtual std::string visit(DividingNumberByCurrency &) = 0;
    virtual std::string visit(ConversionToNumeric &) = 0;
    virtual std::string visit(MissMatchOperandTypes &) = 0;

    // Runtime errors
    virtual std::string visit(InvalidNumberScanNum &) = 0;
    virtual std::string visit(InvalidCurrencySymbol &) = 0;
    virtual std::string visit(NoReturn &) = 0;
    virtual std::string visit(OverflowOrUnderflow &) = 0;
    virtual std::string visit(ZeroDevision &) = 0;
    virtual std::string visit(MissingProperMainFunction &) = 0;


    
};