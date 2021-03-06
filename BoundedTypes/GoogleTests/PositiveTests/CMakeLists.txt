#
# How to test for build or compile time failures.
# https://stackoverflow.com/questions/30155619/expected-build-failure-tests-in-
# cmake
#
# Configure google-test as a downloadable library.
include(${PROJECT_SOURCE_DIR}/BuildScripts/CMake/BuildGoogleTests.cmake)
find_package(GTest REQUIRED)
# The name of this directory
get_filename_component(ThisGoogleTestDirectory ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Add Local sources
file(GLOB TEST_SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
message("Google Implementation Test CPP Sources:" ${TEST_SRC})
if(TEST_SRC)

  # Lib includes
  add_executable(${ThisGoogleTestDirectory}_GoogleTest "${TEST_SRC}")

  # include_directories(${PROJECT_SOURCE_DIR}/Library)

  target_include_directories(
    ${ThisGoogleTestDirectory}_GoogleTest
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Library>)

  set_target_properties(${ThisGoogleTestDirectory}_GoogleTest
                        PROPERTIES LINKER_LANGUAGE CXX)

  target_link_libraries(
    ${ThisGoogleTestDirectory}_GoogleTest
    ${GMOCK_LIBRARY}
    ${GMOCK_MAIN_LIBRARY}
    ${GTEST_LIBRARY}
    ${GTEST_MAIN_LIBRARY}
    pthread
    gmock_main
    gtest_main
    gtest
    gmock
    BoundedTypes)

  # target_link_libraries(${ThisGoogleTestDirectory}_GoogleTest DemoLibrary
  # gtest gtest_main gmock gmock_main pthread)

  add_dependencies(AllGoogleTests ${ThisGoogleTestDirectory}_GoogleTest
                   BoundedTypes)
  set(UNIT_TEST_TARGETS
      ${UNIT_TEST_TARGETS} ${ThisGoogleTestDirectory}_GoogleTest
      PARENT_SCOPE)
  add_test(${ThisGoogleTestDirectory}_GoogleTest
           ${CMAKE_CURRENT_BINARY_DIR}/${ThisGoogleTestDirectory}_GoogleTest)
endif()
