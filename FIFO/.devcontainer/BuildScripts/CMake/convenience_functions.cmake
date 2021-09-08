find_package(GTest REQUIRED)

function(add_headers)
  # message("CMAKE_PARENT_LIST_FILE: " ${CMAKE_PARENT_LIST_FILE})
  message("CMAKE_CURRENT_LIST_FILE: " ${CMAKE_CURRENT_LIST_FILE})
  get_filename_component(this_directory ${CMAKE_PARENT_LIST_FILE} DIRECTORY)
  # message("Calling Directory: " ${this_directory})
  get_filename_component(this_folder ${this_directory} NAME)

  # message("ARGN: " ${ARGN})

  add_library(${this_folder})
  message("New Library: " ${this_folder})
  target_sources(${this_folder} INTERFACE ${ARGN})

endfunction(add_headers)

function(add_sources)

  get_filename_component(this_directory ${CMAKE_PARENT_LIST_FILE} DIRECTORY)
  get_filename_component(this_folder ${this_directory} NAME)
  target_sources(${this_folder} PRIVATE ${ARGN})
  set_target_properties(${this_folder} PROPERTIES LINKER_LANGUAGE "CXX")
  message("Added source: ${ARGN}")

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
