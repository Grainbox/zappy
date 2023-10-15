/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

int right(server_t *srv, client_t *cli, char **args)
{
    (void)srv;
    (void)args;

    cli->player->dir = (cli->player->dir + 1) % 4;
    return dprintf(cli->fd, "ok\n");
}
