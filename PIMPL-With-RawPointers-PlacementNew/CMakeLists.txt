cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
project(main LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE "Debug")


message("Compiler used: ${CMAKE_CXX_COMPILER_ID}, Build Type: ${CMAKE_BUILD_TYPE}")

if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )

    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -march=native -O0 -pg -ggdb -g3 -Wall -Walloca -fno-omit-frame-pointer -fsanitize=address --no-inline -Weffc++ -Wnarrowing -Wnamespaces -Wreorder -fdiagnostics-show-location=once -fdiagnostics-color=auto -Wpedantic -Warray-bounds -Wc++11-compat -Wconversion")
    else()
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -march=native -O3 -Wall -Walloca -fno-omit-frame-pointer -fsanitize=address --no-inline -Weffc++ -Wnarrowing -Wnamespaces -Wreorder -fdiagnostics-show-location=once -fdiagnostics-color=auto -Wpedantic -Warray-bounds -Wc++11-compat -Wconversion")
    endif()

elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "llvm" OR  "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS_GENERAL}  -O0 -g3 -pg -ggdb -Wnoc++98-compat -Weverything -fno-omit-frame-pointer -fsanitize-memory-track-origins -fsanitize=memory -Wunused-private-field -fshow-source-location -fcolor-diagnostics" )
    else()
        set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS_GENERAL}  -O3 -Weverything -Wnoc++98-compat -Wunused-private-field -fno-omit-frame-pointer -fsanitize-memory-track-origins -fsanitize=memory -fshow-source-location -fcolor-diagnostics" )
    endif()

    set(CMAKE_AR "llvm-ar")
    set(CMAKE_RANLIB "llvm-ranlib")
    set(CMAKE_LD "llvm-ld")

else( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
    set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd" )
    

endif()


file(GLOB SRC ${CURRENT_LIST_DIR} *.cpp)

add_subdirectory("${PROJECT_SOURCE_DIR}/Library")
include_directories("${PROJECT_SOURCE_DIR}/Library")

add_executable(main "${SRC}")



target_link_libraries( main PUBLIC MyLibrary )
