/*
** EPITECH PROJECT, 2023
** shell
** File description:
** execute
*/

#pragma once

#include <sys/types.h>

#include "shell/env.h"
#include "shell/command.h"

/**
 * @brief Execute a command.
 *
 * @param command The command to execute.
 * @param env The environment.
 */
void command_run(char *command, sh_env_t *env);

/**
 * @brief Execute a parsed command.
 *
 * @param command Parsed command to execute
 * @param env Shell environment
 */
pid_t command_exec(command_t *command, command_group_t *group, sh_env_t *env);

/**
 * @brief Bind stdin and stdout file descriptors of the current process to
 * the given file descriptors.
 *
 * @param command Command containing the file descriptors.
 * @return int 0 if success, -1 otherwise.
 */
int command_bind_fd(command_t *command, command_group_t *group);

/**
 * @brief Run a command group.
 *
 * @param group Group to run.
 * @param env Shell environment.
 * @return int Exit status of the group.
 */
int run_command_group(command_group_t *group, sh_env_t *env);

/**
 * @brief Wait for a process to complete.
 *
 * @param pid Process ID.
 * @param env Shell environment.
 * @return int Exit status of the process.
 */
void wait_process(pid_t pid, sh_env_t *env);
