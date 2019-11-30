# Configure google-test as a downloadable library.
include(${PROJECT_SOURCE_DIR}/BuildScripts/CMake/BuildGoogleTests.cmake)
find_package(GTest REQUIRED)
# The name of this directory
get_filename_component(ThisGoogleTestDirectory ${CMAKE_CURRENT_SOURCE_DIR} NAME)


# Add Local sources
file(GLOB_RECURSE TEST_SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
if ( TEST_SRC )

    # All sources...
    file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

    # minus the main
    list(FILTER SRC EXCLUDE REGEX "main.cpp")

    # Lib includes
    add_executable(${ThisGoogleTestDirectory}_GoogleTest "${SRC}" "${TEST_SRC}")



    #target_include_directories(${ThisGoogleTestDirectory}_GoogleTest
    #			PUBLIC
    #      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src> # All data types used in the definition of core-functions.
  #)


    set_target_properties(${ThisGoogleTestDirectory}_GoogleTest PROPERTIES LINKER_LANGUAGE CXX)
    target_link_libraries(${ThisGoogleTestDirectory}_GoogleTest gtest gtest_main gmock gmock_main pthread)
    #target_link_libraries(${ThisGoogleTestDirectory}_GoogleTest DemoLibrary ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} pthread)

    add_dependencies( AllGoogleTests ${ThisGoogleTestDirectory}_GoogleTest)
    set(UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} ${ThisGoogleTestDirectory}_GoogleTest PARENT_SCOPE)
    add_test (${ThisGoogleTestDirectory}_GoogleTest ${CMAKE_CURRENT_BINARY_DIR}/${ThisGoogleTestDirectory}_GoogleTest)
endif()
