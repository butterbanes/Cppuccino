find_package(GTest REQUIRED)

add_executable(Cppuccino_unit_tests
    Integer/Integer_unit_tests.cpp
)

target_link_libraries(Cppuccino_unit_tests
    PRIVATE
        Cppuccino::Cppuccino
        GTest::gtest_main
)

add_test(NAME Cppuccino_tests COMMAND Cppuccino_unit_tests)