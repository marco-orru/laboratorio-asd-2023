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
      printf("\t%s\n", word);
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
