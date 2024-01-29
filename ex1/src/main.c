#include <stdlib.h>
#include <string.h>
#include "records-sorter.h"

#define ENABLE_ARG_OVERRIDES 0
#define ENABLE_PROFILER 1

#if ENABLE_PROFILER
#include <time.h>
#endif

#if ENABLE_ARG_OVERRIDES
#define OVERRIDE_IN_PATH "resources/records.csv"
#define OVERRIDE_OUT_PATH "resources/sorted.txt"
#define OVERRIDE_THRESHOLD 40
#define OVERRIDE_FIELD_ID FIELD_INTEGER
#endif

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Defines constants for indexing argv.
enum ARGS {
    ARG_IN_FILE_PATH = 1,
    ARG_OUT_FILE_PATH,
    ARG_SORTING_THRESHOLD,
    ARG_SORTING_FIELD
};

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Performs the processing of the input file, reading and sorting the specified field, and saving the result
//          in the specified file.
static int process_file(const char* in_path, const char* out_path, size_t sorting_threshold, FieldId field_id) {
    FILE* in_file, *out_file;
#if ENABLE_PROFILER
    clock_t begin, end;
    char field_name[16];
#endif

    in_file = fopen(in_path, "r");

    if (!in_file) {
        fprintf(stderr, "Error while opening input file.\n");
        return EXIT_FAILURE;
    }

    out_file = fopen(out_path, "w");
    if (!out_file) {
        fclose(in_file);

        fprintf(stderr, "Error while opening output file.\n");
        return EXIT_FAILURE;
    }

#if ENABLE_PROFILER
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

    printf("[PROFILER] Sorting %s fields with threshold %zu.\n", field_name, sorting_threshold);
    begin = clock();
#endif

    sort_records(in_file, out_file, sorting_threshold, field_id);

#if ENABLE_PROFILER
    end = clock();
    printf("[PROFILER] Records sorted. Elapsed time: %f seconds.\n", (double)(end - begin) / CLOCKS_PER_SEC);
#endif

    fclose(out_file);
    fclose(in_file);

    return EXIT_SUCCESS;
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Entry point.
int main(int argc, char* argv[]) {
    const char* in_file_path;
    const char* out_file_path;
    size_t sorting_threshold;
    FieldId sorting_field_id;

#if ENABLE_ARG_OVERRIDES
    in_file_path = OVERRIDE_IN_PATH;
    out_file_path = OVERRIDE_OUT_PATH;
    sorting_threshold = OVERRIDE_THRESHOLD;
    sorting_field_id = OVERRIDE_FIELD_ID;
#else
    if (argc != 5) {
        fprintf(stderr, "Wrong number of arguments passed.\n");
        fprintf(stderr, "You should pass four arguments: "
                        "the input file name, "
                        "the output file name, "
                        "the sorting threshold and"
                        "the field id to sort (0 - STRING, 1 - INT, 2 - FLOAT).\n");
        return EXIT_FAILURE;
    }

    in_file_path = argv[ARG_IN_FILE_PATH];
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
        fprintf(stderr, "The field id to sort has not been specified correctly.\n");
        return EXIT_FAILURE;
    }
#endif

    return process_file(in_file_path, out_file_path, sorting_threshold, sorting_field_id);
}
