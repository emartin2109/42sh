/*
** EPITECH PROJECT, 2023
** shell
** File description:
** token_syntax
*/

#include "shell/tokenizer.h"
#include "shell/string.h"

void process_commands(token_list_t *tokens)
{
    for (size_t i = 0; i < tokens->size; i++) {
        token_t *token = &tokens->tokens[i];
        token_t *prev = i > 0 ? &tokens->tokens[i - 1] : NULL;

        if (token->type != TOK_WORD)
            continue;
        if (prev == NULL || prev->type == TOK_PIPE
            || prev->type == TOK_SEMICOLON)
            token->type = TOK_COMMAND;
    }
}

token_result_t tokenize_redirection(const char **input, token_t *token)
{
    if (**input == '<' && (*input)[1] == '<') {
        *token = (token_t) {TOK_APPEND_IN, str_copy("<<", 2)};
        *input += 2;
        return TOK_RES_OK;
    }
    if (**input == '>' && (*input)[1] == '>') {
        *token = (token_t) {TOK_APPEND_OUT, str_copy(">>", 2)};
        *input += 2;
        return TOK_RES_OK;
    }
    if (**input == '<') {
        *token = (token_t) {TOK_REDIRECT_IN, str_copy("<", 1)};
        *input += 1;
    }
    if (**input == '>') {
        *token = (token_t) {TOK_REDIRECT_OUT, str_copy(">", 1)};
        *input += 1;
    }
    return TOK_RES_OK;
}

token_result_t tokenize_ampersand(const char **input, token_t *token)
{
    if (**input == '&' && (*input)[1] == '&') {
        *token = (token_t) {TOK_AND, str_copy("&&", 2)};
        *input += 2;
    }

    return TOK_RES_OK;
}

token_result_t tokenize_pipe_semicolon(const char **input, token_t *token)
{
    if (**input == '|' && (*input)[1] == '|') {
        token->type = TOK_OR;
        token->value = str_copy("||", 2);
        *input += 2;
    }
    if (**input == '|') {
        token->type = TOK_PIPE;
        token->value = str_copy("|", 1);
        *input += 1;
    }
    if (**input == ';') {
        token->type = TOK_SEMICOLON;
        token->value = str_copy(";", 1);
        *input += 1;
    }

    return TOK_RES_OK;
}
