cmake_minimum_required(VERSION 3.10)
project(myProject LANGUAGES CXX)
#SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
SET(CMAKE_CXX_STANDARD 14)

include(${CMAKE_CURRENT_SOURCE_DIR}/BuildScripts/CMake/BuildAndRunAllGoogleTests.cmake)

file(GLOB_RECURSE SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")
include_directories("${PROJECT_SOURCE_DIR}/src")
add_executable(myProject "${SRC}")
set_target_properties(myProject PROPERTIES LINKER_LANGUAGE "CXX")

#set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS_GCC_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
                                -march=native \
                                -rdynamic \
                                -O0 \
                                -pg \
                                -ggdb \
                                -g3 \
                                -Wall \
                                -fdump-rtl-all \
                                -Werror=reorder \
                                -fvisibility=hidden \
                                -Weffc++ \
                                -Werror=uninitialized \
                                --no-inline \
                                -Werror=narrowing \
                                -Wnamespaces \
                                -Werror=reorder \
                                -fdiagnostics-show-location=once \
                                -Werror=unused-parameter \
                                -fdiagnostics-color=auto \
                                -Werror=pedantic \
                                -Warray-bounds \
                                -fstack-protector-strong \
                                -fstack-protector \
                                -D_FORTIFY_SOURCE=2 \
                                -Wconversion \
                                -Werror=unused-value")

set(CMAKE_CXX_FLAGS_CLANG_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
                                -march=native \
                                -rdynamic \
                                -O0 \
                                -pg \
                                -ggdb \
                                -g3 \
                                -Wall \
                                -Werror=reorder \
                                -fvisibility=hidden \
                                -Weffc++ \
                                -Werror=uninitialized \
                                -Werror=narrowing \
                                -Wnamespaces \
                                -Werror=reorder \
                                -fdiagnostics-show-location=once \
                                -Werror=unused-parameter \
                                -fdiagnostics-color=auto \
                                -Werror=pedantic \
                                -Warray-bounds \
                                -fstack-protector-strong \
                                -fstack-protector \
                                -D_FORTIFY_SOURCE=2 \
                                -Wconversion \
                                -Werror=unused-value")


set(CMAKE_CXX_FLAGS_GCC_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} \
                                -march=native \
                                -rdynamic \
                                -O2 \
                                -Wall \
                                -fdump-rtl-all \
                                -Werror=reorder \
                                -fvisibility=hidden \
                                -Weffc++ \
                                -Werror=uninitialized \
                                --no-inline \
                                -Werror=narrowing \
                                -Wnamespaces \
                                -Werror=reorder \
                                -fdiagnostics-show-location=once \
                                -Werror=unused-parameter \
                                -fdiagnostics-color=auto \
                                -Werror=pedantic \
                                -Warray-bounds \
                                -fstack-protector-strong \
                                -fstack-protector \
                                -D_FORTIFY_SOURCE=2 \
                                -Wconversion \
                                -Werror=unused-value")
                                
set(CMAKE_CXX_FLAGS_CLANG_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} \
                                -march=native \
                                -rdynamic \
                                -O2 \
                                -Wall \
                                -Werror=reorder \
                                -fvisibility=hidden \
                                -Weffc++ \
                                -Werror=uninitialized \
                                -Werror=narrowing \
                                -Wnamespaces \
                                -Werror=reorder \
                                -fdiagnostics-show-location=once \
                                -Werror=unused-parameter \
                                -fdiagnostics-color=auto \
                                -Werror=pedantic \
                                -Warray-bounds \
                                -fstack-protector-strong \
                                -fstack-protector \
                                -D_FORTIFY_SOURCE=2 \
                                -Wconversion \
                                -Werror=unused-value")
                                
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS_RELEASE, ${CMAKE_CXX_FLAGS_CLANG_RELEASE})
    set(CMAKE_CXX_FLAGS_DEBUG, ${CMAKE_CXX_FLAGS_CLANG_DEBUG})
    
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_RELEASE, ${CMAKE_CXX_FLAGS_GCC_RELEASE})
    set(CMAKE_CXX_FLAGS_DEBUG, ${CMAKE_CXX_FLAGS_GCC_DEBUG})
    
endif()

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -march=native -rdynamic -O0 -ggdb -g3 -Wall -fdump-rtl-all -Werror=reorder -fvisibility=hidden -Weffc++ -Werror=uninitialized --no-inline -Wnarrowing -Wnamespaces -Wreorder -fdiagnostics-show-location=once -Werror=unused-parameter -fdiagnostics-color=auto -Wpedantic -Warray-bounds -fstack-protector-strong -fstack-protector -D_FORTIFY_SOURCE=2 -Wconversion")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -march=native -O0 -pg -ggdb -Wall -Weffc++")


target_link_libraries( myProject PUBLIC )


# Build and Run Google Tests
BuildAndRunAllGoogleTests()
