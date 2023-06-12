/*
** EPITECH PROJECT, 2023
** shell
** File description:
** file
*/

#include <stdio.h>
#include <stdlib.h>

#include "shell/history.h"
#include "shell/macros.h"
#include "shell/util.h"

static int load_file(history_t *history, FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    while ((read = getline(&line, &len, file)) != -1) {
        if (line[read - 1] == '\n') line[read - 1] = '\0';
        if (push_history(history, line) == ERROR_RETURN) {
            free(line);
            return ERROR_RETURN;
        }
    }

    free(line);
    return SUCCESS_RETURN;
}

int load_history(history_t *history, char *home)
{
    if (home == NULL) return SUCCESS_RETURN;
    char *path = expand_home("~/.42sh_history", home);
    if (path == NULL) return ERROR_RETURN;

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        free(path);
        return SUCCESS_RETURN;
    }

    if (load_file(history, file) == ERROR_RETURN) {
        fclose(file);
        free(path);
        return ERROR_RETURN;
    }

    fclose(file);
    free(path);
    return SUCCESS_RETURN;
}

int write_history(history_t *history, char *home)
{
    if (home == NULL) return SUCCESS_RETURN;
    char *path = expand_home("~/.42sh_history", home);
    if (path == NULL) return ERROR_RETURN;

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        free(path);
        return ERROR_RETURN;
    }

    for (size_t i = 0; i < history->size; i++) {
        fprintf(file, "%s\n", history->commands[i]);
    }

    fclose(file);
    free(path);
    return SUCCESS_RETURN;
}
