#pragma once

/**
 * @brief Function pointer type for element comparison in a SkipList.
 *
 * @remark A comparison function of this type should take two pointers to elements
 * and return an integer value indicating their relative order:
 * <ul>
 *      <li>A negative value if the first element is less than the second.</li>
 *      <li>Zero if the elements are equal</li>
 *      <li>A positive value if the first element is greater than the second</li>
 * </ul>
 *
 * @param a Pointer to the first element for comparison.
 * @param b Pointer to the second element for comparison.
 * @return An integer representing the comparison result.
 */
typedef int (*compare_fn)(const void *, const void *);

/**
 * @brief Comparator function for integers.
 *
 * @remark This function compares two integers pointed to by 'left' and 'right'.
 * It returns a negative value if 'left' is less than 'right', zero if they are equal,
 * and a positive value if 'left' is greater than 'right'.
 *
 * @param left  Pointer to the first integer.
 * @param right Pointer to the second integer.
 * @return      A negative value if 'left' is less than 'right', zero if they are equal,
 *              and a positive value if 'left' is greater than 'right'.
 *
 * @note The use of this comparator for values other than integers will cause undefined behavior.
 */
extern const compare_fn int_comparator;

/**
 * @brief Comparator function for floating-point numbers.
 *
 * @remark This function compares two floats pointed to by 'left' and 'right'.
 * It returns a negative value if 'left' is less than 'right', zero if they are equal,
 * and a positive value if 'left' is greater than 'right'.
 *
 * @param left  Pointer to the first float.
 * @param right Pointer to the second float.
 * @return      A negative value if 'left' is less than 'right', zero if they are equal,
 *              and a positive value if 'left' is greater than 'right'.
 *
 * @note The use of this comparator for values other than floats will cause undefined behavior.
 */
extern const compare_fn float_comparator;

/**
 * @brief Comparator function for strings.
 *
 * @remark This function compares two strings pointed to by 'left' and 'right'.
 * It returns a negative value if the first non-matching character in 'left' is greater (in ASCII) than that of 'right',
 * zero if they are equal, and a positive value if the first non-matching character in 'left' is lower (in ASCII) than
 * that of 'right'.
 *
 * @param left  Pointer to the first string.
 * @param right Pointer to the second string.
 * @return      A negative value if 'left' is less than 'right', zero if they are equal,
 *              and a positive value if 'left' is greater than 'right'.
 *
 * @note The use of this comparator for values other than integers will cause undefined behavior.
 * @note The strings shall be null-terminated.
 */
extern const compare_fn string_comparator;
