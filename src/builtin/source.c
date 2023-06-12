/*
** EPITECH PROJECT, 2023
** shell
** File description:
** source
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shell/builtin.h"
#include "shell/execute.h"
#include "shell/util.h"

void load_source(char *path, sh_env_t *env, bool is_rc)
{
    FILE *file = fopen(path, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int line_count = 1;

    if (file == NULL) {
        if (is_rc) return;
        fprintf(stderr, "source: %s: No such file or directory.\n", path);
        return;
    }
    while ((read = getline(&line, &len, file)) != -1) {
        command_run(line, env);
        if (env->exit_status != 0)
            fprintf(stderr,
            "source: %s:%d: Error while executing.\n", path, line_count);
        line_count++;
    }
    free(line);
    fclose(file);
}

void rc_loader(sh_env_t *env)
{
    char *home = sh_env_get(env, "HOME");
    if (home == NULL) return;
    char *rc_path = expand_home("~/.42shrc", home);
    if (rc_path == NULL) return;

    load_source(rc_path, env, true);
    free(rc_path);
}

int builtin_source(command_t *command, sh_env_t *env)
{
    if (command->args.argv[1] == NULL) {
        fprintf(stderr, "source: Too few arguments.\n");
        return 1;
    }

    load_source(command->args.argv[1], env, false);

    return 0;
}
