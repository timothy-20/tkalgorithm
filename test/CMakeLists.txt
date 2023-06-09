FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
)

set(GTEST_FORCE_SHARED_CRT ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
        tests
        singly_linked_list_test.cpp
        doubly_linked_list_test.cpp
        dynamic_array_test.cpp
        skip_list_test.cpp
        queue_test.cpp
        utility_test.cpp
        binary_search_tree_test.cpp
        xor_linked_list_test.cpp
        sort_test.cpp
)
target_compile_features(tests PRIVATE cxx_std_20)
target_link_libraries(tests PRIVATE library GTest::gtest_main)

add_test(
        NAME tests_library
        COMMAND tests
)