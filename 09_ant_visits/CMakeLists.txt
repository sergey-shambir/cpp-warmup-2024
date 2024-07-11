
add_executable(antvisits_tests solution.h solution.cpp solution_test.cpp)
target_link_libraries(antvisits_tests PRIVATE Catch2::Catch2WithMain)
custom_enable_sanitizers(antvisits_tests)
add_test(antvisits_tests antvisits_tests)

add_executable(antvisits solution.h solution.cpp main.cpp)
custom_enable_sanitizers(antvisits)
