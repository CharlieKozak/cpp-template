include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.6.0
)
FetchContent_MakeAvailable(Catch2)

# Add all of the source files for your tests
set(SOURCES
  fibonacci_tests.cpp
)

set(TEST_NAME ${PROJECT_NAME}_test)
add_executable(${TEST_NAME} ${SOURCES})

target_link_libraries(${TEST_NAME} PRIVATE fibonacci Catch2::Catch2WithMain)
target_compile_definitions(${TEST_NAME} PRIVATE )

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(${TEST_NAME} PRIVATE -Wall -Wextra -pedantic)
  target_compile_options(${TEST_NAME} PRIVATE -Wno-vla -Wno-unused-parameter)
endif()

enable_testing()
list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(${TEST_NAME})

# Run the test program, with a dependency on building it.
#add_custom_target(TestOneIsOne
#        COMMAND ${CMAKE_CTEST_COMMAND} --build-target hw5_test -V --output-on-failure -R one_is_one
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#        DEPENDS ${PROJECT_NAME}
#        COMMENT "Build and test"
#        )










