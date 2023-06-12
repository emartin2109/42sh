/*
** EPITECH PROJECT, 2023
** shell
** File description:
** group
*/

#include <stdlib.h>
#include <unistd.h>

#include "shell/command.h"
#include "shell/env.h"
#include "shell/execute.h"
#include "shell/macros.h"
#include "shell/resolve.h"

int run_pipes(command_group_t *group, sh_env_t *env)
{
    pid_t *pids = malloc(sizeof(pid_t) * group->size);
    if (pids == NULL) return ERROR_RETURN;

    for (size_t i = 0; i < group->size; i++) {
        pids[i] = command_exec(&group->commands[i], group, env);
    }

    for (size_t i = 0; i < group->size; i++) {
        if (group->commands[i].in.type == FD_PIPE)
            close(group->commands[i].in.fd);
        if (group->commands[i].out.type == FD_PIPE)
            close(group->commands[i].out.fd);
    }

    for (size_t i = 0; i < group->size; i++) {
        wait_process(pids[i], env);
    }

    free(pids);
    return SUCCESS_RETURN;
}

int run_command_group(command_group_t *group, sh_env_t *env)
{
    if (group == NULL) return ERROR_RETURN;
    if (resolve_command_group(group, env) == ERROR_RETURN) return ERROR_RETURN;

    if (group->size == 1) {
        command_exec(&group->commands[0], group, env);
    } else {
        if (run_pipes(group, env) == ERROR_RETURN) return ERROR_RETURN;
    }

    close_group_fd(group);
    return SUCCESS_RETURN;
}
