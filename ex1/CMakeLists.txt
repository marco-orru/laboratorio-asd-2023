cmake_minimum_required(VERSION 3.27)
project(MergeBinaryInsertionSort C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(LIB_NAME "merge-bin-insertion-sort")
set(EXC_NAME "main_ex1")

add_library(${LIB_NAME} STATIC
        src/library/merge-binary-insertion-sort.c
)

add_executable(${EXC_NAME}
        src/main.c
)