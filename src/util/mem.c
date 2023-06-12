/*
** EPITECH PROJECT, 2023
** shell
** File description:
** mem
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "shell/util.h"

size_t mem_array_len(char **array)
{
    size_t len = 0;
    for (size_t i = 0; array[i] != NULL; i++)
        len++;

    return len;
}

void mem_free_array(char **array)
{
    for (size_t i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
