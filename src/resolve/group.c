/*
** EPITECH PROJECT, 2023
** shell
** File description:
** group
*/

#include "shell/builtin.h"
#include "shell/resolve.h"
#include "shell/macros.h"
#include "shell/string.h"

static int resolve_command(command_t *command, sh_env_t *env)
{
    if (command == NULL) return ERROR_RETURN;

    if (expand_args_home(&command->args, env) == ERROR_RETURN)
        return ERROR_RETURN;

    if (is_builtin(command->args.argv[0])) {
        char *path = str_copy(command->args.argv[0], 0);
        command->path = path;
        command->builtin = true;
    } else {
        char *path = resolve_path(command->args.argv[0], env);
        command->path = path;
    }

    return SUCCESS_RETURN;
}

int resolve_command_group(command_group_t *group, sh_env_t *env)
{
    if (group == NULL) return ERROR_RETURN;

    if (resolve_group_fd(group) == ERROR_RETURN)
        return ERROR_RETURN;
    for (size_t i = 0; i < group->size; i++) {
        if (resolve_command(&group->commands[i], env) == ERROR_RETURN)
            return ERROR_RETURN;
    }

    return SUCCESS_RETURN;
}
