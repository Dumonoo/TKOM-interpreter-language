add_library(ErrorReporter ErrorReporter.cpp)
add_subdirectory(ErrVisitors)

target_link_libraries(ErrorReporter ErrVisitorEng)
# target_link_libraries(Lexer Token)
# target_link_libraries(Lexer utils)