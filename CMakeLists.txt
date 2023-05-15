cmake_minimum_required(VERSION 3.20)
project(tkom-interpreter VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)


enable_testing()

# Adding src files
add_subdirectory(src)
add_subdirectory(tests)

include_directories(src) 

add_executable(tkom-interpreter main.cpp)

target_link_libraries(tkom-interpreter PUBLIC Token)
target_link_libraries(tkom-interpreter PUBLIC Lexer)
target_link_libraries(tkom-interpreter PUBLIC Parser)
target_link_libraries(tkom-interpreter PUBLIC ErrorReporter)
target_link_libraries(tkom-interpreter PUBLIC utils)

target_link_libraries(tkom-interpreter PUBLIC LogVisitor)
target_link_libraries(tkom-interpreter PUBLIC SemanticVisitor)
target_link_libraries(tkom-interpreter PUBLIC InterpreterVisitor)

target_link_libraries(tkom-interpreter PUBLIC ConfigParser)

target_compile_options(tkom-interpreter PUBLIC -Wall -Wextra -Wpedantic -Werror)

# Tests segment
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
