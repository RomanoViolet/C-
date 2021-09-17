find_package(GTest REQUIRED)

function(add_headers)

  message("CMAKE_CURRENT_LIST_FILE: " ${CMAKE_CURRENT_LIST_FILE})
  get_filename_component(this_directory ${CMAKE_PARENT_LIST_FILE} DIRECTORY)
  get_filename_component(this_folder ${this_directory} NAME)
  add_library(${this_folder} STATIC ${ARGN})
  message("New Library: " ${this_folder} " with: " ${ARGN})

endfunction(add_headers)

function(add_sources)

  get_filename_component(this_directory ${CMAKE_PARENT_LIST_FILE} DIRECTORY)
  get_filename_component(this_folder ${this_directory} NAME)
  message("Added source: ${ARGN} to library ${this_folder}")
  target_sources(${this_folder} PRIVATE ${ARGN})
  # target_sources(${this_folder} PUBLIC ${ARGN})
  set_target_properties(${this_folder} PROPERTIES LINKER_LANGUAGE "CXX")
  # message("Added source: ${ARGN} to library ${this_folder}")

endfunction(add_sources)

function(add_unittests)
  enable_testing()
  get_filename_component(this_directory ${CMAKE_PARENT_LIST_FILE} DIRECTORY)
  get_filename_component(this_folder ${this_directory} NAME)
  set(name_of_test_executable ${this_folder}_tests)
  add_executable(${name_of_test_executable})
  target_sources(${name_of_test_executable} PRIVATE ${ARGN})
  set_target_properties(${name_of_test_executable} PROPERTIES LINKER_LANGUAGE
                                                              CXX)
  message("Added unit test: ${name_of_test_executable} with source: ${ARGN}")

  gtest_discover_tests(${name_of_test_executable})
  target_link_libraries(
    ${name_of_test_executable}
    ${this_folder}
    ${GMOCK_LIBRARY}
    ${GMOCK_MAIN_LIBRARY}
    ${GTEST_LIBRARY}
    ${GTEST_MAIN_LIBRARY}
    pthread
    gmock_main
    gtest_main
    gmock)

endfunction(add_unittests)

function(add_compile_abort_unittests shellScript errorString)
  enable_testing()

  message("Added compile abort unittests with script ${shellScript}")

  get_filename_component(this_directory ${CMAKE_PARENT_LIST_FILE} DIRECTORY)
  get_filename_component(this_folder ${this_directory} NAME)

  set(name_of_test_executable ${this_folder}_compile_abort_tests)

  if(TARGET ${name_of_test_executable})

  else()

    add_test(
      NAME ${name_of_test_executable}
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
      COMMAND ${shellScript})

    set_tests_properties(
      ${name_of_test_executable}
      PROPERTIES WILL_FAIL
      PROPERTIES PASS_REGULAR_EXPRESSION ${errorString})
  endif()

endfunction(add_compile_abort_unittests)
