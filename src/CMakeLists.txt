set(
        INCLUDE
        "${CMAKE_SOURCE_DIR}/include/queue.h"
)
set(
        SOURCE
        queue.cpp
)

add_library(library SHARED ${SOURCE})
target_include_directories(library PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(library PUBLIC cxx_std_20)

source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${INCLUDE}
)