/*
** EPITECH PROJECT, 2023
** shell
** File description:
** env
*/

#include <stdbool.h>
#include <stdlib.h>

#include "shell/history.h"
#include "shell/macros.h"
#include "shell/env.h"
#include "shell/string.h"

static size_t envp_size(char **envp)
{
    size_t size = 0;
    while (envp[size] != NULL) size++;

    return size;
}

static sh_env_kv_t *envp_parse(char **envp, size_t size)
{
    if (size == 0) return NULL;
    sh_env_kv_t *env = malloc(sizeof(sh_env_kv_t) * size);
    if (env == NULL) return NULL;

    for (size_t i = 0; i < size; i++) {
        char **kv = str_split_once(envp[i], "=");
        if (kv == NULL) return NULL;

        env[i] = (sh_env_kv_t) {kv[0], kv[1], false};
        free(kv);
    }

    return env;
}

sh_env_t *sh_env_init(char **envp)
{
    sh_env_t *env = calloc(1, sizeof(sh_env_t));
    history_t *history = init_history();
    if (env == NULL || history == NULL) return NULL;
    size_t size = envp_size(envp);
    sh_env_kv_t *kv = envp_parse(envp, size);

    env->env = kv;
    env->env_size = size;
    env->env_capacity = size;
    env->history = history;

    if (load_history(env->history, sh_env_get(env, "HOME"))
        == ERROR_RETURN) return NULL;

    return env;
}

void sh_env_free(sh_env_t *env)
{
    for (size_t i = 0; i < env->env_size; i++) {
        free(env->env[i].key);
        free(env->env[i].value);
    }
    for (size_t i = 0; i < env->alias_size; i++) {
        free(env->alias[i].name);
        free(env->alias[i].value);
    }

    free(env->env);
    free(env->alias);
    free_history(env->history);
    free(env);
}

char **sh_env_to_array(sh_env_t *env)
{
    char **envp = malloc(sizeof(char *) * (env->env_size + 1));
    if (envp == NULL) return NULL;

    for (size_t i = 0; i < env->env_size; i++) {
        envp[i] = str_concat(env->env[i].key, env->env[i].value, "=");
        if (envp[i] == NULL) return NULL;
    }
    envp[env->env_size] = NULL;

    return envp;
}
