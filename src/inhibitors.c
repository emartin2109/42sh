/*
** EPITECH PROJECT, 2023
** shell
** File description:
** inhibitors
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "shell/inhibitors.h"

static void change_bool_state (bool *state)
{
    if (state == NULL)
        return;
    if (*state == true)
        *state = false;
    else if (*state == false)
        *state = true;
}

char get_escape_sequence (const char backslashed_char)
{
    char result = 6;
    int i = 0;
    while (ESCAPE_SEQUENCE_LIST[i]) {
        if (backslashed_char == ESCAPE_SEQUENCE_LIST[i++])
            result += i;
    }
    if (result == 6)
        result = backslashed_char;
    return result;
}

static void backslash_handler (const char *input, int *j, int *i, char *output)
{
    char new_char;

    if (output == NULL || j == NULL || i == NULL || input == NULL) return;
    new_char = input[*i + 1];
    output[*j] = new_char;
    (*i) += 1;
    (*j) += 1;
    return;
}

char *parse_backslash (char *input)
{
    int i = -1;
    int j = 0;
    bool string_need_to_be_parsed = true;

    if (input == NULL) return NULL;
    char *output = malloc ((strlen(input) + 1) * sizeof(char));
    if (output == NULL) return NULL;
    while (input[++i]) {
        if (input[i] == '\"' || input[i] == '\'')
            change_bool_state(&string_need_to_be_parsed);
        if (input[i] == '\\' && string_need_to_be_parsed) {
            backslash_handler(input, &j, &i, output);
            continue;
        }
        if (!string_need_to_be_parsed || (input[i] != '\\' && input[i] != '`'))
            output[j++] = input[i];
    }
    output[j] = '\0';
    free(input);
    return output;
}
