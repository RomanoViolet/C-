# Get a list of all source files.
file(GLOB_RECURSE SRC *.hpp *.inl *.cpp)

# Compile the interface files into a library
add_library (Interfaces STATIC ${SRC})

# In case of .inl files which CMake cannot associate to C++. Set the language explicitly.
# At the moment, only .cpp and .hpp files have been provided.
set_target_properties(Interfaces PROPERTIES LINKER_LANGUAGE CXX)
