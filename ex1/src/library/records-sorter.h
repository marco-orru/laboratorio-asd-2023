#pragma once

#include <stdio.h>

#ifndef NUMBER_OF_RECORDS
#define NUMBER_OF_RECORDS 20000000
#endif

typedef enum FieldId {
    FIELD_STRING,
    FIELD_INTEGER,
    FIELD_FLOAT
} FieldId;

void sort_records(FILE *infile, FILE *outfile, size_t sorting_threshold, FieldId field_id);