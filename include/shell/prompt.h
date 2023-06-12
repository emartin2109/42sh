/*
** EPITECH PROJECT, 2023
** shell
** File description:
** prompt
*/

#pragma once

#include "shell/env.h"

/* PROMPTS */

/**
 * @brief Display interactive prompt.
 *
 * @param env Shell environment.
 * @return int Shell exit status.
 */
int interactive_prompt(sh_env_t *env);

/**
 * @brief Display basic interactive prompt (no colors / cursor movement).
 *
 * @param env Shell environment.
 * @return int Shell exit status.
 */
int basic_interactive_prompt(sh_env_t *env);

/**
 * @brief Execute command in non-interactive mode.
 *
 * @param env Shell environment.
 * @return int Shell exit status.
 */
int non_interactive_command(sh_env_t *env);

/* ANSI ESCAPE CODES */

#define ANSI_ESC     '\033'

#define A_DEL     '\177'
#define A_MLEFT   "\033[D"
#define A_MRIGHT  "\033[C"
#define A_ERASE   "\033[K"

#define K_EOT     '\004'
#define K_RIGHT   'C'
#define K_LEFT    'D'
#define K_UP      'A'
#define K_DOWN    'B'
#define K_START   'H'
#define K_END     'F'
#define K_SUPPR   "3~"

#define C_RED     "\033[31m"
#define C_GREEN   "\033[32m"
#define C_BLUE    "\033[34m"
#define C_RESET   "\033[0m"

/* LINE BUFFER */

typedef struct {
    char *buffer;
    size_t cursor; //< position of the cursor in the buffer
    size_t history; //< index of the current position in history (0 = current)
    size_t size;
    size_t capacity;
    bool is_history; //< true if the current line is a history command
} line_buffer_t;

/**
 * @brief Initialize a line buffer.
 *
 * @return line_buffer_t* Line buffer (NULL on error)
 */
line_buffer_t *line_buffer_init(void);

/**
 * @brief Add a character to the line buffer at the cursor position and move the
 * cursor to the right.
 *
 * @param line Line buffer.
 * @param c Character to add.
 * @return int 0 on success, -1 on error.
 */
int line_buffer_add(line_buffer_t *line, char c);

/**
 * @brief Remove a character from the line buffer at the cursor position and
 * move the cursor to the left.
 *
 * @param line Line buffer.
 */
void line_buffer_remove(line_buffer_t *line);

/**
 * @brief Reset the line buffer and cursor position.
 *
 * @param line Line buffer.
 * @return int 0 on success, -1 on error.
 */
int line_buffer_reset(line_buffer_t *line);

/**
 * @brief Free a line buffer.
 *
 * @param line Line buffer to free.
 */
void free_line_buffer(line_buffer_t *line);

/* LINE EDITING */

typedef enum {
    P_OK,
    P_ERROR,
    P_EXIT,
} prompt_res_t;

/**
 * @brief Read a line from stdin with interactive editing.
 *
 * @param line Line buffer.
 * @param history Shell history.
 * @return int 0 on success, -1 on error.
 */
prompt_res_t interactive_prompt_line(line_buffer_t *line, history_t *history);

/**
 * @brief Print a character to stdout and add it to the line buffer.
 *
 * @param line Line buffer.
 * @param input Character to print.
 * @return int 0 on success, -1 on error.
 */
int print_char(line_buffer_t *line, char input);

/**
 * @brief Delete the last character from the line buffer and from stdout.
 *
 * @param line Line buffer.
 */
void delete_char(line_buffer_t *line);

/**
 * @brief Move the cursor to the right.
 *
 * @param line Line buffer.
 * @param n Number of characters to move.
 */
void move_cursor_right(line_buffer_t *line, size_t n);

/**
 * @brief Move the cursor to the left.
 *
 * @param line Line buffer.
 * @param n Number of characters to move.
 */
void move_cursor_left(line_buffer_t *line, size_t n);

/**
 * @brief Print all characters from the cursor position to the end of the line
 * buffer.
 *
 * @param line Line buffer.
 */
void print_from_cursor(line_buffer_t *line);

/**
 * @brief Print all characters in the line buffer and put the cursor at the end.
 *
 * @param line Line buffer.
 */
void print_all(line_buffer_t *line);

/* HISTORY */

/**
 * @brief Show previous command from history, either as full command or as
 * autocompletion.
 *
 * @param line Line buffer.
 * @param history Shell history.
 * @return int 0 on success, -1 on error.
 */
int show_prev_history(line_buffer_t *line, history_t *history);

/**
 * @brief Show next command from history, either as full command or as
 * autocompletion.
 *
 * @param line Line buffer.
 * @param history Shell history.
 * @return int 0 on success, -1 on error.
 */
int show_next_history(line_buffer_t *line, history_t *history);
