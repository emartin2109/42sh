/*
** EPITECH PROJECT, 2023
** shell
** File description:
** expand
*/

#include <stdlib.h>
#include <stdio.h>

#include "shell/resolve.h"
#include "shell/macros.h"
#include "shell/util.h"

static int expand_single_home(char **arg, sh_env_t *env)
{
    if (**arg != '~') return SUCCESS_RETURN;

    char *home = sh_env_get(env, "HOME");
    if (home == NULL) {
        fprintf(stderr, "No $home variable set.\n");
        return ERROR_RETURN;
    }

    char *expanded = expand_home(*arg, home);
    free(*arg);
    *arg = expanded;
    return SUCCESS_RETURN;
}

int expand_args_home(command_args_t *args, sh_env_t *env)
{
    for (size_t i = 0; i < args->size; i++) {
        if (expand_single_home(&args->argv[i], env) == ERROR_RETURN)
            return ERROR_RETURN;
    }

    return SUCCESS_RETURN;
}
