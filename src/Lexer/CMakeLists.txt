add_library(Lexer Lexer.cpp)
target_link_libraries(Lexer Token)
target_link_libraries(Lexer utils)
target_link_libraries(Lexer ErrorReporter)