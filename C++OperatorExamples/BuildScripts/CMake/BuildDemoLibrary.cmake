# Convenience function to be called from the main CMakeLists.txt
function(buildCPPProject)

  # tell CMake where to find all headers required by the sources.

  file(GLOB_RECURSE CPPProject_SOURCES ${PROJECT_SOURCE_DIR}/Library/*.hpp
       ${PROJECT_SOURCE_DIR}/Library/*.inl)

  # Library dependencies: headers
  include_directories(${PROJECT_SOURCE_DIR}/Library)

  add_library(OverloadOperators "${CPPProject_SOURCES}")
  set_target_properties(OverloadOperators PROPERTIES LINKER_LANGUAGE "CXX")

endfunction(buildCPPProject)
