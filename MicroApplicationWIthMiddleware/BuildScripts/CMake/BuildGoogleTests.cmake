# Paths for libraries are updated.
function(BuildGoogleTests)

    find_package(Threads REQUIRED)
    find_package( GTest ) 
    add_custom_target(AllGoogleTests ALL DEPENDS ${UNIT_TEST_TARGETS})
    add_subdirectory("${PROJECT_SOURCE_DIR}/GoogleTests")

endfunction(BuildGoogleTests)
