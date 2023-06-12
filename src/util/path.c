/*
** EPITECH PROJECT, 2023
** shell
** File description:
** path
*/

#include <string.h>

#include "shell/util.h"
#include "shell/string.h"

char *normalize_directory(char *path)
{
    if (path == NULL) return NULL;

    size_t len = strlen(path);
    if (path[len - 1] == '/') {
        return str_copy(path, 0);
    } else {
        return str_concat(path, "/", NULL);
    }
}

char *expand_home(char *path, char *home)
{
    if (*path != '~') return path;
    char *expanded = str_concat(home, path + 1, NULL);
    return expanded;
}
