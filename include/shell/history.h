/*
** EPITECH PROJECT, 2023
** shell
** File description:
** history
*/

#pragma once

#include <stddef.h>

/**
 * @brief Shell history structure.
 */
typedef struct {
    char **commands;
    size_t size;
    size_t capacity;
} history_t;

/**
 * @brief Initializes the shell history.
 *
 * @return history_t* The initialized shell history (NULL on error).
 */
history_t *init_history(void);

/**
 * @brief Push a command to the shell history.
 *
 * @param history The shell history.
 * @param command The command to push (will be duplicated)
 * @return int 0 on success, 1 on error.
 */
int push_history(history_t *history, char *command);

/**
 * @brief Free the shell history.
 *
 * @param history The shell history.
 */
void free_history(history_t *history);

/**
 * @brief Load history from history file (~/.42sh_history). This function does
 * not fail if the history file does not exist or cannot be opened.
 *
 * @param history The shell history.
 * @param home The home directory of the user.
 * @return int 0 on success, 1 on error.
 */
int load_history(history_t *history, char *home);

/**
 * @brief Write history to history file (~/.42sh_history). This function does
 * not fail if the history file cannot be opened.
 *
 * @param history The shell history.
 * @param home The home directory of the user.
 * @return int 0 on success, 1 on error.
 */
int write_history(history_t *history, char *home);
