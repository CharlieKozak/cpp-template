## Configure a library

set(LIB_NAME treasure)

add_library(${LIB_NAME} STATIC
        treasure.cpp
)

target_include_directories(${LIB_NAME}
        PUBLIC
                ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${LIB_NAME} PRIVATE "-Wall" "-Wextra" "-pedantic")
        # These were previously required by assignments; avoid unless necessary
        target_compile_options(${LIB_NAME} PRIVATE "-Wno-vla" "-Wno-unused-parameter")
endif()
