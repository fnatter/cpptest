cmake_minimum_required (VERSION 3.7)
project (cpptest1)
file(GLOB SOURCES "src/*.cpp")
add_executable(rationalnumber_test ${SOURCES})

include(CTest)
add_test(rationalnumber_test_runs rationalnumber_test 1/2 + 1/2)

