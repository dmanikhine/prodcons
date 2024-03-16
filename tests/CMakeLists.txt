# setup test dependencies

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(MyUnitTests  myunittests.cpp)

target_link_libraries(MyUnitTests GTest::gtest_main)

add_test(MyUnitTestCmake MyUnitTests)
