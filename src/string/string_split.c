/*
** EPITECH PROJECT, 2023
** shell
** File description:
** string_split
*/

#include <stdlib.h>
#include <string.h>

#include "shell/string.h"

char **str_split(const char *str, const char *delimiters)
{
    if (str == NULL) return NULL;
    while (str_char_in(*str, delimiters)) str++;

    size_t part_count = 1;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str_char_in(str[i], delimiters)) part_count++;
        while (str_char_in(str[i], delimiters)) i++;
    }

    char **result = malloc(sizeof(char *) * (part_count + 1));
    if (result == NULL) return NULL;

    for (size_t i = 0; i < part_count; i++) {
        size_t part_size = str_len_until(str, delimiters);
        result[i] = str_copy(str, part_size);
        str += part_size;
        while (str_char_in(*str, delimiters)) str++;
    }
    result[part_count] = NULL;
    return result;
}

char **str_split_once(const char *str, const char *delimiters)
{
    if (str == NULL) return NULL;
    char **result = malloc(sizeof(char *) * 2);
    if (result == NULL) return NULL;

    size_t str_length = strlen(str);
    size_t start_index = str_len_until(str, delimiters);

    result[0] = str_copy(str, start_index);
    result[1] = str_copy(str + start_index + 1, str_length - start_index - 1);

    return result;
}

char *str_trim(char *str)
{
    if (str == NULL) return NULL;
    size_t string_length = strlen(str);
    if (string_length == 0) return str;

    size_t start_index = 0;
    size_t end_index = string_length - 1;
    while (str[start_index] == ' ' || str[start_index] == '\t'
        || str[start_index] == '\n') start_index++;
    while ((str[end_index] == ' ' || str[end_index] == '\t'
        || str[end_index] == '\n') && end_index > start_index) {
        end_index--;
    }

    size_t new_length = end_index - start_index + 1;
    return str_copy(str + start_index, new_length);
}
