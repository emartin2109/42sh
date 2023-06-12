/*
** EPITECH PROJECT, 2023
** shell
** File description:
** bind
*/

#include <unistd.h>

#include "shell/command.h"
#include "shell/execute.h"
#include "shell/macros.h"

int command_bind_fd(command_t *command, command_group_t *group)
{
    if (command->in.type != FD_NULL && dup2(command->in.fd, STDIN) == -1)
        return ERROR_RETURN;
    if (command->out.type != FD_NULL && dup2(command->out.fd, STDOUT) == -1)
        return ERROR_RETURN;

    for (size_t i = 0; i < group->size; i++) {
        if (group->commands[i].in.type == FD_PIPE)
            close(group->commands[i].in.fd);
        if (group->commands[i].out.type == FD_PIPE)
            close(group->commands[i].out.fd);
    }

    return SUCCESS_RETURN;
}
