/*
** EPITECH PROJECT, 2023
** epitech-shell
** File description:
** Inhibitors
*/

#pragma once

#define ESCAPE_SEQUENCE_LIST "abtnvfr"

/**
 * @brief this function allows to get a string of character where backslash
 * are parsed like tcsh.
 *
 * @param input - the string that need to be parsed. this param will be
 * free within the function.
 * @return char* - the new string that is parsed
 */
char *parse_backslash (char *input);
