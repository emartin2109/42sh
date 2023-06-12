/*
** EPITECH PROJECT, 2023
** shell
** File description:
** history
*/

#include <stdlib.h>
#include <string.h>

#include "shell/history.h"
#include "shell/macros.h"

static const size_t DEFAULT_HISTORY_SIZE = 64;

history_t *init_history(void)
{
    history_t *history = calloc(1, sizeof(history_t));
    if (history == NULL) return NULL;

    history->capacity = DEFAULT_HISTORY_SIZE;
    history->commands = calloc(DEFAULT_HISTORY_SIZE, sizeof(char *));
    if (history->commands == NULL) return NULL;

    return history;
}

static void move_to_end(history_t *history, size_t index)
{
    char *cmd = history->commands[index];
    for (size_t i = index; i < history->size - 1; i++) {
        history->commands[i] = history->commands[i + 1];
    }
    history->commands[history->size - 1] = cmd;
}

int push_history(history_t *history, char *command)
{
    if (strlen(command) == 0) return SUCCESS_RETURN;
    for (size_t i = 0; i < history->size; i++) {
        if (strcmp(history->commands[i], command) == 0) {
            move_to_end(history, i);
            return SUCCESS_RETURN;
        }
    }

    if (history->size == history->capacity) {
        history->capacity *= 2;
        history->commands = realloc(history->commands,
            history->capacity * sizeof(char *));
        if (history->commands == NULL) return ERROR_RETURN;
    }

    char *cmd_clone = strdup(command);
    if (cmd_clone == NULL) return ERROR_RETURN;
    history->commands[history->size] = cmd_clone;
    history->size++;
    return SUCCESS_RETURN;
}

void free_history(history_t *history)
{
    if (history == NULL) return;

    for (size_t i = 0; i < history->size; i++) {
        free(history->commands[i]);
    }
    free(history->commands);
    free(history);
}
