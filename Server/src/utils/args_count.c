/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

size_t args_count(char **args)
{
    size_t count = 0;
    while (args[count] != NULL) {
        count++;
    }
    return count;
}
