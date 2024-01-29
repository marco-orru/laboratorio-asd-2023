#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "merge-binary-insertion-sort.h"
#include "records-sorter.h"

#define MACRO_START do
#define MACRO_END while(0)

#define GET_STRING(records, i) (((char**)records)[(i)])
#define GET_INTEGER(records, i) (((int*)records)[(i)])
#define GET_FLOAT(records, i) (((float *)records)[(i)])

#define LINE_BUFFER_SIZE 128

static void *alloc_records(FieldId fieldId) {
    void *records;

    switch (fieldId) {
        case FIELD_STRING:
            records = malloc(sizeof(char *) * NUMBER_OF_RECORDS);
            break;
        case FIELD_INTEGER:
            records = malloc(sizeof(int) * NUMBER_OF_RECORDS);
            break;
        case FIELD_FLOAT:
            records = malloc(sizeof(float) * NUMBER_OF_RECORDS);
            break;
    }

    return records;
}

static void free_records(void *records, FieldId fieldId) {
    int i;

    switch (fieldId) {
        case FIELD_STRING:
            for (i = 0; i < NUMBER_OF_RECORDS; i++)
                free(GET_STRING(records, i));
        case FIELD_INTEGER:
        case FIELD_FLOAT:
            free(records);
            break;
    }
}

#define LOAD_STRING(records, index, str)                                \
MACRO_START                                                             \
{                                                                       \
    GET_STRING(records, i) = calloc(strlen(field) + 1, sizeof(char));   \
    strcpy(GET_STRING(records, i++), field);                            \
}                                                                       \
MACRO_END

#define LOAD_INT(records, index, integer) (GET_INTEGER(records, index++) = atoi((integer)))
#define LOAD_FLOAT(records, index, flt) (GET_FLOAT(records, index++) = atof((flt)))

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"

static void load_records(FILE *in_file, FieldId field_id, void *records) {
    char line_buffer[LINE_BUFFER_SIZE];
    char *field;
    size_t i;

    i = 0;

    while (i < NUMBER_OF_RECORDS && fgets(line_buffer, LINE_BUFFER_SIZE, in_file)) {
        strtok(line_buffer, ",");  // IGNORE ID

        field = strtok(NULL, ",");  // STRING field
        if (field_id == FIELD_STRING) {
            LOAD_STRING(records, i, field);
            continue;
        }

        field = strtok(NULL, ",");  // STRING int
        if (field_id == FIELD_INTEGER) {
            LOAD_INT(records, i, field);
            continue;
        }

        field = strtok(NULL, ",");  // STRING float
        if (field_id == FIELD_FLOAT) {
            LOAD_FLOAT(records, i, field);
            continue;
        }
    }
}

#pragma clang diagnostic pop

#undef LOAD_STRING
#undef LOAD_INT
#undef LOAD_FLOAT

static void store_records(FILE *out_file, FieldId field_id, void *records) {
    int i;

    for (i = 0; i < NUMBER_OF_RECORDS; ++i) {
        switch (field_id) {
            case FIELD_STRING:
                fprintf(out_file, "%s\n", GET_STRING(records, i));
                break;

            case FIELD_INTEGER:
                fprintf(out_file, "%d\n", GET_INTEGER(records, i));
                break;

            case FIELD_FLOAT:
                fprintf(out_file, "%f\n", GET_FLOAT(records, i));
                break;
        }
    }
}

static void sort(void *records, FieldId field_id, size_t threshold) {
    size_t elem_size;
    compare_fn compare_fn;

    switch (field_id) {
        case FIELD_STRING:
            elem_size = sizeof(char *);
            compare_fn = string_comparator;
            break;

        case FIELD_INTEGER:
            elem_size = sizeof(int);
            compare_fn = int_comparator;
            break;

        case FIELD_FLOAT:
            elem_size = sizeof(float);
            compare_fn = float_comparator;
            break;
    }

    merge_binary_insertion_sort(records, NUMBER_OF_RECORDS, elem_size, threshold, compare_fn);
}

void sort_records(FILE *in_file, FILE *out_file, size_t sorting_threshold, FieldId field_id) {
    void *records;

    assert(in_file);
    assert(out_file);
    assert(in_file != out_file);
    assert(sorting_threshold > 0);
    assert(field_id >= FIELD_STRING && field_id <= FIELD_FLOAT);

    records = alloc_records(field_id);

    load_records(in_file, field_id, records);
    sort(records, field_id, sorting_threshold);
    store_records(out_file, field_id, records);

    free_records(records, field_id);
}
