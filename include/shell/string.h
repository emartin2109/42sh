/*
** EPITECH PROJECT, 2023
** shell
** File description:
** string
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Get the length of a string until one of the specified characters.
 *
 * @param str The string.
 * @param delimiters The delimiters (use '\0' to get the length of the
 * whole string).
 * @return size_t The length of the string.
 */
size_t str_len_until(const char *str, const char *delimiters);

/**
 * @brief Allocates a copy of the specified string with the specified
 * length.
 *
 * @param str The string to copy.
 * @param len The length of the string to copy (use 0 to copy the whole
 * string).
 * @return char* The allocated copy of the string (NULL if the allocation
 * failed).
 */
char *str_copy(const char *str, size_t len);

/**
 * @brief Concatenate two strings with a separator.
 *
 * @param str1 First string.
 * @param str2 Second string.
 * @param sep The separator.
 * @return char* The concatenated string (NULL if the allocation failed).
 */
char *str_concat(const char *str1, const char *str2, const char *sep);

/**
 * @brief Split a string on the specified delimiters and returns an array
 * of the parts.
 *
 * @param str The string to split.
 * @param delimiters List of delimiters
 * @return char** An array of the parts, ended by NULL (NULL if the
 * allocation failed).
 */
char **str_split(const char *str, const char *delimiters);

/**
 * @brief Split a string once on one of the specified delimiters and
 * returns an array of the two parts.
 *
 * @param str The string to split.
 * @param delimiters List of delimiters
 * @return char** An array of the two parts (NULL if the delimiter is not
 * found).
 */
char **str_split_once(const char *str, const char *delimiter);

/**
 * @brief Remove starting and ending spaces/newlines/tabs from a string.
 *
 * @param str The string to trim.
 * @return char* The trimmed string (NULL if the allocation failed).
 */
char *str_trim(char *str);

/**
 * @brief Check if a character is in the given list of characters.
 *
 * @param c The character to check.
 * @param list The list of characters.
 * @return bool true if the character is in the list, false otherwise.
 */
bool str_char_in(char c, const char *list);

/**
 * @brief Remove the ending newline of a string.
 *
 * @param str The string.
 */
void str_remove_newline(char *str);

/**
 * @brief Parse an int from a string.
 *
 * @param str The string to parse.
 * @param number Pointer to the variable that will contain the parsed number.
 * @return int 0 if the parsing succeeded, -1 otherwise.
 */
int str_parse_int(const char *str, int *number);
