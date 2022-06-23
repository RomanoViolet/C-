include(convenience_functions)
include_directories(${PROJECT_SOURCE_DIR}/CoreFunctions)
include_directories(${PROJECT_SOURCE_DIR}/CoreFunctions/Library)
add_headers(${PROJECT_SOURCE_DIR}/CoreFunctions/Application/Consumer.hpp
            ${PROJECT_SOURCE_DIR}/CoreFunctions/Application/Producer.hpp)
add_sources(${PROJECT_SOURCE_DIR}/CoreFunctions/Application/Consumer.cpp
            ${PROJECT_SOURCE_DIR}/CoreFunctions/Application/Producer.cpp)

create_executable(main.cpp)
