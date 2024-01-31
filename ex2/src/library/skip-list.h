#pragma once
#include <stdlib.h>
#include "comparator.h"

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

void new_skiplist(SkipList **list, size_t max_height, compare_fn compare);

void clear_skiplist(SkipList **list);

void insert_skiplist(SkipList *list, void *item);

const void* search_skiplist(SkipList *list, void *item);

