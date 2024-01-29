cmake_minimum_required(VERSION 3.27)
project(MergeBinaryInsertionSort C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(EXC_NAME "main_ex1")

set(OUTPUT_DIR "../bin")
set(LIB_DIR "src/library")
file(COPY resources DESTINATION ${OUTPUT_DIR})

add_compile_options("-pedantic" "-Wall" "-O3")

add_executable(${EXC_NAME}
        src/library/merge-binary-insertion-sort.c
        src/library/records-sorter.c
        src/main.c
)

target_include_directories(${EXC_NAME} PRIVATE ${LIB_DIR})

set_target_properties(${EXC_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_compile_definitions(${EXC_NAME} PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
)