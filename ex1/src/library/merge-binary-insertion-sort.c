#include <memory.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "merge-binary-insertion-sort.h"
#include "assert_util.h"

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Gets a pointer to the element at the specified index inside the specified array.
#define GET_ELEMENT(base, index, size) ((void*)(((unsigned char*)(base)) + (index) * (size)))

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Perform binary search on a sorted array to find the correct position for an element.
// NOTE: The sorted array is the sub-array with [0, upper - 1] bounds of the base array, which has [0, size - 1] bounds.
static size_t binary_search(void *base, size_t size, void *elem, size_t upper, compare_fn compare) {
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

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Shifts to the right by one position the items in range [insert_ids, from_idx - 1].
static void *shift_right(void *base, size_t size, size_t insert_idx, size_t from_idx) {
  void *pivot, *pivot_dest;
  size_t shift_sz;

  pivot = GET_ELEMENT(base, insert_idx, size);
  pivot_dest = GET_ELEMENT(base, insert_idx + 1, size);

  shift_sz = (from_idx - insert_idx) * size;
  ASSERT(memcpy(pivot_dest, pivot, shift_sz), "Unable to shift memory", shift_right);

  return pivot;
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Sorts the given array using the binary insertion sort algorithm, using the specified compare function to
//          compare elements.
static void binary_insertion_sort(void *base, size_t count, size_t size, compare_fn compare) {
  size_t i, new_pos;
  void *current_elem, *src_elem, *dst_elem;

  src_elem = malloc(size);

  ASSERT(src_elem, "Unable to allocate memory for the inserted element", binary_insertion_sort);

  for (i = 1; i < count; ++i) {
    current_elem = GET_ELEMENT(base, i, size);
    new_pos = binary_search(base, size, current_elem, i - 1, compare);

    ASSERT(memcpy(src_elem, current_elem, size), "Unable to save a copy of the current element", binary_insertion_sort);
    dst_elem = shift_right(base, size, new_pos, i);
    ASSERT(memcpy(dst_elem, src_elem, size), "Unable to copy the inserted element into its destination", binary_insertion_sort);
  }

  free(src_elem);
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Merges two sorted arrays into one.
static void merge(void *l_base, size_t l_count, void *r_base, size_t r_count, size_t size, compare_fn compare) {
  void *res, *src;
  size_t res_size, l_idx, r_idx, res_idx;

  res_size = (l_count + r_count) * size;
  res = malloc(res_size);

  ASSERT(res, "Unable to allocate memory for the merging array", merge);

  l_idx = r_idx = res_idx = 0;

  while (l_idx < l_count && r_idx < r_count) {
    if (compare(GET_ELEMENT(l_base, l_idx, size), GET_ELEMENT(r_base, r_idx, size)) <= 0) {
      src = GET_ELEMENT(l_base, l_idx++, size);
    } else {
      src = GET_ELEMENT(r_base, r_idx++, size);
    }

    ASSERT(memcpy(GET_ELEMENT(res, res_idx++, size), src, size), "Unable to copy an element to the merging array", merge);
  }

  if (l_idx < l_count)
    ASSERT(memcpy(GET_ELEMENT(res, res_idx, size), GET_ELEMENT(l_base, l_idx, size), size * (l_count - l_idx)), "Unable to copy an element to the merging array", merge);

  if (r_idx < r_count)
    ASSERT(memcpy(GET_ELEMENT(res, res_idx, size), GET_ELEMENT(r_base, r_idx, size), size * (r_count - r_idx)), "Unable to copy an element to the merging array", merge);

  ASSERT(memcpy(l_base, res, res_size), "Unable to copy the merge array to the destination", merge);

  free(res);
}

/*---------------------------------------------------------------------------------------------------------------*/

void merge_binary_insertion_sort(void *base, size_t count, size_t size, size_t threshold, compare_fn compare) { // NOLINT(*-no-recursion)
  size_t half;
  void *half_base;

  ASSERT_NULL_PARAMETER(base, merge_binary_insertion_sort);
  ASSERT_NULL_PARAMETER(compare, merge_binary_insertion_sort);
  ASSERT(count > 0, "The array must contain at least one element", merge_binary_insertion_sort);
  ASSERT(size > 0, "The element size cannot be zero", merge_binary_insertion_sort);

  if (count == 1)
    return;

  if (count <= threshold) {
    binary_insertion_sort(base, count, size, compare);
    return;
  }

  half = count / 2;
  half_base = GET_ELEMENT(base, half, size);

  merge_binary_insertion_sort(base, half, size, threshold, compare);
  merge_binary_insertion_sort(half_base, count - half, size, threshold, compare);

  merge(base, half, half_base, count - half, size, compare);
}

