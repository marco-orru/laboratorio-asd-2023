#include <stdlib.h>

#include "records-sorter.h"

#ifndef ENABLE_PROFILER
#define ENABLE_PROFILER 0
#endif

#if !ENABLE_PROFILER
#include <string.h>
#endif

#ifndef PROFILE_ONLY_SORTING
// PURPOSE: When this is enabled, the profiler will profile only the execution of the sorting algorithm,
//          and not the execution of the file reading and writing.
#define PROFILE_ONLY_SORTING 1 && ENABLE_PROFILER
#endif

#if ENABLE_PROFILER && !defined(PROFILE_TEST)
// PURPOSE: When in profiling mode, selects the test to execute from the predefined tests.
#define PROFILE_TEST 1
#endif

#if ENABLE_PROFILER && !PROFILE_ONLY_SORTING
#include <time.h>
#endif

// PURPOSE: Defines the default tests.
#if ENABLE_PROFILER
#if !defined(NUMBER_OF_THRESHOLDS) && !defined(PROFILE_THRESHOLDS)
#if PROFILE_TEST == 0
#define NUMBER_OF_THRESHOLDS 1
#define PROFILE_THRESHOLDS {}
#elif PROFILE_TEST == 1
#define NUMBER_OF_THRESHOLDS 11
#define PROFILE_THRESHOLDS {0, 5, 10, 20, 50, 80, 100, 500, 1000, 5000, 10000}
#elif  // ADD OTHER TESTS HERE
// ...
#endif
#else
#error "No profiler test selected"
#endif
#endif

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Defines constants for indexing argv.
enum ARGS {
    ARG_IN_FILE_PATH = 1,
#if !ENABLE_PROFILER
    ARG_OUT_FILE_PATH,
    ARG_SORTING_THRESHOLD,
    ARG_SORTING_FIELD,
#endif
    NUM_ARGS
};

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Performs the processing of the input file, reading and sorting the specified field, and saving the result
//          in the specified file.
#if ENABLE_PROFILER
static int process_file(const char *in_path, size_t sorting_threshold, FieldId field_id)
#else
static int process_file(const char *in_path, const char *out_path, size_t sorting_threshold, FieldId field_id)
#endif
{
    FILE* in_file;

#if !ENABLE_PROFILER
    FILE *out_file;
#endif

#if ENABLE_PROFILER & !PROFILE_ONLY_SORTING
    clock_t begin, end;
    char field_name[16];
#endif

    in_file = fopen(in_path, "r");

    if (!in_file) {
        fprintf(stderr, "Error while opening input file.\n");
        return EXIT_FAILURE;
    }

#if !ENABLE_PROFILER
    out_file = fopen(out_path, "w");
    if (!out_file) {
        fclose(in_file);

        fprintf(stderr, "Error while opening output file.\n");
        return EXIT_FAILURE;
    }
#endif

#if ENABLE_PROFILER && !PROFILE_ONLY_SORTING
    begin = clock();
#elif !ENABLE_PROFILER
    printf("Sorting records...\n");
#endif

#if ENABLE_PROFILER
    sort_records(in_file, sorting_threshold, field_id);
#else
    sort_records(in_file, out_file, sorting_threshold, field_id);
#endif

#if ENABLE_PROFILER && !PROFILE_ONLY_SORTING
    end = clock();

    switch (field_id) {
        case FIELD_STRING:
            strcpy(field_name, "STRING");
            break;
        case FIELD_INTEGER:
            strcpy(field_name, "INT");
            break;
        case FIELD_FLOAT:
            strcpy(field_name, "FLOAT");
            break;
    }

    printf("[PROFILER] Records loaded, sorted and saved [%s, THRESHOLD: %zu]. Elapsed time: %f seconds.\n",
           field_name,
           sorting_threshold,
           (double) (end - begin) / CLOCKS_PER_SEC);
#elif !ENABLE_PROFILER
    printf("Records have been sorted and saved to the specified file.\n");
#endif

#if !ENABLE_PROFILER
    fclose(out_file);
#endif

    fclose(in_file);

    return EXIT_SUCCESS;
}

