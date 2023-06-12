/*
** EPITECH PROJECT, 2023
** shell
** File description:
** execute
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#include "shell/execute.h"
#include "shell/builtin.h"
#include "shell/command.h"
#include "shell/macros.h"
#include "shell/string.h"
#include "shell/util.h"

static void child_exec(command_t *command, command_group_t *group,
sh_env_t *env)
{
    char **envp = sh_env_to_array(env);
    if (envp == NULL) return;
    if (command_bind_fd(command, group) == ERROR_RETURN) return;
    if (execve(command->path, command->args.argv, envp) == -1) {
        env->exit_status = 1;
        if (errno == ENOENT) {
            fprintf(stderr, "%s: Command not found.", command->path);
        } else {
            print_error(command->path, errno, false);
        }
        if (errno == ENOEXEC) {
            fprintf(stderr, " Wrong architecture.");
            env->exit_status = 126;
        }
        fprintf(stderr, "\n");
    }
    mem_free_array(envp);
    env->exit_silent = true;
    env->exit = true;
}

static void signal_error(int wstatus, sh_env_t *env)
{
    int signal = WTERMSIG(wstatus);
    if (signal == SIGFPE) {
        fprintf(stderr, "Floating exception");
    } else {
        char *signal_name = strsignal(signal);
        fprintf(stderr, "%s", signal_name);
    }

    if (WCOREDUMP(wstatus))
        fprintf(stderr, " (core dumped)");

    fprintf(stderr, "\n");
    env->exit_status = 128 + signal;
}

void wait_process(pid_t pid, sh_env_t *env)
{
    if (pid == -1) return;
    int wstatus;
    while (1) {
        if (waitpid(pid, &wstatus, 0) == -1) {
            perror("waitpid");
            return;
        }

        if (WIFEXITED(wstatus)) {
            env->exit_status = WEXITSTATUS(wstatus);
            return;
        }
        if (WIFSIGNALED(wstatus)) {
            signal_error(wstatus, env);
            return;
        }
    }
}

pid_t command_exec(command_t *command, command_group_t *group, sh_env_t *env)
{
    if (command == NULL) return ERROR_EXIT;
    if (command->path == NULL || *command->path == '\0') return ERROR_EXIT;

    if (command->builtin) {
        builtin_exec(command, env);
        return -1;
    }

    pid_t child_pid = fork();

    if (child_pid == 0)
        child_exec(command, group, env);
    if (child_pid > 0) {
        if (group->size <= 1) wait_process(child_pid, env);
        return (child_pid);
    }
    if (child_pid == -1)
        perror("fork");

    return -1;
}
