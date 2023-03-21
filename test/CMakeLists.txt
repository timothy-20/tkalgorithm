FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests queue_test.cpp)
target_compile_features(tests PRIVATE cxx_std_20)
target_link_libraries(tests PRIVATE library GTest::gtest_main)

add_test(
        NAME tests_library
        COMMAND tests
)