#include "unity.h"
#include "merge-binary-insertion-sort.h"
#include <time.h>
#include <stdlib.h>

/* FROM PROFILER */
#define BEST_INT_SORTING_THRESHOLD 50
#define BEST_FLOAT_SORTING_THRESHOLD 50
#define BEST_STRING_SORTING_THRESHOLD 50

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Gets a pointer to the element at the specified index inside the specified array.
#define GET_ELEMENT(base, index, size) ((void*)(((unsigned char*)(base)) + (index) * (size)))

// PURPOSE: Returns 1 if the array is sorted, 0 otherwise.
static int is_array_sorted(const void *arr, size_t count, size_t size, compare_fn comparator) {
  size_t i;

  for (i = 1; i < count; i++) {
    if (comparator(GET_ELEMENT(arr, i - 1, size), GET_ELEMENT(arr, i, size)) > 0)
      return 0;
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

static void int_array_test(int size) {
  int *array;
  size_t i;

  array = malloc(sizeof(int) * size);

  for (i = 0; i < size; i++)
    array[i] = rand_int();

  merge_binary_insertion_sort(array, size, sizeof(int), BEST_INT_SORTING_THRESHOLD, int_comparator);

  TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(int), int_comparator));

  free(array);
}

static void test_int_array_10(void) {
  int_array_test(10);
}

static void test_int_array_100(void) {
  int_array_test(100);
}

static void test_int_array_1000(void) {
  int_array_test(1000);
}

static void test_int_array_10000(void) {
  int_array_test(10000);
}

static void test_int_array_100000(void) {
  int_array_test(100000);
}

static void test_int_array_1000000(void) {
  int_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

static void float_array_test(int size) {
  float *array;
  size_t i;

  array = malloc(sizeof(float) * size);

  for (i = 0; i < size; i++)
    array[i] = rand_float();

  merge_binary_insertion_sort(array, size, sizeof(float), BEST_FLOAT_SORTING_THRESHOLD, float_comparator);

  TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(float), float_comparator));

  free(array);
}

static void test_float_array_10(void) {
  float_array_test(10);
}

static void test_float_array_100(void) {
  float_array_test(100);
}

static void test_float_array_1000(void) {
  float_array_test(1000);
}

static void test_float_array_10000(void) {
  float_array_test(10000);
}

static void test_float_array_100000(void) {
  float_array_test(100000);
}

static void test_float_array_1000000(void) {
  float_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemoryLeak"

static void string_array_test(int size) {
  char **array;
  size_t i;

  array = malloc(sizeof(char *) * size);

  for (i = 0; i < size; i++)
    array[i] = rand_string();

  merge_binary_insertion_sort(array, size, sizeof(char *), BEST_STRING_SORTING_THRESHOLD, dyn_string_comparator);

  TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(char *), dyn_string_comparator));

  for (i = 0; i < size; i++)
    free(array[i]);

  free(array);
}

#pragma clang diagnostic pop

static void test_string_array_10(void) {
  string_array_test(10);
}

static void test_string_array_100(void) {
  string_array_test(100);
}

static void test_string_array_1000(void) {
  string_array_test(1000);
}

static void test_string_array_10000(void) {
  string_array_test(10000);
}

static void test_string_array_100000(void) {
  string_array_test(100000);
}

static void test_string_array_1000000(void) {
  string_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

void setUp(void) {}

void tearDown(void) {}

int main(void) {
  srand(time(NULL)); // NOLINT(*-msc51-cpp)
  UNITY_BEGIN();

  printf("TESTING INTEGER ARRAYS.....\n");
  RUN_TEST(test_int_array_10);
  RUN_TEST(test_int_array_100);
  RUN_TEST(test_int_array_1000);
  RUN_TEST(test_int_array_10000);
  RUN_TEST(test_int_array_100000);
  RUN_TEST(test_int_array_1000000);

  printf("TESTING FLOAT ARRAYS.....\n");
  RUN_TEST(test_float_array_10);
  RUN_TEST(test_float_array_100);
  RUN_TEST(test_float_array_1000);
  RUN_TEST(test_float_array_10000);
  RUN_TEST(test_float_array_100000);
  RUN_TEST(test_float_array_1000000);

  printf("TESTING STRING ARRAYS.....\n");
  RUN_TEST(test_string_array_10);
  RUN_TEST(test_string_array_100);
  RUN_TEST(test_string_array_1000);
  RUN_TEST(test_string_array_10000);
  RUN_TEST(test_string_array_100000);
  RUN_TEST(test_string_array_1000000);

  return UNITY_END();
}
