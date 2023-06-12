/*
** EPITECH PROJECT, 2023
** shell
** File description:
** resolver
*/

#include <stdlib.h>
#include <unistd.h>

#include "shell/resolve.h"
#include "shell/builtin.h"
#include "shell/string.h"
#include "shell/util.h"

static char *resolve_directory(char *path, char *directory)
{
    char *normalized_dir = normalize_directory(directory);
    char *resolve_path = str_concat(normalized_dir, path, NULL);
    free(normalized_dir);

    if (access(resolve_path, X_OK) == 0)
        return resolve_path;

    free(resolve_path);
    return NULL;
}

static char *resolve_from_env(char *path, sh_env_t *env)
{

    char *path_dirs = sh_env_get(env, "PATH");
    if (path_dirs == NULL) return str_copy(path, 0);
    char **parsed_path = str_split(path_dirs, ":");
    if (parsed_path == NULL) return str_copy(path, 0);

    for (size_t i = 0; parsed_path[i] != NULL; i++) {
        char *resolved = resolve_directory(path, parsed_path[i]);
        if (resolved != NULL) {
            mem_free_array(parsed_path);
            return resolved;
        }
    }
    mem_free_array(parsed_path);
    return NULL;
}

char *resolve_path(char *path, sh_env_t *env)
{
    if (path == NULL) return NULL;
    if (*path == '/' || *path == '.' || *path == '\0')
        return str_copy(path, 0);

    char *resolved = resolve_from_env(path, env);
    if (resolved != NULL) {
        return resolved;
    } else {
        return str_copy(path, 0);
    }
}
