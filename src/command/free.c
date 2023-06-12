/*
** EPITECH PROJECT, 2023
** shell
** File description:
** free
*/

#include <stdlib.h>

#include "shell/command.h"

static void command_free(command_t *command)
{
    for (size_t i = 0; i < command->args.size; i++) {
        free(command->args.argv[i]);
    }
    if (command->path != NULL) free(command->path);
    free(command->args.argv);
}

static void command_group_free(command_group_t *group)
{
    for (size_t i = 0; i < group->size; i++) {
        command_free(&group->commands[i]);
    }
    free(group->commands);
}

void command_exec_free(command_exec_t *exec)
{
    for (size_t i = 0; i < exec->size; i++) {
        command_group_free(&exec->groups[i]);
    }
    free(exec->groups);
    free(exec);
}
