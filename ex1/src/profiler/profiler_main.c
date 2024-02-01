#include "assert_util.h"
#include "records-sorter.h"

#define PROFILER_PRINT(msg) printf("[PROFILER]: " msg "\n")

enum Args {
  ARG_INPUT_FILE_PATH = 1,
  ARG_FIRST_THRESHOLD,
  ARG_MIN_NUM_ARGS
};

/*---------------------------------------------------------------------------------------------------------------*/

static void profile_execution(const char *input_file_path, size_t *thresholds, size_t threshold_count) {
  FILE *input_file;
  size_t i;

  input_file = fopen(input_file_path, "r");
  ASSERT(input_file, "Unable to open the input file", profile_execution);

  init_profiler__records_sorter(input_file);

  ASSERT(!fclose(input_file), "Unable to close the input file", profile_execution);

  PROFILER_PRINT("Processing STRING fields...");
  for (i = 0; i < threshold_count; ++i)
    profile__records_sorter(thresholds[i], FIELD_STRING);

  PROFILER_PRINT("Processing INTEGER fields...");
  for (i = 0; i < threshold_count; ++i)
    profile__records_sorter(thresholds[i], FIELD_INTEGER);

  PROFILER_PRINT("Processing FLOAT fields...");
  for (i = 0; i < threshold_count; ++i)
    profile__records_sorter(thresholds[i], FIELD_FLOAT);

  shutdown_profiler__records_sorter();
}

/*---------------------------------------------------------------------------------------------------------------*/

int main(int argc, char *argv[]) {
  const char *input_file_path;
  size_t *thresholds, thresholds_count;
  size_t i;

  ASSERT(argc >= ARG_FIRST_THRESHOLD, "Wrong number of arguments passed (input file path not found)", main);
  ASSERT(argc >= ARG_MIN_NUM_ARGS, "Wrong number of arguments passed (sorting threshold list not found)", main);

  input_file_path = argv[ARG_INPUT_FILE_PATH];

  thresholds_count = (argc - ARG_FIRST_THRESHOLD);
  thresholds = (size_t *) malloc(sizeof(size_t) * thresholds_count);
  ASSERT(thresholds, "Unable to allocate memory for thresholds list", main);

  for (i = ARG_FIRST_THRESHOLD; i < ARG_FIRST_THRESHOLD + thresholds_count; i++) {
    ASSERT(sscanf(argv[i], "%zu", &thresholds[i - ARG_FIRST_THRESHOLD]), "Unable to parse a sorting threshold", main); // NOLINT(*-err34-c)
    ASSERT(thresholds[i] >= 0, "A sorting threshold must be greater than or equal to 0", main);
  }

  profile_execution(input_file_path, thresholds, thresholds_count);

  free(thresholds);
  return EXIT_SUCCESS;
}
