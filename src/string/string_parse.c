/*
** EPITECH PROJECT, 2023
** shell
** File description:
** parse
*/

#include <limits.h>
#include <string.h>

#include "shell/string.h"
#include "shell/macros.h"

bool str_char_in(char c, const char *list)
{
    if (list == NULL) return false;
    for (size_t i = 0; list[i] != '\0'; i++) {
        if (list[i] == c) return true;
    }
    return false;
}

void str_remove_newline(char *str)
{
    if (str == NULL) return;
    size_t str_length = strlen(str);
    if (str[str_length - 1] == '\n' && str_length > 0)
        str[str_length - 1] = '\0';
}

int str_parse_int(const char *str, int *number)
{
    int n = 0;
    int sign = 1;

    if (*str == '-') {
        sign = -1;
        str++;
    }

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') return ERROR_RETURN;
        int parsed = str[i] - '0';

        if (n > INT_MAX / 10 ||
            (n == INT_MAX / 10 && parsed > INT_MAX % 10))
            return ERROR_RETURN;
        n = n * 10 + parsed;
    }

    *number = n * sign;
    return SUCCESS_RETURN;
}
