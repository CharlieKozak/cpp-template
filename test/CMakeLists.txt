cmake_minimum_required(VERSION 3.5)
find_package(Catch2 3 REQUIRED)

# Add all of the source files for your tests
set(SOURCES
  "treasure_tests.cpp"
)

# This wil be the name of the main test program
set(TEST_NAME ${PROJECT_NAME}_test)
# Reference the file that hods main() for the test system
add_executable(${TEST_NAME} test_main.cpp ${SOURCES})

target_link_libraries(${TEST_NAME} PRIVATE libtreasure Catch2::Catch2WithMain)
target_compile_definitions(${TEST_NAME} PRIVATE ) # Set preprocessor definitions, like #define DEBUG 1

target_compile_options(${TEST_NAME} PRIVATE "-Wno-vla") # Disable variable length array warning, int foobar[SIZE]
target_compile_options(${TEST_NAME} PRIVATE "-Wno-unused-parameter") # The instructors required a func def with unused params.
target_compile_options(${TEST_NAME} PRIVATE "-Wall")
target_compile_options(${TEST_NAME} PRIVATE "-Wextra")
target_compile_options(${TEST_NAME} PRIVATE "-Werror")
target_compile_options(${TEST_NAME} PRIVATE "-pedantic")


enable_testing() # alternate of include(CTest)
include(Catch)
# Discover the tests described in the source files.
catch_discover_tests(${TEST_NAME})

# Add additional tests, which can use external scripts, alternate arguments, etc
add_test(NAME ExtraTest COMMAND ${TEST_NAME})

# Run the test program, with a dependency on building it.
#add_custom_target(TestOneIsOne
#        COMMAND ${CMAKE_CTEST_COMMAND} --build-target hw5_test -V --output-on-failure -R one_is_one
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#        DEPENDS ${PROJECT_NAME}
#        COMMENT "Build and test"
#        )










