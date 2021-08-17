list(APPEND CMAKE_MODULE_PATH
     "${CMAKE_CURRENT_LIST_DIR}/.devcontainer/BuildScripts/CMake")

# preferences
include(
    ${CMAKE_CURRENT_SOURCE_DIR}/.devcontainer/BuildScripts/CMake/SetBuildChainSpecifications.cmake
)

cmake_minimum_required(VERSION 3.16)

# Supply arguments as key-value pairs CompilerChain: gcc | llvm | msvc | mingw
# LanguageStandard: 11 | 14 | 17 BuildType: Debug | Release
setbuildchainspecifications(CompilerChain ${COMPILER} LanguageStandard
                            ${STANDARD} BuildType ${CMAKE_BUILD_TYPE})

# The name of the project
project(
    demo
    VERSION 0.1
    LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Tool Compliance
include(
    ${CMAKE_CURRENT_SOURCE_DIR}/.devcontainer/BuildScripts/CMake/ToolCompliance.cmake
)

# For setting global variables, such as required directories
include(
    ${CMAKE_CURRENT_SOURCE_DIR}/.devcontainer/BuildScripts/CMake/SetGlobalVariables.cmake
)

# Function to build DemoApplication as a library. Not everything is linked yet.
include(
    ${CMAKE_CURRENT_SOURCE_DIR}/.devcontainer/BuildScripts/CMake/BuildDemoLibrary.cmake
)

# Convenience functions for installing DemoApplication locally
include(
    ${CMAKE_CURRENT_SOURCE_DIR}/.devcontainer/BuildScripts/CMake/InstallDemoApplicationLocally.cmake
)

# Ensure that all tools and versions are compliant. Minimum acceptable versions
# are speciied as key-value pairs Currently, only minimum git version is
# required
ensuretoolcompliance(Git 2.25)

# Set Global variables such as the commit-hash of the FancySquareRoot library
# that must be used.
setglobalvariables(Location_of_GoogleTests "${PROJECT_SOURCE_DIR}/GoogleTests")

# Build CPPProject as a library, but is not yet linked to external dependencies,
# as FancySquareRoot library
builddemoproject()

# Install the built package locally in order to support find_package
# installcppproject( Location "${PROJECT_SOURCE_DIR}/build/DemoLibrary"
# VERSION_MAJOR 0 # The version of the library is set to
# VERSION_MAJOR.VERSION_MINOR VERSION_MINOR 9)
