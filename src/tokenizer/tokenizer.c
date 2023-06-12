/*
** EPITECH PROJECT, 2023
** shell
** File description:
** tokenizer
*/

#include <stdlib.h>

#include "shell/tokenizer.h"
#include "shell/macros.h"
#include "shell/util.h"
#include "shell/inhibitors.h"
#include "stdio.h"

static void print_token_error(token_result_t res)
{
    if (res == TOK_RES_UNMATCHED_SIMPLE_QUOTE)
        fprintf(stderr, "Unmatched \"'\".\n");
    if (res == TOK_RES_UNMATCHED_DOUBLE_QUOTE)
        fprintf(stderr, "Unmatched '\"'.\n");
}

token_list_t *tokenize(const char *input)
{
    token_list_t *tokens = malloc(sizeof(token_list_t));
    if (tokens == NULL) return NULL;
    *tokens = (token_list_t) {malloc(sizeof(token_t) * 32), 0, 32};
    if (tokens->tokens == NULL) return NULL;

    while (*input != '\0') {
        token_t tok = {0};
        token_result_t res = next_token(&input, &tok);
        if (res == TOK_RES_END) break;
        if (res != TOK_RES_OK) {
            print_token_error(res);
            token_list_free(tokens);
            return NULL;
        }
        tok.value = parse_backslash(tok.value);
        if (token_list_push(tokens, tok) == ERROR_RETURN) return NULL;
    }

    process_commands(tokens);
    return tokens;
}

int token_list_push(token_list_t *tokens, token_t token)
{
    if (token.value == NULL) return ERROR_RETURN;

    if (tokens->size == tokens->capacity) {
        tokens->capacity *= 2;
        tokens->tokens = realloc(tokens->tokens,
            sizeof(token_t) * tokens->capacity);
        if (tokens->tokens == NULL) return ERROR_RETURN;
    }
    tokens->tokens[tokens->size++] = token;
    return SUCCESS_RETURN;
}

void token_list_free(token_list_t *tokens)
{
    for (size_t i = 0; i < tokens->size; i++)
        free(tokens->tokens[i].value);
    free(tokens->tokens);
    free(tokens);
}
