#include "assert_util.h"
#include "errors-finder.h"

#define PROFILER_PRINT(msg) printf("[PROFILER]: " msg "\n")

/*---------------------------------------------------------------------------------------------------------------*/

enum Args {
  ARG_DICT_FILE_PATH = 1,
  ARG_CORRECTME_FILE_PATH,
  ARG_FIRST_MAX_HEIGHT,
  ARG_MIN_NUM_ARGS
};

/*---------------------------------------------------------------------------------------------------------------*/

static void profile_execution(const char* dict_file_path, const char* correctme_file_path, size_t* max_heights, size_t max_heights_count) {
  FILE* dict_file, *correctme_file;
  size_t i;

  dict_file = fopen(dict_file_path, "r");
  ASSERT(dict_file, "Unable to open the dictionary file", process_file);

  correctme_file = fopen(correctme_file_path, "r");
  ASSERT(correctme_file, "Unable to open the correctme file", process_file);

  init_profiler__errors_finder(correctme_file);

  ASSERT(!fclose(correctme_file), "Unable to close the correctme file", process_file);

  PROFILER_PRINT("Processing...");
  for (i = 0; i < max_heights_count; ++i) {
    profiler__errors_finder(dict_file, max_heights[i]);
    rewind(dict_file);
  }

  ASSERT(!fclose(dict_file), "Unable to close the dictionary file", correctme_file);

  shutdown_profiler__errors_finder();
}

/*---------------------------------------------------------------------------------------------------------------*/

int main(int argc, char* argv[]) {
  const char* dict_file_path;
  const char* correctme_file_path;
  size_t* max_heights, max_heights_count;
  size_t i;

  ASSERT(argc >= ARG_CORRECTME_FILE_PATH, "Wrong number of arguments passed (dictionary file path not found)", main);
  ASSERT(argc >= ARG_FIRST_MAX_HEIGHT, "Wrong number of arguments passed (correctme file path not found)", main);
  ASSERT(argc >= ARG_MIN_NUM_ARGS, "Wrong number of arguments passed (max height list not found)", main);

  dict_file_path = argv[ARG_DICT_FILE_PATH];
  correctme_file_path = argv[ARG_CORRECTME_FILE_PATH];

  max_heights_count = (argc - ARG_FIRST_MAX_HEIGHT);
  max_heights = (size_t *) malloc(sizeof(size_t) * max_heights_count);
  ASSERT(max_heights, "Unable to allocate memory for max height list", main);

  for (i = ARG_FIRST_MAX_HEIGHT; i < ARG_FIRST_MAX_HEIGHT + max_heights_count; i++) {
    ASSERT(sscanf(argv[i], "%zu", &max_heights[i - ARG_FIRST_MAX_HEIGHT]), "Unable to parse a sorting threshold", main); // NOLINT(*-err34-c)
    ASSERT(max_heights[i] >= 0, "A sorting threshold must be greater than or equal to 0", main);
  }

  profile_execution(dict_file_path, correctme_file_path, max_heights, max_heights_count);

  free((void*)max_heights);

  return EXIT_SUCCESS;
}
