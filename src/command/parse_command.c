/*
** EPITECH PROJECT, 2023
** shell
** File description:
** parse_command
*/

#include "shell/string.h"
#include "shell/command.h"

static command_res_t command_parse_inner(token_list_t *tokens, size_t *index,
    command_t *command)
{
    token_t *token = &tokens->tokens[*index];
    if (token->type == TOK_PIPE || token->type == TOK_SEMICOLON
        || token->type == TOK_AND || token->type == TOK_OR)
        return CMD_RES_OK;

    if (token->type == TOK_WORD || token->type == TOK_COMMAND) {
        command_push_arg(command, str_copy(token->value, 0));
        *index += 1;
    }

    if (token->type == TOK_REDIRECT_IN)
        return parse_redirect_in(tokens, index, command);
    if (token->type == TOK_REDIRECT_OUT)
        return parse_redirect_out(tokens, index, command);
    if (token->type == TOK_APPEND_OUT)
        return parse_append_out(tokens, index, command);
    if (token->type == TOK_APPEND_IN)
        return parse_append_in(tokens, index, command);

    return CMD_RES_OK;
}

command_res_t command_parse(token_list_t *tokens, size_t *index,
    command_t *command)
{
    while (*index < tokens->size) {
        token_t *token = &tokens->tokens[*index];
        if (token->type == TOK_PIPE
            || token->type == TOK_SEMICOLON
            || token->type == TOK_AND
            || token->type == TOK_OR)
            return CMD_RES_OK;

        command_res_t res = command_parse_inner(tokens, index, command);
        if (res != CMD_RES_OK)
            return res;
    }

    if (command->args.size == 0)
        return CMD_RES_EMPTY;
    return CMD_RES_OK;
}
