#pragma once
#include <stddef.h>

/**
 * @brief Function pointer type for element comparison in sorting algorithms.
 *
 * @remark A comparison function of this type should take two pointers to elements
 * and return an integer value indicating their relative order:
 * <ul>
 *      <li>A negative value if the first element is less than the second.</li>
 *      <li>Zero if the elements are equal</li>
 *      <li>A positive value if the first element is greater than the second</li>
 * </ul>
 *
 * @param a Pointer to the first element for comparison.
 * @param b Pointer to the second element for comparison.
 * @return An integer representing the comparison result.
 */
typedef int (*compare_fn)(const void*, const void*);

/**
 * @brief Perform a hybrid sorting algorithm that combines binary insertion sort and merge sort over an array of
 * generic items.
 *
 * @remark This function recursively applies merge sort until the array size falls below a specified threshold,
 * at which point it switches to binary insertion sort for smaller partitions.
 *
 * @param base      Pointer to the beginning of the array to be sorted.
 * @param count     Number of elements in the array.
 * @param size      Size of each element in the array, in bytes.
 * @param threshold The threshold at which the algorithm switches from merge sort to binary insertion sort.
 * @param compare   Pointer to the comparison function that defines the order of elements.
 *
 * @note This operation has linearithmic time complexity O(N log N).
 */
void merge_binary_insertion_sort(void *base, size_t count, size_t size, size_t threshold, compare_fn compare);
