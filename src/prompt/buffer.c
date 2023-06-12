/*
** EPITECH PROJECT, 2023
** shell
** File description:
** buffer
*/

#include <stddef.h>
#include <stdlib.h>

#include "shell/macros.h"
#include "shell/prompt.h"

static const size_t BUFFER_DEFAULT_CAP = 64;

line_buffer_t *line_buffer_init(void)
{
    line_buffer_t *line = calloc(1, sizeof(line_buffer_t));
    if (line == NULL) return NULL;

    line->capacity = BUFFER_DEFAULT_CAP;
    line->buffer = calloc(BUFFER_DEFAULT_CAP, sizeof(char));
    if (line->buffer == NULL) {
        free(line);
        return NULL;
    }

    return line;
}

void free_line_buffer(line_buffer_t *line)
{
    if (line == NULL) return;
    free(line->buffer);
    free(line);
}

int line_buffer_add(line_buffer_t *line, char c)
{
    if (line->size + 1 >= line->capacity) {
        line->capacity *= 2;
        line->buffer = realloc(line->buffer, line->capacity + 1);
        if (line->buffer == NULL) return ERROR_RETURN;
    }

    for (size_t i = line->size; i > line->cursor; i--) {
        line->buffer[i] = line->buffer[i - 1];
    }

    line->buffer[line->cursor] = c;
    line->size++;
    line->cursor++;
    line->buffer[line->size] = '\0';

    return SUCCESS_RETURN;
}

void line_buffer_remove(line_buffer_t *line)
{
    if (line->cursor == 0 || line->size == 0)
        return;

    for (size_t i = line->cursor; i < line->size; i++) {
        line->buffer[i - 1] = line->buffer[i];
    }

    line->size--;
    line->cursor--;
    line->buffer[line->size] = '\0';
}

int line_buffer_reset(line_buffer_t *line)
{
    line->size = 0;
    line->cursor = 0;
    line->history = 0;
    line->is_history = false;
    line->buffer[0] = '\0';

    return SUCCESS_RETURN;
}
