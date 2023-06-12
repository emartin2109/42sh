/*
** EPITECH PROJECT, 2023
** shell
** File description:
** string
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "shell/string.h"

size_t str_len_until(const char *str, const char *delimiters)
{
    if (str == NULL) return 0;
    size_t len = 0;
    while (str[len] != '\0' && !str_char_in(str[len], delimiters)) len++;

    return len;
}

char *str_copy(const char *str, size_t len)
{
    if (str == NULL) return NULL;
    size_t str_length = strlen(str);
    if (len > str_length || len == 0) len = str_length;

    char *result = malloc(sizeof(char) * (len + 1));
    if (result == NULL) return NULL;

    for (size_t i = 0; i < len; i++) {
        result[i] = str[i];
    }
    result[len] = '\0';

    return result;
}

char *str_concat(const char *str1, const char *str2, const char* sep)
{
    if (str1 == NULL) return str_copy(str2, 0);
    if (str2 == NULL) return str_copy(str1, 0);
    if (sep == NULL) sep = "";

    size_t str1_length = strlen(str1);
    size_t str2_length = strlen(str2);
    size_t sep_length = strlen(sep);

    char *result = malloc(
        sizeof(char) * (str1_length + str2_length + sep_length + 1));
    if (result == NULL) return NULL;

    for (size_t i = 0; i < str1_length; i++)
        result[i] = str1[i];
    for (size_t i = 0; i < sep_length; i++)
        result[str1_length + i] = sep[i];
    for (size_t i = 0; i < str2_length; i++)
        result[str1_length + sep_length + i] = str2[i];
    result[str1_length + sep_length + str2_length] = '\0';
    return result;
}
