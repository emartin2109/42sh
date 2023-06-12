/*
** EPITECH PROJECT, 2023
** shell
** File description:
** prompt
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>

#include "shell/execute.h"
#include "shell/macros.h"
#include "shell/prompt.h"
#include "shell/util.h"

static void print_colored_prompt(sh_env_t *env)
{
    char *path = getcwd(NULL, 0);

    if (path != NULL) {
        fprintf(stdout, C_BLUE "%s " C_RESET, path);
        free(path);
    }

    if (env->exit_status == 0) {
        fprintf(stdout, C_GREEN "[%d] " C_RESET, env->exit_status);
    } else {
        fprintf(stdout, C_RED "[%d] " C_RESET, env->exit_status);
    }

    fprintf(stdout, C_BLUE "$> " C_RESET);
}

static struct termios setup_interactive_prompt(void)
{
    struct termios old_term;
    struct termios term;

    tcgetattr(STDIN_FILENO, &old_term);
    term = old_term;
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    return old_term;
}

int interactive_prompt(sh_env_t *env)
{
    line_buffer_t *line = line_buffer_init();
    if (line == NULL) return 1;

    while (env->exit == false) {
        print_colored_prompt(env);
        struct termios old_term = setup_interactive_prompt();
        int prompt_result = interactive_prompt_line(line, env->history);
        tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
        if (prompt_result == P_ERROR) return 1;
        if (prompt_result == P_EXIT) {
            env->exit = true;
        } else {
            printf("\n");
            command_run(line->buffer, env);
        }
    }
    free_line_buffer(line);
    if (env->exit_silent == false)
        fprintf(stdout, "exit\n");
    return env->exit_status;
}

int basic_interactive_prompt(sh_env_t *env)
{
    char *input = NULL;
    size_t input_size = 0;

    while (env->exit == false) {
        fprintf(stdout, "$> ");

        if (getline(&input, &input_size, stdin) == -1) {
            env->exit = true;
        } else {
            command_run(input, env);
        }
    }

    if (input != NULL)
        free(input);

    if (env->exit_silent == false)
        fprintf(stdout, "exit\n");
    return env->exit_status;
}

int non_interactive_command(sh_env_t *env)
{
    char *input = NULL;
    size_t input_size = 0;

    while (env->exit == false) {
        if (getline(&input, &input_size, stdin) == -1) {
            env->exit = true;
        } else {
            command_run(input, env);
        }
    }

    if (input != NULL)
        free(input);
    return env->exit_status;
}
