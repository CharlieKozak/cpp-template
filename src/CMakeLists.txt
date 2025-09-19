# Main program source files and executables



##
## Add a simple executable
###

## Core library containing calculate API
set(CALC_CORE calculator_core)
add_library(${CALC_CORE} STATIC
	calculate.cpp
)
target_include_directories(${CALC_CORE}
	PUBLIC ${PROJECT_SOURCE_DIR}/include
)
target_compile_features(${CALC_CORE} PUBLIC cxx_std_17)

## Calculator executable
set(EXEC_NAME calculator)
add_executable(${EXEC_NAME} calculator.cpp)
target_link_libraries(${EXEC_NAME} PRIVATE ${CALC_CORE})

# These compile options make the compiler add extra warnings and treat warnings as errors
target_compile_options(${EXEC_NAME} PRIVATE "-Wall")
target_compile_options(${EXEC_NAME} PRIVATE "-Wextra")
target_compile_options(${EXEC_NAME} PRIVATE "-Werror")
target_compile_options(${EXEC_NAME} PRIVATE "-pedantic")
