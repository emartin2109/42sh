/*
** EPITECH PROJECT, 2023
** shell
** File description:
** local
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "shell/local.h"
#include "shell/env.h"
#include "shell/command.h"
#include "shell/string.h"
#include "shell/macros.h"

static bool is_alphanumeric(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    if (c >= 'A' && c <= 'Z')
        return true;
    if (c >= 'a' && c <= 'z')
        return true;
    return false;
}

static void print_local_env(sh_env_t *env)
{
    for (size_t i = 0; i < env->env_size; i++) {
        if (env->env[i].key != NULL && env->env[i].value != NULL
            && env->env[i].local)
            printf("%s=%s\n", env->env[i].key, env->env[i].value);
    }
}

static int sh_local_set(sh_env_t *env, size_t i, command_t *command)
{
    char *splited[2] = {NULL, NULL};
    bool malloced = false;

    if (strchr(command->args.argv[i], '=') == NULL) {
        splited[0] = command->args.argv[i];
        splited[1] = "";
    } else {
        char **tmp = str_split_once(command->args.argv[i], "=");
        splited[0] = tmp[0];
        splited[1] = tmp[1];
        malloced = true;
        free(tmp);
    }
    if (sh_env_set(env, splited[0], splited[1], true) == ERROR_RETURN)
        return ERROR_RETURN;
    if (malloced) {
        free(splited[0]);
        free(splited[1]);
    }
    return SUCCESS_RETURN;
}

int builtin_local_set(command_t *command, sh_env_t *env)
{
    if (command->args.size == 1) {
        print_local_env(env);
        return SUCCESS_RETURN;
    }

    for (size_t i = 1; i < command->args.size; i++) {
        if (!is_alphanumeric(command->args.argv[i][0])) {
            fprintf(stderr, "setenv: Variable name must contain");
            fprintf(stderr, " alphanumeric characters.\n");
            return 1;
        }

        if (sh_local_set(env, i, command) == ERROR_RETURN)
            return ERROR_RETURN;
    }

    return SUCCESS_RETURN;
}

int builtin_local_unset(command_t *command, sh_env_t *env)
{
    for (size_t i = 1; i < command->args.size; i++) {
        sh_env_unset(env, command->args.argv[i], true);
    }

    return SUCCESS_RETURN;
}
