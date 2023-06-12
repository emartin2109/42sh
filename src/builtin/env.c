/*
** EPITECH PROJECT, 2023
** shell
** File description:
** env
*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "shell/macros.h"
#include "shell/builtin.h"
#include "shell/util.h"
#include "shell/string.h"

int builtin_env(command_t *command, sh_env_t *env)
{
    size_t args_len = command->args.size - 1;

    if (args_len > 0) {
        fprintf(stderr, "env: '%s'", command->args.argv[1]);
        fprintf(stderr, ": No such file or directory\n");
        return 127;
    }

    for (size_t i = 0; i < env->env_size; i++) {
        sh_env_kv_t var = env->env[i];
        if (var.key == NULL || var.local) continue;
        dprintf(command->out.fd, "%s=%s\n", var.key, var.value);
    }

    return 0;
}

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

int builtin_setenv(command_t *command, sh_env_t *env)
{
    size_t args_len = command->args.size - 1;
    if (args_len < 1)
        return builtin_env(command, env);
    if (args_len > 2) {
        fprintf(stderr, "setenv: Too many arguments.\n");
        return 1;
    }
    size_t key_len = strlen(command->args.argv[1]);
    for (size_t i = 0; i < key_len; i++) {
        if (!is_alphanumeric(command->args.argv[1][i])) {
            fprintf(stderr, "setenv: Variable name must contain");
            fprintf(stderr, " alphanumeric characters.\n");
            return 1;
        }
    }
    char *key = command->args.argv[1];
    char *value = args_len == 2 ? command->args.argv[2] : "";
    if (sh_env_set(env, key, value, false) == ERROR_RETURN)
        return 1;
    return 0;
}

int builtin_unsetenv(command_t *command, sh_env_t *env)
{
    size_t args_len = command->args.size - 1;
    if (args_len == 0) {
        fprintf(stderr, "unsetenv: Too few arguments.\n");
        return 1;
    }

    for (size_t i = 1; i < args_len + 1; i++) {
        sh_env_unset(env, command->args.argv[i], false);
    }

    return 0;
}
