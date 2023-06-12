/*
** EPITECH PROJECT, 2023
** shell
** File description:
** tokenizer
*/

#include <criterion/criterion.h>

#include "shell/tokenizer.h"

Test(tokenizer, single_word) {
    char *input = "ls";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 1);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");
}

Test(tokenizer, multiple_words) {
    char *input = "ls -l";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 2);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[1].value, "-l");
}

Test(tokenizer, empty) {
    char *input = "";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 0);
}

Test(tokenizer, spaces_between) {
    char *input = "ls   -l";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 2);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[1].value, "-l");
}

Test(tokenizer, spaces_leading) {
    char *input = "   ls -l";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 2);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[1].value, "-l");
}

Test(tokenizer, spaces_trailing) {
    char *input = "ls -l   ";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 2);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[1].value, "-l");
}

Test(tokenizer, tabs) {
    char *input = "ls\t-l";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 2);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[1].value, "-l");
}

Test(tokenizer, simple_quotes) {
    char *input = "'ls'";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 1);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");
}

Test(tokenizer, simple_quotes_multiple_words) {
    char *input = "'ls' -l";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 2);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[1].value, "-l");
}

Test(tokenizer, unclosed_simple_quotes) {
    char *input = "'ls";
    token_list_t *tokens = tokenize(input);

    cr_assert_null(tokens);
}

Test(tokenizer, double_quotes) {
    char *input = "\"ls\"";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 1);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");
}

Test(tokenizer, double_quotes_multiple_words) {
    char *input = "\"ls\" -l";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 2);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[1].value, "-l");
}

Test(tokenizer, unclosed_double_quotes) {
    char *input = "\"ls";
    token_list_t *tokens = tokenize(input);

    cr_assert_null(tokens);
}

Test(tokenizer, pipe) {
    char *input = "ls | cat";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 3);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_PIPE);
    cr_assert_str_eq(tokens->tokens[1].value, "|");

    cr_assert_eq(tokens->tokens[2].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[2].value, "cat");
}

Test(tokenizer, double_pipe) {
    char *input = "ls || cat";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 3);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_OR);
    cr_assert_str_eq(tokens->tokens[1].value, "||");

    cr_assert_eq(tokens->tokens[2].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[2].value, "cat");
}

Test(tokenizer, double_ampersand) {
    char *input = "ls && ls";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 3);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_AND);
    cr_assert_str_eq(tokens->tokens[1].value, "&&");

    cr_assert_eq(tokens->tokens[2].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[2].value, "ls");
}

Test(tokenizer, pipe_no_space) {
    char *input = "ls|cat";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 3);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_PIPE);
    cr_assert_str_eq(tokens->tokens[1].value, "|");

    cr_assert_eq(tokens->tokens[2].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[2].value, "cat");
}

Test(tokenizer, semicolon) {
    char *input = "ls ; cat";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 3);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_SEMICOLON);
    cr_assert_str_eq(tokens->tokens[1].value, ";");

    cr_assert_eq(tokens->tokens[2].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[2].value, "cat");
}

Test(tokenizer, semicolon_no_space) {
    char *input = "ls;cat";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 3);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_SEMICOLON);
    cr_assert_str_eq(tokens->tokens[1].value, ";");

    cr_assert_eq(tokens->tokens[2].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[2].value, "cat");
}

Test(tokenizer, redirection_in) {
    char *input = "ls < file";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 3);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_REDIRECT_IN);
    cr_assert_str_eq(tokens->tokens[1].value, "<");

    cr_assert_eq(tokens->tokens[2].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[2].value, "file");
}

Test(tokenizer, redirect_no_space) {
    char *input = "ls<file";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 3);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_REDIRECT_IN);
    cr_assert_str_eq(tokens->tokens[1].value, "<");

    cr_assert_eq(tokens->tokens[2].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[2].value, "file");
}

Test(tokenizer, redirection_out) {
    char *input = "ls > file";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 3);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_REDIRECT_OUT);
    cr_assert_str_eq(tokens->tokens[1].value, ">");

    cr_assert_eq(tokens->tokens[2].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[2].value, "file");
}

Test(tokenizer, append_out) {
    char *input = "ls >> file";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 3);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_APPEND_OUT);
    cr_assert_str_eq(tokens->tokens[1].value, ">>");

    cr_assert_eq(tokens->tokens[2].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[2].value, "file");
}

Test(tokenizer, append_in) {
    char *input = "ls << file";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 3);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_APPEND_IN);
    cr_assert_str_eq(tokens->tokens[1].value, "<<");

    cr_assert_eq(tokens->tokens[2].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[2].value, "file");
}

Test(tokenizer, redirection_both) {
    char *input = "ls < file >>> file2";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 6);

    cr_assert_eq(tokens->tokens[0].type, TOK_COMMAND);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_REDIRECT_IN);
    cr_assert_str_eq(tokens->tokens[1].value, "<");

    cr_assert_eq(tokens->tokens[2].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[2].value, "file");

    cr_assert_eq(tokens->tokens[3].type, TOK_APPEND_OUT);
    cr_assert_str_eq(tokens->tokens[3].value, ">>");

    cr_assert_eq(tokens->tokens[4].type, TOK_REDIRECT_OUT);
    cr_assert_str_eq(tokens->tokens[4].value, ">");

    cr_assert_eq(tokens->tokens[5].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[5].value, "file2");
}
