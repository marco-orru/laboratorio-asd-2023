#include "unity.h"
#include "skip-list.h"

#define BEST_INT_MAX_HEIGHT 10  // To test

#define NUMBER_OF_ITEMS_TO_INSERT 100

/*---------------------------------------------------------------------------------------------------------------*/

static int is_skiplist_ordered(SkipList *list) {
  SkipListNode *current_node, *previous_node;

  previous_node = list->heads[0];
  if (!previous_node)
    return 1;

  current_node = list->heads[0]->next[0];
  if (!current_node)
    return 1;

  while (current_node) {
    if (list->compare(current_node->item, previous_node->item) < 0)
      return 0;

    previous_node = current_node;
    current_node = current_node->next[0];
  }

  return 1;
}

/*---------------------------------------------------------------------------------------------------------------*/

#define RANDOM_INT_MIN 0
#define RANDOM_INT_MAX 1000

// PURPOSE: Generates a random integer between RANDOM_INT_MIN e RANDOM_INT_MAX
static int rand_int(void) {
  return rand() % (RANDOM_INT_MAX - RANDOM_INT_MIN + 1) + RANDOM_INT_MIN; // NOLINT(*-msc50-cpp)
}

#define RANDOM_FLOAT_MIN 0.f
#define RANDOM_FLOAT_MAX 1000.f

static float rand_float(void) {
  return ((float) rand() / RAND_MAX) * (RANDOM_FLOAT_MAX - RANDOM_FLOAT_MIN) + RANDOM_FLOAT_MIN; // NOLINT(*-msc50-cpp)
}

#define RANDOM_STRING_MIN 5
#define RANDOM_STRING_MAX 20

#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemoryLeak"

static char *rand_string(void) {
  size_t length, i;
  char *str;

  length = rand() % (RANDOM_STRING_MAX - RANDOM_STRING_MIN + 1) + RANDOM_STRING_MIN; // NOLINT(*-msc50-cpp)
  str = malloc(sizeof(char) * length);

  for (i = 0; i < length - 1; i++) {
    str[i] = (char) (rand() % 256); // NOLINT(*-msc50-cpp)
  }

  str[i] = '\0';
  return str;
}

#pragma clang diagnostic pop

/*---------------------------------------------------------------------------------------------------------------*/

static void test_new_int_skiplist(void) {
  SkipList *skipList;

  new_skiplist(&skipList, BEST_INT_MAX_HEIGHT, int_comparator);
  TEST_ASSERT_TRUE(skipList);

  clear_skiplist(&skipList);
}


static void test_insert_int_skiplist(void) {
  SkipList *skip_list;
  size_t i;
  int *items[NUMBER_OF_ITEMS_TO_INSERT];

  new_skiplist(&skip_list, BEST_INT_MAX_HEIGHT, int_comparator);

  for (i = 0; i < NUMBER_OF_ITEMS_TO_INSERT; ++i) {
    items[i] = (int *) malloc(sizeof(int));
    *items[i] = rand_int();
    insert_skiplist(skip_list, items[i]);
  }

  TEST_ASSERT_TRUE(is_skiplist_ordered(skip_list));

  clear_skiplist(&skip_list);
}

static void test_search_int_skiplist(void) {
  SkipList *skip_list;
  size_t i;
  int value;
  int *items[NUMBER_OF_ITEMS_TO_INSERT];

  new_skiplist(&skip_list, BEST_INT_MAX_HEIGHT, int_comparator);

  value = 20;
  TEST_ASSERT_FALSE(search_skiplist(skip_list, &value));

  for (i = 0; i < NUMBER_OF_ITEMS_TO_INSERT; ++i) {
    items[i] = (int *) malloc(sizeof(int));
    *items[i] = rand_int();
    insert_skiplist(skip_list, items[i]);
  }

  for (i = 0; i < NUMBER_OF_ITEMS_TO_INSERT; ++i)
    TEST_ASSERT_TRUE(search_skiplist(skip_list, items[i]));

  clear_skiplist(&skip_list);
}

static void test_clear_int_skiplist(void) {
  SkipList *skip_list;
  size_t i;
  int *items[NUMBER_OF_ITEMS_TO_INSERT];
  new_skiplist(&skip_list, BEST_INT_MAX_HEIGHT, int_comparator);

  for (i = 0; i < NUMBER_OF_ITEMS_TO_INSERT; ++i) {
    items[i] = (int *) malloc(sizeof(int));
    *items[i] = rand_int();
    insert_skiplist(skip_list, items[i]);
  }

  clear_skiplist(&skip_list);
  TEST_ASSERT_FALSE(skip_list);
}

/*---------------------------------------------------------------------------------------------------------------*/

static void test_new_float_skiplist(void) {
  SkipList *skipList;

  new_skiplist(&skipList, BEST_INT_MAX_HEIGHT, float_comparator);
  TEST_ASSERT_TRUE(skipList);

  clear_skiplist(&skipList);
}


