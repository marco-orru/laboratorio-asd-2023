#pragma once
#include <stddef.h>

typedef int (*compare_fn)(const void*, const void*);

void merge_binary_insertion_sort(void *base, size_t count, size_t size, size_t threshold, compare_fn compare);
