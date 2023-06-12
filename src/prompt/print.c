/*
** EPITECH PROJECT, 2023
** shell
** File description:
** print
*/

#include <stdio.h>

#include "shell/prompt.h"

void print_from_cursor(line_buffer_t *line)
{
    printf("%s%s", A_ERASE, line->buffer + line->cursor);
    for (size_t i = 0; i < line->size - line->cursor; i++)
        printf(A_MLEFT);
}

void print_all(line_buffer_t *line)
{
    move_cursor_left(line, line->cursor);
    printf("%s%s", A_ERASE, line->buffer);
    line->cursor = line->size;
}
