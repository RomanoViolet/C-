#[[
include(convenience_functions)
add_headers(TypeExists.hpp CircularBuffer.hpp)
add_sources(CircularBuffer.inl)
add_unittests(unit_tests.cpp)
add_compile_abort_unittests(
  ${CMAKE_CURRENT_LIST_DIR}/runNegativeCompilerTests.sh "constraint_error")
]]

find_package(GTest REQUIRED)

enable_testing()
add_library(CircularBuffer CircularBuffer.hpp CircularBuffer.inl TypeExists.hpp)
set_target_properties(CircularBuffer PROPERTIES LINKER_LANGUAGE "CXX")

add_executable(UnitTestExecutable ${CMAKE_CURRENT_LIST_DIR}/unit_tests.cpp)
set_target_properties(UnitTestExecutable PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(UnitTestExecutable CircularBuffer ${GTEST_LIBRARY}
                      ${GTEST_MAIN_LIBRARY} pthread gtest_main)
gtest_discover_tests(UnitTestExecutable)

add_test(
  NAME NEGATIVE_COMPILER_TESTS
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  COMMAND ${CMAKE_CURRENT_LIST_DIR}/runNegativeCompilerTests.sh)

set_tests_properties(
  NEGATIVE_COMPILER_TESTS
  PROPERTIES WILL_FAIL
  PROPERTIES PASS_REGULAR_EXPRESSION "constraint_error")

# add_test(NAME USUAL_TESTS COMMAND UnitTestExecutable)