/*---------------------------------------------------------------------------------------------------------------*/

#if ENABLE_PROFILER

// PURPOSE: Automatically executes the test through all fields with various thresholds.
static int profile_execution(const char *in_file_path, size_t *thr) {
    size_t i;

    printf("[PROFILER] Processing STRING fields...\n");
    for (i = 0; i < NUMBER_OF_THRESHOLDS; ++i) {
        if (process_file(in_file_path, thr[i], FIELD_STRING) != 0)
            return EXIT_FAILURE;
    }

    printf("[PROFILER] Processing INT fields...\n");
    for (i = 0; i < NUMBER_OF_THRESHOLDS; ++i) {
        if (process_file(in_file_path, thr[i], FIELD_INTEGER) != 0)
            return EXIT_FAILURE;
    }

    printf("[PROFILER] Processing FLOAT fields...\n");
    for (i = 0; i < NUMBER_OF_THRESHOLDS; ++i) {
        if (process_file(in_file_path, thr[i], FIELD_FLOAT) != 0)
            return EXIT_FAILURE;
    }

    records_sorter__release_profiler();

    return EXIT_SUCCESS;
}

#endif

/*---------------------------------------------------------------------------------------------------------------*/

#if !ENABLE_PROFILER
// PURPOSE: Tests the string representation of the field type.
#define TEST_STR_FIELD_ID(value, str) (!strcmp("FIELD_" value, str) || !strcmp(value, str))
#endif

// PURPOSE: Entry point.
int main(int argc, char* argv[]) {
    const char* in_file_path;

#if !ENABLE_PROFILER
    const char* out_file_path;
    size_t sorting_threshold;
    FieldId sorting_field_id;
    char sorting_field_id_str[16];
#endif

#if ENABLE_PROFILER
    size_t thresholds[NUMBER_OF_THRESHOLDS] = PROFILE_THRESHOLDS;
#endif

    if (argc < NUM_ARGS) {
        fprintf(stderr, "Wrong number of arguments passed.\n");

#if !ENABLE_PROFILER
        fprintf(stderr, "You should pass four arguments: "
                        "the input file name, "
                        "the output file name, "
                        "the sorting threshold and"
                        "the field id to sort (0 - STRING, 1 - INTEGER, 2 - FLOAT).\n");
#else
        fprintf(stderr, "You should pass one arguments: "
                        "the input file name.\n");
#endif
        return EXIT_FAILURE;
    }

    in_file_path = argv[ARG_IN_FILE_PATH];

#if !ENABLE_PROFILER
    out_file_path = argv[ARG_OUT_FILE_PATH];

    if (!strcmp(in_file_path, out_file_path)) {
        fprintf(stderr, "The two specified file paths refers to the same file.\n");
        return EXIT_FAILURE;
    }

    if (sscanf(argv[ARG_SORTING_THRESHOLD], "%zu", &sorting_threshold) != 1) { // NOLINT(*-err34-c)
        fprintf(stderr, "The sorting threshold has not been specified correctly.\n");
        return EXIT_FAILURE;
    }

    if (sscanf(argv[ARG_SORTING_FIELD], "%d", (int*)&sorting_field_id) != 1) { // NOLINT(*-err34-c)
        if (sscanf(argv[ARG_SORTING_FIELD], "%s", sorting_field_id_str) == 1) {
            if (TEST_STR_FIELD_ID("STRING", sorting_field_id_str)) sorting_field_id = FIELD_STRING;
            else if (TEST_STR_FIELD_ID("INTEGER", sorting_field_id_str)) sorting_field_id = FIELD_INTEGER;
            else if (TEST_STR_FIELD_ID("FLOAT", sorting_field_id_str)) sorting_field_id = FIELD_FLOAT;
            else goto ERROR;
        } else {
            ERROR:
            fprintf(stderr, "The field id to sort has not been specified correctly.\n");
            return EXIT_FAILURE;
        }
    }
#endif

#if ENABLE_PROFILER
    return profile_execution(in_file_path, thresholds);
#else
    return process_file(in_file_path, out_file_path, sorting_threshold, sorting_field_id);
#endif
}
