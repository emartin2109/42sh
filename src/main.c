/*
** EPITECH PROJECT, 2023
** shell
** File description:
** main
*/

#include <unistd.h>
#include <string.h>

#include "shell/builtin.h"
#include "shell/macros.h"
#include "shell/prompt.h"
#include "shell/env.h"

int main(int argc, char **argv, char **envp)
{
    (void) argc;
    (void) argv;

    sh_env_t *env = sh_env_init(envp);
    char *no_color = sh_env_get(env, "NO_COLOR");
    int exit_status = SUCCESS_EXIT;

    rc_loader(env);

    if (isatty(STDIN)) {
        if (no_color != NULL && no_color[0] != '\0')
            exit_status = basic_interactive_prompt(env);
        else
            exit_status = interactive_prompt(env);
    } else {
        exit_status = non_interactive_command(env);
    }

    sh_env_free(env);
    return exit_status;
}
