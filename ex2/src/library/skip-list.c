#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "skip-list.h"

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Prints an error message and aborts the program
#define PRINT_ERROR(msg)    \
do {                        \
    fprintf(stderr, msg);   \
    fflush(stderr);         \
    abort();                \
} while(0)

// PURPOSE: Verifies that an unsafe function returns non-zero, or aborts if it returns zero.
#define VERIFY(cmd)                                                 \
do {                                                                \
    if (!(cmd))                                                     \
        PRINT_ERROR("[VERIFY_ERROR]: (" #cmd ") == FALSE");         \
} while (0)

/*---------------------------------------------------------------------------------------------------------------*/

void new_skiplist(SkipList **list, size_t max_height, compare_fn compare) {
    SkipList* skiplist;

    assert(list);
    assert(max_height >= 1);
    assert(compare);

    skiplist = (SkipList*)malloc(sizeof(SkipList));
    skiplist->max_level = 0;
    skiplist->max_height = max_height;
    skiplist->compare = compare;
    skiplist->heads = (SkipListNode**) calloc(max_height, sizeof(SkipListNode*));

    VERIFY(skiplist->heads);

    *list = skiplist;
}

/*---------------------------------------------------------------------------------------------------------------*/

void clear_skiplist(SkipList **list) {
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Returns a number between 0 and 1,
static int random(void) {
    static int random_initialized = 0;

    if (!random_initialized) {
        srand(time(NULL)); // NOLINT(*-msc51-cpp)
        random_initialized = 1;
    }

    return rand() % 2; // NOLINT(*-msc50-cpp)
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Generates a random level value in the range [1, max_height].
static size_t random_level(size_t max_height) {
    size_t level;

    level = 1;

    while (random() && level < max_height)
        level++;

    return level;
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Allocates and initializes a node of the specific size with the specific item
static SkipListNode* create_node(void* item, size_t size) {
    SkipListNode *node;

    node = (SkipListNode*) malloc(sizeof(SkipListNode));

    VERIFY(node);

    node->item = item;
    node->size = size;
    node->next = (SkipListNode**) calloc(size, sizeof(SkipListNode*));

    VERIFY(node->next);

    return node;
}

/*---------------------------------------------------------------------------------------------------------------*/

void insert_skiplist(SkipList *list, void *item) {
    SkipListNode* new_node;
    SkipListNode** base_nodes;
    size_t i;

    assert(list);
    assert(item);

    new_node = create_node(item, random_level(list->max_height));
    if (new_node->size > list->max_level)
        list->max_level = new_node->size;

    base_nodes = list->heads;
    for (i = list->max_level - 1; (int)i >= 0; i--) {
        if (!base_nodes[i] || list->compare(item, base_nodes[i]->item) < 0) {
            if (i < new_node->size) {
                new_node->next[i] = base_nodes[i];
                base_nodes[i] = new_node;
            }
        } else {
            base_nodes = base_nodes[i]->next;
            i++;
        }
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

const void *search_skiplist(SkipList *list, void *item) {
    SkipListNode** base_nodes;
    size_t i;

    base_nodes = list->heads;

    for (i = list->max_level - 1; (int)i >= 0; i--) {
        while (base_nodes[i]->next[i] && list->compare(base_nodes[i]->next[i]->item, item) <= 0)
            base_nodes = base_nodes[i]->next;
    }

    if (list->compare(base_nodes[0]->item, item) == 0)
        return base_nodes[0]->item;

    return NULL;
}

#if 0
/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Prints a node.
static void print_int_skiplist_node(SkipListNode** node, size_t size, size_t max_level)
{
    size_t i;
    int number;

    number = *(int*)node[0]->item;

    printf("%d\t", number);
    for (i = 1; i < size; i++)
        printf("%d\t", number);
    for (; i < max_level; i++)
        printf("|\t");
    printf("\n");

    for (i = 0; i < max_level; i++)
        printf("|\t");
    printf("\n");

    if (node[0]->next[0])
        print_int_skiplist_node(node[0]->next, node[0]->next[0]->size, max_level);
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE
static void print_int_skiplist(SkipList* list) {
    size_t i;

    for (i = 0; i < list->max_level; i++)
        printf("*\t");
    for (; i < list->max_height; i++)
        printf("x\t");
    printf("\n");

    for (i = 0; i < list->max_level ; i++)
        printf("|\t");
    printf("\n");

    print_int_skiplist_node(list->heads, list->heads[0]->size, list->max_level);

    for (i = 0; i < list->max_level ; i++)
        printf("NIL\t");
    printf("\n");
}
#endif
