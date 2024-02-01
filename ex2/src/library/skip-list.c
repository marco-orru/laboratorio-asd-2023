#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "assert_util.h"
#include "skip-list.h"

/*---------------------------------------------------------------------------------------------------------------*/

void new_skiplist(SkipList **list, size_t max_height, compare_fn compare) {
  SkipList *skiplist;

  ASSERT_NULL_PARAMETER(list, new_skiplist);
  ASSERT_NULL_PARAMETER(compare, new_skiplist);
  ASSERT(max_height >= 1, "max_height must be >= 1", new_skiplist);

  skiplist = (SkipList *) malloc(sizeof(SkipList));

  ASSERT(skiplist, "Unable to allocate memory for a SkipList", new_skiplist);

  skiplist->max_level = 0;
  skiplist->max_height = max_height;
  skiplist->compare = compare;
  skiplist->heads = (SkipListNode **) calloc(max_height, sizeof(SkipListNode *));

  ASSERT(skiplist->heads, "Unable to allocate memory for the SkipList heads array", new_skiplist);

  *list = skiplist;
}

/*---------------------------------------------------------------------------------------------------------------*/

void clear_skiplist(SkipList **list) {
  SkipList *list_ptr;
  SkipListNode *current_node, *next_node;

  ASSERT_NULL_PARAMETER(list, clear_skiplist);
  ASSERT(*list, "'list' parameter points to a NULL list", clear_skiplist);

  list_ptr = *list;

  current_node = list_ptr->heads[0];

  while (current_node) {
    next_node = current_node->next[0];
    free(current_node->item);
    free(current_node->next);
    free(current_node);
    current_node = next_node;
  }

  free(list_ptr->heads);
  free(list_ptr);

  *list = NULL;
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
static SkipListNode *create_node(void *item, size_t size) {
  SkipListNode *node;

  node = (SkipListNode *) malloc(sizeof(SkipListNode));

  ASSERT(node, "Unable to allocate memory for a SkipListNode", create_node);

  node->item = item;
  node->size = size;
  node->next = (SkipListNode **) calloc(size, sizeof(SkipListNode *));

  ASSERT(node->next, "Unable to allocate memory for the next SkipListNode array", create_node);

  return node;
}

/*---------------------------------------------------------------------------------------------------------------*/

void insert_skiplist(SkipList *list, void *item) {
  SkipListNode *new_node;
  SkipListNode **base_nodes;
  size_t i;

  ASSERT_NULL_PARAMETER(list, insert_skiplist);
  ASSERT_NULL_PARAMETER(item, insert_skiplist);

  new_node = create_node(item, random_level(list->max_height));
  if (new_node->size > list->max_level)
    list->max_level = new_node->size;

  base_nodes = list->heads;
  for (i = list->max_level - 1; (int) i >= 0; i--) {
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
  SkipListNode **base_nodes;
  size_t i;

  ASSERT_NULL_PARAMETER(list, insert_skiplist);
  ASSERT_NULL_PARAMETER(item, insert_skiplist);

  if (!list->heads[0])
    return NULL;

  base_nodes = list->heads;

  for (i = list->max_level - 1; (int) i >= 0; i--) {
    while (base_nodes[i]->next[i] && list->compare(base_nodes[i]->next[i]->item, item) <= 0)
      base_nodes = base_nodes[i]->next;
  }

  if (list->compare(base_nodes[0]->item, item) == 0)
    return base_nodes[0]->item;

  return NULL;
}
