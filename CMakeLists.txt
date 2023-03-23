cmake_minimum_required(VERSION 3.14...3.26)
project(
        tkalgorithm
        VERSION 1.0.0
        DESCRIPTION "library project"
        LANGUAGES CXX
)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    include(CTest)
    enable_testing()

    find_package(Doxygen)

    if (DOXYGEN_FOUND)
        message(STATUS "Doxygen version@${DOXYGEN_VERSION}")
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs.")
    endif()
endif()

include(FetchContent)

FetchContent_Declare(
        fmtlib
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 9.1.0
)
FetchContent_MakeAvailable(fmtlib)

add_subdirectory(src)
add_subdirectory(app)

if ((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(test)
else()
    message(STATUS "Fail to add subdirectory 'test'")
endif()

set(CMAKE_CXX_STANDARD 20)