#include <string.h>
#include <ctype.h>
#include "errors-finder.h"
#include "skip-list.h"
#include "assert_util.h"

// PURPOSE: Defines the maximum word length that can be parsed from the dictionary file.
#define MAX_WORD_LENGTH 64

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Loads the dictionary file.
static void load_dictionary(FILE *dict_file, SkipList *dictionary) {
  char line_buffer[MAX_WORD_LENGTH];
  size_t word_len;
  char *word;

  while (fgets(line_buffer, MAX_WORD_LENGTH, dict_file)) {
    word_len = strlen(line_buffer);
    word = (char *) malloc(sizeof(char) * word_len);
    strncpy(word, line_buffer, word_len);
    word[word_len - 1] = '\0';
    insert_skiplist(dictionary, word);
  }
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Reads the next alphabetic word from the text file
static char *read_next_word(FILE *text_file) {
  static char word_buffer[MAX_WORD_LENGTH];
  size_t i;
  int chr;

  // Ignore leading non-alpha chars.
  while ((chr = fgetc(text_file)) != EOF && !isalpha(chr));

  if (feof(text_file))
    return NULL;

  i = 0;

  do {
    word_buffer[i++] = (char) chr;
  } while ((chr = fgetc(text_file)) != EOF && isalpha(chr));

  word_buffer[i] = '\0';
  return word_buffer;
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Print the errors found in specified file.
static void print_errors(FILE *text_file, SkipList *dictionary) {
  char *word;

  printf("Errors found:\n");
  while ((word = read_next_word(text_file))) {
    if (!search_skiplist(dictionary, word))
      printf("  - %s\n", word);
  }
}

/*---------------------------------------------------------------------------------------------------------------*/

void find_errors(FILE *dict_file, FILE *text_file, size_t max_height) {
  SkipList *dictionary;

  ASSERT_NULL_PARAMETER(dict_file, find_errors);
  ASSERT_NULL_PARAMETER(text_file, text_file);
  ASSERT(max_height >= 1, "'max_height' parameter must be >= 1", new_skiplist);

  new_skiplist(&dictionary, max_height, string_case_insensitive_comparator);

  printf("Loading dictionary...\n");
  load_dictionary(dict_file, dictionary);
  printf("Finding errors...\n");
  print_errors(text_file, dictionary);
  clear_skiplist(&dictionary);
}

/*---------------------------------------------------------------------------------------------------------------*/

#if __PROFILER
#include <time.h>

#define INIT_WORDS_CAPACITY 32

#define PROFILER_PRINT(msg) printf("[PROFILER]: " msg "\n")
#define PROFILER_PRINT_RESULT__INSERT(operation, height, start, end) \
    printf("[PROFILER]<operation=" operation ", max_height=%zu>: Completed in %f seconds.\n", (height), (double) ((end) - (start)) / CLOCKS_PER_SEC)

static char** words = NULL;
static size_t words_count = 0;
static size_t words_capacity = 0;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-suspicious-realloc-usage"
static void load_text(FILE* text_file) {
  const char* word;
  char* word_to_alloc;

  words = (char**) malloc(sizeof(char*) * INIT_WORDS_CAPACITY);
  words_count = 0;
  words_capacity = INIT_WORDS_CAPACITY;

  while ((word = read_next_word(text_file))) {
    if (words_count >= words_capacity) {
      words_capacity *= 2;
      words = (char**) realloc((void*)words, sizeof(char*) * words_capacity);
      ASSERT(words, "Unable to reallocate the words array", text_file);
    }

    word_to_alloc = (char*) malloc(sizeof(char) * strlen(word));
    ASSERT(word_to_alloc, "Unable to allocate memory for a word", load_text);

    strcpy(word_to_alloc, word);
    words[words_count++] = word_to_alloc;
  }
}
#pragma clang diagnostic pop

void init_profiler__errors_finder(FILE *text_file) {
  ASSERT_NULL_PARAMETER(text_file, init_profiler__errors_finder);

  PROFILER_PRINT("Initializing profiler...");

  PROFILER_PRINT("Initializing text...");
  load_text(text_file);

  PROFILER_PRINT("Profiler initialized.");
}

void shutdown_profiler__errors_finder(void) {
  size_t i;

  PROFILER_PRINT("Shutting down profiler...");

  PROFILER_PRINT("Deallocating text...");
  for (i = 0; i < words_count; ++i)
    free((void*)words[i]);

  free((void*)words);

  words = NULL;
  words_count = 0;
  words_capacity = 0;

  PROFILER_PRINT("Profiler shut down.");
}

static void find_errors_static(SkipList* dictionary) {
  size_t i;

  for (i = 0; i < words_count; ++i)
    search_skiplist(dictionary, words[i]);
}

void profiler__errors_finder(FILE *dict_file, size_t max_height) {
  SkipList* dictionary;
  clock_t start_insert, end_insert;
  clock_t start_search, end_search;

  new_skiplist(&dictionary, max_height, string_case_insensitive_comparator);

  start_insert = clock();
  load_dictionary(dict_file, dictionary);
  end_insert = clock();

  start_search = clock();
  find_errors_static(dictionary);
  end_search = clock();

  PROFILER_PRINT_RESULT__INSERT("INSERT", max_height, start_insert, end_insert);
  PROFILER_PRINT_RESULT__INSERT("SEARCH", max_height, start_search, end_search);

  clear_skiplist(&dictionary);
}

#endif
