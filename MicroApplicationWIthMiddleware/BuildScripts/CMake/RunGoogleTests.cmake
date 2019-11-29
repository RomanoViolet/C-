include(CTest)

function(RunGoogleTests)
  if(BUILD_TESTING)
    # Run all tests via CTest
    add_custom_command(TARGET AllGoogleTests POST_BUILD
                       COMMAND ctest --verbose
                       COMMENT "Running Unit Tests..."
                       WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
  endif(BUILD_TESTING)
endfunction(RunGoogleTests)
