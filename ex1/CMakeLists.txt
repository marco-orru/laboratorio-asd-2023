cmake_minimum_required(VERSION 3.27)
project(MergeBinaryInsertionSort C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(EXC_NAME "main_ex1")
set(UNIT_NAME "tests_ex1")

set(OUTPUT_DIR "../bin")
set(LIB_DIR "src/library")
set(UNIT_LIB_DIR "src/tests/lib")
file(COPY resources DESTINATION ${OUTPUT_DIR})

add_compile_options("-pedantic" "-Wall" "-O3" "-DENABLE_PROFILER=0")

add_executable(${EXC_NAME}
        src/library/merge-binary-insertion-sort.c
        src/library/records-sorter.c
        src/main.c
)

add_executable(${UNIT_NAME}
        src/library/merge-binary-insertion-sort.c
        src/tests/lib/unity.c
        src/tests/tests_main.c
)

target_include_directories(${EXC_NAME} PRIVATE ${LIB_DIR})
target_include_directories(${UNIT_NAME} PRIVATE ${UNIT_LIB_DIR} ${LIB_DIR})

set_target_properties(${EXC_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

set_target_properties(${UNIT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/unit_test
)

