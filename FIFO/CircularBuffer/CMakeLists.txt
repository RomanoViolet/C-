include(convenience_functions)
add_headers(CircularBuffer.hpp)
add_sources(main.cpp)
add_unittests(unit_tests.cpp)

# Negative Compiler Tests
find_package(GTest REQUIRED)
enable_testing()
add_test(
  NAME NEGATIVE_COMPILER_TESTS
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  COMMAND ${CMAKE_CURRENT_LIST_DIR}/runNegativeCompilerTests.sh)

set_tests_properties(
  NEGATIVE_COMPILER_TESTS
  PROPERTIES WILL_FAIL
  PROPERTIES PASS_REGULAR_EXPRESSION "static_assert")

# add_sources() add_testfiles()
