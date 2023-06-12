/*
** EPITECH PROJECT, 2023
** shell
** File description:
** util
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>

/* MEMORY */

/**
 * @brief Get the length of a null-terminated array of strings.
 *
 * @param array The array.
 * @return size_t The length of the array.
 */
size_t mem_array_len(char **array);

/**
 * @brief Free a null-terminated array of strings.
 *
 * @param array The array to free.
 */
void mem_free_array(char **array);

/* PATH */

/**
 * @brief Normalize a directory path by adding a trailing slash if necessary.
 *
 * @param path The path to normalize.
 * @return char* The normalized path (NULL if the allocation failed).
 */
char *normalize_directory(char *path);

/**
 * @brief Expand a path by replacing '~' with the home directory.
 *
 * @param path The path to expand.
 * @return char* The expanded path (NULL if the allocation failed).
 */
char *expand_home(char *path, char *home);

/* ERROR */

/**
 * @brief Print the error message corresponding to the specified error code.
 *
 * @param prefix The prefix of the error message.
 * @param code The error code.
 * @param newline Whether to print a newline at the end of the message.
 */
void print_error(const char *prefix, int code, bool newline);
