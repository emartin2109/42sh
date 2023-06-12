/*
** EPITECH PROJECT, 2023
** epitech-shell
** File description:
** aliasses
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "shell/env.h"
#include "shell/execute.h"
#include "shell/command.h"
#include "shell/macros.h"
#include "shell/tokenizer.h"
#include "shell/resolve.h"

static void add_to_new_tokens(int token_pos, token_list_t *tokens,
token_list_t *alias_tokens, token_list_t *new_tokens)
{
    int new_token_pos = 0;

    for (int i = 0; i < token_pos; i ++) {
        new_tokens->tokens[new_token_pos].type = tokens->tokens[i].type;
        new_tokens->tokens[new_token_pos].value = tokens->tokens[i].value;
        new_token_pos ++;
    }
    for (int i = 0; i < (int) alias_tokens->size; i ++) {
        new_tokens->tokens[new_token_pos].type = alias_tokens->tokens[i].type;
        new_tokens->tokens[new_token_pos].value = alias_tokens->tokens[i].value;
        new_token_pos ++;
    }
    for (int i = token_pos + 1; i < (int) tokens->size; i ++) {
        new_tokens->tokens[new_token_pos].type = tokens->tokens[i].type;
        new_tokens->tokens[new_token_pos].value = tokens->tokens[i].value;
        new_token_pos ++;
    }
}

static token_list_t *insert_alias_to_tokens(token_list_t *alias_tokens,
token_list_t *tokens, int token_pos)
{
    token_list_t *new_tokens = malloc(sizeof(token_list_t));
    if (new_tokens == NULL)
        return NULL;
    new_tokens->capacity = alias_tokens->capacity + tokens->capacity;
    new_tokens->size = alias_tokens->size + tokens->size - 1;
    new_tokens->tokens = malloc(sizeof(token_t) * new_tokens->size);
    if (new_tokens->tokens == NULL)
        return NULL;

    add_to_new_tokens(token_pos, tokens, alias_tokens, new_tokens);

    free(tokens->tokens[token_pos].value);
    free(tokens->tokens);
    free(tokens);
    free(alias_tokens->tokens);
    free(alias_tokens);

    return new_tokens;
}

static token_list_t *compare_with_aliases(token_list_t *tokens, sh_env_t *env,
int i)
{
    for (int x = 0; x < (int) env->alias_size; x++) {
        if (strncmp(env->alias[x].name, tokens->tokens[i].value,
        (int) strlen(env->alias[x].name) + 1) == 0)
            tokens = insert_alias_to_tokens(tokenize
            (env->alias[x].value), tokens, i);
        if (tokens == NULL)
            return NULL;
    }

    return tokens;
}

token_list_t *check_for_aliases(token_list_t *tokens, sh_env_t *env)
{
    if (tokens == NULL || env == NULL)
        return NULL;

    for (int i = 0; i < (int) tokens->size; i++) {
        if (tokens->tokens[i].type != TOK_COMMAND)
            continue;
        tokens = compare_with_aliases(tokens, env, i);
        if (tokens == NULL)
            return NULL;
    }

    return tokens;
}
