add_library(CallContext CallContext.cpp)
add_library(Environment Environment.cpp)
add_library(Scope Scope.cpp)
add_library(Variable Variable.cpp)


target_link_libraries(Environment CallContext)
target_link_libraries(CallContext Scope)
target_link_libraries(Scope Variable)