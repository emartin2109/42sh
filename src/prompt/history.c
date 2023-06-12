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
#include "shell/prompt.h"

static int replace_with_history(line_buffer_t *line, char *command)
{
    size_t command_len = strlen(command);
    if (command_len + 1 >= line->capacity) {
        line->capacity = command_len + 1;
        line->buffer = realloc(line->buffer, line->capacity);
        if (line->buffer == NULL) return ERROR_RETURN;
    }

    line->buffer = strcpy(line->buffer, command);
    line->size = command_len;

    print_all(line);
    return SUCCESS_RETURN;
}

int show_prev_history(line_buffer_t *line, history_t *history)
{
    if (line->size == 0 || line->is_history == true) {
        if (line->history < history->size) {
            line->history++;
            line->is_history = true;

            char *command = history->commands[history->size - line->history];
            return replace_with_history(line, command);
        }
    }
    return SUCCESS_RETURN;
}

int show_next_history(line_buffer_t *line, history_t *history)
{
    if (line->is_history == true) {
        if (line->history > 1) {
            line->history--;

            char *command = history->commands[history->size - line->history];
            return replace_with_history(line, command);
        } else {
            line->is_history = false;
            line->history = 0;
            line->buffer[0] = '\0';
            line->size = 0;
            print_all(line);
        }
    }
    return SUCCESS_RETURN;
}
