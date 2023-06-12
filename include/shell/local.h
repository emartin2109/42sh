/*
** EPITECH PROJECT, 2023
** shell
** File description:
** local
*/

#pragma once

#include "shell/command.h"
#include "shell/env.h"

/**
 * @brief Execute unsetenv builtin command (local).
 *
 * @param command Parsed shell command.
 * @param env Shell environment.
 * @return int Exit status.
 */
int builtin_local_unset(command_t *command, sh_env_t *env);

/**
 * @brief Execute setenv builtin command (local).
 *
 * @param command Parsed shell command.
 * @param env Shell environment.
 * @return int Exit status.
 */
int builtin_local_set(command_t *command, sh_env_t *env);
