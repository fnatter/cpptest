cmake_minimum_required (VERSION 3.7)
project (NW-cmake)
file(GLOB SOURCES "*.cpp")
add_executable(Alignment ${SOURCES})

include(CTest)
add_test(AlignmentRuns Alignment AC ABC 1 -1 -1)

