/*
** EPITECH PROJECT, 2023
** shell
** File description:
** parse_redirect
*/

#include "shell/command.h"
#include "shell/macros.h"

command_res_t parse_redirect_in(token_list_t *tokens, size_t *index,
    command_t *command)
{
    if (*index + 1 >= tokens->size)
        return CMD_RES_REDIRECT_NAME;

    token_t *token = &tokens->tokens[*index + 1];
    if (token->type != TOK_WORD)
        return CMD_RES_REDIRECT_NAME;
    if (command->in.type != FD_NULL)
        return CMD_RES_REDIRECT_AMBIGUOUS;

    command->in = (fd_t) {FD_FILE, STDIN, token->value};
    *index += 2;
    return CMD_RES_OK;
}

command_res_t parse_redirect_out(token_list_t *tokens, size_t *index,
    command_t *command)
{
    if (*index + 1 >= tokens->size)
        return CMD_RES_REDIRECT_NAME;

    token_t *token = &tokens->tokens[*index + 1];
    if (token->type != TOK_WORD)
        return CMD_RES_REDIRECT_NAME;
    if (command->out.type != FD_NULL)
        return CMD_RES_REDIRECT_AMBIGUOUS;

    command->out = (fd_t) {FD_FILE, STDOUT, token->value};
    *index += 2;
    return CMD_RES_OK;
}

command_res_t parse_append_out(token_list_t *tokens, size_t *index,
    command_t *command)
{
    if (*index + 1 >= tokens->size)
        return CMD_RES_REDIRECT_NAME;

    token_t *token = &tokens->tokens[*index + 1];
    if (token->type != TOK_WORD)
        return CMD_RES_REDIRECT_NAME;
    if (command->out.type != FD_NULL)
        return CMD_RES_REDIRECT_AMBIGUOUS;

    command->out = (fd_t) {FD_APPEND, STDOUT, token->value};
    *index += 2;
    return CMD_RES_OK;
}

command_res_t parse_append_in(token_list_t *tokens, size_t *index,
    command_t *command)
{
    (void) command;

    if (*index + 1 >= tokens->size)
        return CMD_RES_REDIRECT_NAME;

    token_t *token = &tokens->tokens[*index + 1];
    if (token->type != TOK_WORD)
        return CMD_RES_REDIRECT_NAME;

    *index += 2;
    return CMD_RES_OK;
}
