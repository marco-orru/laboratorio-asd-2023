cmake_minimum_required(VERSION 3.27)
project(MergeBinaryInsertionSort C)

set(CMAKE_C_STANDARD 11)

add_compile_options("-Wall" "-pedantic" "-O3")

set(MAIN_OUTPUT_DIR "../bin")
set(UT_OUTPUT_DIR "${MAIN_OUTPUT_DIR}/ut")

set(MAIN_NAME "main_ex1")
set(PROFILER_NAME "profiler_ex1")
set(UT_NAME "ut_ex1")

set(SRC_DIR "src")
set(LIB_DIR "${SRC_DIR}/library")
set(UT_DIR "${SRC_DIR}/ut")
set(UT_SUITE_DIR "${UT_DIR}/suite")  # Unity

add_executable(${MAIN_NAME}
        "${SRC_DIR}/main.c"
        "${LIB_DIR}/merge-binary-insertion-sort.c"
        "${LIB_DIR}/records-sorter.c"
)

set_target_properties(${MAIN_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIR}
)

target_include_directories(${MAIN_NAME} PRIVATE ${LIB_DIR})

add_executable(${PROFILER_NAME}
        "${SRC_DIR}/main.c"
        "${LIB_DIR}/merge-binary-insertion-sort.c"
        "${LIB_DIR}/records-sorter.c"
)

set_target_properties(${PROFILER_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIR}
)

target_include_directories(${PROFILER_NAME} PRIVATE ${LIB_DIR})

target_compile_definitions(${PROFILER_NAME} PRIVATE ENABLE_PROFILER=1)

add_executable(${UT_NAME}
        "${UT_DIR}/ut_main.c"
        "${LIB_DIR}/merge-binary-insertion-sort.c"
        "${UT_SUITE_DIR}/unity.c"
)

set_target_properties(${UT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${UT_OUTPUT_DIR}
)

target_include_directories(${UT_NAME} PRIVATE ${LIB_DIR} ${UT_SUITE_DIR})