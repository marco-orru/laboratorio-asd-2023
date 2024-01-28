cmake_minimum_required(VERSION 3.27)
project(MergeBinaryInsertionSort C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(merge-bin-insertion-sort STATIC
        library/merge-binary-insertion-sort.c)
