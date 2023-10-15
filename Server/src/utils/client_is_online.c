/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

bool client_is_online(server_t *srv, client_t *cli_ptr)
{
    client_t *tmp = srv->clients;

    while (tmp) {
        if (tmp == cli_ptr)
            return (true);
        tmp = tmp->next;
    }
    return (false);
}
