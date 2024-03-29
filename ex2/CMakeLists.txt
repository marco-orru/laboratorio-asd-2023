cmake_minimum_required(VERSION 3.27)
project(SkipList C)

set(CMAKE_C_STANDARD 11)

add_compile_options("-Wall" "-pedantic" "-O3" "-Wno-unknown-pragmas")

set(MAIN_OUTPUT_DIR "../bin")
set(PROFILER_OUTPUT_DIR "${MAIN_OUTPUT_DIR}/profiler")
set(UT_OUTPUT_DIR "${MAIN_OUTPUT_DIR}/ut")

set(MAIN_NAME "main_ex2")
set(PROFILER_NAME "profiler_ex2")
set(UT_NAME "ut_ex2")

set(SRC_DIR "src")
set(LIB_DIR "${SRC_DIR}/library")
set(PROFILER_DIR "${SRC_DIR}/profiler")
set(UT_DIR "${SRC_DIR}/ut")
set(UT_SUITE_DIR "${UT_DIR}/suite")  # Unity

add_executable(${MAIN_NAME}
        "${SRC_DIR}/main.c"
        "${LIB_DIR}/comparator.c"
        "${LIB_DIR}/skip-list.c"
        "${LIB_DIR}/errors-finder.c"
)

set_target_properties(${MAIN_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${MAIN_OUTPUT_DIR}
)

target_include_directories(${MAIN_NAME} PRIVATE ${LIB_DIR})

add_executable(${PROFILER_NAME}
        "${PROFILER_DIR}/profiler_main.c"
        "${LIB_DIR}/comparator.c"
        "${LIB_DIR}/skip-list.c"
        "${LIB_DIR}/errors-finder.c"
)

set_target_properties(${PROFILER_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROFILER_OUTPUT_DIR}
)

target_include_directories(${PROFILER_NAME} PRIVATE ${LIB_DIR} ${PROFILER_DIR})
target_compile_definitions(${PROFILER_NAME} PRIVATE "__PROFILER")

add_executable(${UT_NAME}
        "${UT_DIR}/ut_main.c"
        "${LIB_DIR}/comparator.c"
        "${LIB_DIR}/skip-list.c"
        "${UT_SUITE_DIR}/unity.c"
)

set_target_properties(${UT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${UT_OUTPUT_DIR}
)

target_include_directories(${UT_NAME} PRIVATE ${LIB_DIR} ${UT_SUITE_DIR})