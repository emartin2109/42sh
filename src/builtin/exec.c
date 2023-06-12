/*
** EPITECH PROJECT, 2023
** shell
** File description:
** exec
*/

#include <stddef.h>
#include <string.h>

#include "shell/builtin.h"
#include "shell/macros.h"
#include "shell/string.h"
#include "shell/local.h"

const sh_builtin_t BUILTIN_COMMANDS[] = {
    {"cd", builtin_cd},
    {"env", builtin_env},
    {"setenv", builtin_setenv},
    {"unsetenv", builtin_unsetenv},
    {"exit", builtin_exit},
    {"set", builtin_local_set},
    {"unset", builtin_local_unset},
    {"history", builtin_history},
    {"source", builtin_source},
    {"alias", builtin_alias},
};

const size_t BUILTIN_COUNT = sizeof(BUILTIN_COMMANDS) / sizeof(sh_builtin_t);

bool is_builtin(char *path)
{
    for (size_t i = 0; i < BUILTIN_COUNT; i++) {
        if (strcmp(path, BUILTIN_COMMANDS[i].name) == 0)
            return true;
    }
    return false;
}

void builtin_exec(command_t *command, sh_env_t *env)
{
    int status = 0;

    for (size_t i = 0; i < BUILTIN_COUNT; i++) {
        if (strcmp(command->path, BUILTIN_COMMANDS[i].name) == 0)
            status = BUILTIN_COMMANDS[i].exec(command, env);
    }

    env->exit_status = status;
}
