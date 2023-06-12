/*
** EPITECH PROJECT, 2023
** shell
** File description:
** update
*/

#include <stdlib.h>
#include <string.h>

#include "shell/env.h"
#include "shell/macros.h"
#include "shell/util.h"
#include "shell/string.h"

char *sh_env_get(sh_env_t *env, const char *key)
{
    for (size_t i = 0; i < env->env_size; i++) {
        if (strcmp(env->env[i].key, key) == 0) {
            return env->env[i].value;
        }
    }
    return NULL;
}

int sh_env_set(sh_env_t *env, const char *key, const char *value, bool local)
{
    for (size_t i = 0; i < env->env_size; i++) {
        if (env->env[i].key == NULL || env->env[i].value == NULL
            || key == NULL) continue;
        if (local && !env->env[i].local) continue;

        if (strcmp(env->env[i].key, key) == 0) {
            free(env->env[i].value);
            env->env[i].value = str_copy(value, 0);
            return env->env[i].value == NULL ? ERROR_RETURN : SUCCESS_RETURN;
        }
    }

    if (sh_env_add(env, key, value, local) == ERROR_RETURN)
        return ERROR_RETURN;

    return SUCCESS_RETURN;
}

int sh_env_add(sh_env_t *env, const char *key, const char *value, bool local)
{
    if (env->env_size == env->env_capacity) {
        env->env_capacity += 5;
        size_t new_size = env->env_capacity * sizeof(sh_env_kv_t);
        env->env = realloc(env->env, new_size);
        if (env->env == NULL) return ERROR_RETURN;
    }

    env->env[env->env_size].key = str_copy(key, 0);
    env->env[env->env_size].value = str_copy(value, 0);
    env->env[env->env_size].local = local;

    if (env->env[env->env_size].key == NULL ||
        env->env[env->env_size].value == NULL)
            return ERROR_RETURN;

    env->env_size++;
    return SUCCESS_RETURN;
}

void sh_env_unset(sh_env_t *env, const char *key, bool local)
{
    for (size_t i = 0; i < env->env_size; i++) {
        if (env->env[i].key == NULL || env->env[i].value == NULL
            || key == NULL) continue;
        if ((local && !env->env[i].local)) continue;

        if (strcmp(env->env[i].key, key) == 0) {
            free(env->env[i].key);
            free(env->env[i].value);
            env->env[i] = (sh_env_kv_t) {NULL, NULL, false};
            return;
        }
    }
}
