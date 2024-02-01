#include <stdlib.h>
#include <string.h>
#include "records-sorter.h"
#include "assert_util.h"

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Defines constants for indexing argv.
enum Args {
  ARG_IN_FILE_PATH = 1,
  ARG_OUT_FILE_PATH,
  ARG_SORTING_THRESHOLD,
  ARG_SORTING_FIELD,
  ARG_NUM_ARGS
};

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Performs the processing of the input file, reading and sorting the specified field, and saving the result
//          in the specified file.
static int process_file(const char *in_path, const char *out_path, size_t sorting_threshold, FieldId field_id) {
  FILE *in_file;
  FILE *out_file;

  in_file = fopen(in_path, "r");
  ASSERT(in_file, "Unable to open the input file", process_file);

  out_file = fopen(out_path, "w");
  ASSERT(out_file, "Unable to open the output file", process_file);

  sort_records(in_file, out_file, sorting_threshold, field_id);

  ASSERT(!fclose(out_file), "Unable to close the output file", process_file);
  ASSERT(!fclose(in_file), "Unable to close the input file", process_file);

  return EXIT_SUCCESS;
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Tests the string representation of the field type.
#define TEST_STR_FIELD_ID(value, str) (!strcmp("FIELD_" value, str) || !strcmp(value, str))

// PURPOSE: Entry point.
int main(int argc, char *argv[]) {
  const char *in_file_path;
  const char *out_file_path;
  size_t sorting_threshold;
  FieldId sorting_field_id;
  char sorting_field_id_str[16];

  ASSERT(argc >= ARG_OUT_FILE_PATH, "Wrong number of arguments passed (input file path not found)", main);
  ASSERT(argc >= ARG_SORTING_THRESHOLD, "Wrong number of arguments passed (output file path not found)", main);
  ASSERT(argc >= ARG_SORTING_FIELD, "Wrong number of arguments passed (sorting threshold not found)", main);
  ASSERT(argc >= ARG_NUM_ARGS, "Wrong number of arguments passed (field id not found)", main);

  in_file_path = argv[ARG_IN_FILE_PATH];
  out_file_path = argv[ARG_OUT_FILE_PATH];

  ASSERT(strcmp(in_file_path, out_file_path), "The two specified file paths refers to the same file.\n", main);
  ASSERT(sscanf(argv[ARG_SORTING_THRESHOLD], "%zu", &sorting_threshold) == 1, "The sorting threshold has not been specified correctly.", main); // NOLINT(*-err34-c)

  if (sscanf(argv[ARG_SORTING_FIELD], "%d", (int *) &sorting_field_id) != 1) { // NOLINT(*-err34-c)
    if (sscanf(argv[ARG_SORTING_FIELD], "%s", sorting_field_id_str) == 1) {
      if (TEST_STR_FIELD_ID("STRING", sorting_field_id_str)) sorting_field_id = FIELD_STRING;
      else if (TEST_STR_FIELD_ID("INTEGER", sorting_field_id_str)) sorting_field_id = FIELD_INTEGER;
      else if (TEST_STR_FIELD_ID("FLOAT", sorting_field_id_str)) sorting_field_id = FIELD_FLOAT;
      else goto ERROR;
    } else {
      ERROR:
      fprintf(stderr, "RUNTIME_ERROR(main): The field id to sort has not been specified correctly.\n");
      abort();
    }
  }

  process_file(in_file_path, out_file_path, sorting_threshold, sorting_field_id);

  return EXIT_SUCCESS;
}
