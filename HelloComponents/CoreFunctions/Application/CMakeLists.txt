include(convenience_functions)
include_directories(${PROJECT_SOURCE_DIR}/CoreFunctions/Library)

add_headers(Producer.hpp Consumer.hpp)
add_sources(Producer.cpp Consumer.cpp)
add_unittests(HelloComponents.test.cpp)
