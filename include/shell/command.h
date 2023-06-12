/*
** EPITECH PROJECT, 2023
** shell
** File description:
** command
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "shell/tokenizer.h"

/* Structures */

#define DEFAULT_ARGS_CAP 8
#define DEFAULT_GROUP_CAP 2
#define DEFAULT_EXEC_CAP 2

typedef enum {
    FD_NULL, ///< Unkown file descriptor (e.g. pipes not yet created)
    FD_INT,  ///< File descriptor (e.g. 0, 1, 2)
    FD_PIPE, ///< Pipe
    FD_FILE,  ///< File path (e.g. /dev/null)
    FD_APPEND, ///< Append to file path
} fd_type_t;

typedef struct {
    fd_type_t type;
    int fd;  ///< File descriptor (only for FD_INT)
    char *path; ///< Path to the file (only for FD_FILE)
} fd_t;

/**
 * @brief Flags for a command group.
 */
typedef enum {
    F_NULL, ///< No flags
    F_DOUBLE_PIPE, ///< Double pipe (||)
    F_DOUBLE_AMPERSAND, ///< Double ampersand (&&)
} group_flags_t;

/**
 * @brief List of arguments for a command.
 */
typedef struct {
    char **argv; ///< Arguments (NULL terminated)
    size_t size;
    size_t capacity;
} command_args_t;

/**
 * @brief Single command structure.
 */
typedef struct {
    char *path; ///< Path to the executable
    command_args_t args; ///< Arguments (args.argv[0] is the executable)
    bool builtin; ///< Whether the command is a builtin
    fd_t in; ///< Input file descriptor
    fd_t out; ///< Output file descriptor
} command_t;

/**
 * @brief Group of commands to be executed in parallel (with pipes)
 */
typedef struct {
    command_t *commands;
    size_t size;
    size_t capacity;
    group_flags_t flags;
} command_group_t;

/**
 * @brief List of command groups to be executed sequentially.
 */
typedef struct {
    command_group_t *groups;
    size_t size;
    size_t capacity;
} command_exec_t;

/* Parser */

typedef enum {
    CMD_RES_OK,
    CMD_RES_ERR,  ///< Other error (malloc, ...)
    CMD_RES_EMPTY,  ///< Empty command ("Invalid null command.")
    CMD_RES_REDIRECT_NAME, ///< "Missing name for redirect."
    CMD_RES_REDIRECT_AMBIGUOUS, ///< "Ambiguous input redirect."
} command_res_t;

/**
 * @brief Parse a command executor from the given tokens.
 *
 * @param tokens Tokens to parse.
 * @return command_exec_t* Command (NULL on error)
 */
command_exec_t *parse_command_exec(token_list_t *tokens);

/**
 * @brief Parse a single command from the given tokens.
 *
 * @param tokens Tokens to parse.
 * @param index Index of the first token to parse.
 * @param command Command to fill.
 * @return command_res_t Result of the operation.
 */
command_res_t command_parse(token_list_t *tokens, size_t *index,
    command_t *command);

/**
 * @brief Print command error to stderr.
 *
 * @param res Result of the command.
 */
void print_command_error(command_res_t res);

/**
 * @brief Parse a REDIRECT_IN token.
 *
 * @param tokens Tokens to parse.
 * @param index Index of the first token to parse.
 * @param command Command to fill.
 * @return command_res_t Result of the operation.
 */
command_res_t parse_redirect_in(token_list_t *tokens, size_t *index,
    command_t *command);

/**
 * @brief Parse a REDIRECT_OUT token.
 *
 * @param tokens Tokens to parse.
 * @param index Index of the first token to parse.
 * @param command Command to fill.
 * @return command_res_t Result of the operation.
 */
command_res_t parse_redirect_out(token_list_t *tokens, size_t *index,
    command_t *command);

/**
 * @brief Parse a APPEND_OUT token.
 *
 * @param tokens Tokens to parse.
 * @param index Index of the first token to parse.
 * @param command Command to fill.
 * @return command_res_t Result of the operation.
 */
command_res_t parse_append_out(token_list_t *tokens, size_t *index,
    command_t *command);

/**
 * @brief Parse a APPEND_IN token.
 *
 * @param tokens Tokens to parse.
 * @param index Index of the first token to parse.
 * @param command Command to fill.
 * @return command_res_t Result of the operation.
 */
command_res_t parse_append_in(token_list_t *tokens, size_t *index,
    command_t *command);

/* Data structures */

/**
 * @brief Allocate a new command executor.
 *
 * @return command_exec_t* New command executor.
 */
command_exec_t *command_exec_new(void);

/**
 * @brief Add a new command group to the command executor.
 *
 * @param exec Command executor.
 * @param flags Flags for the command group.
 * @return command_group_t* New command group.
 */
command_group_t *command_exec_add_group(command_exec_t *exec,
    group_flags_t flags);

/**
 * @brief Add a new command to the command group.
 *
 * @param group Command group.
 * @return command_t* New command.
 */
command_t *command_group_add_command(command_group_t *group);

/**
 * @brief Push a new argument to the command.
 *
 * @param command Command.
 * @param arg Argument to push.
 * @return int 0 on success, -1 on error.
 */
int command_push_arg(command_t *command, char *arg);

/**
 * @brief Free a command executor.
 *
 * @param exec Command executor.
 */
void command_exec_free(command_exec_t *exec);
