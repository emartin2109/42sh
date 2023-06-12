/*
** EPITECH PROJECT, 2023
** shell
** File description:
** line
*/

#include <stdio.h>

#include "shell/history.h"
#include "shell/macros.h"
#include "shell/prompt.h"
#include "shell/util.h"

static int handle_ansi_escape(line_buffer_t *line, history_t *history)
{
    if (getc(stdin) != '[') return SUCCESS_RETURN;
    int code = getc(stdin);

    if (code == K_UP) return show_prev_history(line, history);
    if (code == K_DOWN) return show_next_history(line, history);

    if (code == K_LEFT) move_cursor_left(line, 1);
    if (code == K_RIGHT) move_cursor_right(line, 1);
    if (code == K_START) move_cursor_left(line, line->cursor);
    if (code == K_END) move_cursor_right(line, line->size - line->cursor);

    if (code == K_SUPPR[0] && getc(stdin) == K_SUPPR[1]
        && line->cursor < line->size) {
        move_cursor_right(line, 1);
        delete_char(line);
    }

    return SUCCESS_RETURN;
}

prompt_res_t interactive_prompt_line(line_buffer_t *line, history_t *history)
{
    line_buffer_reset(line);

    while (true) {
        int input = getc(stdin);

        if (input == K_EOT) return P_EXIT;
        if (input == '\n') break;
        if (input == ANSI_ESC) {
            handle_ansi_escape(line, history);
            continue;
        }
        if (input == A_DEL) {
            delete_char(line);
            continue;
        }
        if (print_char(line, (char) input) == ERROR_RETURN)
            return P_ERROR;
    }
    return P_OK;
}
