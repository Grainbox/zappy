/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>


int forward(server_t *srv, client_t *cli, char **args)
{
    (void)args;
    if (cli->player->dir == UP)
        move_direction(srv, cli, 0, -1);
    if (cli->player->dir == DOWN)
        move_direction(srv, cli, 0, 1);
    if (cli->player->dir == LEFT)
        move_direction(srv, cli, -1, 0);
    if (cli->player->dir == RIGHT)
        move_direction(srv, cli, 1, 0);
    return dprintf(cli->fd, "ok\n");
}
