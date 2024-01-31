#pragma once
#include <stdlib.h>
#include "comparator.h"

/**
 * @brief Represents a skip list.
 */
typedef struct SkipList {
    struct SkipListNode **heads;  ///< Array of pointers to the head node of each level up to <code>max_height</code>.
    size_t max_level;  ///< Max number of pointers currently valid in a single node.
    size_t max_height;  ///< Max number of valid pointers that a single node can contain.
    compare_fn compare;  ///< Pointer to the comparison function for ordering items.
} SkipList;

/**
 * @brief Represents a node of a skip list.
 */
typedef struct SkipListNode {
    struct SkipListNode** next;  ///< Array of pointers to the next nodes for each level up to <code>size</code>.
    size_t size;  ///< The length of the <code>next</code array (i.e. the number of referenced levels by this node).
    void* item;  ///< Pointer to the item stored into this node.
} SkipListNode;

/**
 * Allocates a new skip list with the specified maximum height and comparison function.
 * @param list Pointer to the pointer that will hold the skip list.
 * @param max_height Maximum number of levels that the skip list can support.
 * @param compare Pointer to the comparison function used for ordering items.
 */
void new_skiplist(SkipList **list, size_t max_height, compare_fn compare);

/**
 * Clears and deallocates the memory used by the skip list.
 * @param list Pointer to the skip list to be cleared.
 * @remark This function also deallocates the memory of the items stored inside the nodes, thus making them invalid
 * anywhere else.
 */
void clear_skiplist(SkipList **list);

/**
 * Inserts a new item into the skip list, maintaining the order.
 * @param list Pointer to the skip list where the item will be inserted.
 * @param item Pointer to the item to be inserted.
 * @remark Once inserted, the item is owned by the skip list. For this reason, once cleared, any other pointer which
 * refers to the item will no longer be valid.
 */
void insert_skiplist(SkipList *list, void *item);

/**
 * Searches for an item in the skip list, using the comparison function to test equality.
 * @param list Pointer to the skip list to be searched.
 * @param item Pointer to the item to be searched for.
 * @return Pointer to the found item if found, otherwise <code>NULL</code>.
 */
const void* search_skiplist(SkipList *list, void *item);
