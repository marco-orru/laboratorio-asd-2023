#include <memory.h>
#include <malloc.h>
#include <mem.h>
#include "merge-binary-insertion-sort.h"

//---------------------------------------------------------------------------------------------\\

// PURPOSE: Gets a pointer to the element at the specified index inside the specified array.
#define GET_ELEMENT(base, index, size) ((void*)(((unsigned char*)(base)) + (index) * (size)))

//---------------------------------------------------------------------------------------------\\

// PURPOSE: Perform binary search on a sorted array to find the correct position for an element.
// NOTE: The sorted array is the sub-array with [0, upper - 1] bounds of the base array, which has [0, size - 1] bounds.
static size_t binary_search(void* base, size_t size, void* elem, size_t upper, compare_fn compare) {
    size_t half, lower;
    void *half_elem;
    int cmp_res;

    lower = 0;

    while (lower < upper) {
        half = (lower + upper) / 2;
        half_elem = GET_ELEMENT(base, half, size);

        cmp_res = compare(elem, half_elem);

        if (cmp_res == 0)
            return half + 1;

        if (cmp_res > 0) lower = half + 1;
        else upper = half;
    }

    return compare(elem, GET_ELEMENT(base, lower, size)) > 0
        ? lower + 1
        : lower;
}

//---------------------------------------------------------------------------------------------\\

// PURPOSE: Shifts to the right by one position the items in range [insert_ids, from_idx - 1].
static void* shift_right(void *base, size_t size, size_t insert_idx, size_t from_idx) {
    void *pivot, *pivot_dest;
    size_t shift_sz;

    pivot = GET_ELEMENT(base, insert_idx, size);
    pivot_dest = GET_ELEMENT(base, insert_idx + 1, size);

    shift_sz = (from_idx - insert_idx) * size;
    memmove(pivot_dest, pivot, shift_sz);

    return pivot;
}

//---------------------------------------------------------------------------------------------\\

// PURPOSE: Sorts the given array using the binary insertion sort algorithm, using the specified compare function to
//          compare elements.
static void binary_insertion_sort(void* base, size_t count, size_t size, compare_fn compare) {
    size_t i, new_pos;
    void* current_elem, *src_elem, *dst_elem;

    src_elem = malloc(size);

    for (i = 1; i < count; ++i) {
        current_elem = GET_ELEMENT(base, i, size);
        new_pos = binary_search(base, size, current_elem, i - 1, compare);

        memcpy(src_elem, current_elem, size);
        dst_elem = shift_right(base, size, new_pos, i);
        memcpy(dst_elem, src_elem, size);
    }

    free(src_elem);
}

//---------------------------------------------------------------------------------------------\\

void merge_binary_insertion_sort(void *base, size_t count, size_t size, size_t threshold, compare_fn compare) {
    binary_insertion_sort(base, count, size, compare);
    // TODO...
}
