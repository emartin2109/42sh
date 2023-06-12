/*
** EPITECH PROJECT, 2023
** shell
** File description:
** history
*/

#include <stdio.h>

#include "shell/builtin.h"

int builtin_history(command_t *command, sh_env_t *env)
{
    for (size_t i = 0; i < env->history->size; i++) {
        dprintf(command->out.fd, "%s\n", env->history->commands[i]);
    }

    return 0;
}
