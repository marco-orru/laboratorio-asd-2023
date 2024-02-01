#pragma once

#include <stdio.h>

#ifndef NUMBER_OF_RECORDS
/**
 * @brief Defines the default number of records present in the record file.
 *
 * @remark This number can be changed by setting this macro before including this header file.
 */
#define NUMBER_OF_RECORDS 20000000
#endif

/**
 * @brief Defines the types of fields that can be read from the record file.
 */
typedef enum FieldId {
  /** @brief Reads the string field. */
  FIELD_STRING,
  /** @brief Reads the integer field */
  FIELD_INTEGER,
  /** @brief Reads the float field */
  FIELD_FLOAT
} FieldId;

/**
 * @brief Reads the records stored in the provided file, then sorts the fields of the specified type and saves the sorted
 * records in another file.
 *
 * @param in_file The .csv file containing the records.
 * @param out_file The .txt file in which the sorted records will be written.
 * @param sorting_threshold The sorting threshold to be passed to the sorting algorithm.
 * @param field_id The type of the fields to be sorted.
 */
void sort_records(FILE *in_file, FILE *out_file, size_t sorting_threshold, FieldId field_id);

#if __PROFILER

/**
 * @brief Initializes he profiler loading the records.
 * @param in_file The .csv file containing the records.
 */
void init_profiler__records_sorter(FILE *in_file);

/**
 * @brief Shutdowns the profiler.
 */
void shutdown_profiler__records_sorter(void);

/**
 * @brief Profile the execution of the sorting algorithm over the unsorted array.
 * @param threshold The sorting threshold to be passed to the sorting algorithm.
 * @param field_id The type of fields to be sorted.
 */
void profile__records_sorter(size_t threshold, FieldId field_id);

#endif
