#include <stdlib.h>
#include "assert_util.h"
#include "errors-finder.h"

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Defines constants for indexing argv.
enum Args {
  ARG_DICT_FILE_PATH = 1,
  ARG_CORRECTME_FILE_PATH,
  ARG_MAX_HEIGHT,
  ARG_NUM_ARGS
};

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Find errors in the correctme file using the specified dictionary
static void process_file(const char* dict_file_path, const char* correctme_file_path, size_t max_height) {
  FILE* dict_file, *correctme_file;

  dict_file = fopen(dict_file_path, "r");
  ASSERT(dict_file, "Unable to open the dictionary file", process_file);

  correctme_file = fopen(correctme_file_path, "r");
  ASSERT(correctme_file, "Unable to open the correctme file", process_file);

  find_errors(dict_file, correctme_file, max_height);

  ASSERT(!fclose(correctme_file), "Unable to close the correctme file", process_file);
  ASSERT(!fclose(dict_file), "Unable to close the dictionary file", process_file);
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Entry point
int main(int argc, char* argv[]) {
  const char* dict_file_path;
  const char* correctme_file_path;
  size_t max_height;

  ASSERT(argc >= ARG_CORRECTME_FILE_PATH, "Wrong number of arguments passed (dictionary file path not found)", main);
  ASSERT(argc >= ARG_MAX_HEIGHT, "Wrong number of arguments passed (correctme file path not found)", main);
  ASSERT(argc >= ARG_NUM_ARGS, "Wrong number of arguments passed (max height not found)", main);

  dict_file_path = argv[ARG_DICT_FILE_PATH];
  correctme_file_path = argv[ARG_CORRECTME_FILE_PATH];

  ASSERT(sscanf(argv[ARG_MAX_HEIGHT], "%zu", &max_height) == 1, "The max height has not been specified correctly", main); // NOLINT(*-err34-c)

  process_file(dict_file_path, correctme_file_path, max_height);

  return EXIT_SUCCESS;
}
