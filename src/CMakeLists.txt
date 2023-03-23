file(
        GLOB_RECURSE INCLUDE
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include/*.h
)
set(
        SOURCE
        array.cpp
        queue.cpp
        ../include/array.h)

add_library(library SHARED ${SOURCE})
target_include_directories(library PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(library PUBLIC cxx_std_20)

source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${INCLUDE}
)