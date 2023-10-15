/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

int inventory(server_t *srv, client_t *cli, char **args)
{
    (void)srv;
    (void)args;
    return dprintf(cli->fd, "[ food %d, linemate %d, deraumere %d, sibur %d, \
mendiane %d, phiras %d, thystame %d ]\n", cli->player->inventory->food,
        cli->player->inventory->linemate, cli->player->inventory->deraumere,
        cli->player->inventory->sibur, cli->player->inventory->mendiane,
        cli->player->inventory->phiras, cli->player->inventory->thystame);
}
