list(APPEND CMAKE_MODULE_PATH
     "${CMAKE_CURRENT_LIST_DIR}/.devcontainer/BuildScripts/CMake")

# preferences
include(SetBuildChainSpecifications)

cmake_minimum_required(VERSION 3.16)

# Supply arguments as key-value pairs CompilerChain: gcc | llvm | msvc | mingw
# LanguageStandard: 11 | 14 | 17 BuildType: Debug | Release
setbuildchainspecifications(CompilerChain ${COMPILER} LanguageStandard
                            ${STANDARD} BuildType ${CMAKE_BUILD_TYPE})

# The name of the project
project(
  CircularBuffer
  VERSION 1.0
  LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()
# add_subdirectory(${PROJECT_SOURCE_DIR}/CircularBuffer_Simplified)
add_subdirectory(${PROJECT_SOURCE_DIR}/CircularBuffer)
