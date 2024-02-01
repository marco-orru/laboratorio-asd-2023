#pragma once

#include <stdlib.h>

/**
 * @brief Prints an error message and aborts the execution
 */
#define PRINT_ERROR(msg, fn)                                          \
do {                                                                  \
  fprintf(stderr, "RUNTIME_ERROR(" #fn "): " msg);                    \
  fflush(stderr);                                                     \
  abort();                                                            \
} while(0)

/**
 * @brief If cond is false, prints an error message and aborts.
 */
#define ASSERT(cond, msg, fn)     \
do {                              \
  if (!(cond))                    \
  PRINT_ERROR(msg, fn);           \
} while(0)

#define ASSERT_NULL_PARAMETER(param, fn) \
  ASSERT(param, "'" #param "' parameter is NULL", fn)
