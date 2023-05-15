#pragma once

class FunctionDefinition;

class AssignmentStatement;
class FunctionCallStatement;
class IfStatement;
class InitializeStatement;
class ReturnStatement;
class WhileStatement;

class OrExpr;
class AndExpr;
class NegationExpr;
class IsEqualExpr;
class NotEqualExpr;
class LessOrEqualExpr;
class LessExpr;
class GreaterOrEqualExpr;
class GreaterExpr;
class AddExpr;
class SubExpr;
class MultExpr;
class DivExpr;
class MinusNegExpr;
class CurrencyExpr;
class ConversionExpr;
class LiteralExpr;
class IdentifierExpr;
class FunCallExpr;
class StringLiteralExpr;
class EmbeddedFunction;

class Parameter;

class IVisitor
{
public:
    IVisitor() = default;
    virtual ~IVisitor() = default;
    virtual void visit(const FunctionDefinition &t) = 0;
    virtual void visit(const EmbeddedFunction &t) = 0;

    virtual void visit(const AssignmentStatement &t) = 0;
    virtual void visit(const FunctionCallStatement &t) = 0;
    virtual void visit(const IfStatement &t) = 0;
    virtual void visit(const InitializeStatement &t) = 0;
    virtual void visit(const ReturnStatement &t) = 0;
    virtual void visit(const WhileStatement &t) = 0;

    virtual void visit(const OrExpr &) = 0;
    virtual void visit(const AndExpr &) = 0;
    virtual void visit(const NegationExpr &) = 0;
    virtual void visit(const IsEqualExpr &) = 0;
    virtual void visit(const NotEqualExpr &) = 0;
    virtual void visit(const LessOrEqualExpr &) = 0;
    virtual void visit(const LessExpr &) = 0;
    virtual void visit(const GreaterOrEqualExpr &) = 0;
    virtual void visit(const GreaterExpr &) = 0;
    virtual void visit(const AddExpr &) = 0;
    virtual void visit(const SubExpr &) = 0;
    virtual void visit(const MultExpr &) = 0;
    virtual void visit(const DivExpr &) = 0;
    virtual void visit(const MinusNegExpr &) = 0;
    virtual void visit(const CurrencyExpr &) = 0;
    virtual void visit(const ConversionExpr &) = 0;
    virtual void visit(const LiteralExpr &) = 0;
    virtual void visit(const IdentifierExpr &) = 0;
    virtual void visit(const FunCallExpr &) = 0;
    
    virtual void visit(const StringLiteralExpr &) = 0;  

    virtual void visit(const Parameter &) = 0; 
};