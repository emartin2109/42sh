/*
** EPITECH PROJECT, 2023
** shell
** File description:
** env
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "shell/history.h"

/**
 * @brief Shell environment key-value pair. If the key is NULL, the structure
 * is considered empty.
 */
typedef struct {
    char *key;
    char *value;
    bool local;
} sh_env_kv_t;

/**
 * @brief Alias structure. Contains the name of the alias and its value.
 *
 */
typedef struct {
    char *name;
    char *value;
} alias_t;

/**
 * @brief Shell environement. Includes exit state and environment variables.
 */
typedef struct {
    bool exit;
    int exit_status;
    bool exit_silent;
    sh_env_kv_t *env;
    size_t env_size;
    size_t env_capacity;
    history_t *history;
    alias_t *alias;
    size_t alias_size;
    size_t alias_capacity;
} sh_env_t;

/**
 * @brief Initializes the shell environment.
 *
 * @param envp Environment variables.
 * @return sh_env_t* The initialized shell environment.
 */
sh_env_t *sh_env_init(char **envp);

/**
 * @brief Free the shell environment.
 *
 * @param env The shell environment.
 */
void sh_env_free(sh_env_t *env);

/**
 * @brief Convert environement to an array of strings (envp).
 *
 * @param env The shell environment.
 * @return char** The array of strings.
 */
char **sh_env_to_array(sh_env_t *env);

/**
 * @brief Get the value of an environment variable.
 *
 * @param env The shell environment.
 * @param key The key of the environment variable.
 * @return char* The value of the environment variable (NULL if not found).
 */
char *sh_env_get(sh_env_t *env, const char *key);

/**
 * @brief Set the value of an environment variable. This function will
 * reallocate the environment variables array if needed.
 *
 * @param env The shell environment.
 * @param key The key of the environment variable.
 * @param value The value of the environment variable.
 * @param local Is a local variable.
 * @return int 0 on success, -1 on error.
 */
int sh_env_set(sh_env_t *env, const char *key, const char *value, bool local);

/**
 * @brief Adds a variable to the environment. This does not check if the
 * variable already exists, use `sh_env_set` instead.
 *
 * @param env The shell environment.
 * @param key The key of the environment variable.
 * @param value The value of the environment variable.
 * @param local Is a local variable.
 * @return int 0 on success, -1 on error.
 */
int sh_env_add(sh_env_t *env, const char *key, const char *value, bool local);

/**
 * @brief Unset an environment variable. This will not shrink the environment
 * variables array.
 *
 * @param env The shell environment.
 * @param key The key of the environment variable.
 * @param local Is a local variable.
 */
void sh_env_unset(sh_env_t *env, const char *key, bool local);
