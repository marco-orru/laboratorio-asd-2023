#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "merge-binary-insertion-sort.h"
#include "records-sorter.h"

#ifndef ENABLE_PROFILER
#define ENABLE_PROFILER 0
#endif

#if ENABLE_PROFILER
#include <time.h>
#endif

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

// PURPOSE: Loads the record from a file, and saves them into the records array.
static void load_records(FILE *in_file, Record *records) {
    char line_buffer[LINE_BUFFER_SIZE];
    size_t i;

    i = 0;

    while (i < NUMBER_OF_RECORDS && fgets(line_buffer, LINE_BUFFER_SIZE, in_file))
        load_record(line_buffer, records, i++);
}

/*---------------------------------------------------------------------------------------------------------------*/

#if !ENABLE_PROFILER
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
#endif

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

    assert(0);
    return 0;
}

/*---------------------------------------------------------------------------------------------------------------*/

#if ENABLE_PROFILER
static Record* g_unsorted_records;
#endif

#if ENABLE_PROFILER
void sort_records(FILE *in_file, size_t sorting_threshold, FieldId field_id)
#else
void sort_records(FILE *in_file, FILE *out_file, size_t sorting_threshold, FieldId field_id)
#endif
{
    Record *records;

#if ENABLE_PROFILER
    clock_t begin, end;
    char field_name[16];
#endif

    assert(in_file);
    assert(sorting_threshold >= 0);
    assert(field_id >= FIELD_STRING && field_id <= FIELD_FLOAT);

#if !ENABLE_PROFILER
    assert(in_file != out_file);
    assert(out_file);
#endif

    g_field_id = field_id;

    records = (Record*)malloc(sizeof(Record) * NUMBER_OF_RECORDS);

    if (!records) {
        fprintf(stderr, "Error while allocating memory for records!");
        abort();
    }

#if ENABLE_PROFILER
    if (!g_unsorted_records) {
        g_unsorted_records = malloc(sizeof(Record) * NUMBER_OF_RECORDS);
        load_records(in_file, records);
        memcpy(g_unsorted_records, records, sizeof(Record) * NUMBER_OF_RECORDS);
    } else {
        memcpy(records, g_unsorted_records, sizeof(Record) * NUMBER_OF_RECORDS);
    }
#endif

    load_records(in_file, records);

#if ENABLE_PROFILER
    begin = clock();
#endif

    merge_binary_insertion_sort(records, NUMBER_OF_RECORDS, sizeof(Record), sorting_threshold, compare_records_fn);

#if ENABLE_PROFILER
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

    printf("[PROFILER] Records sorted [%s, THRESHOLD: %zu]. Elapsed time: %f seconds.\n",
           field_name,
           sorting_threshold,
           (double) (end - begin) / CLOCKS_PER_SEC);
#else
    store_records(out_file, records);
#endif

    free((void*)records);

    g_field_id = -1;
}

/*---------------------------------------------------------------------------------------------------------------*/

#if ENABLE_PROFILER
void records_sorter__release_profiler(void) {
    free((void*)g_unsorted_records);
    g_unsorted_records = NULL;
}
#endif
