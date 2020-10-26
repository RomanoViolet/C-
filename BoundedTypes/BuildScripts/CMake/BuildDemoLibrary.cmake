# Convenience function to be called from the main CMakeLists.txt
function(buildCPPProject)

  # tell CMake where to find all headers required by the sources.

  file(GLOB_RECURSE Library_SOURCES ${PROJECT_SOURCE_DIR}/Library/*.hpp
       ${PROJECT_SOURCE_DIR}/Library/*.inl)

  # Library dependencies: headers
  include_directories(${PROJECT_SOURCE_DIR}/Library)

  add_library(BoundedTypes "${Library_SOURCES}")
  set_target_properties(BoundedTypes PROPERTIES LINKER_LANGUAGE "CXX")

endfunction(buildCPPProject)
