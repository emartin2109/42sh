/*
** EPITECH PROJECT, 2023
** shell
** File description:
** command
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "shell/command.h"
#include "shell/macros.h"
#include "shell/string.h"
#include "shell/tokenizer.h"

void print_command_error(command_res_t res)
{
    if (res == CMD_RES_EMPTY)
        fprintf(stderr, "Invalid null command.\n");
    if (res == CMD_RES_REDIRECT_NAME)
        fprintf(stderr, "Missing name for redirect.\n");
    if (res == CMD_RES_REDIRECT_AMBIGUOUS)
        fprintf(stderr, "Ambiguous input redirect.\n");
}

static bool handle_separator(token_list_t *tokens, size_t *index,
    command_group_t **group, command_exec_t *exec)
{
    if (tokens->tokens[*index].type == TOK_PIPE) {
        (*index) += 1;
        return true;
    }
    if (tokens->tokens[*index].type == TOK_SEMICOLON) {
        (*index) += 1;
        *group = command_exec_add_group(exec, F_NULL);
        return true;
    }
    if (tokens->tokens[*index].type == TOK_OR) {
        (*index) += 1;
        *group = command_exec_add_group(exec, F_DOUBLE_PIPE);
        return true;
    }
    if (tokens->tokens[*index].type == TOK_AND) {
        (*index) += 1;
        *group = command_exec_add_group(exec, F_DOUBLE_AMPERSAND);
        return true;
    }
    return false;
}

command_exec_t *parse_command_exec(token_list_t *tokens)
{
    command_exec_t *exec = command_exec_new();
    if (exec == NULL) return NULL;
    command_group_t *group = command_exec_add_group(exec, F_NULL);
    if (group == NULL) return NULL;

    size_t index = 0;
    while (index < tokens->size) {
        if (handle_separator(tokens, &index, &group, exec))
            continue;

        command_t *command = command_group_add_command(group);
        if (command == NULL) return NULL;
        command_res_t res = command_parse(tokens, &index, command);
        if (res != CMD_RES_OK) {
            print_command_error(res);
            command_exec_free(exec);
            return NULL;
        }
    }
    return exec;
}
