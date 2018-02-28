cmake_minimum_required (VERSION 3.7)
project (cpptest1)
file(GLOB SOURCES "src/*.cpp")
add_executable(rationalnumber_test ${SOURCES})

#define a macro to simplify adding tests, then use it
macro (do_test testname arg result)
  add_test (${testname} rationalnumber_test ${arg})
  set_tests_properties (${testname}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

include(CTest)
add_test(rationalnumber_test_runs rationalnumber_test 1/2 + 1/2)
#do_test (rationalnumber_test_simple_addition "1/2 + 1/2" "1/2 + 1/2 = 1/1\n")
add_test(rationalnumber_test_simple_addition rationalnumber_test 1/2 + 1/2)
set_tests_properties(rationalnumber_test_simple_addition PROPERTIES PASS_REGULAR_EXPRESSION "1/2 \\+ 1/2 = 1/1")