#include "../IVisitor.h"
#include <iostream>

#include "../../Elements/Statement/FunctionDefinition.h"
#include "../../Elements/Statement/EmbeddedFunction.h"

#include "../../Elements/Statement/AssignmentStatement.h"
#include "../../Elements/Statement/FunctionCallStatement.h"
#include "../../Elements/Statement/IfStatement.h"
#include "../../Elements/Statement/InitializeStatement.h"
#include "../../Elements/Statement/ReturnStatement.h"
#include "../../Elements/Statement/WhileStatement.h"

#include "../../Elements/Expression/OrExpr.h"
#include "../../Elements/Expression/AndExpr.h"

#include "../../Elements/Expression/NegationExpr.h"

#include "../../Elements/Expression/IsEqualExpr.h"
#include "../../Elements/Expression/NotEqualExpr.h"
#include "../../Elements/Expression/LessOrEqualExpr.h"
#include "../../Elements/Expression/LessExpr.h"
#include "../../Elements/Expression/GreaterOrEqualExpr.h"
#include "../../Elements/Expression/GreaterExpr.h"

#include "../../Elements/Expression/AddExpr.h"
#include "../../Elements/Expression/SubExpr.h"

#include "../../Elements/Expression/MultExpr.h"
#include "../../Elements/Expression/DivExpr.h"

#include "../../Elements/Expression/MinusNegExpr.h"

#include "../../Elements/Expression/CurrencyExpr.h"
#include "../../Elements/Expression/ConversionExpr.h"

#include "../../Elements/Expression/LiteralExpr.h"
#include "../../Elements/Expression/IdentifierExpr.h"
#include "../../Elements/Expression/FunCallExpr.h"

#include "../../Elements/Expression/StringLiteralExpr.h"

#include "../../Elements/IElement.h"
#include "../../Elements/Program.h"

class LogVisitor : public IVisitor
{
    mutable int level = 0;
    void nextLevel();
    void previousLevel();
    std::ostream &os = std::cout;

public:
    LogVisitor();
    ~LogVisitor() = default;

    void print(const IElement &element) const;
    void printIExprVector(const std::vector<IExpr> &expressions);
    void printIStateVector(const std::vector<IState> &statements);
    void printLeftAndRight(const IExpr &left, const IExpr &right);

    void visit(const Program &program);
    void visit(const FunctionDefinition &statement) override;
    void visit(const EmbeddedFunction &statement) override;

    void visit(const AssignmentStatement &statement) override;
    void visit(const FunctionCallStatement &statement) override;
    void visit(const IfStatement &statement) override;
    void visit(const InitializeStatement &statement) override;
    void visit(const ReturnStatement &statement) override;
    void visit(const WhileStatement &statement) override;

    void visit(const OrExpr &expr) override;
    void visit(const AndExpr &expr) override;
    void visit(const NegationExpr &expr) override;
    void visit(const IsEqualExpr &expr) override;
    void visit(const NotEqualExpr &expr) override;
    void visit(const LessOrEqualExpr &expr) override;
    void visit(const LessExpr &expr) override;
    void visit(const GreaterOrEqualExpr &expr) override;
    void visit(const GreaterExpr &expr) override;
    void visit(const AddExpr &expr) override;
    void visit(const SubExpr &expr) override;
    void visit(const MultExpr &expr) override;
    void visit(const DivExpr &expr) override;
    void visit(const MinusNegExpr &expr) override;
    void visit(const CurrencyExpr &expr) override;
    void visit(const ConversionExpr &expr) override;
    void visit(const LiteralExpr &expr) override;
    void visit(const IdentifierExpr &expr) override;
    void visit(const FunCallExpr &expr) override;

    void visit(const StringLiteralExpr &expr) override;
    void visit(const Parameter &expr) override;
};