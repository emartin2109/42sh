/*
** EPITECH PROJECT, 2023
** shell
** File description:
** error
*/

#include <string.h>
#include "stdio.h"

#include "shell/util.h"
#include "shell/macros.h"
#include "shell/string.h"

void print_error(const char *prefix, int code, bool newline)
{
    if (prefix != NULL) {
        fprintf(stderr, "%s: ", prefix);
    }

    char *error = strerror(code);
    fprintf(stderr, "%s.", error);
    if (newline)
        fprintf(stderr, "\n");
}
