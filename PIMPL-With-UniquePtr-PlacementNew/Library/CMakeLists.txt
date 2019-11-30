file(GLOB SRC ${CURRENT_LIST_DIR} *.cpp)

message("Library Sources: ${SRC}")

add_library(MyLibrary "${SRC}")

