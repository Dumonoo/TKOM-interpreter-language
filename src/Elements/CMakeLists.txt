add_subdirectory(Expression)
add_subdirectory(Statement)
add_subdirectory(Interpretation)

add_library(Program Program.cpp)
add_library(Parameter Parameter.cpp)

target_link_libraries(Program EmbeddedFunction)
# add_library()