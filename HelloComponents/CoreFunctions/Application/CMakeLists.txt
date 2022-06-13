include(convenience_functions)
include_directories(${PROJECT_SOURCE_DIR}/CoreFunctions/Library)
add_headers(Producer.hpp Consumer.hpp)
add_sources(Producer.cpp Consumer.cpp)
# add_unittests(unit_tests.cpp) add_compile_abort_unittests(
# ${CMAKE_CURRENT_LIST_DIR}/runNegativeCompilerTests_CPP20Concepts.sh
# "constraint_error") add_compile_abort_unittests(
# ${CMAKE_CURRENT_LIST_DIR}/runNegativeCompilerTests_CPP17.sh "incomplete type")
