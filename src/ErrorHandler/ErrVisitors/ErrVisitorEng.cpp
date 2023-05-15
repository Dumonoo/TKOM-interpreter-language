#include "ErrVisitorEng.h"

using namespace std;

string ErrVisitorEng::visit(UndefinedToken &err)
{
    return "undefined token";
}

string ErrVisitorEng::visit(UnknowEscapeCharacter &err)
{
    return "unknow escape character";
}

string ErrVisitorEng::visit(CommentTooLong &err)
{
    return "too long comment";
}

string ErrVisitorEng::visit(TextConstantTooLong &err)
{
    return "text constant too long - max length is: ";
}

string ErrVisitorEng::visit(UnknownCharacter &err)
{
    return "unknown character";
}

string ErrVisitorEng::visit(LeadingZero &err)
{
    return "leading zero in front of the number";
}

string ErrVisitorEng::visit(LostPrecision &err)
{
    return "precision lost - maximum decimal places: ";
}

string ErrVisitorEng::visit(NumberOverflow &err)
{
    return "number overflow - max decimal number: ";
}

string ErrVisitorEng::visit(MissingBackSlash &err)
{
    return "missing \" in text constant";
}

string ErrVisitorEng::visit(TooSimilarIdentifier &err)
{
    return "identifier to similar to keyword";
}

string ErrVisitorEng::visit(TooLongIdentifier &err)
{
    return "too long identifier  max length is: ";
}

string ErrVisitorEng::visit(MissingFile &err)
{
    return "couldn't find file";
}

string ErrVisitorEng::visit(UnexpectedToken &err)
{
    return "unexpected token - expected: ";
}

string ErrVisitorEng::visit(RedefinitionOf &err)
{
    return "redefiniton of function: ";
}

string ErrVisitorEng::visit(ExpectedParameter &err)
{
    return "expected parameter here";
}

string ErrVisitorEng::visit(ExpectedCondition &err)
{
    return "expected condition here";
}

string ErrVisitorEng::visit(MissingElement &err)
{
    return "missing: ";
}

string ErrVisitorEng::visit(ExpectedExpressionAfter &err)
{
    return "expected expression after: ";
}

string ErrVisitorEng::visit(ExpectedExpressionBefore &err)
{
    return "expected expression before: ";
}

string ErrVisitorEng::visit(MissingElementBefore &err)
{
    return " before: ";
}

string ErrVisitorEng::visit(MissingElementAfter &err)
{
    return " after: ";
}

string ErrVisitorEng::visit(ExpectedArgument &err)
{
    return " expected argument before: ";
}

string ErrVisitorEng::visit(CurrencyInIdentifierInConversion &err)
{
    return " detected currency in currency conversion: ";
}

string ErrVisitorEng::visit(UnknownCurrency &err)
{
    return " unknown currency: ";
}

string ErrVisitorEng::visit(HeaderDuplicate &err)
{
    return " currency already in matrix: ";
}

string ErrVisitorEng::visit(CurrencyNotInHeader &err)
{
    return " currency not in header: ";
}

string ErrVisitorEng::visit(MissingDenaminationValues &err)
{
    return " config matrix size error - should be nxn: ";
}

string ErrVisitorEng::visit(ConfigExample &err)
{
    return "config matrix should be n x n like this example:\n"
           "@   USD   CAD; \n"
           "USD 1     1.2583;\n"
           "CAD 0.2340  1 ;\n";
}

string ErrVisitorEng::visit(MissingConfig &err)
{
    return "missing config file";
}

// Semantic check 

string ErrVisitorEng::visit(ParameterRedefinition &err)
{
    return "parameter redefinition (parameter:function): ";
}

string ErrVisitorEng::visit(UndefindedVaraibale &err)
{
    return "undefined variable (variable:function) in: ";
}

string ErrVisitorEng::visit(AssignmentInvalidType &err)
{
    return "redeclaration invalid type (variable:expected type): ";
}

string ErrVisitorEng::visit(Type &t)
{
    if(t == Type::NUM)
        return "num";
    if(t == Type::CUR)
        return "cur";
    if(t == Type::VOID)
        return "void";
    if(t == Type::PLUS)
        return "+";
    if(t == Type::MINUS)
        return "-";

    if(t == Type::GREATER_OR_EQUAL)
        return ">=";
    if(t == Type::GREATER)
        return ">";
    if(t == Type::LESS_OR_EQUAL)
        return "<=";
    if(t == Type::LESS)
        return "<";
    if(t == Type::IS_EQUAL)
        return "==";
    if(t == Type::NOT_EQUAL)
        return "!=";
    return "null";
}

string ErrVisitorEng::visit(CallOfUndefindedFunction &err)
{
    return "call of undefinded function (undefinded funcion:inside function): ";
}

string ErrVisitorEng::visit(InvalidArgumentCount &err)
{
    return "invalid arguments count (function:function calling:expectedArguments:givenArguments): ";
}

string ErrVisitorEng::visit(InvalidArgumentType &err)
{
    return "invalid argument type (function:function calling:parameter name:expected type:given type): ";
}

string ErrVisitorEng::visit(InvalidInitialValueType &err)
{
    return "invalid initial value type (function:variable name:expected type:given type): ";
}

string ErrVisitorEng::visit(VariableRedeclaration &err)
{
    return "variable redeclaration (variable name:function name): ";
}

string ErrVisitorEng::visit(MissingReturnExpression &err)
{
    return "missing return expression in  (function name: expression expected type): ";
}

string ErrVisitorEng::visit(InvalidReturnType &err)
{
    return "invalid return type  (function name: expected retrun type): ";
}

string ErrVisitorEng::visit(MulitplicationOfTwoCurrencies &err)
{
    return "multiplication of two currencies in function: ";
}

string ErrVisitorEng::visit(DividingNumberByCurrency &err)
{
    return "dividing number by currency in function: ";
}

string ErrVisitorEng::visit(ConversionToNumeric &err)
{
    return "conversion @ to numeric variable (function:numeric variable name): ";
}

string ErrVisitorEng::visit(MissMatchOperandTypes &err)
{
    return "miss match operand types (function:operator:type1:type2): ";
}

// Runtime 

string ErrVisitorEng::visit(InvalidNumberScanNum &err)
{
    return "given user input to scanNum was invalid - retries: ";
}

string ErrVisitorEng::visit(InvalidCurrencySymbol &err)
{
    return "given user input to scanCur was invalid - retries: ";
}

string ErrVisitorEng::visit(NoReturn &err)
{
    return "function execution reach end of function definion and didnt encounter return statement in non void function: ";
}

string ErrVisitorEng::visit(OverflowOrUnderflow &err)
{
    return "value overflow or underflow during runtime operation";
}

string ErrVisitorEng::visit(ZeroDevision &err)
{
    return "encountered division by 0 during runtime";
}

string ErrVisitorEng::visit(MissingProperMainFunction &err)
{
    return "main function should be void and have 0 arguments - function: ";
}