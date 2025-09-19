include(FetchContent)
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.6.0
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

set(TEST_NAME tests)
add_executable(${TEST_NAME}
	calculator_tests.cpp
)
target_link_libraries(${TEST_NAME} PRIVATE calculator_core Catch2::Catch2WithMain)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(${TEST_NAME} PRIVATE -Wall -Wextra -pedantic)
	target_compile_options(${TEST_NAME} PRIVATE -Wno-vla -Wno-unused-parameter)
endif()
list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(${TEST_NAME})







