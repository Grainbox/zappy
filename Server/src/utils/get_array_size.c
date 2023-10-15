/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** get_array_size
*/

#include "server.h"

/**
 * @brief Returns the size of a char **
 * @param args The array calculated
*/
int get_array_size(char **args)
{
    int i = 0;

    for (; args[i] != NULL; i++);
    return i;
}
