function(add_headers)

  message("CMAKE_CURRENT_LIST_FILE: " ${CMAKE_CURRENT_LIST_FILE})
  get_filename_component(this_directory ${CMAKE_PARENT_LIST_FILE} DIRECTORY)
  get_filename_component(this_folder ${this_directory} NAME)
  add_library(${this_folder} STATIC ${ARGN})
  message("New Library: " ${this_folder} " with: " ${ARGN})
  set(library_name
      "${this_folder}"
      CACHE INTERNAL "library_name")

endfunction(add_headers)

function(add_sources)

  get_filename_component(this_directory ${CMAKE_PARENT_LIST_FILE} DIRECTORY)
  get_filename_component(this_folder ${this_directory} NAME)
  message("Added source: ${ARGN} to library ${this_folder}")
  target_sources(${this_folder} PRIVATE ${ARGN})
  set(source_list
      "${ARGN}"
      CACHE INTERNAL "source_list")
  # target_sources(${this_folder} PUBLIC ${ARGN})
  set_target_properties(${this_folder} PROPERTIES LINKER_LANGUAGE "CXX")
  # message("Added source: ${ARGN} to library ${this_folder}")

endfunction(add_sources)

function(create_executable)
  get_filename_component(this_directory ${CMAKE_PARENT_LIST_FILE} DIRECTORY)
  get_filename_component(this_folder ${this_directory} NAME)
  set(name_of_test_executable ${this_folder}_app)
  message("Executable is: ${name_of_test_executable}")
  add_executable(${name_of_test_executable} ${source_list} ${ARGN})
  target_link_libraries(${name_of_test_executable} ${library_name})
endfunction(create_executable)

function(add_unittests)
  enable_testing()
  find_package(GTest CONFIG REQUIRED)
  include(GoogleTest)
  include_directories(${GTEST_INCLUDE_DIRS})
  get_filename_component(this_directory ${CMAKE_PARENT_LIST_FILE} DIRECTORY)
  get_filename_component(this_folder ${this_directory} NAME)
  set(name_of_test_executable ${this_folder}_tests)
  add_executable(${name_of_test_executable})
  target_sources(${name_of_test_executable} PRIVATE ${ARGN})
  set_target_properties(${name_of_test_executable} PROPERTIES LINKER_LANGUAGE
                                                              CXX)
  message(
    "Added unit test: ${name_of_test_executable} with source: ${ARGN} and ${GTEST_LIBRARY}"
  )

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
    gmock
    gtest)

endfunction(add_unittests)

function(add_compile_abort_unittests shellScript errorString)
  enable_testing()

  message("Added compile abort unittests with script ${shellScript}")

  get_filename_component(this_directory ${CMAKE_PARENT_LIST_FILE} DIRECTORY)
  get_filename_component(this_folder ${this_directory} NAME)
  get_filename_component(this_negative_test ${shellScript} NAME_WE)
  message("Name of negative test: ${this_negative_test}")

  set(name_of_test_executable ${this_folder}_${this_negative_test})

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
