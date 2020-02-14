# Convenience function to be called from the main CMakeLists.txt
function(buildCPPProject)

  # tell CMake where to find all headers required by the sources.
  include_directories(
    ${PROJECT_SOURCE_DIR}/CoreFunctions/Interfaces # Interfaces required for
                                                   # components
  )

  file(GLOB_RECURSE CPPProject_SOURCES
       ${PROJECT_SOURCE_DIR}/CoreFunctions/Implementation/*.cpp)
  message("CPPProject_Sources: " ${CPPProject_SOURCES})

  # Library dependencies
  include_directories(${PROJECT_SOURCE_DIR}/CoreFunctions/Library
                      ${PROJECT_SOURCE_DIR}/CoreFunctions)
                      
  add_subdirectory(${PROJECT_SOURCE_DIR}/CoreFunctions/Library)

  add_library(CPPProject "${CPPProject_SOURCES}")
  target_link_libraries(CPPProject Library)
  set_target_properties(CPPProject PROPERTIES LINKER_LANGUAGE "CXX")

endfunction(buildCPPProject)
