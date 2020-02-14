# Get a list of all source files.
file(GLOB SRC *.hpp *.inl *.cpp)

# Compile the interface files into a library
add_library (Library STATIC ${SRC})

# In case of .inl files which CMake cannot associate to C++. Set the language explicitly.
# At the moment, only .cpp and .hpp files have been provided.
set_target_properties(Library PROPERTIES LINKER_LANGUAGE CXX)
