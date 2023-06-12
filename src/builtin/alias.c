/*
** EPITECH PROJECT, 2023
** epitech-shell
** File description:
** alias
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "shell/command.h"
#include "shell/env.h"

static int enlarge_aliases_capacity(sh_env_t *env)
{
    env->alias_capacity += 10;
    env->alias = realloc(env->alias, sizeof(alias_t) * env->alias_capacity);
    if (env->alias == NULL) {
        env->alias_capacity -= 10;
        return 1;
    }

    return 0;
}

static int show_aliases(sh_env_t *env)
{
    for (int i = 0; i < (int) env->alias_size; i++)
        printf("%s=%s\n", env->alias[i].name, env->alias[i].value);

    return 0;
}

int builtin_alias(command_t *command, sh_env_t *env)
{
    if (command->args.size == 1)
        return show_aliases(env);
    if (command->args.size != 3) return 1;

    for (int i = 0; i < (int) env->alias_size; i++) {
        if (strncmp(env->alias[i].name, command->args.argv[1],
        strlen(env->alias[i].name) + 1) == 0) {
            free(env->alias[i].value);
            env->alias[i].value = strdup(command->args.argv[2]);
            return 0;
        }
    }
    if (env->alias_capacity == env->alias_size)
        if (enlarge_aliases_capacity(env) == 1)
            return 1;

    env->alias[env->alias_size].name = strdup(command->args.argv[1]);
    env->alias[env->alias_size].value = strdup(command->args.argv[2]);
    env->alias_size++;
    return 0;
}
