#include <string.h>
#include "comparator.h"

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Compares two ints from two generic pointers.
static int int_comparator_fn(const void *left, const void *right) {
    int a = *(int *) left;
    int b = *(int *) right;

    if (a > b) return 1;
    if (a < b) return -1;
    return 0;
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Compares two floats from two generic pointers.
static int float_comparator_fn(const void *left, const void *right) {
    float a = *(float *) left;
    float b = *(float *) right;

    if (a > b) return 1;
    if (a < b) return -1;
    return 0;
}

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Compares two strings from two generic pointers.
static int string_comparator_fn(const void *left, const void *right) {
    char *a = (char *) left;
    char *b = (char *) right;

    return strcmp(a, b);
}

/*---------------------------------------------------------------------------------------------------------------*/

const compare_fn int_comparator = int_comparator_fn;
const compare_fn float_comparator = float_comparator_fn;
const compare_fn string_comparator = string_comparator_fn;
