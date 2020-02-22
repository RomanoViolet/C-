# Get a list of all source files.
file(GLOB_RECURSE SRC *.hpp *.inl *.cpp)

# Compile the interface files into a library
add_library(Library STATIC ${SRC})

include_directories("${PROJECT_SOURCE_DIR}/CoreFunctions")

# In case of .inl files which CMake cannot associate to C++. Set the language
# explicitly. At the moment, only .cpp and .hpp files have been provided.
set_target_properties(Library PROPERTIES LINKER_LANGUAGE CXX)
