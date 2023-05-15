#include "IErrVisitor.h"
#include "../Errors.h"
#include "../../Elements/Type.h"

class ErrVisitorEng : public IErrVisitor
{
public:
    ErrVisitorEng() = default;
    ~ErrVisitorEng() = default;

    // std::string getTypeName(Type t);

    std::string visit(UndefinedToken &err) override;
    std::string visit(UnknowEscapeCharacter &err) override;
    std::string visit(CommentTooLong &err) override;
    std::string visit(TextConstantTooLong &err) override;
    std::string visit(UnknownCharacter &err) override;
    std::string visit(LeadingZero &err) override;
    std::string visit(LostPrecision &err) override;
    std::string visit(NumberOverflow &err) override;
    std::string visit(MissingBackSlash &err) override;
    std::string visit(TooSimilarIdentifier &err) override;
    std::string visit(TooLongIdentifier &err) override;
    std::string visit(MissingFile &err) override;

    std::string visit(UnexpectedToken &err) override;
    std::string visit(RedefinitionOf &err) override;
    std::string visit(ExpectedParameter &err) override;
    std::string visit(ExpectedCondition &err) override;
    std::string visit(MissingElement &err) override;
    std::string visit(ExpectedExpressionAfter &err) override;

    std::string visit(MissingElementBefore &err) override;
    std::string visit(ExpectedArgument &err) override;
    std::string visit(MissingElementAfter &err) override;
    std::string visit(ExpectedExpressionBefore &err) override;

    std::string visit(CurrencyInIdentifierInConversion &err) override;
    std::string visit(UnknownCurrency &err) override;

    std::string visit(HeaderDuplicate &err) override;
    std::string visit(CurrencyNotInHeader &err) override;
    std::string visit(MissingDenaminationValues &err) override;
    std::string visit(ConfigExample &err) override;
    std::string visit(MissingConfig &err) override;
    // Semantic check
    std::string visit(ParameterRedefinition &) override;
    std::string visit(UndefindedVaraibale &) override;
    std::string visit(AssignmentInvalidType &) override;
    std::string visit(Type &) override;
    std::string visit(CallOfUndefindedFunction &) override;
    std::string visit(InvalidArgumentCount &) override;
    std::string visit(InvalidArgumentType &) override;
    std::string visit(InvalidInitialValueType &) override;
    std::string visit(VariableRedeclaration &) override;
    std::string visit(MissingReturnExpression &) override;
    std::string visit(InvalidReturnType &) override;
    std::string visit(MulitplicationOfTwoCurrencies &) override;
    std::string visit(DividingNumberByCurrency &) override;
    std::string visit(ConversionToNumeric &) override;
    std::string visit(MissMatchOperandTypes &) override;

    // Runtime
    std::string visit(InvalidNumberScanNum &) override;
    std::string visit(InvalidCurrencySymbol &) override;
    std::string visit(NoReturn &) override;
    std::string visit(OverflowOrUnderflow &) override;
    std::string visit(ZeroDevision &) override;
    std::string visit(MissingProperMainFunction &) override;
};