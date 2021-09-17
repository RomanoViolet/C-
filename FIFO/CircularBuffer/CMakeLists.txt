include(convenience_functions)
add_headers(TypeExists.hpp CircularBuffer.hpp)
add_sources(CircularBuffer.inl)
add_unittests(unit_tests.cpp)
add_compile_abort_unittests(
  ${CMAKE_CURRENT_LIST_DIR}/runNegativeCompilerTests.sh "constraint_error")
