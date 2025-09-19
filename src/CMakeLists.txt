# Main program source files and executables



##
## Add a simple executable
###

## Hello World executable
set(EXEC_NAME calculator)
add_executable(${EXEC_NAME} calculator.cpp)

# These compile options make the compiler add extra warnings and treat warnings as errors
target_compile_options(${EXEC_NAME} PRIVATE "-Wall")
target_compile_options(${EXEC_NAME} PRIVATE "-Wextra")
target_compile_options(${EXEC_NAME} PRIVATE "-Werror")
target_compile_options(${EXEC_NAME} PRIVATE "-pedantic")
