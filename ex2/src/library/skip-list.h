#pragma once
#include <stdlib.h>

/**
 * @brief Function pointer type for element comparison in a SkipList.
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
typedef int (*compare_fn)(const void *, const void *);

typedef struct SkipList {
    struct SkipListNode **heads;
    size_t max_level;
    size_t max_height;
    compare_fn compare;
} SkipList;

typedef struct SkipListNode {
    struct SkipListNode** next;
    size_t size;
    void* item;
} SkipListNode;

void new_skiplist(struct SkipList **list, size_t max_height, compare_fn compare);

void clear_skiplist(struct SkipList **list);

void insert_skiplist(struct SkipList *list, void *item);

const void* search_skiplist(struct SkipList *list, void *item);
