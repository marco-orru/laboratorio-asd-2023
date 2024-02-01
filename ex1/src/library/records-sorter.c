#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "merge-binary-insertion-sort.h"
#include "assert_util.h"
#include "records-sorter.h"

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: The max length of a line.
#define LINE_BUFFER_SIZE 128

// PURPOSE: The max length of the string field.
// NOTE: Strings are stored statically to prevent allocations and memory fragmentation.
#define STRING_FIELD_LEN 32

// PURPOSE: Represents a record.
typedef struct Record {
    size_t id;
    char string_field[STRING_FIELD_LEN];
    int int_field;
    float float_field;
} Record;

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Parses a record id from its string representation and stores it into the record array.
#define LOAD_ID(records, i, str_id) ((records)[(i)].id = atoi((str_id)))

// PURPOSE: Parses a string field and stores it into the record array.
#define LOAD_STRING(records, i, field)                                      \
do                                                                          \
{                                                                           \
    strcpy((records)[(i)].string_field, (field));                           \
}                                                                           \
while (0)

// PURPOSE: Parses an int field and stores it into the record array.
#define LOAD_INT(records, i, field) ((records)[(i)].int_field = atoll((field)))

// PURPOSE: Parses a float field and stores it into the record array.
#define LOAD_FLOAT(records, i, field) ((records)[(i)].float_field = atof((field)))

/*---------------------------------------------------------------------------------------------------------------*/

static void load_record(char* line, Record* records, size_t index) {
    char* field;

    field = strtok(line, ",");
    LOAD_ID(records, index, field); // NOLINT(*-err34-c)

    field = strtok(NULL, ",");
    LOAD_STRING(records, index, field);

    field = strtok(NULL, ",");
    LOAD_INT(records, index, field); // NOLINT(*-err34-c)

    field = strtok(NULL, ",");
    LOAD_FLOAT(records, index, field); // NOLINT(*-err34-c)
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Loads the records from a file, and saves them into the records array.
static void load_records(FILE *in_file, Record *records) {
    char line_buffer[LINE_BUFFER_SIZE];
    size_t count;

    count = 0;

    while (count < NUMBER_OF_RECORDS && fgets(line_buffer, LINE_BUFFER_SIZE, in_file))
        load_record(line_buffer, records, count++);
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Writes the records array into the specified file.
static void store_records(FILE *out_file, Record *records) {
    int i;
    Record * record;

    for (i = 0; i < NUMBER_OF_RECORDS; ++i) {
        record = &records[i];
        fprintf(out_file, "%zu,%s,%d,%f\n",
                record->id,
                record->string_field,
                record->int_field,
                record->float_field);
    }
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: The field id to be used in the comparator function.
static FieldId g_field_id;

// PURPOSE: The records comparator function.
static int compare_records_fn(const void* record_a, const void* record_b) {
    const Record * a = (const Record*) record_a;
    const Record * b = (const Record*) record_b;

    switch (g_field_id) {
        case FIELD_STRING:
            return string_comparator(a->string_field, b->string_field);
        case FIELD_INTEGER:
            return int_comparator(&a->int_field, &b->int_field);
        case FIELD_FLOAT:
            return float_comparator(&a->float_field, &b->float_field);
    }

    PRINT_ERROR("Invalid field ID", compare_records_fn);
    return 0;
}

/*---------------------------------------------------------------------------------------------------------------*/

void sort_records(FILE *in_file, FILE *out_file, size_t sorting_threshold, FieldId field_id) {
    Record *records;

    ASSERT_NULL_PARAMETER(in_file, sort_records);
    ASSERT_NULL_PARAMETER(out_file, sort_records);
    ASSERT(sorting_threshold >= 0, "The sorting threshold must be >= 0", sort_records);
    ASSERT(field_id >= FIELD_STRING && field_id <= FIELD_FLOAT, "The field id is not in the valid range [1, 3]", sort_records);
    ASSERT(in_file != out_file, "The two provided files are pointing to the same file", sort_records);

    g_field_id = field_id;

    records = (Record*) malloc(sizeof(Record) * NUMBER_OF_RECORDS);

    ASSERT(records, "Unable to allocate memory for records", sort_records);

    printf("Loading records...\n");
    load_records(in_file, records);
    printf("Sorting records...\n");
    merge_binary_insertion_sort(records, NUMBER_OF_RECORDS, sizeof(Record), sorting_threshold, compare_records_fn);
    printf("Storing records...\n");
    store_records(out_file, records);

    free((void*)records);

    g_field_id = -1;
}

/*---------------------------------------------------------------------------------------------------------------*/

#if __PROFILER
#include <time.h>

#define PROFILER_PRINT(msg) printf("[PROFILER]: " msg "\n")
#define PROFILER_PRINT_RESULT(threshold, field_id, start, end) \
    printf("[PROFILER]<field=%s, threshold=%zu>: Sorted in %f seconds.\n", get_field_name((field_id)), (threshold), (double) ((end) - (start)) / CLOCKS_PER_SEC)

static Record* unsorted_records = NULL;

void init_profiler__records_sorter(FILE* in_file) {
    ASSERT_NULL_PARAMETER(in_file, init_profiler__records_sorter);
    ASSERT(!unsorted_records, "Profiler has been already initialized", init_profiler__records_sorter);

    PROFILER_PRINT("Initializing profiler...");

    PROFILER_PRINT("Allocating unsorted records...");
    unsorted_records = (Record*) malloc(sizeof(Record) * NUMBER_OF_RECORDS);
    ASSERT(unsorted_records, "Unable to allocate memory for the unsorted records array", init_profiler__records_sorter);

    PROFILER_PRINT("Loading records...");
    load_records(in_file, unsorted_records);

    PROFILER_PRINT("Profiler initialized.");
}

void shutdown_profiler__records_sorter(void) {
    ASSERT(unsorted_records, "Profiler already shut down", shutdown_profiler__records_sorter);

    PROFILER_PRINT("Shutting down profiler...");

    PROFILER_PRINT("Deallocating unsorted records...");
    free((void*)unsorted_records);

    PROFILER_PRINT("Profiler shut down.");
}

static const char* get_field_name(FieldId field_id) {
    switch (field_id) {
        case FIELD_STRING:
            return "STRING";
        case FIELD_INTEGER:
            return "INTEGER";
        case FIELD_FLOAT:
            return "FLOAT";
    }

    PRINT_ERROR("Invalid field ID", get_field_name);
    return 0;
}

void profile__records_sorter(size_t threshold, FieldId field_id) {
    Record* to_be_sorted;
    clock_t start, end;

    ASSERT(threshold >= 0, "The sorting threshold must be >= 0", profile__records_sorter);
    ASSERT(field_id >= FIELD_STRING && field_id <= FIELD_FLOAT, "The field id is not in the valid range [1, 3]", profile__records_sorter);

    to_be_sorted = (Record*) malloc(sizeof(Record) * NUMBER_OF_RECORDS);
    ASSERT(to_be_sorted, "Unable to allocate memory for records to be sorted", profile__records_sorter);

    ASSERT(memcpy(to_be_sorted, unsorted_records, sizeof(Record) * NUMBER_OF_RECORDS), "Unable to copy the unsorted records array", profile__records_sorter);

    g_field_id = field_id;

    start = clock();
    merge_binary_insertion_sort(to_be_sorted, NUMBER_OF_RECORDS, sizeof(Record), threshold, compare_records_fn);
    end = clock();

    PROFILER_PRINT_RESULT(threshold, field_id, start, end);

    free((void*)to_be_sorted);

    g_field_id = -1;
}
#endif
