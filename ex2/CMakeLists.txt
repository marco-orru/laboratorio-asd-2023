cmake_minimum_required(VERSION 3.27)
project(SkipList C)

set(CMAKE_C_STANDARD 11)

add_compile_options("-Wall" "-pedantic" "-O3")

set(MAIN_OUTPUT_DIR "../bin")

set(MAIN_NAME "main_ex2")

set(SRC_DIR "src")
set(LIB_DIR "${SRC_DIR}/library")

add_executable(${MAIN_NAME}
        "${SRC_DIR}/main.c"
        "${LIB_DIR}/skip-list.c"
)

set_target_properties(${MAIN_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIR}
)

target_include_directories(${MAIN_NAME} PRIVATE ${LIB_DIR})