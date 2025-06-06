add_executable(Vector3_Tests Vector3.cpp)
target_link_libraries(Vector3_Tests PRIVATE include gtest_main)
add_test(NAME VectorTests COMMAND Vector3_Tests)