static void test_insert_float_skiplist(void) {
  SkipList *skip_list;
  size_t i;
  float *items[NUMBER_OF_ITEMS_TO_INSERT];

  new_skiplist(&skip_list, BEST_INT_MAX_HEIGHT, float_comparator);

  for (i = 0; i < NUMBER_OF_ITEMS_TO_INSERT; ++i) {
    items[i] = (float *) malloc(sizeof(float));
    *items[i] = rand_float();
    insert_skiplist(skip_list, items[i]);
  }

  TEST_ASSERT_TRUE(is_skiplist_ordered(skip_list));

  clear_skiplist(&skip_list);
}

static void test_search_float_skiplist(void) {
  SkipList *skip_list;
  size_t i;
  float value;
  float *items[NUMBER_OF_ITEMS_TO_INSERT];

  new_skiplist(&skip_list, BEST_INT_MAX_HEIGHT, float_comparator);

  value = 20.f;
  TEST_ASSERT_FALSE(search_skiplist(skip_list, &value));

  for (i = 0; i < NUMBER_OF_ITEMS_TO_INSERT; ++i) {
    items[i] = (float *) malloc(sizeof(float));
    *items[i] = rand_float();
    insert_skiplist(skip_list, items[i]);
  }

  for (i = 0; i < NUMBER_OF_ITEMS_TO_INSERT; ++i)
    TEST_ASSERT_TRUE(search_skiplist(skip_list, items[i]));

  clear_skiplist(&skip_list);
}

static void test_clear_float_skiplist(void) {
  SkipList *skip_list;
  size_t i;
  float *items[NUMBER_OF_ITEMS_TO_INSERT];
  new_skiplist(&skip_list, BEST_INT_MAX_HEIGHT, float_comparator);

  for (i = 0; i < NUMBER_OF_ITEMS_TO_INSERT; ++i) {
    items[i] = (float *) malloc(sizeof(float));
    *items[i] = rand_float();
    insert_skiplist(skip_list, items[i]);
  }

  clear_skiplist(&skip_list);
  TEST_ASSERT_FALSE(skip_list);
}

/*---------------------------------------------------------------------------------------------------------------*/

static void test_new_string_skiplist(void) {
  SkipList *skipList;

  new_skiplist(&skipList, BEST_INT_MAX_HEIGHT, string_comparator);
  TEST_ASSERT_TRUE(skipList);

  clear_skiplist(&skipList);
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemoryLeak"

static void test_insert_string_skiplist(void) {
  SkipList *skip_list;
  size_t i;
  char *items[NUMBER_OF_ITEMS_TO_INSERT];

  new_skiplist(&skip_list, BEST_INT_MAX_HEIGHT, string_comparator);

  for (i = 0; i < NUMBER_OF_ITEMS_TO_INSERT; ++i) {
    items[i] = rand_string();
    insert_skiplist(skip_list, items[i]);
  }

  TEST_ASSERT_TRUE(is_skiplist_ordered(skip_list));

  clear_skiplist(&skip_list);
}

static void test_search_string_skiplist(void) {
  SkipList *skip_list;
  size_t i;
  char *value;
  char *items[NUMBER_OF_ITEMS_TO_INSERT];

  new_skiplist(&skip_list, BEST_INT_MAX_HEIGHT, string_comparator);

  value = "TEST";
  TEST_ASSERT_FALSE(search_skiplist(skip_list, &value));

  for (i = 0; i < NUMBER_OF_ITEMS_TO_INSERT; ++i) {
    items[i] = rand_string();
    insert_skiplist(skip_list, items[i]);
  }

  for (i = 0; i < NUMBER_OF_ITEMS_TO_INSERT; ++i)
    TEST_ASSERT_TRUE(search_skiplist(skip_list, items[i]));

  clear_skiplist(&skip_list);
}

static void test_clear_string_skiplist(void) {
  SkipList *skip_list;
  size_t i;
  char *items[NUMBER_OF_ITEMS_TO_INSERT];
  new_skiplist(&skip_list, BEST_INT_MAX_HEIGHT, string_comparator);

  for (i = 0; i < NUMBER_OF_ITEMS_TO_INSERT; ++i) {
    items[i] = rand_string();
    insert_skiplist(skip_list, items[i]);
  }

  clear_skiplist(&skip_list);
  TEST_ASSERT_FALSE(skip_list);
}

#pragma clang diagnostic pop

/*---------------------------------------------------------------------------------------------------------------*/

void setUp(void) {}

void tearDown(void) {}

int main(void) {
  UNITY_BEGIN();

  printf("TESTING INT SKIPLIST...\n");
  RUN_TEST(test_new_int_skiplist);
  RUN_TEST(test_insert_int_skiplist);
  RUN_TEST(test_search_int_skiplist);
  RUN_TEST(test_clear_int_skiplist);

  printf("TESTING FLOAT SKIPLIST...\n");
  RUN_TEST(test_new_float_skiplist);
  RUN_TEST(test_insert_float_skiplist);
  RUN_TEST(test_search_float_skiplist);
  RUN_TEST(test_clear_float_skiplist);

  printf("TESTING STRING SKIPLIST...\n");
  RUN_TEST(test_new_string_skiplist);
  RUN_TEST(test_insert_string_skiplist);
  RUN_TEST(test_search_string_skiplist);
  RUN_TEST(test_clear_string_skiplist);

  return UNITY_END();
}
