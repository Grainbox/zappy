/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#pragma once

// Position on 2D map
typedef struct position_s {
    int x;
    int y;
} position_t;

// Split string by delimiter
char **split(char *str, char delim);

// Free args array
void free_args(char **args);

/**
 * @brief Return the positive value of a number or 0 if it's negative
 * @param x The number to be tested
 */
#define POS_OR_ZERO(x) (x < 0 ? 0 : x)
