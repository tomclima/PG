
add_executable(runTests
    Vector3.cpp
    Point3.cpp
    utils.cpp
)

target_link_libraries(runTests PRIVATE include gtest_main)

add_test(NAME UnitTests COMMAND runTests)