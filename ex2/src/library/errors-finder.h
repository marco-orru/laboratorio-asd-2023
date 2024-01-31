#pragma once
#include <stdio.h>

/**
 * Prints the words in the given text file that are not present in the specified dictionary text file.
 * @param dict_file Pointer to the dictionary text file.
 * @param text_file Pointer to the text file to be corrected.
 * @param max_height Parameter for the skiplist, determining its maximum height.
 *
 * @note Higher values of @c max_height may improve search efficiency at the cost of space.
 * @note @c max_height must be greater than or equal to 1.
 */
void find_errors(FILE *dict_file, FILE *text_file, size_t max_height);
