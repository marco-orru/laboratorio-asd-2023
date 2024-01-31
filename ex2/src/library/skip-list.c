#include <assert.h>
#include "skip-list.h"

/*---------------------------------------------------------------------------------------------------------------*/

void new_skiplist(struct SkipList **list, size_t max_height, compare_fn compare) {
    SkipList* skiplist;

    assert(list);
    assert(max_height >= 1);
    assert(compare);

    skiplist = (SkipList*)malloc(sizeof(SkipList));
    skiplist->heads = NULL;
    skiplist->max_level = 0;
    skiplist->max_height = max_height;
    skiplist->compare = compare;

    *list = skiplist;
}

/*---------------------------------------------------------------------------------------------------------------*/

void clear_skiplist(struct SkipList **list) {

}

/*---------------------------------------------------------------------------------------------------------------*/

void insert_skiplist(struct SkipList *list, void *item) {

}

/*---------------------------------------------------------------------------------------------------------------*/

const void *search_skiplist(struct SkipList *list, void *item) {
    return NULL;
}
