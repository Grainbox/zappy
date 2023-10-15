/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

void free_args(char **args)
{
    if (!args)
        return;
    for (size_t i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}
