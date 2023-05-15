add_library(Parser Parser.cpp)
target_link_libraries(Parser Lexer)
target_link_libraries(Parser ConfigParser)
target_link_libraries(Parser Program)
target_link_libraries(Parser Parameter)

target_link_libraries(Parser AssignmentStatement)
target_link_libraries(Parser FunctionCallStatement)
target_link_libraries(Parser FunctionDefinition)
target_link_libraries(Parser IfStatement)
target_link_libraries(Parser InitializeStatement)
target_link_libraries(Parser ReturnStatement)
target_link_libraries(Parser WhileStatement)


target_link_libraries(Parser OrExpr)
target_link_libraries(Parser AndExpr)

target_link_libraries(Parser NegationExpr)

target_link_libraries(Parser IsEqualExpr)
target_link_libraries(Parser NotEqualExpr)
target_link_libraries(Parser LessOrEqualExpr)
target_link_libraries(Parser GreaterOrEqualExpr)
target_link_libraries(Parser LessExpr)
target_link_libraries(Parser GreaterExpr)

target_link_libraries(Parser AddExpr)
target_link_libraries(Parser SubExpr)

target_link_libraries(Parser MultExpr)
target_link_libraries(Parser DivExpr)

target_link_libraries(Parser MinusNegExpr)

target_link_libraries(Parser LiteralExpr)
target_link_libraries(Parser IdentifierExpr)
target_link_libraries(Parser FunCallExpr)

target_link_libraries(Parser StringLiteralExpr)

target_link_libraries(Parser ConversionExpr)
target_link_libraries(Parser CurrencyExpr)


